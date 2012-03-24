//
//  table.h
//  dsa_assignment2
//
//  Created by Artur Shinkevich on 11-10-27.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include <iostream>
#include <string.h>
using namespace std;

// 
//  Class declarations ahead
//

template <class TYPE>
class Table{
    
public:
    virtual bool remove(const char* key) = 0;
    virtual bool find(const char* key, TYPE& holder) = 0;
    virtual bool insert(const TYPE& data) = 0;
    virtual bool modify(const TYPE& data) = 0;
    virtual int size() const = 0;
};

template <class TYPE>
class Simple : public Table<TYPE>{
    TYPE* data_;
    int count_of_records_;
    int maximum_cap_;
    void grow();
    int binary_insert_search(TYPE *array, const TYPE &data, int low, int high);
    int binary_search(TYPE *array, const char *key, int low, int high);
    
public:
    Simple();
    bool remove(const char* key);
    bool find(const char* key, TYPE& holder);
    bool insert(const TYPE& data);
    bool modify(const TYPE& data);
    int size() const;
    ~Simple();
};

template <class TYPE>
class LPHash : public Table<TYPE>{
    TYPE* data_;
    int count_of_records_;
    int maximum_cap_;
    int search(const char* key);
    void grow();
    int isbetween(int rm, int proper, int next); //Catherines Leung code 
public:
    LPHash();
    LPHash(int maxExpected);
    bool remove(const char* key);
    bool find(const char* key, TYPE& holder);
    bool insert(const TYPE& data);
    bool modify(const TYPE& data);
    int size() const;
    ~LPHash();
};


// Next three classes are needed for ChainHash Class

template <class TYPE> 
class Node{
public:
    TYPE data_;
    Node *prev_;
    Node *next_;
    Node(){ next_ = prev_ = NULL; };
    Node(TYPE x, Node *p = NULL, Node *n = NULL) { data_ = x; prev_ = p; next_ = n; }
    const TYPE& data() const {return data_; }; 
};


template <class TYPE>
class SAList
{
    friend class Node<TYPE>;
    Node<TYPE> *start_;
    Node<TYPE> *curr_;
public:
    SAList ();
    SAList (const SAList<TYPE>& source);
    SAList (TYPE newdata[], int sz);
    SAList &operator=(const SAList<TYPE>& x);
    ~SAList(); 
    void insert(const TYPE &x);
    bool isEmpty() const;
    bool get(TYPE passback[], int max) const;
    bool remove(const TYPE& key);
    bool modify(const TYPE &x);
    Node<TYPE>* search(const char *key);
};

template <class TYPE>
class ChainHash  : public Table<TYPE>{
    SAList<TYPE> *data_; //not sure if I need this
    int maximum_cap_;
    int count_of_records_;
public:
    ChainHash ();
    ChainHash (int maxExpected);
    bool remove(const char* key);
    bool find(const char* key, TYPE& holder);
    bool insert(const TYPE& data);
    bool modify(const TYPE& data);
    int size() const;
    ~ChainHash ();
};

//********************************// 
//  Simple class functions ahead  //
//********************************//

template <class TYPE>
Simple<TYPE>::Simple(){
    maximum_cap_ = 100;
    data_ = new TYPE[maximum_cap_];
    count_of_records_ = 0;
}


// This binary search is only used by insert function
// it is recursive as well
template <class TYPE>
int Simple<TYPE>::binary_insert_search(TYPE *array, const TYPE &data, int low, int high){
    int record_number;
    int comparison_result;
    
    if (high == 0)
        record_number = 0;
    else{
        int mid =  (low + high) / 2;
        if( (high - low) < 1)
            record_number = mid;
        else{
            comparison_result = strcmp(array[mid].key(), data.key());
            
            if (comparison_result > 0)
                record_number = binary_insert_search(array, data, low, mid);
            else if ( comparison_result < 0)
                record_number = binary_insert_search(array, data, mid+1, high);
            else
                record_number = -1; 
        }
    }
    
    return record_number;
}


// This is a regular recursive binary search function
template <class TYPE>
int Simple<TYPE>::binary_search(TYPE *array, const char *key, int low, int high){
    int record_number = -1;
    int comparison_result;
    
    if(high > 0 && high != low)
    {
        int mid = (low + high) / 2;
        comparison_result = strcmp(array[mid].key(), key);
        
        if(comparison_result == 0)
            record_number = mid;
        else if (comparison_result > 0)
            record_number = binary_search(array, key, low, mid);
        else
            record_number = binary_search(array, key, mid+1, high);
    }
    
    return record_number;
}

// Grow a table if out of space
template <class TYPE>
void Simple<TYPE>::grow(){
    int new_size = maximum_cap_*1.35;
    TYPE *temp = new TYPE[new_size];
    
    for(int i = 0; i < count_of_records_; i++)
        temp[i] = data_[i];
    
    maximum_cap_ = new_size;
    delete [] data_;
    data_ = temp;
    
}

template <class TYPE>
bool Simple<TYPE>::remove(const char *key){
    bool result = false;
    
    int pos = binary_search(data_, key, 0, count_of_records_);
    if( pos != -1 ){
        count_of_records_--;
        for(int i = pos; i < count_of_records_; i++)
            data_[i] = data_[i+1];
        result = true;
    }
    
    return result;
}

template <class TYPE>
bool Simple<TYPE>::find(const char *key, TYPE &holder){
    bool result = false;
    
    int position = binary_search(data_, key, 0, count_of_records_);
    if (  position != -1 ){
        holder = data_[position];
        result = true;
    }
      
    return result;
}

template <class TYPE>
bool Simple<TYPE>::insert(const TYPE &data){
    bool result = false;
        
    int position = binary_insert_search(data_, data, 0, count_of_records_);
    
    if(position != -1){
        if(count_of_records_ >= maximum_cap_)
            grow();
        count_of_records_++;
        if( data_[position+1].key() ){
            for(int i = count_of_records_; i > position; i --)
                data_[i] = data_[i-1];
        }
        data_[position] = data;
        result = true;
    }
    
    return result;
}

template <class TYPE>
bool Simple<TYPE>::modify(const TYPE &data){
    bool result = false;
    
    int position = binary_search(data_, data.key(), 0, count_of_records_);
    
    if( position != -1 ){
        data_[position] = data;
        result = true;
    }
    
    return result;
}

template <class TYPE>
int Simple<TYPE>::size() const{
    
    return count_of_records_;
}

template <class TYPE>
Simple<TYPE>::~Simple(){
    delete [] data_;
}

//********************************//
//  LPHash class functions ahead  //
//********************************//

template <class TYPE>
LPHash<TYPE>::LPHash(){
    count_of_records_ = 0;
}

template <class TYPE>
LPHash<TYPE>::LPHash(int maxExpected){
    count_of_records_ = 0;
    maximum_cap_ = maxExpected * 1.35;
    data_ = new TYPE[maximum_cap_];
}


// This function was partially copied from Catherine Leungs example
template <class TYPE>
int LPHash<TYPE>::search(const char *key){
    int position = -1;
    int start = HashFunction(key, maximum_cap_);
    
    if(data_[start].key()[0]){
        if( strcmp(data_[start].key(), key) ){
            int i;
            for(i = start+1; i != start && data_[i].key()[0] &&
                             strcmp(data_[i].key(), key); i++); 
            if(data_[i].key()[0] && !strcmp(data_[i].key(), key))
                position=i;
        }
        else
            position = start;
    }
    
    return position;
}


// I was on the way to finish it
// but my not being sober enough prevented me from
// finishing bonus part so let it just stay here
template <class TYPE>
void LPHash<TYPE>::grow(){
//    cout << "<< Growing " << endl;
    TYPE *temp = new TYPE[maximum_cap_];
    
    for(int i = 0, j = 0; i < maximum_cap_; i++){
        if( data_[i].key() != 0 )
                temp[j++] = data_[i];
    }
    
    
//    for(int i = 0; i < count_of_records_; i ++)
//        cout << i <<temp[i].key() << endl;
    delete [] data_;
    
    int position;
    maximum_cap_ *= 1.35;
    
    for(int i = 0; i < count_of_records_; i++){
        position = HashFunction(temp[i].key(), maximum_cap_);
        data_[position] = temp[i];
    }
    
    //cout << j << endl;
//    maximum_cap_ = new_size;
//    delete [] data_;
//    
//    data_ = new TYPE[maximum_cap_];
//    int position = 0;
//    for(int i = 0; i < j; i++){
//        position = HashFunction(temp[i].key(), maximum_cap_);
//        data_[position] = temp[i];
//    }
}


// This function was mostly copied from Catherine Leungs example
template <class TYPE>
bool LPHash<TYPE>::remove(const char *key){
    bool result = false;
    
    int position = search(key);
    
    if( position != -1 ){
        TYPE *empty = new TYPE("");
        data_[position] = *empty;
        
        int next = position+1;
        while (data_[next].key()[0]) {
            int proper_position = HashFunction(data_[next].key(), maximum_cap_);
            if(isbetween(position, proper_position, next) ){
                
                
                data_[position] = data_[next];
                data_[next] = *empty;
                position = next;
            }
            next++;
        }
        count_of_records_--;
        result = true;
    }
    
    return result;
}

// isbetween function was copied from Catherine Leungs example
template <class TYPE>
int LPHash<TYPE>::isbetween(int rm, int proper, int next){
    int retval=0;
    if(proper < next){
        if(rm >= proper && rm < next)
            retval=1;
    }
    else if(proper > next){
        if((rm >= proper && rm < maximum_cap_) ||
           (rm >=0 && rm < next))
            retval=1;
    }
    
    return retval;
}

template <class TYPE>
bool LPHash<TYPE>::find(const char *key, TYPE &holder){
    bool result = false;
    
    int pos = search(key);
    if( pos != -1 ){
        holder = data_[pos];
        result = true;
    }
    
    return result;
}

template <class TYPE>
bool LPHash<TYPE>::insert(const TYPE &data){
    bool result = false;
    int start = HashFunction(data.key(), maximum_cap_);
    
    if( count_of_records_ < maximum_cap_ ){
        count_of_records_++;
        for(;data_[start].key()[0];start++);
        data_[start] = data;
        result = true;
        
    }
        
    return result;
}

template <class TYPE>
bool LPHash<TYPE>::modify(const TYPE &data){
    bool result = false;
    
    int pos = search(data.key());
    if( pos != -1 ){
        data_[pos] = data;
        result = true;
    }
    
    return result;
}

template <class TYPE>
int LPHash<TYPE>::size() const{
    return count_of_records_;
}

template <class TYPE>
LPHash<TYPE>::~LPHash(){

}

/*********************************************
            LINKED LIST CLASS
*********************************************/

// Base case constructor
template <class TYPE>
SAList<TYPE>::SAList(){
    start_ = curr_ = NULL;
}

// Constructor that returns data in a linked list
template <class TYPE>
SAList<TYPE>::SAList(TYPE newdata[],int sz):SAList(){
    for(int i = 0; i < sz; i++)
    {
        curr_->data_ = newdata[i];
        curr_ = curr_->next_;
    }
    
}

// Copy constructor
template <class TYPE>
SAList<TYPE>::SAList(const SAList<TYPE>& source){
    *this = source;
}    

// Destructor, obviously ... 
template <class TYPE>
SAList<TYPE>::~SAList(){ }


template <class TYPE>
void SAList<TYPE>::insert(const TYPE &x){
    
    Node<TYPE>* temp = new Node<TYPE>(x,NULL,start_);
    
    if(start_)
    {
        start_->prev_=temp;
        start_ = temp;
    }
    else
        start_ = curr_ = temp;
    
}

template <class TYPE>
bool SAList<TYPE>::isEmpty() const{
    return start_ == NULL ? true : false;
}

template <class TYPE>
bool SAList<TYPE>::get(TYPE passback[], int max) const{
    bool result = false;
    Node<TYPE>* temp = start_;
    
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

template <class TYPE>
Node<TYPE>* SAList<TYPE>::search(const char *key){
    Node<TYPE>* temp = start_;
    Node<TYPE>* resultNode = NULL;
    bool found = false; 
    
    while(temp && !found)
    {
        if(strcmp(key, temp->data_.key()) == 0)
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
        }
    }
    
    return resultNode;
    
}

template <class TYPE>
bool SAList<TYPE>::remove(const TYPE& key){
    Node<TYPE>* temp = start_;
    bool found = false;
    
    
    while(temp && !found)
    {
        if( strcmp(key.key(), temp->data_.key()) == 0)
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

template <class TYPE>
bool SAList<TYPE>::modify(const TYPE &x){
    bool found = false;
    Node<TYPE>* temp = start_;
    
    while(temp && !found){
        if( strcmp(x.key(), temp->data_.key()) == 0 ){
            temp->data_ = x;
            found = true;
        }
        else
            temp = temp->next_;
     }
    
    return found;
}

template <class TYPE>
SAList<TYPE>& SAList<TYPE>::operator=(const SAList<TYPE>& source){
    if(this != &source)
    {
        start_ = curr_ = new Node<TYPE>();
        Node<TYPE>* temp = source.start_;
        
        start_->data_ = source.start_->data_;
        curr_ = start_;
        
        for (temp = source.start_->next_; temp; temp = temp->next_)
        {
            
            if(start_ == curr_)
            {
                start_->next_ = new Node<TYPE>();
                start_->next_->prev_ = start_;
                start_->next_->data_ = temp->data_; 
                curr_ = start_->next_;
            }
            else
            {
                curr_->next_ = new Node<TYPE>();
                curr_->next_->data_ = temp->data_;
                curr_->next_->prev_ = curr_;
                curr_ = curr_->next_;
            }
            
        }
    }
    
    return *this;
}


//***********************************//
//  ChainHash class functions ahead  //
//***********************************//

template <class TYPE>
ChainHash<TYPE>::ChainHash(){
    maximum_cap_ = 100;
    data_ = new SAList<TYPE>[maximum_cap_];
    count_of_records_ = 0;
}

template <class TYPE>
ChainHash<TYPE>::ChainHash(int maxExpected){
    maximum_cap_ = maxExpected;
    data_ = new SAList<TYPE>[maximum_cap_];
    count_of_records_ = 0;
    cout << maximum_cap_ << endl;
}

template <class TYPE>
bool ChainHash<TYPE>::remove(const char *key){
    bool result = false;
    int position = HashFunction(key, maximum_cap_);
    
    result = data_[position].remove(key);
    count_of_records_--;
    
    return result;    
}

template <class TYPE>
bool ChainHash<TYPE>::find(const char *key, TYPE &holder){
    bool result = false;
    
    int position = HashFunction(key, maximum_cap_);
    Node<TYPE>* temp = data_[position].search(key);
    
    if( temp != 0 ){
        holder = temp->data();
        result = true;
    }
    
    return result;
}

template <class TYPE>
bool ChainHash<TYPE>::insert(const TYPE &data){
    bool result = false;
    
    int position = HashFunction(data.key(), maximum_cap_);
    
    
    if(!data_[position].search(data.key())){
        data_[position].insert(data);
        count_of_records_++;
        result = true;
    }
    
    return result;
}

template <class TYPE>
bool ChainHash<TYPE>::modify(const TYPE &data){
    bool result = false;
   
    int position = HashFunction(data.key(), maximum_cap_);
    
    if( data_[position].modify(data) )
        result = true;
    
    
    
    return result;
}

template <class TYPE>
int ChainHash<TYPE>::size() const{
    return count_of_records_;
}
 
template <class TYPE>
ChainHash<TYPE>::~ChainHash(){
    delete [] data_;
}