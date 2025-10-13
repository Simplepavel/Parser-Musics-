#include "Song.hpp"
#include "request.hpp"

Song::Song() {};


std::ostream &operator<<(std::ostream &argv1, Song &argv2)
{
    argv1 << "Artist: " << argv2.artist_title << ' ';
    argv1 << "Track: " << argv2.title << ' ';
    argv1 << "Url: " << argv2.download_url;
    return argv1;
}

void remove_space(std::string &value)
{
    while (value[0] == '\n' || value[0] == ' ')
    {
        value.erase(0, 1);
    }
    int end = value.size() - 1;
    if (end < 0)
    {
        return;
    }
    while (value[end] == '\n' || value[end] == ' ')
    {
        value.erase(end, 1);
        --end;
    }
}

bool Song::download()
{
    std::ofstream file(directory + "\\" + artist_title + "~" + title + ".mp3", std::ios::binary); // файл сам закроется
    return get(file, download_url);
}