//
//  spellcheck.C
//  Created by Ramiz Hanan 820431970 on 1/26/20.
//  Copyright © 2020 RMB. All rights reserved.
//
#include <fstream>
#include <iostream>
#include "dictionary.h"

using namespace std;

const char *separators = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
void insertWords(std::string validWordFilePath, Dictionary dict);
void searchWords(std::string checkWordFilePath, Dictionary dict);
bool checkArgs(const char *argv[]);

int main(int argc, const char *argv[])
{
    Dictionary dict = Dictionary();
    std::string wordFilePath = argv[2];
    std::string checkFilePath = argv[1];

    if (checkArgs(argv))
    {
        insertWords(wordFilePath, dict);
        searchWords(checkFilePath, dict);
    }
    
    return 0;
}

bool checkArgs(const char *argv[])
{
    if (argv[1] == NULL || argv[2] == NULL)
    {
        if (argv[1] == NULL)
        {
            cerr << "Missing arg: Please enter absolute path of file to be checked" << endl;
            return false;
        }
        if (argv[2] == NULL)
        {
            cerr << "Missing arg: Please enter absolute path of dictionary word list" << endl;
            return false;
        }
    }
    return true;
}

void insertWords(std::string wordFilePath, Dictionary dict)
{
    //Read in valid word file
    std::ifstream wordFile(wordFilePath);
    
    if (wordFile.good())
    {
        for (std::string line; std::getline(wordFile, line);)    //each line contains a word
        {
            char *cString = new char[line.length() + 1];
            //convert from standard string to c string
            std::strcpy(cString, line.c_str());
            
            char *parsedWord = (char*)strtok(cString, separators);
            while (parsedWord != 0) //iterate through words
            {
                char toLowerCase;
                int i = 0;
                
                //convert to lower case before inserting
                while (parsedWord[i])
                {
                    toLowerCase = parsedWord[i];
                    parsedWord[i] = tolower(toLowerCase);
                    i++;
                }
                
                //populate dictionary tree
                dict.insert(dict.root, parsedWord, parsedWord);
                
                parsedWord = (char*)strtok(NULL, separators);
            }
            delete[] cString;
        }
        wordFile.close();
    }
}

void searchWords(std::string checkFilePath, Dictionary dict)
{
    
    //Read in file to be checked for spelling
    std::ifstream wordCheckFile(checkFilePath);
    
    if (wordCheckFile.good())
    {
        
        for (std::string line; std::getline(wordCheckFile, line);)
        {
            char *cString2 = new char[line.length() + 1];
            std::strcpy(cString2, line.c_str());
            
            // cstr now contains a c-string copy of str
            char *parsed = (char*)strtok(cString2, separators);
            while (parsed != 0 && parsed[0] != '\r')
            {
                char c = NULL;
                int i = 0;
                //retain original case word for printing out
                char *backup = new char[20];
                
                while (parsed[i])    //convert to lower case
                {
                    c = parsed[i];
                    backup[i] = c;
                    parsed[i] = tolower(c);
                    i++;
                }
                
                //perform search on each word and print misspelled
                if (dict.search(dict.root, parsed, parsed) == MISSPELLED){
                    int originalLength = 0;
                    while(parsed[originalLength]){ //Bux fix: one word had trailing space
                        cout << backup[originalLength];
                        originalLength++;
                    }
                    cout << endl;
                }
                
                backup = NULL;
                parsed = (char*)strtok(NULL, separators);
            }
            delete[] cString2;
        }
    }
    
    wordCheckFile.close();
    
}
