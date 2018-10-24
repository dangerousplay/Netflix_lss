//
// Created by dangerous on 21/10/18.
//
#include <locale>
#include <iostream>
#include <algorithm>
#include <regex>

#ifndef NETFLIX_LSS_STRINGUTILS_H
#define NETFLIX_LSS_STRINGUTILS_H

size_t findCaseInsensitive(std::string data, std::string toSearch, size_t pos = 0)
{
    // Convert complete given String to lower case
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    // Convert complete given Sub String to lower case
    std::transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
    // Find sub string in given string
    return data.find(toSearch, pos);
}

bool findByRegex(std::string regex, std::string toSearch){

    std::regex specialChars { R"([-[\]{}()*+?.,\^$|#\s])" };

    std::string sanitized = std::regex_replace(regex, specialChars, R"(\$&)" );

    std::regex self_regex(sanitized,
                          std::regex_constants::ECMAScript | std::regex_constants::icase);

    return std::regex_search(toSearch, self_regex);
}
#endif //NETFLIX_LSS_STRINGUTILS_H;