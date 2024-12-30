#include <iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"booksystem.h"
#include "logsystem.h"
#include"usersystem.h"
using namespace  std;
logsystem Logsystem;
usersystem UserSystem;
booksystem BookSystem;
int main() {
    string line;
    TokenScanner scanner;
    while(getline(cin,line)) {
        scanner.Initialize(line);
        string command;
        command = scanner.NextToken();
        if(command == "quit" || command == "exit") {
            UserSystem.Clear();
            return 0;
        }
        else if(command == "su") {
            UserSystem.Su(line);
        }
        else if(command == "logout") {
            UserSystem.Logout();
        }
        else if(command == "register") {
            UserSystem.Register(line);
        }
        else if(command == "passwd") {
            UserSystem.Passwd(line);
        }
        else if(command == "useradd") {
            UserSystem.UserAdd(line);
        }
        else if(command == "delete") {
            UserSystem.Delete(line);
        }
        else if(command == "show") {
            string command2 = scanner.NextToken();
            string command3 ;
            if(command2 == "finance") {
                if(!scanner.HasMoreToken()) {
                    Logsystem.Show();
                }
                else {
                    command3 = scanner.NextToken();
                    if(!is_count(command3)) {
                        errorcout();
                    }
                    size_t count = Size_t(command3);
                    Logsystem.ShowCount(count);
                }
                /*##需要补充LOGSYSTEM的show函数,以及和图书系统购入售出相关的记录*/
            }
            else {
                BookSystem.Show(line,UserSystem);
            }
        }
        else if(command == "buy") {
            BookSystem.Buy(line,Logsystem,UserSystem);
        }
        else if(command == "select") {
            BookSystem.Select(line,UserSystem);
        }
        else if(command == "modify") {
            BookSystem.Modify(line,UserSystem);
        }
        else if(command == "import") {
            BookSystem.Import(line,UserSystem,Logsystem);
        }
        else if(command == "log") {

        }
        else if(command == "report") {
            if(scanner.NextToken() == "finance") {}
            if(scanner.NextToken() == "employee"){}
        }
        else if(command == "eof") {
            break;
        }
        else if(command == "") {
            break;
        }
        else {
            errorcout();
        }
    }
    return 0;
}
