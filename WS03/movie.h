#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */


#include "mediaItem.h"
#include "settings.h"
#include <iostream>
#include <string>

namespace seneca
{
    class Movie : public MediaItem {
    private:
        
        Movie(const std::string& title, const std::string& summary, unsigned short year);

    public:
        void display(std::ostream& out) const override;

        static Movie* createItem(const std::string& strMovie);
    };
}

#endif /* MOVIE_H */

