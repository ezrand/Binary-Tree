#include <iostream> 
#include <string>
#include <sstream>
#include <memory>
#include "BST.h" 
using namespace std;

const int DICTIONARY_SIZE = 10;

int main()
{
	cout << "CSCN 215 Assignment 2 -- Threaded Binary Tree -- Ezra Anderson" << endl; 
	cout << "Testing the insert function to build my tree." << endl; 
	BST<int, string>* nBST = new BST<int, string>();
	//insert key value function statements below
	nBST->insert(77, "seventy-seven");
	nBST->insert(70, "seventy");
	nBST->insert(75, "seventy-five");
	nBST->insert(66, "sixty-six");
	nBST->insert(79, "seventy-nine");
	nBST->insert(68, "sixty-eight");
	nBST->insert(67, "sixty-seven");
	nBST->insert(69, "sixty-nine");
	nBST->insert(90, "ninety");
	nBST->insert(85, "eighty-five");
	nBST->insert(83, "eighty-three");
	nBST->insert(87, "eighty-seven");
	nBST->insert(65, "sixty-five");

	cout << "My BST size is: " << nBST->size() << endl;

	//print function, calls print which calls print help in the BST
	nBST->print();

	//inorder function, calls inorder which calls findnext to segment through the data members
	cout << "In order print: " << endl;

	nBST->printInOrder();

	//reverse print function, calls printreverse which calls find previous to segment through the data members in reverse
	cout << endl << endl << "Reverse order print: " << endl;

	nBST->printReverse();

}