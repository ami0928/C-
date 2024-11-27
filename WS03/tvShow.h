/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */


#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include "settings.h"
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

namespace seneca {

class TvShow : public MediaItem {
public:
    struct TvEpisode {
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };
    
private:
    std::string m_id;
    std::vector<TvEpisode> m_episodes;
    

    TvShow(const std::string& id, const std::string& title, const std::string& summary, unsigned short year);
    static unsigned int parseTimeToSeconds(const std::string& lengthStr) {
          int hours = 0, minutes = 0, seconds = 0;
          char delimiter;
          std::istringstream stream(lengthStr);
          
          stream >> hours >> delimiter >> minutes >> delimiter >> seconds;
          return (hours * 3600) + (minutes * 60) + seconds;
      }
    
public:
    void display(std::ostream& out) const override;
    static TvShow* createItem(const std::string& strShow);
    template <typename Collection_t>
    static void addEpisode(Collection_t& col, const std::string& strEpisode);
    double getEpisodeAverageLength() const;
    std::list<std::string> getLongEpisodes() const;
    std::string getId() const {return m_id;}
};

template <typename Collection_t>
void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode) {
    
    if (strEpisode.empty() || strEpisode[0] == '#') {
        throw "Not a valid episode.";
    }

    std::istringstream stream(strEpisode);
    std::string id, numberOverallStr, seasonStr, numberInSeasonStr, airDate, lengthStr, title, summary;

    std::getline(stream, id, ',');
    std::getline(stream, numberOverallStr, ',');
    std::getline(stream, seasonStr, ',');
    std::getline(stream, numberInSeasonStr, ',');
    std::getline(stream, airDate, ',');
    std::getline(stream, lengthStr, ',');
    std::getline(stream, title, ',');
    std::getline(stream, summary);


    MediaItem::trim(id);
    MediaItem::trim(numberOverallStr);
    MediaItem::trim(seasonStr);
    MediaItem::trim(numberInSeasonStr);
    MediaItem::trim(airDate);
    MediaItem::trim(lengthStr);
    MediaItem::trim(title);
    MediaItem::trim(summary);

    unsigned short numberOverall = std::stoi(numberOverallStr);
    unsigned short season = seasonStr.empty() ? 1 : std::stoi(seasonStr);
    unsigned short numberInSeason = std::stoi(numberInSeasonStr);
    
    unsigned int length = parseTimeToSeconds(lengthStr);
    


    TvEpisode episode{ nullptr, numberOverall, season, numberInSeason, airDate, length, title, summary };


        for (size_t i = 0; i < col.size(); ++i) {
           
            TvShow* tvShowPtr = dynamic_cast<TvShow*>(col[i]);

            if (tvShowPtr && tvShowPtr->getId() == id) {
                episode.m_show = tvShowPtr;
                tvShowPtr->m_episodes.push_back(episode);
                return;
        }
    }
}

}

#endif /* TVSHOW_H */

