#ifndef MYSTRING_H
#define MYSTRING_H

class MyString {
public:
    MyString(const char* str = "");
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);
    MyString operator+(const char* str) const;
    MyString& operator+=(const char* str);
    bool operator==(const MyString& a)const;
    char operator[](int slot);
    char& operator*();
    const char& operator*()const;

    MyString erase(const char* valuesToErase) const;
    MyString fromPositionSubString(const int pos, const int len) const;
    MyString substring(int startingIndex, int endingIndex) const;
    bool empty();
    void append(const char* newString);
    void setString(char* strn);
    char* getString() const;
    void setLength(int size);
    int getLength() const;
    const char getCharAt(const int i) const;
    int findFirstOccurrence(const char* strn) const;
    int findLastOccurrence(const char* strn) const;
    int stringLength(const char* str) const;
    void concatenateStrings(char* dest, const char* src) const;
    void copyStrings(char* dest, const char* src);
    const int compare(const char* str1)const;
    const int stringByteSize() const;
    const int totalByteSize() const;

private:
    char* str;
    int length;
    void free();
    void copy(const MyString &s);
};


#endif // MYSTRING_H