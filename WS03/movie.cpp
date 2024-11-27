/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */


#include "movie.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>


namespace seneca
{
   
    Movie::Movie(const std::string& title, const std::string& summary, unsigned short year)
        : MediaItem(title, summary, year) { }

   
    void Movie::display(std::ostream& out) const {
        if (g_settings.isTableView()) {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << getYear() << " | ";
            out << std::left;

            if (g_settings.getMaxSummaryWidth() > -1) {
                if (static_cast<short>(getSummary().size()) <= g_settings.getMaxSummaryWidth()) {
                    out << getSummary();
                } else {
                    out << getSummary().substr(0, g_settings.getMaxSummaryWidth() - 3) << "...";
                }
            } else {
                out << getSummary();
            }
            out << std::endl;
        } else {
            size_t pos = 0;
            out << getTitle() << " [" << getYear() << "]\n";
            out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << '\n';

            while (pos < getSummary().size()) {
                out << "    " << getSummary().substr(pos, g_settings.getMaxSummaryWidth()) << '\n';
                pos += g_settings.getMaxSummaryWidth();
            }

            out << std::setw(getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    
    Movie* Movie::createItem(const std::string& strMovie) {
        if (strMovie.empty() || strMovie[0] == '#') {
            throw "Not a valid movie.";
        }

        std::istringstream stream(strMovie);
        std::string title, yearStr, summary;

      
        std::getline(stream, title, ',');
        std::getline(stream, yearStr, ',');
        std::getline(stream, summary);

        MediaItem::trim(title);
        MediaItem::trim(yearStr);
        MediaItem::trim(summary);

        unsigned short year = std::stoi(yearStr);

      
        return new Movie(title, summary, year);
    }
}

