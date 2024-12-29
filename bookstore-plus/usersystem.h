#ifndef USERSYSTEM_H
#define USERSYSTEM_H
#include <iostream>
#include<string>
#include<sstream>
#include<vector>
#include "tools.h"
#include "storage.h"
using namespace std;
const string USERINDEX = "USERINDEX";
const string USER = "USER";
struct user {
    char Userid[30]={};
    char Password[30] = {};
    char UserName[30] = {};
    int Privilege = 0;
    bool operator < (const user & other) const {
        return  Userid < other.Userid;
    }
    bool operator >  (const user & other) const {
        return  Userid > other.Userid;
    }
    bool operator == (const user & other) const {
        return  Userid == other.Userid;
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
    user user_now;
    user empty{"empty"};
public:
    usersystem();
    void Su(const string &line);
    void Logout();
    void Register(const string & line);
    void Passwd(const string & line);
    void UserAdd(const string & line);
    void Delete(const string & line);
    login& get_login_now() {
        return login_now.back();
    }

};
#endif //USERSYSTEM_H
