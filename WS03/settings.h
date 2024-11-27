/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */


#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca{

class Settings {
public:
    short m_maxSummaryWidth{80};
    bool m_tableView{false};
    
    
    short getMaxSummaryWidth() const { return m_maxSummaryWidth; }
    bool isTableView() const { return m_tableView; }
};


extern Settings g_settings;
}

#endif /* SENECA_SETTINGS_H */

