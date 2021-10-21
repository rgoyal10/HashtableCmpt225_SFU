//CMPT225 assignment4
//Ritika Goyal (301401516)

#include "HashTable.h"

//helper yes_prime
//POST : checks if n is prime or not
//PARAM: n = integer which is checked if it is prime
bool HashTable::yes_prime(const int n) const
{
	if(n==1)
		return false;
	for(int i=2;i<=n/2;i++)
		if(n%i==0)
			return false;
	return true;
}

//helper copy_hashTable
//POST: copies the content of h HashTable into calling object
//PARAM: h = hashtable to be copied
void HashTable::copy_hashTable(const HashTable& h)
{
	size_arr = h.size_arr;
	current_size=h.current_size;
	value_h2=h.value_h2;
	str_arr= new string [size_arr];
	for(int i=0;i<size_arr;i++)
		str_arr[i]=h.str_arr[i];
}

//helper key_value
//POST: finds the key value maped to the parameter
//PARAM: str = string whose key value to be found, size_of_arr = size of hashtable 
int HashTable::key_value(string str, int size_of_arr) const
{
	int value = 0;
	int i= 0 ;
	int mod_value = size_of_arr;
	if(str.length()==0)
		return 0;
	if(str.length()==1)
	{
		value = (str[i]-96) % mod_value;
		return value;
	}
	//using horner's method
	value = (str[i]-96) * 32 + (str[i+1]-96);
	i=2;
	int count =0;
	while(count<str.length()-2)
	{
		value = (value % mod_value) * 32 + (str[i]-96);
		i++;
		count++;
	}
	value = value % mod_value ;
	return value;
}

//Default constructor
//POST: creates hash table of size 101 and initialise all array elements as empty string
//sets the value of h2 prime number greater than half the array size
HashTable::HashTable()
{
	size_arr=101;
	current_size=0;
	str_arr= new string[size_arr];
	for(int i=0;i<size_arr;i++)
		str_arr[i]="";
	int n = (size_arr/2)+1;
	bool isPrime = false;
	while(!isPrime)
	{

		if(yes_prime(n))
			isPrime=true;
		else
			n++;
	}
	value_h2 = n;


}

//Non default constructor
//POST: creates a hash table to store n items 
//size of hash table is first prime number greater than 2n and initialises all array elements as empty string
//sets the value of h2 prime number greater than half the array size
//PARAM: n = size of items to be stored in hash table
 HashTable::HashTable(int n)
 {
 	current_size=0;
 	int size = 2*n + 1;
 	bool isPrime=false;
 	while(!isPrime)
	{

		if(yes_prime(size))
			isPrime=true;
		else
			size++;
	}
	size_arr=size;
	str_arr = new string[size_arr];
	for(int i=0;i<size_arr;i++)
		str_arr[i]="";
	int x = (size_arr/2)+1;
	isPrime = false;
	while(!isPrime)
	{

		if(yes_prime(x))
			isPrime=true;
		else
			x++;
	}
	value_h2 = x;
 }

//Copy constructor
//POST: copies the content of parameter into calling object by deep copy
//PARAM: h = HashTable tupe parameter whose content are copied into calling object
HashTable:: HashTable(const HashTable & h)
{
	copy_hashTable(h);
}

//Destructor
//POST: de-allocates any dynamic memory associated with the calling object
HashTable:: ~HashTable()
{
	delete [] str_arr;
}

//Assignment operator
//POST: creates a deep copy of its parameter, assign it to the calling object
//PARAM: h = hashtable whose contents are copied to calling object
HashTable & HashTable:: operator=(const HashTable & h)
{
	if(this != &h)
	{
		if(size_arr!=0)
			delete [] str_arr;
		copy_hashTable (h);
	}
	return *this;
}	

//find method
//POST: returns true if its string parameter is in hash table, return false if it is not
//PARAM: str = string parameter to be found in hash table 
bool HashTable::find(string str) const
{
	int h1 = key_value(str,size_arr) % size_arr;
	int h2 = value_h2 - (key_value(str,value_h2));
	while(str_arr[h1]!= "" )
	{
		if(str_arr[h1]== str)
		     return true;
		h1=h1+h2;
		if(h1>=size_arr-1)
			h1 = h1 % size_arr;
	}
	return false;
}

//insert method
//PARAM: checks if its parameter is in the has table 
//if not found insert it using double hashing and manages the size of array by checking value of load factor
//PARAM: str = string type parameter to be inserted in hash table
void HashTable::insert(string str)
{

	if(find(str))
		return ;
	int h1 = key_value(str,size_arr) % size_arr;
	int h2 = value_h2 - (key_value(str,value_h2));
	while(str_arr[h1]!= "")
	{
		h1=h1+h2;
		if(h1>=size_arr-1)
			h1=h1%size_arr;
	}
	str_arr[h1]= str;
	current_size++;
	float x =loadFactor();
	if(x>0.67)
	{

		string * temp;
		int before_size = size_arr;
		size_arr = 2 * size_arr + 1;
	 	bool isPrime=false;
	 	while(!isPrime)
		{

			if(yes_prime(size_arr))
				isPrime=true;
			else
				size_arr++;
		}
		temp = new string[size_arr];
		for(int i=0;i<size_arr;i++)
			temp[i]="";
		int new_h = size_arr/2+1;
		isPrime = false;
	 	while(!isPrime)
		{
    
			if(yes_prime(new_h))
				isPrime=true;
			else
				new_h++;
		}
		value_h2=new_h;
		int j=0;
		for(int i =0 ; i<current_size;i++)
		{
			while(str_arr[j]=="")
			{
				j++;
			}
			int h1 = key_value(str_arr[j],size_arr) % size_arr;
			int h2 = value_h2 - (key_value(str_arr[j],value_h2));
			while(temp[h1]!= "")
			{
				h1=h1+h2;
				if(h1>=size_arr-1)
					h1=h1%size_arr;
			}
			temp[h1]= str_arr[j];
			j++;
		}

		delete [] str_arr;
		str_arr = temp;
	}

}

//size method
//POST:returns the number of items stored in the hash table
int HashTable::size() const
{
	return current_size;
}

//maxSize method
//POST: returns the size of the hash table's underlying array
int HashTable::maxSize() const
{
	return size_arr;
}

//loadFactor method
//POST: returns the load factor of the hash table
float HashTable::loadFactor() const
{
	return (current_size*1.0/size_arr);
}

