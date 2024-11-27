/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */


#include "spellChecker.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>


namespace seneca{

SpellChecker::SpellChecker(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        throw "Bad file name!";
    }
    
    std::string line;
    int index = 0;
    while (getline(file, line) && index < 6) {
        std::istringstream ss(line);
        ss >> m_badWords[index] >> m_goodWords[index];
        index++;
    }
    
    if (index != 6) {
        throw "File does not contain exactly 6 word pairs!";
    }
}


void SpellChecker::operator()(std::string& text) {
    for (size_t i = 0; i < m_badWords.size(); ++i) {
        size_t pos = 0;
        while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
            text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
            m_replaceCount[i]++;
            pos += m_goodWords[i].length();
        }
    }
}


void SpellChecker::showStatistics(std::ostream& out) const {
    std::cout << "Spellchecker Statistics" << std::endl;
    for (size_t i = 0; i < m_badWords.size(); ++i) {
        std::cout << std::setw(15)  << m_badWords[i] << ": "
        << m_replaceCount[i] << " replacements" << std::endl;
    }
}
};
