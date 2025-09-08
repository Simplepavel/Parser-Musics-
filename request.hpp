#include <fstream>
#include <iostream>
#include <curl/curl.h>

size_t write_data(char *data, size_t size_chunk, size_t count_chunk, std::ofstream *buffer);
bool post(std::ofstream &result, const std::string &url, std::string &fields);
bool get(std::ofstream &result, const std::string &url);