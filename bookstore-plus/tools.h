#ifndef TOOLS_H
#define TOOLS_H
#include<string>
#include<iostream>
#include<cctype>
#include<vector>
#include <sstream>
using namespace std;
void errorcout() ;
size_t Size_t(const string &);
double Double(const string &);
bool is_id_password(const string & str);
bool is_name(const string & str);
bool is_privilege(const string & str);
bool is_isbn(const string & str);
bool is_bookname_author(const string & str);
bool is_keyword(const string & str);
bool is_quantity(const string & str);
bool is_price_totalcost(const string & str);
bool is_count(const string & str);
char* string_to_char(const string & str,int M);
string skip_string (string & a) ;
string char_to_string(char* a,int size);
vector<string> split_string(const string & input,char delimiter);
class TokenScanner {
public:
    TokenScanner() = default;
    void Initialize(const string & original);
    bool HasMoreToken();
    std::string NextToken();
    string Left();
    void skip_index();
private:
    string line;
    int pos;
    int len;
};
#endif //TOOLS_H
