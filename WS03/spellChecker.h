/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */


#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <array>
#include <iostream>

namespace seneca{

class SpellChecker {
private:
    std::array<std::string, 6> m_badWords;
    std::array<std::string, 6> m_goodWords;
    std::array<int, 6> m_replaceCount = {0};
    
public:
    SpellChecker(const char* filename);
    void operator()(std::string& text);

    void showStatistics(std::ostream& out) const;
};

}

#endif // SPELLCHECKER_H

