//
// Created by hanifa on 4/28/20.
//

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <wait.h>
#include "LetterFrequency.h"
using namespace std;

/**
 * Computes the occurrences for each letter of the alphabet
 * in a given file
 * @param filename
 */
void LetterFrequency::central(std::string filename) {
    // Read the content of the file
    ifstream fileContent(filename);

    if (!fileContent) {
        cout << "Issue with reading the file" << endl;
        exit(5);
    }

    // Vector container to hold all characters from the given text file
    vector<char> characters;

    // Fill the vector with every character from the text file
    char c;
    while (fileContent >> c) {
        characters.push_back(c);
    }

    if (characters.empty()) {
        cout << "The file is empty; "
                "thus, statistics is 0 for all letters."
                << endl;
        exit(3);
    }

    // Close file
    fileContent.close();

    // Iteration to find the count for all letters of the alphabet
    // Using separate processes (via fork()) and
    // Using pipes to communicate between child and parent
    // Child computes the count and parent prints the result.
    int status;
    char letter = 'a';

    for (int i = 0; i < 26; i++) {
        // Create pipe
        int pipefds[2];
        pipe(pipefds);

        if (pipe(pipefds)==-1){
            fprintf(stderr, "Pipe to write value for Parent Failed");
            return;
        }

        // Start fork process
        pid_t pid;
        pid = fork();

        if (pid == 0) { // Child process executing
                int val = frequency(characters, letter);
                // Send the count for the ith letter of the alphabet to the parent
                close(pipefds[0]);
                write(pipefds[1], &val, sizeof(val));
                close(pipefds[1]);
                exit(2);
        }
        else if (pid > 0) { // Parent process is executing
            int value = 0;
            // Read the count for the ith letter of the alphabet from the child
            close(pipefds[1]);
            read(pipefds[0], &value, sizeof(value));
            close(pipefds[0]);
            cout << "[" << letter << "] = " << value << endl;

            waitpid(pid, &status, 0);
        }
        else {
            cout << "Error in attempt to fork this process" << endl;
        }
        letter++;
    }
}


/**
 * Calculates the total occurence for a given letter
 * @param content
 * @param letter
 * @return
 */
int LetterFrequency::frequency(std::vector<char> content, char letter) {
    int count = 0;
    vector<char>::const_iterator it ;
    for (it = content.begin(); it != content.end(); ++it) {
        char current = tolower(*it);
        if (current >= 'a' && current <= 'z' && current == letter) {
            count++;
        }
    }
    return count;
}