//
//  Ramiz Hanan 820431970
//  Created by RMB on 1/29/20.
//  Copyright © 2020 RMB. All rights reserved.
//
#include <stdio.h>
#include <string>
#include "dictionary.h"

using namespace std;

//Creates new entry node
Entry* newEntry()
{
    Entry *temp = new Entry();
    temp->isEndOfWord = false;
    for (int i = 0; i < Nchars; i++)
        temp->next[i] = NULL;
    
    return temp;
    
}

//initialize dictionary root node
Dictionary::Dictionary()
{
    root = newEntry();
}

//performs insertion if word does not exist and is of correct format
ResultType Dictionary::insert(Entry *root, const char *characters, const char *targetWord)
{
    if (correctFormat(characters))
    {
        if (recSearch(root, characters, targetWord))
            return EXISTS;
        else
        {
            if (recInsert(root, characters, targetWord))
                return ADDED;
        }
    }
    
    return BADCHARS;
}

//helper function for recursively inserting a word into dictionary
bool Dictionary::recInsert(Entry *root, const char *characters, const char *targetWord)
{
    
    if (characters[0] != '\0')
    {
        int childIndex = letterIndex(characters[0]);
        if (root->next[childIndex] == NULL)
        {
            //if the letter entry is not there, create new entry
            root->next[childIndex] = newEntry();
        }
        insert(root->next[childIndex], characters + sizeof(char), targetWord);
    }
    else
    {
        root->isEndOfWord = true;
    }
    return true;
}

//Performs search and returns if word exists or not
ResultType Dictionary::search(Entry *root, const char *characters, const char *targetWord)
{
    if (recSearch(root, characters, targetWord))
        return CORRECT;
    else
        return MISSPELLED;
}

//helper function to perform recursive search on word
bool Dictionary::recSearch(Entry *root, const char *chars, const char *targetWord)
{
    int index = letterIndex(chars[0]);
    
    if (!root)    //entry does not exist
        return false;
    
    if (chars[0] != '\0' && chars[1] == '\0')
    {
        // Condition of finding letter entries
        
        if (!root->next[index])    //if next character does not exist
            return false;
        
        if (root->next[index]->isEndOfWord)    // Reached last letter and it is marked as end of word
            return true;
        
        else
            return false;    //reached last letter and it is not marked end of word
    }
    
    return recSearch(root->next[index], chars + sizeof(char), targetWord);    //pass rest of word recursively
}

//returns index of letter
int Dictionary::letterIndex(char letter)
{
    if (letter == '\'') return 26;    //special case '
    
    else if (isalpha(letter))    //extra error checking
        return letter - 'a';    //gives letter position e.g. a = 0, z = 26
    
    return -1;
}

//error checking the format
bool Dictionary::correctFormat(const char *characters)
{
    int i = 0;
    int valid = 1;
    char letter;
    while (characters[i] != '\0')
    {
        letter = characters[i];
        if (!isalpha(letter) && letter != '\'')
            valid = 0;
        i++;
    }
    
    return valid;
}

// helper function to check if current entry is a leaf entry
bool Dictionary::isLeafEntry(Entry *root)
{
    return root->isEndOfWord != false;
}
