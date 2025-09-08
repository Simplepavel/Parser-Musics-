#include "request.hpp"

size_t write_data(char *data, size_t size_chunk, size_t count_chunk, std::ofstream *buffer)
{
    if (buffer)
    {
        buffer->write(data, size_chunk * count_chunk);
        return size_chunk * count_chunk;
    }
    return 0;
}

bool post(std::ofstream &result, const std::string &url, std::string &fields)
{
    CURL *connection = curl_easy_init();
    curl_easy_setopt(connection, CURLOPT_POST, 1);
    curl_easy_setopt(connection, CURLOPT_POSTFIELDS, fields.c_str());
    curl_easy_setopt(connection, CURLOPT_URL, url.c_str());


    curl_easy_setopt(connection, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(connection, CURLOPT_WRITEFUNCTION, write_data);

    curl_easy_setopt(connection, CURLOPT_FOLLOWLOCATION, 1);
    CURLcode response = curl_easy_perform(connection);
    curl_easy_cleanup(connection);
    bool flag = (response == CURLE_OK);
    if (!flag)
    {
        std::cout << curl_easy_strerror(response) << '\n';
    }
    return flag;
}

bool get(std::ofstream &result, const std::string &url) // делает запроѝ на ѝайт и запиѝывает его ответ в result параметр
{
    CURL *connection = curl_easy_init();
    curl_easy_setopt(connection, CURLOPT_URL, url.c_str());
    curl_easy_setopt(connection, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(connection, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(connection, CURLOPT_FOLLOWLOCATION, 1);
    CURLcode response = curl_easy_perform(connection);
    curl_easy_cleanup(connection);
    bool flag = (response == CURLE_OK);
    if (!flag)
    {
        std::cout << curl_easy_strerror(response) << '\n';
    }
    return flag;
}
