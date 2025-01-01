#ifndef LOGSYSTEM_H
#define LOGSYSTEM_H
#include <iostream>
#include<string>
#include<sstream>
#include<vector>
#include<fstream>
#include "tools.h"
#include "storage.h"
#include"usersystem.h"
class usersystem;
using namespace std;
const string LOGDATA = "LOGDATA";
class logsystem {
public:
        logsystem();
        ~logsystem();
        long long count;
        void ShowCount(size_t & count,usersystem &);
        void Show(usersystem &);
        void Earn(const double&);
        void Revenue(const double&);

private:
        vector<double> record;
        double income ;
        double revenue ;
        fstream datafile;
        long long records ;
};
#endif //LOGSYSTEM_H
