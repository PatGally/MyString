#include<iostream>
#include <cstring>
using namespace std;

class MyString {
  private:
    char* str;
    int length;

  void free() {
    if(str != nullptr)
      delete[] str;
  }

  void copy(const MyString& s) {
    length = s.length;
    str = new char[length + 1];
    copyStrings(str, s.str);
  }

  public:
    MyString(const char* s = ""){ //the s is assigned to a default value of "" if nothing is passed in
      length = strlen(s);
      str = new char[length+ 1];  //+1 makes space for the terminator \0
      copyStrings(str, s);
    }
    MyString(const MyString& other){  //copy constructor
      copy(other);
    }
    ~MyString(){
      cout<<"In destructor"<<endl;
      free();
    }

  MyString& operator=(const MyString& other) {
      if (this != &other) {
        free();
        copy(other);
      }
      return *this;
    }
  MyString operator+=(const char* stringToAdd) {
      MyString temp = (*this);

      length =  length + strlen(stringToAdd);
      char* tempStr = new char[length + 1];

      copyStrings(tempStr, str);
      concatenateStrings(tempStr, stringToAdd);
      delete[] temp.str;
      temp.str = tempStr;
      *this = temp;

      return *this;
    }
  char operator[](int slot){
    if (slot < 0 || slot > length)
      throw runtime_error("Index out of bounds");
    return str[slot];
    }
  void concatenateStrings(char* dest, const char* src) {
      while (*dest) {
        dest++;   //Increment to end of the original string;
      }

      while (*src) {
        *dest = *src;     //Add to the end of the original string, modifying it
        dest++;
        src++;
      }
      *dest = '\0';   //End string with terminator
    }
  void copyStrings(char* dest, const char* src) {
      if (dest == nullptr || src == nullptr)
        throw invalid_argument("Null pointer provided to copyString");
      while (*src) {
        *dest = *src;
        dest++;
        src++;
      }
      *dest = '\0';
    }
  MyString fromPositionSubString(const int pos, const int len) {
      if (pos < 0 || pos > length) {
        throw runtime_error("Position out of bounds");
      }
      if (len > length || len < 0) {
        throw runtime_error("Length is out of bounds");
      }
      char* temp = new char[len + 1]; //Buffer String
      int index = 0;
      for (int i = 0; i < len; i++) {
        temp[i] = str[pos + i];
      }
      temp[len] = '\0';
      MyString newString(temp); //Create MyString object
      delete[] temp;  //Deallocate buffer
      return newString;
    }

  MyString substring(int startingIndex, int endingIndex) const{
      if (endingIndex > length || startingIndex < 0 || startingIndex >= endingIndex) {
        return MyString("");
      }
      int subLength = endingIndex - startingIndex;  //Do not add the +1 here, so u can use this for placing the terminator at end of list
      MyString subString;
      subString.str = new char[subLength + 1];  //Need to add the plus 1 here in order to make room for proper termination of the string. Without, it causes undefined behavior
      for (int i = 0; i < subLength; i++) {
        subString.str[i] = this -> str[startingIndex + i];
      }
      subString.str[subLength] = '\0';  //Terminates the string
      subString.setLength(subLength);
      return subString;
    }

    bool empty() {
      if (length == 0) return true;
      return false;
    }

    MyString erase(const char* valuesToErase) const{
      const int lengthOfErase = strlen(valuesToErase);    //Use strlen since it is not an array and a pointer
      char* temp= new char[length + 1]; //assigns the str member variable a size
      int index = 0;
      for (int i = 0; i < length; i++) {
        bool notFound = true;
        for (int j = 0; j < lengthOfErase; j++) {
          if (this->str[i] == valuesToErase[j]) {
            notFound = false;
            break;
          }
        }
        if (notFound) {
          temp[index] = str[i];
          index++;
        }
      }
      temp[index] = '\0';
      MyString newString(temp); //Create object based off the buffer string that was created
      delete[] temp;  //Deallocate the buffer
      return newString;
    }
    void setString( char* strn) {
      this -> str = strn;
    }
    char* getString() const{
      return str;
    }
    void setLength(int size) {
      length = size;
    }
    int getLength() const{
      return length;
    }
    const char getCharAt(const int i) const{
      return str[i];
    }
    const int stringByteSize() {
      return sizeof(char) *(length+1);
    }
    const int totalByteSize() {
      return sizeof(this) + sizeof(char) * length + 1;
    }

};

bool operator == (const MyString& a, const MyString& b) {
  cout<< "In == operator" << endl;
  bool notEqual = true;
  for (int i = 0; i < a.getLength(); i++) {
    if (a.getCharAt(i) != b.getCharAt(i)) {
      notEqual = false;
    }
  }
  return notEqual;
}

int main(){

  MyString m("xv");
  MyString n("hello");
  n = n.fromPositionSubString(4,1);
  cout<< n.getString()<<  endl;
  //MyString n(m);  // Explicitly calls the copy constructor
  if (m == n) cout<< "true";
  else cout << "false"<< endl;

  MyString sub = n.substring(0,2 );
  cout<<"Sub: " << sub.getString()<< endl;

  MyString str("Hello");
 // cout<< str.getString()<< endl;
  char* cs = new char[str.getLength() + 1];
  str.copyStrings(cs, str.getString());
  cout<<"Hell " << cs<<endl;
  delete[] cs;
  //delete[] sub; //Have to use the [] to deallocate the whole array. Without the [] it only deletes the first value since pointers point to the first value of the array
  return 0;
}
