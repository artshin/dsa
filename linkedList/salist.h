//
//  salist.h
//  doublyLinkedList
//
//  Created by Artur Shinkevich on 11-10-08.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
using namespace std;

template <class T> 
class Node{
public:
    T data_;
    Node *prev_;
    Node *next_;
    Node(){ next_ = prev_ = NULL; };
    Node(T x, Node *p = NULL, Node *n = NULL) { data_ = x; prev_ = p; next_ = n; }
    const Node<T>* next() const { return next_; };
    const Node<T>* prev() const { return prev_; };
    const T& data() const {return data_; }; 
    
};


template <class T>
class SAList
{
    friend class Node<T>;
    Node<T> *start_;
    Node<T> *curr_;
public:
    SAList ();
    SAList (const SAList<T>& source);
    SAList (T newdata[], int sz);
    SAList &operator=(const SAList<T>& x);
    ~SAList(); 
    void insert(const T &x);
    bool isEmpty() const;
    bool get(T passback[], int max) const;
    bool remove(const T& key, bool (*match)(const T&,const T&));
    Node<T>* search(const T& key,bool (*match)(const T&,const T&));
};


// Base case constructor
template <class T>
SAList<T>::SAList(){
    start_ = curr_ = NULL;
}

// Constructor that returns data in a linked list
template <class T>
SAList<T>::SAList(T newdata[],int sz):SAList(){
    for(int i = 0; i < sz; i++)
    {
        curr_->data_ = newdata[i];
        curr_ = curr_->next_;
    }
        
}

// Copy constructor
template <class T>
SAList<T>::SAList(const SAList<T>& source){
    *this = source;
}    

// Destructor, obviously ... 
template <class T>
SAList<T>::~SAList(){ }


template <class T>
void SAList<T>::insert(const T &x){
    
    Node<T>* temp = new Node<T>(x,NULL,start_);
    
    if(start_)
    {
        start_->prev_=temp;
        start_ = temp;
    }
    else
        start_ = curr_ = temp;
    
}

template <class T>
bool SAList<T>::isEmpty() const{
    return start_ == NULL ? true : false;
}

template <class T>
bool SAList<T>::get(T passback[], int max) const{
    bool result = false;
    Node<T>* temp = start_;
    
    if(temp)
    {
        for(int i = 0; i < max; i++)
        {
            passback[i] = temp->data_;
            if(temp->next())
                temp = temp->next_;
            if(!temp && i < max)
                result = true;
        }
    }
    return result;
    
}


// Search and remove functions are kind of the same
// in termns of adjusting linked list, so don't panic,
// I won't discuss the logic here. It WORKS!!! 
// NOTHING ELSE MATTERS!!!
template <class T>
Node<T>* SAList<T>::search(const T& key, bool (*match)(const T&,const T&)){
    Node<T>* temp = start_;
    Node<T>* resultNode = NULL;
    bool found = false; 
    int i = 0;
    
    while(temp && !found)
    {
        if(match(key,temp->data_))
        {
            
            resultNode = temp;
            if(temp != start_)
            {
                if(temp->next_)
                {
                    temp->prev_->next_ = temp->next_;
                    temp->next_->prev_ = temp->prev_;
                    temp->prev_ = NULL;
                    
                }
                else
                    temp->prev_->next_ = NULL;
                
                temp->next_ = start_;
                start_->prev_ = temp;
                start_ = temp;
            }
                
            found = true;
        }
        else{
            temp = temp->next_;
            i++;
        }
    }
    
    return resultNode;
    
}

template <class T>
bool SAList<T>::remove(const T& key, bool (*match)(const T&,const T&)){
    Node<T>* temp = start_;
    bool found = false;
    
    
    while(temp && !found)
    {
        if(match(key,temp->data_))
        {   
            if(temp != start_)
            {
                if(temp->next_)
                {
                    temp->prev_->next_ = temp->next_;
                    temp->next_->prev_ = temp->prev_;
                    temp->prev_ = NULL;
                }
                else
                    temp->prev_->next_ = NULL;
            }
            else
            {
                start_ = temp->next_;
                delete temp;
            }
            found = true;
        }
        else
            temp = temp->next_;
    }
    
    return found;
}


// Assignment operator, complete magic
// I decided not to change anything, 
// It works and makes me happy
template <class T>
SAList<T>& SAList<T>::operator=(const SAList<T>& source){
    if(this != &source)
    {
        start_ = curr_ = new Node<T>();
        Node<T>* temp = source.start_;
    
        start_->data_ = source.start_->data_;
        curr_ = start_;
    
        for (temp = source.start_->next_; temp; temp = temp->next_)
        {
        
            if(start_ == curr_)
            {
                start_->next_ = new Node<T>();
                start_->next_->prev_ = start_;
                start_->next_->data_ = temp->data_; 
                curr_ = start_->next_;
            }
            else
            {
                curr_->next_ = new Node<T>();
                curr_->next_->data_ = temp->data_;
                curr_->next_->prev_ = curr_;
                curr_ = curr_->next_;
            }
        
        }
    }
    return *this;
}


/*!!!!!!!!! OVER !!!!!!!!!! ITS OVER !!!!!!!!!! */


