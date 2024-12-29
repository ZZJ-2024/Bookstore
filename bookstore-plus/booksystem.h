#ifndef BOOKSYSTEM_H
#define BOOKSYSTEM_H
#include<string>
#include<iostream>
#include<vector>
#include<iomanip>
#include"storage.h"
#include "logsystem.h"
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
    char ISBN[20] = {};
    char BookName[60] = {};
    char Author[60] = {};
    char Keyword[60] = {};
    size_t Quantity = 0;
    double Price = 0.00;
    double TotalCost = 0.00;
    vector<string> Keywords;
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
        if(ISBN != other.ISBN) {
            return ISBN < other.ISBN;
        }
        else {
            return id < other.id;
        }
    }
    bool operator > (const isbn_id & other) const {
        if(ISBN != other.ISBN) {
            return ISBN > other.ISBN;
        }
        else {
            return id > other.id;
        }
    }
    bool operator == (const isbn_id & other) const {
        if(ISBN != other.ISBN)return false;
        if(id != other.id)return false;
        return true;
    }
};
struct bookname_id {
    char BookName[60] = {};
    long long id= -1;
    bool operator < (const bookname_id & other) const {
        if(BookName != other.BookName) {
            return BookName < other.BookName;
        }
        else {
            return id < other.id;
        }
    }
    bool operator > (const bookname_id & other) const {
        if(BookName != other.BookName) {
            return BookName > other.BookName;
        }
        else {
            return id > other.id;
        }
    }
    bool operator == (const bookname_id & other) const {
        if(BookName != other.BookName)return false;
        if(id!= other.id)return false;
        return true;
    }
};
struct author_id {
    char Author[60] = {};
    long long id= -1;
    bool operator < (const author_id & other) const {
        if(Author != other.Author) {
            return Author < other.Author;
        }
        else {
            return id < other.id;
        }
    }
    bool operator > (const author_id & other) const {
        if(Author != other.Author) {
            return Author > other.Author;
        }
        else {
            return id > other.id;
        }
    }
    bool operator == (const author_id & other) const {
        if(Author != other.Author)return false;
        if(id!= other.id)return false;
        return true;
    }
};
struct keyword_id {
    char Keyword[60] = {};
    long long id= -1;
    bool operator < (const keyword_id & other) const {
        if(Keyword != other.Keyword) {
            return Keyword < other.Keyword;
        }
        else {
            return id < other.id;
        }
    }
    bool operator > (const keyword_id & other) const {
        if(Keyword != other.Keyword) {
            return Keyword > other.Keyword;
        }
        else {
            return id > other.id;
        }
    }
    bool operator == (const keyword_id & other) const {
        if(Keyword != other.Keyword)return false;
        if(id!= other.id)return false;
        return true;
    }
};

class booksystem {
public:
    booksystem();
    void Show(const string & line);
    void Buy(const string &,logsystem&);
    void Select(const string & ,usersystem&);
    void Modify(const string & line,usersystem&);
    void Import(const string &line,usersystem&,logsystem&);

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
