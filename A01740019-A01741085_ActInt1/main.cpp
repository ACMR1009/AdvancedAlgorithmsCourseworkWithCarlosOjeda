/*  Actividad Integradora 1
This code is an implementation of different algorithms to find substrings within a given string, longest palindromes, and the longest common substring between two strings.
    Ana Cristina Munguia Romero, A01740019
    Carlos Noel Ojeda Angulo, A01741085
    Date: september 11, 2021
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Function that reads the file with the name stored in 'fileName'.
// It receives the name of the file as a string and returns another
// string storing the content of the file.
//Complexity: O(n) where 'n' is the number of characters in the file 'fileName'
string readFile(string fileName){
	string str, line;
	fstream fin = fstream(fileName);
	if(!fin.is_open()){
        cout << "Error: File " << fileName << " not found" << endl;
	}else {
		while(!fin.eof()){
			getline(fin, line);
            str += line;
		}
  	}
	fin.close();
	return str;
}

//Function that generates the corresponding LPS array for the
// string 'pattern', storing the longest suffix that's also a prefix
// at a given position. It receives a reference to the
// string 'pattern' and an empty array to fill out. It returns a
// pointer to the completed array.
//Complexity: O(n) where 'n' is the number of characters in 'pattern'
int * generateLPS(string& pattern, int array[]){
    int i = 0,
        j = 1;
	array[0] = 0;
	while(j < pattern.size()){
		if(pattern[i] == pattern[j]){
			array[j] = i+1;
			i++;
			j++;
		}else if(i == 0){
            array[j] = 0;
			j++;
        }else {
			i = array[i-1];
		}
	}
    return array;
}

//Function that looks for a certain 'pattern' string within
// a certain 'text' string. If the 'pattern' is found in the 'text'
// the function returns 'true' and prints the position within
// the 'text' where the 'pattern' starts. If 'pattern' is not found
// the function returns 'false'.
//Complexity: O(n+m) where 'm' is the number of characters in 'text' and 'n' the number of characters in 'pattern'
bool searchByKMP(string& text, string& pattern){
    int n = text.size(),
        m = pattern.size();
	int array[m];
    int *lps = generateLPS(pattern, array);
	
	int i = 0,
		j = 0;
	while(i<n){
		if(pattern[j] == text[i]){
			if(j == m-1){
				cout << "true " << i - m+1 << endl;
				return true;
			}
            i++;
            j++;
        }else if(j > 0){
            j = lps[j-1];
        }else {
			i++;
		}
	}
	cout << "false" << endl;
    return false;
}

//Function that turns any given string 'text' into an odd-sized
// string by inserting '#' in between the characters.
//Complexity: O(n) where 'n' is the number of characters in 'text'
void makeStringOdd(string& text){
    int newSize = text.size() * 2 + 1;

    for(int i=0; i<newSize; i++){
        if(i%2 == 0){
            text.insert(i,"#");
        }
    }
}

//Function that looks for the longest palindrome in the given 'text' 
// string and prints the initial and final position of this 
// palindrome.
//Complexity: O(n) where 'n' is the number of characters in 'text'
void findLongestPalindrome(string text){
    makeStringOdd(text);
	
	int right = -1,
		left  = -1;
	int palindromeSizes[text.size()];

    for(int i=0; i<text.size(); i++){
		if(i <= right){
            palindromeSizes[i] = min(palindromeSizes[2*left - i], right-i);
        }else {
            palindromeSizes[i] = 0;
        }
		
        while(text[i - palindromeSizes[i]-1] == text[i + palindromeSizes[i]+1]){
			palindromeSizes[i] += 1;
        }
		
		if(i+palindromeSizes[i] > right){
			right = i + palindromeSizes[i];
			left  = i;
		}
    }
    
	//Obtain initial position
    int currentLongestPosition = 0;
	for(int i=0; i<text.size(); i++){
		if(palindromeSizes[i] > palindromeSizes[currentLongestPosition]){
			currentLongestPosition = i;
		}
    }

	int initialPos = (currentLongestPosition - (palindromeSizes[currentLongestPosition]-1)) / 2 + 1;
	cout << initialPos << " ";
	
	//Obtain final position
	int finalPos = initialPos + (palindromeSizes[currentLongestPosition])-1;
    cout << finalPos << endl;
}

//Function that looks for the longest common substring between two
// given strings 'text1' and 'text2' and prints the initial and
// final positions of said substring within 'text1'.
//Complexity: O(n*m) where 'n' is the number of characters in 'text1' and 'm' in 'text2'
void findLongestSubstring(string& text1, string& text2){
	vector<vector<int>> matrix;
    int result = 0,
		firstPosition,
        finalPosition;

    for(int i=0; i<text1.size(); i++){
        vector<int> list;
        for(int j=0; j<text2.size(); j++){
            if(i==0 || j==0){
                list.push_back(0);
            }else if(text1[i-1] == text2[j-1]){
				list.push_back(matrix[i-1][j-1] + 1);
                if((matrix[i-1][j-1] + 1) > result){
                    result = (matrix[i-1][j-1] + 1);
                    finalPosition = i;
                }
			}else {
				list.push_back(0);
			}
        }
        matrix.push_back(list);
    }
    
	firstPosition = finalPosition - result + 1;
	cout << firstPosition << " " << finalPosition << endl;
}

int main(){
	string transmission1 = "transmission1.txt",
		   transmission2 = "transmission2.txt", 
           mcode1 = "mcode1.txt",
           mcode2 = "mcode2.txt", 
		   mcode3 = "mcode3.txt";

	transmission1 = readFile(transmission1);
	transmission2 = readFile(transmission2);
	mcode1 = readFile(mcode1);
	mcode2 = readFile(mcode2);
	mcode3 = readFile(mcode3);

	//Search for malicious code in transmission files
	searchByKMP(transmission1, mcode1);
    searchByKMP(transmission1, mcode2);
    searchByKMP(transmission1, mcode3);

    searchByKMP(transmission2, mcode1);
    searchByKMP(transmission2, mcode2);
    searchByKMP(transmission2, mcode3);

	cout << endl;

    //Search for longest palindrome in transmission files
    findLongestPalindrome(transmission1);
    findLongestPalindrome(transmission2);
    
	cout << endl;
	
	//Search for longest common substring in transmission files
    findLongestSubstring(transmission1, transmission2);

	return 0;
}