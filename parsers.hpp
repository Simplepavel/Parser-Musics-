#include <set>
#include <string>
#include <fstream>
#include <vector>
#include <gumbo.h>
#include <iostream>
#include "song.hpp"
#include <thread>
#include <chrono>
class Find
{
protected:
    std::string file_to_string(std::ifstream &file);
};

class Find_Artists : public Find // поиск и парсинг артистов
{
    std::set<std::string> result;
    void find(GumboNode *node, std::set<std::string> &argv2);

public:
    std::set<std::string> &parse(std::ifstream &file);
};

class Find_Tracks : public Find
{
    std::vector<Song> result;
    void find(GumboNode *node, std::vector<Song> &argv2);
    void find_title_artist(GumboElement*, Song&);
    void find_url_download(GumboElement*, Song&);

public:
    std::vector<Song> &parse(std::ifstream &file); // передаем html-файл c треками
};


