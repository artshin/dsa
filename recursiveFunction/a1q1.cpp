//
//  a1q1.cpp
//  assignment1DSA
//
//  Created by Artur Shinkevich on 11-10-08.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "a1q1.h"


bool MajorityElement(int arr[], int& majority, int sz){
    bool result = false;
    int numOfCandidate = 0;
    int can;
    
    //Names of variables are pretty desriptive
    //and the following code speaks for itself
    
    if(Candidate(arr, sz, can))
    {
        for(int i = 0; i < sz; i++)
        {
            if(can == arr[i])
                numOfCandidate++;
        }
        if(numOfCandidate > sz/2)
            result = true;
    }
    if(result)
        majority = can;
    
    return result;
}

bool Candidate(int arr[], int sz, int& can){
    bool result = false;
    int temp[sz];
    int temp_counter = 0;
    
    // temp is an array to hold new values from 
    // original array. Temp_counter is needed as
    // counter (obviously) and as an array size
    // to be passed to another Candidate function
    
    if(sz != 0)
    {
        if(sz == 1)
        {
            can = arr[0];
            result = true;
        }
        else
        {
            for(int i = 0; i < sz; i+=2)
            {
                if(arr[i] == arr[i+1])
                    temp[temp_counter++] = arr[i];
                temp[temp_counter] = NULL;
            }
            
            result = Candidate(temp,temp_counter,can);
            
            if(sz%2 != 0 && !result) // if array size is odd and no candidate
            {                        // is found then the last number is candidate
                can = arr[sz-1];
                result = true;
            }
        }
    }
    return result;
}
