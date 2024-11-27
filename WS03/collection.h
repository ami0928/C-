/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */


#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <vector>
#include <functional>
#include "mediaItem.h"


namespace seneca
{
    class Collection
    {
    private:
        std::string m_name;
        std::vector<MediaItem*> m_items;
        void (*m_observer)(const Collection&, const MediaItem&) = nullptr;  
    public:
        Collection(const std::string& name);
        ~Collection();

        // コピー・ムーブ操作を禁止
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(Collection&&) = delete;


        const std::string& name() const;

        size_t size() const;
        void setObserver(void (*observer)(const Collection&, const MediaItem&));
        Collection& operator+=(MediaItem* item);
        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;
        void removeQuotes();

        void sort(const std::string& field);
        friend std::ostream& operator<<(std::ostream& out, const Collection& collection);
    };
}

#endif // SENECA_COLLECTION_H

