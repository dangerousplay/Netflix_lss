//
// Created by aluno on 24/10/18.
//

#include "stringUtils.h"

size_t findCaseInsensitive(std::string data, std::string toSearch, size_t pos){
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

bool contains(std::string first, const std::string &second){
    return findByRegex(std::move(first), second);
}

