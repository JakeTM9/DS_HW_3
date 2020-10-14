#include <iostream>
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

	string saveFullName(void);
	string saveNumber(void);

	string firstName;
	string lastName;

    string number; // for number storage


    //for the BST of People
    Person *left; //left child
    Person *right; //right child
    
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

Person::Person() {
	firstName, lastName, number = "";
}

Person::Person(string first, string last, string num){
	firstName = first;
	lastName = last;
    number = num;
}

// START BST Class

class BinarySearchTree{
public:
    BinarySearchTree();
	void add(Person person);
    Person *find(key k); //nonrecursive search function
	void display(Person *leaf);
	void savetree(Person *leaf, fstream &myfile);
	string fullname;
	string number;

    bool isEmpty (void) {return (root == NULL);}; //a quick way to tell if the tree has elements
    string test; //another quick way to debug tree constructor
	Person *root; //root of tree

private:

	void add(Person person, Person *leaf); // recursive add function
    Person *find(key k, Person *leaf); //recursive search function
    
};

BinarySearchTree::BinarySearchTree(){
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

void BinarySearchTree::add(Person person, Person *leaf) { // This is the recursively calling insert function that takes place after the public insert function to check if there is even anything in the BST

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

Person *BinarySearchTree::find(key k, Person *leaf){
    if(leaf != NULL){
        if((k.last == leaf->lastName)&&(k.first == leaf->firstName)){
            return leaf; //winner winner
        }
        else if(k.last < leaf->lastName){ // if last name is less than the leaf
            return find(k, leaf->left); // we recursively call search tp the left child
        }
        else if(k.last > leaf->lastName){ // if last name is greater than the leaf
            return find(k, leaf->right); // we recursively call search tp the righ child
        }
        else{ // here we go its first name time
            if(k.first < leaf->firstName){ // if last name is less than the leaf
                return find(k, leaf->left); // we recursively call search tp the left child
            }
            else{
                 return find(k, leaf->right); // we recursively call search tp the righ child
            }
        }
    }
    else{
        return NULL; //oopsie ur name aint in the book cheif
    }
}


Person *BinarySearchTree::find(key k){ //this guy starts so the recursive can go
    return find( k, root); // begin recursive
}

void BinarySearchTree::display(Person *leaf) {
	if (leaf != NULL) {
		display(leaf->left);
		leaf->printFullName();
		leaf->printNumber();
		display(leaf->right);
	}
}

void BinarySearchTree::savetree(Person *leaf, fstream &myfile) {
	if (myfile.is_open()) {
		if (leaf != NULL) {
			savetree(leaf->left, myfile);
			myfile << leaf->firstName << " " << leaf->lastName << " " << leaf->number << endl;
			savetree(leaf->right, myfile);
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
    //void Delete(); //delete number given name
    void Find(); // ??
    //void Change(); //change number given name
    //void Display(); //dumps book

private:
    
};

UserInterface::UserInterface() {}

void UserInterface::Menu(){
	bool run = true;
	char choice;
	string fileinput;

	//continuous loop to enable multiple uses
	while (run) {
		cout << "What would you like to do? \n 1. Add a new entry. \n 2. Delete an entry.\n";
		cout << "3. Find an entry's number. \n 5. Change an entry's number.\n";
		cout << "6. Display entire phone book. \n 7. Enter filename and save tree based on file. \n 0. Exit and save.\n";
		cout << "Enter the number corresponding with your selection: \n";
		cin >> choice;
		switch (choice) {
		case '1':
			Add();
			break;
		case '2':
			//Delete();
			break;
		case '3':
			Find();
			break;
		case '4':
			//Change();
			break;
		case '5':
			//Display();
			break;
		case '7':
			cout << "Enter filename: ";
			cin >> fileinput;
	//		fileinput = "/Users/Andi/GIT/DS_HW_3/phonebook.txt"; //DELETE
			ReadPhonebook(fileinput);
			break;
		case '0':
			cout << "Enter filename to save current data: ";
			cin >> fileinput;
	//		fileinput = "/Users/Andi/GIT/DS_HW_3/mydata.txt"; //DELETE
			SavePhonebook(fileinput);
			run = false;
			break;
		default:
			cout << "Please enter a valid choice. \n";
			break;
		}
	}

}

void UserInterface::ReadPhonebook(string fileinput) {
	fstream phonebook;
	string first, last, phonenumber = "";

	phonebook.open(fileinput);

	if (phonebook.is_open()) {
		while (phonebook >> first >> last >> phonenumber) {
			Person person = Person(first, last, phonenumber);
			book.tree.add(person);
		}
		cout << "Data imported from " << fileinput << endl;
		phonebook.close();
	}
	else {
		cout << "Cannot open file" << endl;
	}
	return;
}

void UserInterface::SavePhonebook(string fileinput) {
	fstream myfile;
	myfile.open(fileinput, fstream::out);
	if (myfile.is_open()) {
		book.tree.savetree(book.tree.root, myfile);
		myfile.close();
	} 
	else {
		cout << "Could not open file" << endl;
	}
	cout << "Data saved to " << fileinput << endl;
	return;
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
	book.tree.find(key); // returns person. not sure what to do.
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