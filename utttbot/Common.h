#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

#ifndef COMMON_H
#define COMMON_H

inline vector<string> split_with_delim(const string& s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

#endif