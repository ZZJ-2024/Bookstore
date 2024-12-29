#include "storage.h"
bool exist(string name) {
    fstream file;
    file.open(name,std::ios::in);
    bool res = file.is_open();
    file.close();
    return res;
}