#include<iostream>
#include "MyString.h"

using namespace std;

void MyString::free() {
    if (str != nullptr)
        delete[] str;
}

void MyString::copy(const MyString& s) {
    length = s.length;
    str = new char[length + 1];
    copyStrings(str, s.str);
}

MyString::MyString(const char* s) {
    length = stringLength(s);
    str = new char[length + 1];
    copyStrings(str, s);
}

MyString::MyString(const MyString& other) {
    copy(other);
}

MyString::~MyString() {
    cout << "In destructor" << endl;
    free();
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

MyString& MyString::operator+=(const char* stringToAdd) {
    MyString temp = (*this);

    length = length + stringLength(stringToAdd);
    char* tempStr = new char[length + 1];

    copyStrings(tempStr, str);
    concatenateStrings(tempStr, stringToAdd);
    delete[] temp.str;
    temp.str = tempStr;
    *this = temp;

    return *this;
}
bool MyString::operator==(const MyString& a) {
    MyString b = (*this);
    bool notEqual = true;
    for (int i = 0; i < a.getLength(); i++) {
        if (a.getCharAt(i) != b.getCharAt(i)) {
            notEqual = false;
        }
    }
    return notEqual;
}

char MyString::operator[](int slot) {
    if (slot < 0 || slot > length)
        throw runtime_error("Index out of bounds");
    return str[slot];
}

int MyString::stringLength(const char* str) const {
    if (str == nullptr)
        throw invalid_argument("Null pointer passed in on stringLength");

    int count = 0;
    while (*str) {
        count++;
        str++;
    }
    return count;
}

void MyString::concatenateStrings(char* dest, const char* src) const {
    while (*dest) {
        dest++;
    }

    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void MyString::copyStrings(char* dest, const char* src) {
    if (dest == nullptr || src == nullptr)
        throw invalid_argument("Null pointer provided to copyString");
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void MyString::append(const char* newString) {
    if (newString == nullptr)
        throw invalid_argument("Nullptr passed into append");
    *this += newString;
}

int MyString::findFirstOccurrence(const char* strn) const {
    if (strn == nullptr || str == nullptr)
        throw invalid_argument("Nullptr passed into findFirstOccurence");

    int lenOfWordToFind = stringLength(strn);
    int lenOfOriginalWord = length;

    if (lenOfOriginalWord == 0 || lenOfWordToFind == 0 || lenOfOriginalWord < lenOfWordToFind) {
        return -1;
    }

    for (int i = 0; i < lenOfOriginalWord; i++) {
        int j = 0;
        bool notRightLetter = false;
        if (strn[0] == str[i]) {
            while (j < lenOfWordToFind && !notRightLetter) {
                if (strn[j] != str[i + j]) {
                    notRightLetter = true;
                }
                j++;
            }
            if (!notRightLetter) {
                return i;
            }
        }
    }

    return -1;
}

int MyString::findLastOccurrence(const char* strn) const {
    if (str == nullptr || strn == nullptr)
        throw invalid_argument("Nullptr passed into findLastOccurence");
    int pos = -1;
    int lenOfWordToFind = stringLength(strn);
    int lenOfOriginalWord = length;

    if (lenOfOriginalWord == 0 || lenOfWordToFind == 0 || lenOfOriginalWord < lenOfWordToFind) { //Validates the data
        return -1;
    }
//Takes the way the characters that would not work due to size at the end of the list, then searches from the back.
    for (int i = lenOfOriginalWord - lenOfWordToFind; i >= 0; i--) { //Looks for the last occurrence of the input
        int j = 0;
        bool notRightLetter = false;
        if (strn[0] == str[i]) {
            while (j < lenOfWordToFind && !notRightLetter) {
                if (strn[j] != str[i + j]) {
                    notRightLetter = true;
                }
                j++;
            }
            if (!notRightLetter) {
                pos = i;
                return pos;
            }
        }
    }
    return pos;
}

MyString MyString::fromPositionSubString(const int pos, const int len) const {
    if (pos < 0 || pos > length) {
        throw runtime_error("Position out of bounds");
    }
    if (len > length || len < 0) {
        throw runtime_error("Length is out of bounds");
    }
    char* temp = new char[len + 1];
    int index = 0;
    for (int i = 0; i < len; i++) {
        temp[i] = str[pos + i];
    }
    temp[len] = '\0';
    MyString newString(temp);
    delete[] temp;
    return newString;
}

MyString MyString::substring(int startingIndex, int endingIndex) const {
    if (endingIndex > length || startingIndex < 0 || startingIndex >= endingIndex) {
        return MyString("");
    }
    int subLength = endingIndex - startingIndex;
    MyString subString;
    subString.str = new char[subLength + 1];
    for (int i = 0; i < subLength; i++) {
        subString.str[i] = this->str[startingIndex + i];
    }
    subString.str[subLength] = '\0';
    subString.setLength(subLength);
    return subString;
}

bool MyString::empty() {
    return length == 0;
}

MyString MyString::erase(const char* valuesToErase) const {
    const int lengthOfErase = stringLength(valuesToErase);
    char* temp = new char[length + 1];
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
    MyString newString(temp);
    delete[] temp;
    return newString;
}

void MyString::setString(char* strn) {
    this->str = strn;
}

char* MyString::getString() const {
    return str;
}

void MyString::setLength(int size) {
    length = size;
}

int MyString::getLength() const {
    return length;
}

const char MyString::getCharAt(const int i) const {
    return str[i];
}

const int MyString::stringByteSize() const {
    return sizeof(char) * (length + 1);
}

const int MyString::totalByteSize() const{
    return sizeof(this) + sizeof(char) * length + 1;
}

