//
//  dictionary.h
//  dsa_assignment3
//
//  Created by Artur Shinkevich on 11-12-05.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <string.h>
#include <iostream>
using namespace std;

class Trie{
    Trie *node_[26];
    bool terminating_;
    char letter_;
public:
    Trie();
    Trie(char letter, bool terminating);
    void add(char* letter);
    bool search(char *word);
    ~Trie();
};


class Dictionary {
    Trie *tree_;
public:
    Dictionary();
    Dictionary(char** data, int size);
    void add(const char* newword); 
    bool lookUp(const char* word);
    ~Dictionary();
};
