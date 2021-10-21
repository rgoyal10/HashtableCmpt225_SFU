//CMPT225 assignment4
//Ritika Goyal (301401516)

#include "HashTable.h"
#include <vector>

//helper function for sorting the result
//using quick sort
//POST: partition the subarray about the pivot where pivot is the element of the array
//PARAM: v is vector of strings 
//start and end are the indexes of array
int partition(vector<string> & v, int start, int end)
{
	string pivot= v[end];
	int high = end-1;
	while(start < high)
	{
		if(v[start]<=pivot)
			start++;
		else if (v[high]>=pivot)
			high--;
		else
		{
			string temp = v[start];
			v[start]=v[high];
			v[high]=temp;
			start++;
			high--;
		}
	}
	if(v[start]<pivot)
	{
		string temp = v[start+1];
		v[start]=v[end];
		v[end]=temp;
		return start+1;

	}
	else
	{
		string temp = v[start];
		v[start]=v[end];
		v[end]=temp;
		return start;
	}
}
//POST:sorts the vector of strings
//PARAM: v is vector of strings 
//start and end are the indexes of array
void quickSort(vector<string> & v, int start,int end)
{
	if(start<end)
	{
		int pivot = partition (v,start,end);
		quickSort(v,start,pivot-1);
		quickSort(v,pivot+1,end);
	}
}

//POST: if word is not in ht, return all strings in ht that can be made by deleting a single letter from word
//PARAM: ht = hashtable from which we are looking the word
//word= string type parameter 
vector<string> extraLetter(const HashTable & ht, string word)
{
	vector<string> v;
	if(ht.find(word))
	{
		v.push_back(word);
		return v;
	}
	
	string str="";
	for(int i=0; i<=word.length()-1;i++)
	{
		str=word;
		str.erase(str.begin()+i);
		if(ht.find(str))
			v.push_back(str);
	}
	quickSort(v,0,v.size()-1);
	return v;
}

//POST:if word is not in ht, returns all strings in ht that can be made swapping any two neighbouring letters in word
//PARAM: ht = hashtable from which we are looking the word
//word= string type parameter 
vector<string> transposition(const HashTable & ht, string word)
{
	vector<string> v;
	if(ht.find(word))
	{
		v.push_back(word);
		return v;
	}

	string str = "";
	for(int i =0 ; i<word.length()-1;i++)
	{
		str = word;
		str[i]=word[i+1];
		str[i+1]=word[i];
		if(ht.find(str))
			v.push_back(str);
	}
	quickSort(v,0,v.size()-1);
	return v;
}

//POST: if word is not in ht, returns all pairs of strings in ht that can be made by inserting a single space in word
//PARAM: ht = hashtable from which we are looking the word
//word= string type parameter 
vector<string> missingSpace(const HashTable & ht, string word)
{
	vector<string> v;
	if(ht.find(word))
	{
		v.push_back(word);
		return v;
	}
	string str="";
	for(int i=0 ; i<word.length()-1;i++)
	{
		str = word;
		str = str +" ";
		for(int j = i+1 ; j< word.length();j++)
		{
			char temp = str[j];
			str[j]=str[word.length()];
			str[word.length()]=temp;
		}
		cout<<"str :"<<str<<endl;
		int index_space = 0;
		for(int j =0 ; j<str.length(); j++)
		{
			if(str[j]==' ')
				index_space=j;
		}
		string temp1 = "";
		//copies the string before ' ' into temp1
		for(int j =0 ;j<index_space;j++)
			temp1+=str[j];
		cout<<"temp1 :"<<temp1<<endl;
		string temp2 = "";
		//copies the string after ' ' into temp2
		for(int j=index_space+1;j<str.length(); j++)
			temp2+=str[j];
		cout<<"temp2 :"<<temp2<<endl<<endl;
		if(ht.find(temp1) && ht.find(temp2))
			v.push_back(str);
	}
	quickSort(v,0,v.size()-1);
	return v;
}

//POST: if word is not in ht, returns all strings in ht that can be made by inserting any single letter of the alphabet at any position in word
//PARAM: ht = hashtable from which we are looking the word
//word= string type parameter 
vector<string> missingLetter(const HashTable & ht, string word)
{
	vector<string> v;
	if(ht.find(word))
	{
		v.push_back(word);
		return v;
	}
	string str="";
	for(int i=0; i<=word.length();i++ )
	{
		for(char ch ='a';ch<='z';ch++)
		{
			str=word;
			str.insert(str.begin()+i,ch);
			if(ht.find(str))
				v.push_back(str);
		}
	}
	quickSort(v,0,v.size()-1);
	return v;

}


//POST:if word is not in ht, returns all strings in ht that can be made by changing any single letter of word to a different letter in the alphabet
//PARAM: ht = hashtable from which we are looking the word
//word= string type parameter 
vector<string> incorrectLetter(const HashTable & ht, string word)
{
	vector<string> v;
	if(ht.find(word))
	{
		v.push_back(word);
		return v;
	}
	string str="";
	for(int i=0; i<word.length();i++)
	{
		str=word;
		for(char ch ='a';ch<='z';ch++)
		{
			str[i]=ch;
			if(ht.find(str))
				v.push_back(str);
		}

	}
	quickSort(v,0,v.size()-1);
	return v;
}
