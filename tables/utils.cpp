/**********************************************************/
/*                                                        */
/* Author: Catherine Leung                                */
/* Utility functions for your hash table                  */
/*                                                        */
/**********************************************************/
#include <string.h>
#include "utils.h"

/*code for hash function comes from: 
  Data Structures and Algorithm Analysis in C++, Third Edition 
  by Mark Allen Weiss. page 188*/
int HashFunction(const char* key, int capacity){
  int hashVal=0;
  int len=strlen(key);
  for(int i=0;i<len;i++){
    hashVal=37*hashVal + key[i];
  }
  hashVal=hashVal%capacity;
  if(hashVal<0)
    hashVal=hashVal+capacity;
  return hashVal;
}
/*this function returns the first number >= N that is a prime*/
int nextprime(int N){
  int start=N%2?N:N+1;
  int rc=0;
  for(int i=start;!rc;i+=2){
    if(isprime(i))
      rc=i;
  }
  return rc;
}
/*this function returns true if N is a prime, false otherwise*/
int isprime(int N){
  int rc=(N<=2)?1:(N%2);
  for(int i=3;i*i<=N;i+=2){
    if(N%i==0)
     rc=0;
  }
  return rc;
}
