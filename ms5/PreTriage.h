#ifndef SENECA_PRETRIAGE_H_
#define SENECA_PRETRIAGE_H_

#include "Patient.h"
#include "Utils.h"
#include "Time.h"
#include "Menu.h"

namespace seneca {
    const int maxNoOfPatients = 100;

    class PreTriage {
        char* m_dataFilename;
        Patient* m_lineup[maxNoOfPatients]={};
        int m_lineupSize = 0;
        Time m_averWaitTest;
        Time m_averWaitConta;

        Time getWaitTime(const Patient& p) const;
        void setAverageWaitTime(const Patient& p);
        int indexOfFirstInLine(char type) const;
        void load();
        void save();
        void reg();
        void admit();
        void lineup() const;

    public:
        PreTriage(const char* dataFilename);
        ~PreTriage();
        void run();
    };
}

#endif // SENECA_PRETRIAGE_H_

