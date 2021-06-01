/* George Chiang
ECE 570
Assignment 0 Inverted Index

Your inverter should print all of the words from all of the inputs, in "alphabetical" order, followed by the document numbers in which they appear, in order.  For example (note: your program must produce exactly this output):

a: 0 1
also: 1
boring: 1
cool: 0
is: 0 1
test: 0 1
this: 0 1

Alphabetical is defined as the order according to ASCII.  So "The" and "the" are separate words, and "The" comes first.  Only certain words should be indexed.  Words are anything that is made up of only alpha characters, and not numbers, spaces, etc.  "Th3e" is two words, "Th" and "e".

Files are incrementally numbered, starting with 0.  Only valid, "open-able" files should be included in the count.  (is_open() comes in handy here.)
*/

#include<string.h>
#include<fstream>
#include<iostream>
#include<map>
#include<stdio.h>
#include<sstream>
#include<cstdio>

using namespace std;

int main(int argc, char** argv) {
	char fnames[50][50];		//Array of filenames
	char c;
	stringstream key, val, ss; 
	map<string, string> invertedIndex; //Map
  	std::pair<std::map<string,string>::iterator,bool> dup;  //Used to check for duplicate words in files
	ifstream inpfile;		//Reads input.txt file which contains list of filenames
  	int i = 0;
  	int numfiles;
  	map<string, string>::iterator traverse; //Used to traverse through the map to output its contents

	inpfile.open(argv[1]);
	if (inpfile)		//Checks if input.txt is valid
  	{
  		while(!inpfile.eof()){	//While input.txt has not reached end of file
  			inpfile >> fnames[i];		//Stores filenames in input.txt into array of filenames
  			i++;
  		}
      numfiles = i;
      inpfile.close();		//Closes input.txt
  	}

  	for(int j = 0; j < numfiles; j++){	//For loop to iterate through fnames array
      ifstream inp2;          //Reads the file based on the filename taken from input.txt  
  	  inp2.open(fnames[j]);
      
  	  if(inp2){			//Checks if the file is valid and not empty
  		while(!inp2.eof()){        
          while(inp2.get(c)){
            if(isalpha(c) && !isspace(c)){                       //Checks if the character pulled from the file is an alphabetic character
              key << c;
            }
            else{
              break;
            }
          }
          val << " " << j;                      //Converts integer that indexes the filenumber to a string with a space in between
          dup = invertedIndex.insert(pair<string,string>(key.str(), val.str()));  //Inserts key value pair into map
          if(!dup.second) {                       //Checks for duplicate words so they dont appear twice
          	string chk1 = dup.first->second;
          	string chk2 = val.str();
          	if(chk1.compare(chk2) != 0) {
            	ss << dup.first->second << val.str();
            	dup.first->second = ss.str();
            	ss.str("");
          	}
          }
        	key.str("");
        	val.str("");
  		}
  			inp2.close();			//Closes the file
  		}
  	}
  	if(invertedIndex.begin()->first == ""){				//Removes blank space at the beginning
  		invertedIndex.erase(invertedIndex.begin());
  	}
    for(traverse = invertedIndex.begin(); traverse != invertedIndex.end(); traverse++){ //Iterates through map
      cout << traverse->first << ":" << traverse->second << "\n"; //Outputs map contents
    }
    return 0;
}
