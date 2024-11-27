/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */



#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "book.h"
#include "settings.h"


namespace seneca {

    Book::Book(const std::string& author, const std::string& title, const std::string& country,
               double price, unsigned short year, const std::string& summary)
        : MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {}


    void Book::display(std::ostream& out) const {
        if (g_settings.m_tableView) {
            out << "B | ";
            out << std::left << std::setfill('.') << std::setw(50) << getTitle() << " | ";
            out << std::right << std::setfill(' ') << std::setw(2) << m_country << " | ";
            out << std::setw(4) << getYear() << " | " << std::left;

            if (g_settings.m_maxSummaryWidth > -1) {
                if (static_cast<short>(getSummary().size()) <= g_settings.m_maxSummaryWidth) {
                    out << getSummary();
                } else {
                    out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
                }
            } else {
                out << getSummary();
            }
            out << std::endl;
        } else {
            size_t pos = 0;
            out << getTitle() << " [" << getYear() << "] [" << m_author << "] ["
                << m_country << "] [" << m_price << "]\n";
            out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < getSummary().size()) {
                out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }


Book* Book::createItem(const std::string& strBook) {
        if (strBook.empty() || strBook[0] == '#') {
            throw "Not a valid book.";
        }

        std::istringstream stream(strBook);
        std::string author, title, country, priceStr, yearStr, summary;

        
        if (!std::getline(stream, author, ',') ||
            !std::getline(stream, title, ',') ||
            !std::getline(stream, country, ',') ||
            !std::getline(stream, priceStr, ',') ||
            !std::getline(stream, yearStr, ',') ||
            !std::getline(stream, summary)) {
            throw std::invalid_argument("Not a valid book.");
        }

    
        MediaItem::trim(author);
        MediaItem::trim(title);
        MediaItem::trim(country);
        MediaItem::trim(priceStr);
        MediaItem::trim(yearStr);
        MediaItem::trim(summary);

    
        double price = std::stod(priceStr);
        unsigned short year = static_cast<unsigned short>(std::stoi(yearStr));


        return new Book(author, title, country, price, year, summary);
    }
}

