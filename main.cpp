#include"MyString.h"
#include<iostream>
using namespace std;

int main(){

    MyString m("xv");
    MyString n("Hello World");
    int pos = n.findLastOccurrence("l");
    cout<< pos<< endl;
    n.append(m.getString());
    cout<< n.getString()<< endl;

    //delete[] sub; //Have to use the [] to deallocate the whole array. Without the [] it only deletes the first value since pointers point to the first value of the array
    return 0;
}