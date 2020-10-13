#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

//struct key (for the BST)
struct key {  //for bst     
        string first, last;       
    };
    
//START PERSON (the nodes for the BST)

class Person {
public:
    Person();
    Person(string a, string b, string c);
    string printFullName (void) {return (k.first + " " + k.last);}
    string printNumber (void) {return (number);}

    
    struct key k;

    string number;

    Person *left;
    Person *right;
    
};

Person::Person() {
    k.first = "";
    k.last = "";
    number = "";

}

Person::Person(string a, string b, string c){
    k.first = a;
    k.last = b;
    number = c;
    
}

 /*Person::Person(Person *) { //this is for returning BST searches
    
    leaf->k.first;
}  */

// START BST (THE BST lol)

class BinarySearchTree{
public:
    BinarySearchTree();
    void insert(struct key k);
    Person *search(key k);
    
    bool treeInit (void) {return (root == NULL);};
    string test;

private:
    
    void insert(struct key k, Person *leaf);
    Person *search(key k, Person *leaf);
    Person *root;
    
};

BinarySearchTree::BinarySearchTree(){
    root = NULL;
    test = "test";
}

void BinarySearchTree::insert(struct key k){
    if(root != NULL){ // for when theres already a BST -> gonna call recursive
        insert(k, root);
    }
    else{
        root = new Person();
        root -> k.first = k.first;
        root -> k.last = k.last;
        if (false){
            //insert number here eventually?
        }

    }
}

void BinarySearchTree::insert(struct key k, Person *leaf){ // THis is the recursivley calling insert function that takes place after the public insert function to check if there is even anything in the BST
    if(k.last < leaf->k.last){ //If what we are inserting is less than the Person we plugged
        if( leaf->left != NULL){ // If key is less than the node and the left child isnt null, recursivley call insert again for the left child
            insert(k, leaf->left);
        }
        else{ // ding ding we got an open spot
            leaf->left = new Person(k.first,k.last,""); // Creates a Person In the Tree
            leaf->left->left = NULL; //new Person left Person null
            leaf->left->right = NULL; //new Person rigt Perso null
        }
    }
    else if(k.last > leaf->k.last){ //If what we are inserting is greater than the Person we plugged
        if( leaf->right != NULL){ // If key is greater than the node and the right child isnt null, recursivley call insert again for the left child
            insert(k, leaf->right);
        }
        else{ // ding ding we got an open spot
            leaf->right = new Person(k.first,k.last,""); // Creates a Person In the Tree
            leaf->left->left = NULL; //new Person left Person null
            leaf->left->right = NULL; //new Person rigt Perso null
        }
    }
    else{
        //this is the case of the last names being the same, time to repeat the above code but with first names

        if(k.first < leaf->k.first){ //If what we are inserting is less than the Person we plugged
            if( leaf->left != NULL){ // If key is less than the node and the left child isnt null, recursivley call insert again for the left child
                insert(k, leaf->left);
            }
            else{ // ding ding we got an open spot
                leaf->left = new Person(k.first,k.last,""); // Creates a Person In the Tree
                leaf->left->left = NULL; //new Person left Person null
                leaf->left->right = NULL; //new Person rigt Perso null
            }
        }
        else { 
            if( leaf->right != NULL){ // If key is greater than the node and the right child isnt null, recursivley call insert again for the left child
                insert(k, leaf->right);
            }
            else{ // ding ding we got an open spot
                leaf->right = new Person(k.first,k.last,""); // Creates a Person In the Tree
                leaf->left->left = NULL; //new Person left Person null
                leaf->left->right = NULL; //new Person rigt Perso null
            }
        }
        
        
    }
}



Person *BinarySearchTree::search(key k, Person *leaf){
    if(leaf != NULL){
        if((k.last == leaf->k.last)&&(k.first == leaf->k.first)){
            return leaf; //winner winner
        }
        else if(k.last < leaf->k.last){ // if last name is less than the leaf
            return search(k, leaf->left); // we recursivley call search tp the left child
        }
        else if(k.last > leaf->k.last){ // if last name is greater than the leaf
            return search(k, leaf->right); // we recursivley call search tp the righ child
        }
        else{ // here we go its first name time
            if(k.first < leaf->k.first){ // if last name is less than the leaf
                return search(k, leaf->left); // we recursivley call search tp the left child
            }
            else{
                 return search(k, leaf->right); // we recursivley call search tp the righ child
            }
        }
    }
    else{
        return NULL; //oopsie ur name aint in the book cheif
    }
}

Person *BinarySearchTree::search(key k){ //this guy starts so the recursive can go
    return search( k, root); // begin recursive
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

    string testFirst = p1.number; //number grab given Person
    cout << testFirst << endl; //number output

    BinarySearchTree tree = BinarySearchTree(); //declare empty binary search tree

    string testTree = tree.test;
    cout << testTree << endl; //tests that the tree was declared properly


    

    tree.insert(p1.k); //inserts ya boy John Wick

    struct key k;  //making a dummy struct to search for John Wick
    k.first = p1.k.first;
    k.last = p1.k.last;

    cout << k.first << endl; // print first name of struct key

    //NEXT TASK -> PRINT THE ENTIRE TREE

    tree.search(k)->printFullName(); // this is here to show you that search is still a bit of a WIP-> may change slightly based on technique for printing tree

    //the rest of the comments below are useless

   // string searchForNumberThroughTreeGivenKey = tree.search(k)->number; // search for his number using the key struct
   // cout << searchForNumberThroughTreeGivenKey << endl;

    
    
    
    //tree.insert(p1); // Inserts a person into the tree

    

    //this struct function will likley be used again for searching (thinking Book function)
    

    //Given a struct, search a Tree
  //  Person* testSearch = tree.search(k);
  //  cout << "NAME: " << testSearch->printFullName() << " NUMBER: " << testSearch->printNumber() << endl;


  //  Book b1 = Book();
   // bool testTree = b1.tree.treeInit();
   // cout << testTree << endl;
   // b1.tree.insert(p1.last);
   // Person testSearch = Person(b1.tree.search(p1.last));
    // cout << "NAME: " << testSearch.printFullName() << " NUMBER: " << testSearch.printNumber() << endl;


}