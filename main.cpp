#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <locale.h>
#include "request.hpp"
#include "parsers.hpp"
#include "windows.h"




int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::string url1 = "https://rus.hitmotop.com/artists/start/";
    std::string url2 = "https://rus.hitmotop.com/artist/";

    std::ofstream artists_pagew; // сюда загружаем страницу со всеми музыкантами
    std::ifstream artists_pager; // отсюда читаем страницу со всеми музыкантами

    std::ofstream tracks_pagew;
    std::ifstream tracks_pager;

    std::set<std::string> id_artists;

    Find_Artists prs1;
    Find_Tracks prs2;
    std::set<std::string> artist_ids;
    int counter = 0;
    for (int i = 0; i <= 1008; i += 48)
    {
        artists_pagew.open("artists_page");
        get(artists_pagew, url1 + std::to_string(i));
        artists_pagew.close();

        artists_pager.open("artists_page");
        artist_ids = std::move(prs1.parse(artists_pager));
        artists_pager.close();
        for (auto j = artist_ids.begin(); j != artist_ids.end(); ++j)
        {
            std::string url = url2 + *j;
            std::cout << url << '\n';
            tracks_pagew.open("musics_page");
            get(tracks_pagew, url);
            tracks_pagew.close();

            tracks_pager.open("musics_page");
            std::vector<Song> song_objects = std::move(prs2.parse(tracks_pager));
            tracks_pager.close();
            for (auto k = song_objects.begin(); k != song_objects.end(); ++k)
            {
                k->download();
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        counter += 48;
        break;
    }
    return 0;
}