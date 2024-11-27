#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "Utils.h"
#include "TriagePatient.h"
#include "TestPatient.h"
#include "PreTriage.h"
#include "Menu.h"

using namespace std;

namespace seneca {
PreTriage::PreTriage(const char* file) {
        if (file != nullptr) {
            m_dataFilename = new char[strlen(file) + 1];
            strcpy(m_dataFilename, file);
        }
        else {
            m_dataFilename = nullptr;
        }

        m_averWaitTest = 15;
        m_averWaitConta = 5;

        m_lineupSize = 0;

        load();
    }

    PreTriage::~PreTriage() {

        for (int i = 0; i < m_lineupSize; i++) {
            delete m_lineupSize[i];
            m_lineupSize[i] ;
        }
        delete m_dataFilename;
    }

void PreTriage::load() {
    cout << "Loading data..." << endl;
    
    
    ifstream file(m_dataFilename);
    if (!file.is_open()) {
        cout << "No data or bad data file!\n" << endl;
        return;
    }
    
    file >> m_averWaitConta;
    file.ignore(1000, ',');
    file >> m_averWaitTest;
    file.ignore(1000, '\n');
    
    m_lineupSize = 0;
    
    while (m_lineupSize < maxNoOfPatients && !file.eof()) {
        Patient* newPatient = nullptr;
        
        char type{};
        file >> type;
        file.ignore(1000, ',');
        
        if (type == 'C') {
            newPatient = new TestPatient();
        }
        else if (type == 'T') {
            newPatient = new TriagePatient();
        }
        else {
            break;
        }
        if (newPatient) {
            if (newPatient->read(file)) {
                m_lineup[m_lineupSize++] = newPatient;
            }
            else {
                delete newPatient;
            }
        }
    };
    
    if (!file.eof()) {
        cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
        if (m_lineupSize == maxNoOfPatients) {
            cout << m_lineupSize << " Records imported...\n\n";
        }
    }
    else if (m_lineupSize == 0) {
        cout << "No data or bad data file!\n\n";
    }
    else {
        cout << m_lineupSize << " Records imported...\n\n";
    }
    file.close();
    
}


void PreTriage::save() {
    ofstream file(m_dataFilename);
    
    if (!file.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }
    
    int contagionCount = 0, triageCount = 0;
    cout << "Saving lineup..." << endl;
    file << m_averWaitConta << "," << m_averWaitTest << "\n";
    
    for (int i = 0; i < m_lineupSize; i++) {
        (m_lineup[i])->write(file) << "\n";
        if (m_lineup[i]->type() == 'C') {
            contagionCount++;
        }
        else if (m_lineup[i]->type() == 'T') {
            triageCount++;
        }
    }
    
    cout << contagionCount
    << " Contagion Tests and "
    << triageCount
    << " Triage records were saved!"
    << endl;
    
    file.close();
}

void PreTriage::run() {
    int selection;
    while (true) {
        cout << "General Healthcare Facility Pre-Triage Application\n"
        << "1- Register\n"
        << "2- Admit\n"
        << "3- View Lineup\n"
        << "0- Exit\n> ";
        cin >> selection;
        
        switch (selection) {
            case 1:
                reg();
                break;
            case 2:
                admit();
                break;
            case 3:
                lineup();
                break;
            case 0:
                return; // ループを抜ける
            default:
                cout << "Invalid selection, try again." << endl;
        }
    }
}

void PreTriage::reg() {
    if (m_lineupSize >= maxNoOfPatients) {
        cout << "Line up full!\n";
        return;
    }
    
    Menu menu("Select Type of Registration:\n1- Contagion Test\n2- Triage\n", 1);
    int selection;
    menu >> selection;
    
    cin.ignore(1000, '\n');
    
    if (selection == 1) {
        m_lineup[m_lineupSize] = new TestPatient();
    }else if (selection == 2) {
        m_lineup[m_lineupSize] = new TriagePatient();
    }else if (selection == 0) {
        return;
    }else {
        cout << "Invalid selection!" << endl;
        return;
    }
    
    m_lineup[m_lineupSize]->setArrivalTime();
    cout << "Please enter patient information: " << endl;
    cin >> *m_lineup[m_lineupSize];
    cout << endl;
    
    cout << "******************************************" << endl;
    cout << *m_lineup[m_lineupSize];
    cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << endl;
    cout << "******************************************" << endl;
    cout << endl;
    
    m_lineupSize++;
}

void PreTriage::admit() {
    Menu menu("Select Type of Admittance:\n1- Contagion Test\n2- Triage\n", 1);
    int selection;
    menu >> selection;
    if (selection == 0) {
        return;
    }
    char type = (selection == 1) ? 'C' : 'T';
    
    int index = indexOfFirstInLine(type);
    if (index == -1) {
        cout << "Lineup is empty!" << endl;
        return;
    }
    
    cout << "\n******************************************\n";
    cout << "Call time: [";
    Time time;
    cout << time.reset();
    cout << "]" << endl;
    cout << "Calling at for " << *m_lineup[index];
    cout << "******************************************\n\n";
    
    // 患者を呼び出した後、待機列から削除する
    delete m_lineup[index];
    for (int i = index; i < m_lineupSize - 1; ++i) {
        m_lineup[i] = m_lineup[i + 1];
    }
    --m_lineupSize;
    
    setAverageWaitTime(*m_lineup[index]); // 削除後の次の患者を対象に平均待ち時間を更新する
}


int PreTriage::indexOfFirstInLine(char type) const {
    for (int i = 0; i < m_lineupSize; i++) {
        if (m_lineup[i]->type() == type) {
            return i;
        }
    }
    return -1;
}

Time PreTriage::getWaitTime(const Patient& p) const {
    char Type = p.type(); // patient -> p に修正
    int waitTime = (Type == 'C') ? m_averWaitConta : m_averWaitTest; // patient -> p に修正
    int patientCount = 0;
    
    for (int i = 0; i < m_lineupSize; i++) {
        if (m_lineup[i]->type() == Type) {
            patientCount++;
        }
    }
    
    return waitTime * patientCount;
}

void PreTriage::setAverageWaitTime(const Patient& p) {
    int CT = U.getTime();
    Time PTT = p.time();
    int PTN = p.number();
    
    if (p.type() == 'C') {
        m_averWaitConta = ((CT - PTT) + (m_averWaitConta * (PTN - 1))) / PTN;
    }else if (p.type() == 'T') {
        m_averWaitTest = ((CT - PTT) + (m_averWaitTest * (PTN - 1))) / PTN;
    }
}

void PreTriage::lineup()const{
    Menu menu("Select The Lineup:\n1- Contagion Test\n2- Triage\n", 1);
    int selection;
    menu >> selection;
    if (selection == 0) {
        return;
    }

    char type = (selection == 1) ? 'C' : 'T';
    cout << "Row - Patient name                                          OHIP     Tk #  Time\n";
    cout << "-------------------------------------------------------------------------------" << std::endl;
    int count = 0;
    for (int i = 0; i < m_lineupSize; i++) {
        if (m_lineup[i]->type() == type) {
            clog.setf(ios::left);
            clog.fill(' ');
            clog.width(4);
            clog << count + 1;
            clog << "- ";
            clog.unsetf(ios::left);

            clog << (*m_lineup[i]) << endl;
            count++;
        }
    }
    if (count == 0) {
        cout << "Line up is empty!" << endl;
    }
    std::cout << "-------------------------------------------------------------------------------\n" ;
}
}

