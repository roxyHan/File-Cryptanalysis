//
// Created by hanifa on 4/28/20.
//
#include <vector>
#include "string"

#ifndef LAB2_LETTERFREQUENCY_H
#define LAB2_LETTERFREQUENCY_H



class LetterFrequency {

public:

    void statistics(std::vector<char>);
    void central(std::string);
    int frequency(std::vector<char>, char);
    void printStats(int[]);
};


#endif //LAB2_LETTERFREQUENCY_H
