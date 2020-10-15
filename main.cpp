#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
using namespace std;

//struct key -> used for finding
struct key {  //for bst     
	string first, last;
};

string toLowerString(string s) {
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

//START CLASS PERSON (the nodes for the BST)

class Person {
public:
	//Constructors
	Person(); // empty constructore
	Person(string first, string last, string num); //first name last name phone number constructor

	string printNameAndNumber(void); // Prints name and number. Returns "first last number" as a string

	string firstName;
	string lastName;
	string number;

	//for the BST of People
	Person* left; //left child
	Person* right; //right child
	Person* parent; //parent
};

string Person::printNameAndNumber() {
	cout << "NAME: " << lastName << ", " << firstName << "	NUMBER: " << number << endl;
	return (firstName + " " + lastName + " " + number);
}

Person::Person() {
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

	void remove(Person* leaf);

	bool isEmpty(void) { return (root == NULL); }; //a quick way to tell if the tree has elements
	Person* root; //root of tree

private:

	void add(Person person, Person* leaf); // recursive add function
	Person* find(key k, Person* leaf); //recursive search function

	//Person* remove(Person* leaf);
};

BinarySearchTree::BinarySearchTree() {
	root = NULL; //init head NULL
}


void BinarySearchTree::add(Person person) {
	if (root != NULL) { // If BST exists go into recursive call
		add(person, root);
	}
	else {
		root = new Person(person.firstName, person.lastName, person.number);
	}
}

// Public add already checks that root != null so it is not indcluded here
// This is the recursive add function that takes place after the public add
// It checks last and first names. The only case not covered is same first and last name
// This case is assumed to not occur per directions
void BinarySearchTree::add(Person person, Person *leaf) {

	//CASE 1: last to be inserted is alphabetically before last on current node
	if (toLowerString(person.lastName) < toLowerString(leaf->lastName)) {
		// If new last is less than the node and the left child isn't null, call add again for the left child
		if (leaf->left != NULL) {
			add(person, leaf->left);
		}
		else { // We have an open spot
			leaf->left = new Person(person.firstName, person.lastName, person.number); // Creates a Person In the Tree
			leaf->left->parent = leaf;
		}
	}
	//CASE 2: last to be inserted is alphabetically after last on current node
	else if (toLowerString(person.lastName) > toLowerString(leaf->lastName)) {
		// If new last is greater than the left last and the right child isn't null, call add again for the right child
		if (leaf->right != NULL) {
			add(person, leaf->right);
		}
		else { // We have an open spot
			leaf->right = new Person(person.firstName, person.lastName, person.number); // Creates a Person In the Tree
			leaf->right->parent = leaf;
		}
	}
	//CASE3
	// This is the case of the last names being the same. Repeat the above code but with first names
	// Cases where first and last are the same are ignored per instructions
	else {

		//CASE3a
		// first to be inserted is alphabetically before first on current node
		if (toLowerString(person.firstName) < toLowerString(leaf->firstName)) {
			// If new first is less than the node and the left child isn't null, recursively call insert again for the left child
			if (leaf->left != NULL) {
				add(person, leaf->left);
			}
			else { // We have an open spot
				leaf->left = new Person(person.firstName, person.lastName, person.number); // Creates a Person In the Tree
				leaf->left->parent = leaf;
			}
		}
		//CASE3b
		// first to be inserted is alphabetically after first on current node
		else {
			// If key is greater than the node and the right child isn't null, recursively call insert again for the right child
			if (leaf->right != NULL) {
				add(person, leaf->right);
			}
			else { // We have an open spot
				leaf->right = new Person(person.firstName, person.lastName, person.number); // Creates a Person in the Tree
				leaf->right->parent = leaf;
			}
		}
	}
}

// Removes an entry but doesn't keep in order
// Bonus action selected with '7' on menu
void BinarySearchTree::remove(Person* personDel){
	if (personDel != NULL) {
		Person* temp = personDel;
		// No children. Just delete
		if (personDel->left == NULL && personDel->right == NULL) {
			if (personDel == root) {
				root = nullptr;
			}
			else if (personDel->parent->right == NULL) {
				personDel->parent->left = nullptr;
			}
			else {
				personDel->parent->right = nullptr;
			}
			delete personDel;
			personDel = nullptr;
		}
		// One child on right. Replace old with child
		else if (personDel->left == NULL && personDel->right != NULL) {
			personDel = personDel->right;
			remove(personDel->right);
		}
		// One child on left. Replace old with child
		else if (personDel->left != NULL && personDel->right == NULL) {
			personDel = personDel->left;
			remove(personDel->left);
		}
		// Two children. Move values and delete successors
		else {
			personDel->firstName = personDel->right->firstName;
			personDel->lastName = personDel->right->lastName;
			personDel->number = personDel->right->number;
			remove(personDel->right);
		}	
	}
}


Person* BinarySearchTree::find(key k) { // Starts recusive function
	return find(k, root);
}

Person* BinarySearchTree::find(key k, Person* leaf) {
	if (leaf != NULL) {
		if ((k.last == leaf->lastName) && (k.first == leaf->firstName)) {
			return leaf; // Person is found. Return it
		}	
		else if (toLowerString(k.last) < toLowerString(leaf->lastName)) { // If last name is less than the leaf's
			return find(k, leaf->left); // Start a find() on the left child
		}
		else if (toLowerString(k.last) > toLowerString(leaf->lastName)) { // If last name is greater than the leaf's
			return find(k, leaf->right); // Start a find() on the right child
		}
		else { // Last names are the same. Check first names
			if (toLowerString(k.first) < toLowerString(leaf->firstName)) { // If first name is less than the leaf's
				return find(k, leaf->left); // Start a find() on the left child
			}
			else {
				return find(k, leaf->right); // Start a find() on the right child
			}
		}
	}
	else {
		return NULL; // The name was not found
	}
}

void BinarySearchTree::display(Person* leaf) { // Inorder traversal
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
	void Delete(); //removes number given name
	void Find(); // finds number given name
	void Change(); //change number given name
	void Display(); //dumps book

	void Remove(); // Deletes phonebook entry

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
		case '7':
			Remove();
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

// Removes a phone number from an entry
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

// Deletes an entry
void UserInterface::Remove() {
	string first;
	string last;
	cout << "What is the first name of the person whose entry you would like to delete?\n";
	cin >> first;
	cout << "What is the last name of the person whos entry you would like to delete?\n";
	cin >> last;

	struct key key;
	key.first = first;
	key.last = last;

	if (book.tree.find(key) == NULL) {
		cout << "No such person exists" << endl;

	}
	else {
		Person* p = book.tree.find(key);
		book.tree.remove(p);
		cout << first << " " << last << "'s entry has been DELETED" << endl;

	}
}

void UserInterface::Find() {
	string first;
	string last;
	cout << "What is the first name of the person you would like to find?\n";
	cin >> first;
	cout << "What is the last name of the person you would like to find?\n";
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