#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;


//START PERSON (the nodes for the BST)

class Person {
public:
    Person();
    Person(string a, string b, string c);
    Person(Person *);
    string printFullName (void) {return (first + " " + last);}
    string printNumber (void) {return (number);}

    Person *left;
    Person *right;
    string first;
    string last;
    string number;
};

Person::Person() {
    first = "";
    last = "";
    number = "";
}

Person::Person(string a, string b, string c){
    first = a;
    last = b;
    number = c;
}

Person::Person(Person* leaf) { //this is for returning BST searches
    first = leaf->first;
    last = leaf ->last;
    number = leaf->number;
}

// START BST (THE BST lol)

class BinarySearchTree{
public:
    BinarySearchTree();

    void insert(string key);
    Person *search(string last);
    void destroy();
    bool treeInit (void) {return (root == NULL);};

private:
    
    void insert(string key, Person *leaf);
    Person *search(string key, Person *leaf);
    Person *root;
    
};

BinarySearchTree::BinarySearchTree(){
    root = NULL;
}

void BinarySearchTree::insert(string key){
    if(root != NULL){ // for when theres already a BST -> gonna call recursive
        insert(key, root);
    }
    else{
        root = new Person("", key, "");
        root -> left == NULL;
        root -> right == NULL;
    }
}

void BinarySearchTree::insert(string key, Person *leaf){ // THis is the recursivley calling insert function that takes place after the public insert function to check if there is even anything in the BST
    if(key < leaf->last){
        if( leaf->left != NULL){ // If key is less than the node and the left child isnt null, recursivley call insert again for the left child
            insert(key, leaf->left);
        }
        else{ // ding ding we got an open spot
            leaf->left = new Person("",key,""); // right now Im just get a BST going with last names
            leaf->left->left = NULL; //new Person left Person null
            leaf->left->right = NULL; //new Person rigt Perso null
        }
    }
    else if(key > leaf->last){
        if(leaf->right != NULL){
            insert(key, leaf->right); // If key is more than Person recursivley call insert but ths time use the person to the right
        }
        else{ //ding ding we got an open spot
            leaf->right = new Person("", key, ""); // new last name to the right child of the current comparison
            leaf->right->left = NULL; //new Person left person null
            leaf->right->right = NULL; //new person right person null
        }

    }
}



Person *BinarySearchTree::search(string key, Person *leaf){
    if(leaf != NULL){
        if(key == leaf->last){
            return leaf; //winner winner
        }
        if(key < leaf->last){ // if last name is less than the leaf
            return search(key, leaf->left); // we recursivley call search tp the left child
        }
        else{
            return search(key, leaf->right); // else we recursivley call search to the right child
        }
    }
    else{
        return NULL; //oopsie ur name aint in the book cheif
    }
}

Person *BinarySearchTree::search(string key){ //this guy starts so the recursive can go
    return search( key, root); // begin recursive
}


//START BOOK (1 level above from BST -> does some stuff in book context that would be clutter in bst class)

class Book{
public:
    Book();

    BinarySearchTree tree;

private:

    
    int numInserts;

};

Book::Book(){
    numInserts = 0;
}

//START UI (allows the user to give commands to the book)

class UI {
public:
    UI();

    void Add(Person p); //add name and number to book given person
    void Delete(string first, string last); //delete number given name
    string Find(string first, string last); //returns number given name
    void Change(string first, string last, string newnNumber); //chane number given name
    void Display(); //dumps book


private:
    
};


//START TEST OUTPUT

int main() {
    Person p1 = Person("John", "Wick", "2169260202");
    cout << "NAME: " << p1.printFullName() << " NUMBER: " << p1.printNumber() << endl;

    Book b1 = Book();
    bool testTree = b1.tree.treeInit();
    cout << testTree << endl;
    b1.tree.insert(p1.last);
    Person testSearch = Person(b1.tree.search(p1.last));
    cout << "NAME: " << testSearch.printFullName() << " NUMBER: " << testSearch.printNumber() << endl;


}