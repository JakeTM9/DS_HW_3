#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;



class Person {
public:
    Person();
    Person(string a, string b, string c);
    string printFullName (void) {return (first + " " + last);}
    string printNumber (void) {return (number);}

private:
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

int main() {
    Person p1 = Person("John", "Wick", "2169260202");
    cout << "NAME: " << p1.printFullName() << " NUMBER: " << p1.printNumber() << endl;

}