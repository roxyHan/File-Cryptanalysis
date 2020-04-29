//
// Created by hanifa on 4/28/20.
//

#include <iostream>
#include <fstream>
#include "LetterFrequency.h"
using namespace std;


void LetterFrequency::central(std::string filename) {
    // Read the content of the file
    ifstream fileContent(filename);

    if (!fileContent) {
        cout << "Issue with reading the file" << endl;
    }

    // Vector container to hold all characters from the given text file
    vector<char> characters;
    int freqencies[26];

    // Fill the vector with every character from the text file
    char c;
    while (fileContent >> c) {
        characters.push_back(c);
    }

    // Close file
    fileContent.close();

    char letter;

    // Iterate over the vector to increase the count for that character
    vector<char>::const_iterator it ;
    for (it = characters.begin(); it != characters.end(); ++it) {
        letter = *it;
        frequency(characters, letter);
        //freqencies[letter -'a'];
    }
    int count = frequency(characters, letter);
    cout << "Total count for the letter '" << letter << "' is: " << count << endl;
}



int LetterFrequency::frequency(std::vector<char> content, char letter) {
    int count = 0;
    vector<char>::const_iterator it ;
    for (it = content.begin(); it != content.end(); ++it) {
        char current = *it;
        if (current == letter || tolower(current) == letter) {
            count++;
        }
    }
    return count;
}




void LetterFrequency::printStats(int * characters) {

}