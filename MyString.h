#ifndef MYSTRING_H
#define MYSTRING_H

class MyString {
public:
    void free();

    void copy(const MyString &s);

    MyString(const char* str = "");
    MyString(const MyString& other);
    ~MyString();

    MyString& operator=(const MyString& other);
    MyString operator+(const char* str) const;
    MyString& operator+=(const char* str);

    char operator[](int slot);

    bool operator==(const MyString& other) const;

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

    const int stringByteSize();

    const int totalByteSize();

    const int stringByteSize() const;
    const int totalByteSize() const;

    int findFirstOccurrence(const char* strn) const;
    int findLastOccurrence(const char* strn) const;
    int stringLength(const char* str) const;
    void concatenateStrings(char* dest, const char* src) const;

    void copyStrings(char *dest, const char *src);

    void copyStrings(char* dest, const char* src) const;

private:
    char* str;
    int length;

};

bool operator==(const MyString& a, const MyString& b);

#endif // MYSTRING_H