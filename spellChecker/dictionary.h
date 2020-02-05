//
//  Ramiz Hanan 820431970
//  Created by RMB on 1/26/20.
//  Copyright © 2020 RMB. All rights reserved.
//
#ifndef DICTIONARY
#define DICTIONARY

#define Nchars 27 /* a-z + ' */

typedef enum {
    CORRECT, // word has correct spelling
    MISSPELLED,
    BADCHARS, // word has characters outside [A-Z,a-z,']
    ADDED,
    EXISTS,
} ResultType;

struct Entry{
    bool isEndOfWord;
    Entry *next[Nchars];
};

class Dictionary{
public:
    Entry* root;
    Dictionary();
    ResultType insert(Entry* root, const char* characters, const char* targetWord);
    ResultType search(Entry* root, const char* characters,const char* targetWord);
private:
    bool recSearch(Entry* root, const char* chars,const char* targetWord);
    bool recInsert(Entry* root, const char* characters, const char* targetWord);
    bool correctFormat(const char* characters);
    bool isLeafEntry(Entry* root);
    int letterIndex(char letter);
    
};

#endif
