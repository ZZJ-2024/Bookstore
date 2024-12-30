#ifndef BOOKSYSTEM_H
#define BOOKSYSTEM_H
#include <complex.h>
#include<string>
#include<iostream>
#include<vector>
#include<iomanip>
#include"storage.h"
#include "logsystem.h"
#include<set>
#include"tools.h"
#include "usersystem.h"
using namespace std;
class usersystem;
class logsystem;
const string ISBN = "ISBN";
const string BOOKNAME = "BOOKNAME";
const string AUTHOR = "AUTHOR";
const string KEYWORD = "KEYWORD";
const string ISBN_ID = "ISBN_ID";
const string BOOKNAME_ID = "BOOKNAME_ID";
const string AUTHOR_ID = "AUTHOR_ID";
const string KEYWORD_ID = "KEYWORD_ID";
const string ID = "ID";
const string BOOK = "BOOK";
struct book {
    char ISBN[21] = {};
    char BookName[61] = {};
    char Author[61] = {};
    char Keyword[61] = {};
    size_t Quantity = 0;
    double Price = 0.00;
    double TotalCost = 0.00;
    vector<string> Keywords;
    bool operator<(const book & other) const {
        return string(ISBN) < string(other.ISBN);
    }
    bool operator ==(const book & other) const {
        return string(ISBN) == string(other.ISBN);
    }
    bool operator > (const book & other) const {
        return string(ISBN) > string(other.ISBN);
    }
};
void print(const book&);
struct id_book {
    long long id = -1;
    book book_store;
    bool operator<(const id_book & other) const {
        return id < other.id;
    }
    bool operator ==(const id_book & other) const {
        return id == other.id;
    }
    bool operator > (const id_book & other) const {
        return id > other.id;
    }
};
struct isbn_id {
    char ISBN[20] = {};
    long long id= -1;
    bool operator < (const isbn_id & other) const {
            return string(ISBN) < string(other.ISBN);
    }
    bool operator > (const isbn_id & other) const {
            return string(ISBN) > string(other.ISBN);
    }
    bool operator == (const isbn_id & other) const {
        if(string(ISBN)!= string(other.ISBN))return false;
        return true;
    }
};
struct bookname_id {
    char BookName[60] = {};
    long long id= -1;
    bool operator < (const bookname_id & other) const {
            return string(BookName) < string(other.BookName);
    }
    bool operator > (const bookname_id & other) const {
            return string(BookName) > string(other.BookName);
    }
    bool operator == (const bookname_id & other) const {
        if(string(BookName) != string(other.BookName))return false;
        return true;
    }
};
struct author_id {
    char Author[60] = {};
    long long id= -1;
    bool operator < (const author_id & other) const {
            return string(Author) < string(other.Author);
    }
    bool operator > (const author_id & other) const {
            return string(Author) > string(other.Author);
    }
    bool operator == (const author_id & other) const {
        if(string(Author) != string(other.Author))return false;
        return true;
    }
};
struct keyword_id {
    char Keyword[60] = {};
    long long id= -1;
    bool operator < (const keyword_id & other) const {
        return string(Keyword) < string(other.Keyword);
    }
    bool operator > (const keyword_id & other) const {
        return string(Keyword) > string(other.Keyword);
    }

    bool operator == (const keyword_id & other) const {
        if(string(Keyword) != string(other.Keyword))return false;
        return true;
    }
};

class booksystem {
public:
    booksystem();
    void Show(const string & line,usersystem&);
    void Buy(const string &,logsystem&,usersystem&);
    void Select(const string & ,usersystem&);
    void Modify(const string & line,usersystem&);
    void Import(const string &line,usersystem&,logsystem&);
    void cout_all();
private:
    TokenScanner scanner;
    long long book_amount = 0;
    string isbn_select = "";
    storage<isbn_id> isbn_ids;
    storage<bookname_id> bookname_ids;
    storage<author_id> author_ids;
    storage<keyword_id> keyword_ids;
    storage<id_book>id_books;
};
#endif //BOOKSYSTEM_H
