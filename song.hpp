#include <string>
#include <iostream>
#include <algorithm>
struct Song
{
    std::string title;
    std::string artist_title;
    std::string download_url;
    const std::string directory = "Track";
    Song();
    bool download();
};

std::ostream &operator<<(std::ostream &argv1, Song &argv2);
void remove_space(std::string &value);