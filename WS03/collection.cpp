/*
 
 Ami Yamada
 159621226
 ayamada4@myseneca.ca
 Nov.14th/2024
 
 */


#include "collection.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>


namespace seneca
{

    Collection::Collection(const std::string& name) : m_name(name) {}

    Collection::~Collection()
    {
        for (auto& item : m_items)
        {
            delete item;
        }
    }


    const std::string& Collection::name() const
    {
        return m_name;
    }


    size_t Collection::size() const
    {
        return m_items.size();
    }

    
    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&))
    {
        m_observer = observer;
    }

    
    Collection& Collection::operator+=(MediaItem* item)
    {
       
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [&item](MediaItem* i) { return i->getTitle() == item->getTitle(); });

        if (it != m_items.end()) {
       
            delete item;
        } else {
            m_items.push_back(item);

            if (m_observer)
                m_observer(*this, *item);
        }

        return *this;
    }

   
    MediaItem* Collection::operator[](size_t idx) const
    {
        if (idx >= m_items.size()) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_items.size()) + "] items.");
        }
        return m_items[idx];
    }


    MediaItem* Collection::operator[](const std::string& title) const
    {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [&title](MediaItem* item) { return item->getTitle() == title; });

        return it != m_items.end() ? *it : nullptr;
    }


void Collection::removeQuotes()
{
    std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item) {
  
        std::string title = item->getTitle();
        std::string summary = item->getSummary();


        if (!title.empty() && title.front() == '\"')
        {
            title.erase(0, 1);
        }
        if (!title.empty() && title.back() == '\"')
        {
            title.erase(title.size() - 1, 1);
        }
        item->setTitle(title);

 
        if (!summary.empty() && summary.front() == '\"')
        {
            summary.erase(0, 1);
        }
        if (!summary.empty() && summary.back() == '\"')
        {
            summary.erase(summary.size() - 1, 1);
        }
        item->setSummary(summary);
    });
}

//void Collection::removeQuotes()
//{
//    std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item) {
//
//        std::string title = item->getTitle();
//        std::string summary = item->getSummary();
//
//
//        if (!title.empty() && title.front() == '\"' && title.back() == '\"')
//        {
//            title = title.substr(1, title.size() - 2);  // substrの結果をtitleに代入
//            item->setTitle(title);  // setTitleを使って元のオブジェクトにセット
//        }
//
//
//        if (!summary.empty() && summary.front() == '\"' && summary.back() == '\"')
//        {
//            summary = summary.substr(1, summary.size() - 2);  //
//            item->setSummary(summary);  // setSummaryを使って元のオブジェクトにセット
//        }
//    });
//}




 
    void Collection::sort(const std::string& field)
    {
        if (field == "title")
        {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
                return a->getTitle() < b->getTitle();
            });
        }
        else if (field == "year")
        {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
                return a->getYear() < b->getYear();
            });
        }
        else
        {
            throw std::invalid_argument("Unsupported field for sorting");
        }
    }

   
    std::ostream& operator<<(std::ostream& out, const Collection& collection)
    {
        for (const auto& item : collection.m_items)
        {
            out << *item; 
        }
        return out;
    }
}

