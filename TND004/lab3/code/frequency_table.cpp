#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert

#include "BinarySearchTree.h"

#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3

struct Row {
    // ADD CODE: exercise 3

    Row() : counter{ 0 } {};

    //constructor takes a word and adds one to counter
    Row(std::string w) : key{ w }, counter{ 1 }{}

    //destructor
    ~Row() = default;

    bool operator<(const Row & r) const { //sort in alphabetic order, first letters starting on the left side
        return key < r.key;
    }

    void increase_counter() { counter++; } //increase counter

    void printRow() const { //how the row shall be printed
        std::cout << std::left << std::setw(25) << key << counter << std::endl;
    }

    std::string key;
    int counter = 0;

};


// Add other stuff, if needed

bool test_char(const char x)
{
    if (isalnum(x) || (x == '\'') ||(x == '’')) {    //  HOW TO CATCH THE ’ SIGN  || (x == '’')
        return false; //The character is valid
    }
    else {
        return true; //The character is invalid
    }
}

void display(Row r) { //displays every row
    r.printRow();
}


#endif

void exercise3() {
#ifdef TEST_EXERCISE3
    {
        std::ifstream file("../code/text_long.txt");  // contains 56 unique words
        // std::ifstream file("../code/text_long.txt"); // contains 497 unique words

        if (!file) {
            std::cout << "Couldn't open file text.txt\n";
            // std::cout << "Couldn't open file text_long.txt\n";
            return;
        }

        // ADD CODE: exercise 3

         BinarySearchTree<Row> frqTable;
    
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

    std::string key; //each word in file
    int counter_file = 0; //number of words in the file
    Row new_entry; //each new row

    while (file >> key) { //as long as there are strings in the file

            // Remove bad characters
        key.erase(remove_if(key.begin(), key.end(), test_char), key.end());

        // Transform to lowercase
        transform(key.begin(), key.end(), key.begin(), [](char c) {return static_cast<char>(::tolower(c)); });

        BinarySearchTree<Row>::Iterator it_key = frqTable.contains_it(key); //creates iterator that points to the place in frqtable that is storing key

        // Add key or increase key's counter
        if (it_key == frqTable.end()) { //if word has not occured, insert it first in frqtable and re iterate to beginning
            frqTable.insert(Row(key));
            it_key = frqTable.begin();
        }
        else { //increase counter if word has occured
            it_key->increase_counter();
        }
        counter_file++;

    }
    std::cout << "Number of words in the file = " << counter_file << std::endl;
    std::cout << "Number of unique words in the file = " << frqTable.get_count_nodes() << std::endl << std::endl;
    std::cout << "\n\n\n";
    std::cout << "Frequency table sorted alphabetically ...\n\n";



    std::for_each(frqTable.begin(), frqTable.end(), display); //display everu row

    std::cout << "\n\n";

    std::cout << "Success!!\n";
#endif
    
    }		
}