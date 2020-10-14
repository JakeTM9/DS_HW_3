#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
using namespace std;

//Code Refactored 10/13

//struct key -> used everywhere. Everything has a .k.first and a .k.last
struct key {  //for bst     
	string first, last;
};

//START CLASS PERSON (the nodes for the BST)

class Person {
public:
	//Constructors
	Person(); // empty constructore
	Person(string first, string last, string num); //first name last name phone number constructor



	string printFullName(void);//obvious
	string printNumber(void); //obvious
	string printNameAndNumber(void);

	string saveFullName(void);
	string saveNumber(void);

	string firstName;
	string lastName;
	string number; // for number storage


	//for the BST of People
	Person* left; //left child
	Person* right; //right child
};

string Person::saveFullName() {
	return (firstName + " " + lastName + " ");
}

string Person::saveNumber() {
	return number;
}

string Person::printFullName() {
	cout << lastName << ", " << firstName << "\n";
	return (firstName + " " + lastName);
}

string Person::printNumber() {
	cout << number << "\n";
	return number;
}


string Person::printNameAndNumber() {
	cout << "NAME: " << lastName << ", " << firstName << "	NUMBER: " << number << endl;
	return (firstName + " " + lastName + " " + number);
}

Person::Person() {
	firstName, lastName, number = "";
}

Person::Person(string first, string last, string num) {
	firstName = first;
	lastName = last;
	number = num;
}



// START BST Class

class BinarySearchTree {
public:
	BinarySearchTree();
	void add(Person person);
	Person* find(key k); //nonrecursive search function
	void display(Person* leaf);
	void savetree(Person* leaf, fstream& myfile);
	string fullname;
	string number;

	bool isEmpty(void) { return (root == NULL); }; //a quick way to tell if the tree has elements
	string test; //another quick way to debug tree constructor
	Person* root; //root of tree

private:

	void add(Person person, Person* leaf); // recursive add function
	Person* find(key k, Person* leaf); //recursive search function

};

BinarySearchTree::BinarySearchTree() {
	root = NULL; //init head NULL
	test = "test"; //init test prints test 
}


void BinarySearchTree::add(Person person) {
	if (root != NULL) { // for when theres already a BST -> gonna call recursive
		add(person, root);
	}
	else {
		root = new Person(person.firstName, person.lastName, person.number);

	}
}

void BinarySearchTree::add(Person person, Person* leaf) { // This is the recursively calling insert function that takes place after the public insert function to check if there is even anything in the BST
	//CASE 1: last < last
	if (person.lastName < leaf->lastName) { //If what we are inserting is less than the Person we plugged
		if (leaf->left != NULL) { // If key is less than the node and the left child isnt null, recursively call insert again for the left child
			add(person, leaf->left);
		}
		else { // ding ding we got an open spot
			leaf->left = new Person(person.firstName, person.lastName, person.number); // Creates a Person In the Tree
			leaf->left->left = NULL; //new Person left Person null
			leaf->left->right = NULL; //new Person right Person null
		}
	}
	//CASE 2: last > last
	else if (person.lastName > leaf->lastName) { //If what we are inserting is greater than the Person we plugged
		if (leaf->right != NULL) { // If key is greater than the node and the right child isnt null, recursively call insert again for the left child
			add(person, leaf->right);
		}
		else { // ding ding we got an open spot
			leaf->right = new Person(person.firstName, person.lastName, person.number); // Creates a Person In the Tree
			leaf->right->left = NULL; //new Person left Person null
			leaf->right->right = NULL; //new Person right Person null
		}
	}
	//CASE3
	//this is the case of the last names being the same, time to repeat the above code but with first names
	else {

		//CASE3a
		if (person.firstName < leaf->firstName) { //If what we are inserting is less than the Person we plugged
			if (leaf->left != NULL) { // If key is less than the node and the left child isnt null, recursively call insert again for the left child
				add(person, leaf->left);
			}
			else { // ding ding we got an open spot
				leaf->left = new Person(person.firstName, person.lastName, person.number); // Creates a Person In the Tree
				leaf->left->left = NULL; //new Person left Person null
				leaf->left->right = NULL; //new Person right Person null
			}
		}
		//CASE3b
		else {
			if (leaf->right != NULL) { // If key is greater than the node and the right child isnt null, recursively call insert again for the left child
				add(person, leaf->right);
			}
			else { // ding ding we got an open spot
				leaf->right = new Person(person.firstName, person.lastName, person.number); // Creates a Person in the Tree
				leaf->right->left = NULL; //new Person left Person null
				leaf->right->right = NULL; //new Person right Person null
			}
		}


	}
}


Person* BinarySearchTree::find(key k, Person* leaf) {
	if (leaf != NULL) {
		if ((k.last == leaf->lastName) && (k.first == leaf->firstName)) {
			return leaf; //winner winner
		}
		else if (k.last < leaf->lastName) { // if last name is less than the leaf
			return find(k, leaf->left); // we recursively call search tp the left child
		}
		else if (k.last > leaf->lastName) { // if last name is greater than the leaf
			return find(k, leaf->right); // we recursively call search tp the righ child
		}
		else { // here we go its first name time
			if (k.first < leaf->firstName) { // if last name is less than the leaf
				return find(k, leaf->left); // we recursively call search tp the left child
			}
			else {
				return find(k, leaf->right); // we recursively call search tp the righ child
			}
		}
	}
	else {
		return NULL; //oopsie ur name aint in the book cheif
	}
}


Person* BinarySearchTree::find(key k) { //this guy starts so the recursive can go
	return find(k, root); // begin recursive
}

void BinarySearchTree::display(Person* leaf) { //alphabetical order traversal
	if (leaf != NULL) {
		display(leaf->left);
		cout << "------------------------------------------------------------------" << endl;
		leaf->printNameAndNumber();
		display(leaf->right);
	}
}


void BinarySearchTree::savetree(Person* leaf, fstream& myfile) {
	if (myfile.is_open()) { //if file is open (it was opened earlier)
		if (leaf != NULL) { //if the tree has not completely been searched, perform inorder search
			savetree(leaf->left, myfile); //recursive call
			myfile << leaf->lastName << ", " << leaf->firstName << ", " << leaf->number << endl; //print data in format LAST, FIRST, NUMBER
			savetree(leaf->right, myfile); //recursive call
		}
	}
}

//START BOOK
class Book {
public:
	Book();
	BinarySearchTree tree;

private:
};

Book::Book() {

}

//START UI (allows the user to give commands to the book)

class UserInterface {
public:
	UserInterface();
	Book book;
	void Menu();
	void ReadPhonebook(string);
	void SavePhonebook(string);
	void Add(); //add name and number to book given person
	void Delete(); //delete number given name
	void Find(); // ??
	void Change(); //change number given name
	void Display(); //dumps book

private:

};

UserInterface::UserInterface() {}

void UserInterface::Menu() {
	bool run = true;
	char choice;
	string fileinput;

	//continuous loop to enable multiple uses
	while (run) {
		cout << "What would you like to do? \n 1. Add a new entry. \n 2. Delete a phone number.\n";
		cout << " 3. Find an entry's number. \n 4. Change an entry's number.\n";
		cout << " 5. Display entire phone book. \n 6. Enter filename and save tree based on file. \n 0. Exit and save.\n";
		cout << "Enter the number corresponding with your selection: \n";
		cin >> choice;
		switch (choice) {
		case '1':
			Add();
			break;
		case '2':
			Delete();
			break;
		case '3':
			Find();
			break;
		case '4':
			Change();
			break;
		case '5':
			Display();
			break;
		case '6':
			cout << "Data must be in format LAST, FIRST, NUMBER. " << endl; //let user know how data will be read in as
			cout << "Enter filename: "; //enter filename for data to be read 
			cin >> fileinput;
			ReadPhonebook(fileinput); //read in data
			break;
		case '0':
			cout << "Enter filename to save current data: "; //enter file to save all data
			cin >> fileinput;
			SavePhonebook(fileinput); //call function 
			run = false; //break loop
			break;
		default:
			cout << "Please enter a valid choice. \n";
			break;
		}
	}

}

void UserInterface::ReadPhonebook(string fileinput) {
	// variable declarations
	fstream phonebook;
	string first, last, phonenumber = "";

	phonebook.open(fileinput); //open file

	if (phonebook.is_open()) { //while the file is open
		while (phonebook >> last >> first >> phonenumber) { //read in the last, first and phonenumber provided in txt
			if (last.find("LAST") == string::npos) { //Ignore entry if it is the identifier made by this program
				last.erase(remove(last.begin(), last.end(), ','), last.end()); //delete any commas in last
				first.erase(remove(first.begin(), first.end(), ','), first.end()); //delete any commas in first
				Person person = Person(first, last, phonenumber); //make a new person based on the input data
				book.tree.add(person); //add person to the book tree
			}
		}
		cout << "Data imported from " << fileinput << endl; //print message stating where the information is from 
		phonebook.close(); //close file
	}
	else {
		cout << "Cannot open file" << endl; //print if the file provided by user cannot be opened
	}
	return; //return
}

void UserInterface::SavePhonebook(string fileinput) {
	fstream myfile; //variable declaration 
	myfile.open(fileinput, fstream::out); //open file to read data out
	if (myfile.is_open()) { //while the file is open
		myfile << "LAST, FIRST, NUMBER\n"; //print the header provided helpful information to user 
		book.tree.savetree(book.tree.root, myfile); //go to function used to save data
		myfile.close(); //close file 
		cout << "Data saved to " << fileinput << endl; //print where data was saved
	}
	else { //if could not open file, print message
		cout << "Could not open file" << endl;
	}
	return; //return
}

void UserInterface::Add() {
	string first;
	string last;
	string number;
	cout << "What is the first name of the person you would like to add?\n";
	cin >> first;
	cout << "What is the last name of the person you would like to add?\n";
	cin >> last;
	cout << "What is the phone number of the person you would like to add? Enter without hyphens or spaces. \n";
	cin.ignore();
	getline(cin, number, '\n');

	while ((number.find("-") != string::npos) || (number.find(' ') != string::npos))
	{
		cout << "Renter without hyphens or spaces. \n";
		cin.ignore();
		getline(cin, number, '\n');
	}

	Person person = Person(first, last, number);
	book.tree.add(person);

}

void UserInterface::Delete() {
	string first;
	string last;
	cout << "What is the first name of the person whose phone number you would like to delete?\n";
	cin >> first;
	cout << "What is the last name of the person whose phone number you would like to delete?\n";
	cin >> last;

	struct key key;
	key.first = first;
	key.last = last;

	if (book.tree.find(key) == NULL) {
		cout << "No such person exists" << endl;

	}
	else {
		Person* p = book.tree.find(key);
		p->number = "";
		cout << first << " " << last << "'s number has been DELETED" << endl;

	}
}

void UserInterface::Find() {
	string first;
	string last;
	cout << "What is the first name of the person you would like to add?\n";
	cin >> first;
	cout << "What is the last name of the person you would like to add?\n";
	cin >> last;

	struct key key;
	key.first = first;
	key.last = last;

	if (book.tree.find(key) == NULL) {
		cout << "No such person exists" << endl;

	}
	else {
		Person* p = book.tree.find(key);
		cout << first << " " << last << "'s number is: " << p->number << endl;

	}



}

void UserInterface::Change() {
	string first;
	string last;
	string newNumber;
	cout << "What is the first name of the person for the phone number you would like to change?\n";
	cin >> first;
	cout << "What is the last name of the person for the phone number you would like to change?\n";
	cin >> last;
	cout << "Please input the new number\n";
	cin >> newNumber;
	struct key key;
	key.first = first;
	key.last = last;


	if (book.tree.find(key) == NULL) {
		cout << "No such person exists" << endl;

	}
	else {
		Person* p = book.tree.find(key);
		string oldNumber = p->number;
		p->number = newNumber;
		cout << first << " " << last << "'s number has been changed FROM: " << oldNumber << " TO: " << p->number << endl;

	}
	



}

void UserInterface::Display() {
	cout << "Displaying Full Book:" << endl;
	if (book.tree.root != NULL) {
		book.tree.display(book.tree.root);
	}
	cout << "------------------------------------------------------------------" << endl;
}
// END UI

//START MAIN

int main() {
	UserInterface UI;
	UI.Menu();
	cout << "Done! Press any key to exit...\n";
	cin.get();
	cin.ignore();
	return 0;
}