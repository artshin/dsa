//
//  dictionary.cpp
//  dsa_assignment3
//
//  Created by Artur Shinkevich on 11-12-05.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "dictionary.h"

/***************************
 |   Trie class functions  |
 ***************************/

Trie::Trie(){
    // Trie default constructor
    
    terminating_ = false;
    letter_ = NULL;
    memset (node_,'\0',sizeof(node_));
}

Trie::Trie(char letter, bool terminating){
    // Trie custom constructor
    
    terminating_ = terminating;
    letter_ = letter;
    memset (node_,'\0',sizeof(node_));
}

void Trie::add(char* word){
    
    
    if(word[0] < 97)
        word[0] = tolower(word[0]);
    
    int position = word[0] - 97;

    if(!node_[position])
        node_[position] = new Trie(word[0],false);
    if(word[1]) // if word is not over
        node_[position]->add(word+1);
    else 
        node_[position]->terminating_ = true;
 
}

bool Trie::search(char *word){
    bool result = false;
    
    if(word[0] < 97)
        word[0] = tolower(word[0]);
    
    int position = word[0] - 97; 
    
    if(node_[position]){
        if(node_[position]->letter_ == word[0]){ // if letter exists
            if(word[1]) // check if word is over
                result = node_[position]->search(word+1); // go to children
            else
                result = node_[position]->terminating_; // assign terminating flag
        }
    }
    
    return result;
}

Trie::~Trie(){
    // Trie deconstructor

    terminating_ = false;
    letter_ = NULL;
    delete [] node_[26];
}


/***************************
|Dictionary class functions|
***************************/

Dictionary::Dictionary(){
    // Dictionary default constructor
}

Dictionary::Dictionary(char** data, int size){
    // Dictionary custom constructor
    
    tree_ = new Trie();
        
    for(int i = 0; i < size; i++)
        tree_->add(data[i]); 
}

void Dictionary::add(const char *newword){
    char temp[strlen(newword)+1];
    strcpy(temp, newword);
    temp[strlen(newword)+1] = '\0';

    tree_->add(temp);
}

bool Dictionary::lookUp(const char *word){
    char temp[strlen(word)+1];
    strcpy(temp, word);
    temp[strlen(word)+1] = '\0';
    
    return tree_->search(temp);
}

Dictionary::~Dictionary(){
    // Dictionary deconstructor
}
