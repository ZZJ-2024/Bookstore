#ifndef USERSYSTEM_H
#define USERSYSTEM_H
#include <iostream>
#include<string>
#include<cstring>
#include<sstream>
#include<vector>
#include "tools.h"
#include "storage.h"
using namespace std;
const string USERINDEX = "USERINDEX";
const string USER = "USER";
struct user {
    char Userid[31]={};
    char Password[31] = {};
    char UserName[31] = {};
    int Privilege = 0;
    bool operator < (const user & other) const {
        return  string(Userid) < string ( other.Userid);
    }
    bool operator >  (const user & other) const {
        return  string(Userid) > string(other.Userid);
    }
    bool operator == (const user & other) const {
        return  string(Userid) ==string (other.Userid);
    }
    user& operator = (const user&other) {
        if (this != &other) {
            std::strcpy(Userid, other.Userid);
            std::strcpy(Password, other.Password);
            std::strcpy(UserName, other.UserName);
            Privilege = other.Privilege;
        }
        return *this;
    }
};
struct login {
    string id = "";
    long long privilege;
    bool if_select = false;
    string select = "";
    bool operator==(const login &other) const {
        return id == other.id;
    }
    bool operator<(const login &other) const {
        return id < other.id;
    }
    bool operator>(const login &other) const {
        return id > other.id;
    }

};
class usersystem {
private:
    storage<user> userstorage;
    vector<login> login_now;
    TokenScanner scanner;
    user empty{"empty"};
    user user_now = empty ;
public:
    usersystem();
    ~usersystem();
    void Su(const string &line);
    void Logout();
    void Register(const string & line);
    void Passwd(const string & line);
    void UserAdd(const string & line);
    void Delete(const string & line);
    int login_number() {
        return login_now.size();
    }
    login& get_login_now() {
        return login_now.back();
    }
    void Clear() {
        login_now.clear();
    }

};
#endif //USERSYSTEM_H
