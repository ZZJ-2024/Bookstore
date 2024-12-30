#ifndef LOGSYSTEM_H
#define LOGSYSTEM_H
#include <iostream>
#include<string>
#include<sstream>
#include<vector>
#include<fstream>
#include "tools.h"
#include "storage.h"
using namespace std;
const string LOGDATA = "LOGDATA";
class logsystem {
public:
        logsystem();
        ~logsystem();
        long long count;
        void ShowCount(size_t & count);
        void Show();
        void Earn(const double&);
        void Revenue(const double&);

private:
        vector<double> record;
        double income = 0.00;
        double revenue = 0.00;
        fstream datafile;
        long long records = 0;
};
#endif //LOGSYSTEM_H
