//CMPT225 assignment4
//Ritika Goyal (301401516)

#pragma once
#include <iostream>
#include<string>
#include<cmath>
using namespace std;

class HashTable{
//private:
public:
	//str_arr is underlying array of string objects
	string* str_arr;
	// size_arr records the size of underlying array
	int size_arr;
	// value_h2 record the value used by h2
	int value_h2;
	// current_size records the number of items in the hash table
	int current_size;

	//helper methods
	//POST : checks if n is prime or not
	//PARAM: n = integer which is checked if it is prime
	bool yes_prime(const int n) const;

	//POST: copies the content of h HashTable into calling object
	//PARAM: h = hashtable to be copied
	void copy_hashTable(const HashTable& h);

	//POST: finds the key value maped to the parameter
	//PARAM: str = string whose key value to be found, size_of_arr = size of hashtable 
	int key_value(string str, int size_of_arr) const;


public:
	//Default constructor
	//POST: creates hash table of size 101 and initialise all array elements as empty string
	//sets the value of h2 prime number greater than half the array size
	HashTable();

	//Non default constructor
	//POST: creates a hash table to store n items 
	//size of hash table is first prime number greater than 2n and initialises all array elements as empty string
	//sets the value of h2 prime number greater than half the array size
	//PARAM: n = size of items to be stored in hash table
	HashTable(int n);

	//Copy constructor
	//POST: copies the content of parameter into calling object by deep copy
	//PARAM: h = HashTable tupe parameter whose content are copied into calling object
	HashTable(const HashTable & h);

	//Destructor
	//POST: de-allocates any dynamic memory associated with the calling object
	~HashTable();

	//Assignment operator
	//POST: creates a deep copy of its parameter, assign it to the calling object
	//PARAM: h = hashtable whose contents are copied to calling object
	HashTable & operator=(const HashTable & h);	

	//insert method
	//PARAM: checks if its parameter is in the has table 
	//if not found insert it using double hashing and manages the size of array by checking value of load factor
	//PARAM: str = string tyoe parameter to be inserted in hash table
	void insert(string str);

	//find method
	//POST: returns true if its string parameter is in hash table, return false if it is not
	//PARAM: str = string parameter to be found in hash table 
	bool find(string str)const;

	//size method
	//POST:returns the number of items stored in the hash table
	int size() const;

	//maxSize method
	//POST: returns the size of the hash table's underlying array
	int maxSize()const;

	//loadFactor method
	//POST: returns the load factor of the hash table
	float loadFactor()const;
};
