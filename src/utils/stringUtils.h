//
// Created by dangerous on 21/10/18.
//
#include <locale>
#include <iostream>
#include <algorithm>

#ifndef NETFLIX_LSS_STRINGUTILS_H
#define NETFLIX_LSS_STRINGUTILS_H

template<typename charT>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
int ci_find_substr( const T& str1, const T& str2, const std::locale& loc)
{
    typename T::const_iterator it = std::search( str1.begin(), str1.end(),
                                                 str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
    if ( it != str1.end() ) return it - str1.begin();
    else return -1; // not found
}

#endif //NETFLIX_LSS_STRINGUTILS_H;