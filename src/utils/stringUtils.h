//
// Created by dangerous on 21/10/18.
//
#include <locale>
#include <iostream>
#include <algorithm>
#include <regex>

#ifndef NETFLIX_LSS_STRINGUTILS_H
#define NETFLIX_LSS_STRINGUTILS_H

size_t findCaseInsensitive(std::string data, std::string toSearch, size_t pos = 0);

bool findByRegex(std::string regex, std::string toSearch);

#endif //NETFLIX_LSS_STRINGUTILS_H;