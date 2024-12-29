#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<array>
#include <cmath>
#include<sstream>
#include<cstdio>
#include "booksystem.h"
using namespace std;
const int M = 400;
template<class data>
struct indexEntry {
    size_t size;
    size_t data_offset;
    size_t position;
    data max;
    int last = -1;
    int next = -1;
};
bool exist(string name) ;
template <class data>
class storage{
public:
    data kv;
    vector<indexEntry<data>>entries;
    storage() = default;
    ~storage();
    void Set(const string & name1,const string & name2);
    indexEntry<data> get_next(indexEntry<data>&target,vector<indexEntry<data>>&entries);
    indexEntry<data> index_get(data&taget,vector<indexEntry<data>>&entries);
    indexEntry<data> create_index(vector<indexEntry<data>>&entries) ;
    void block_fracture(indexEntry<data>&target,data&,vector<indexEntry<data>>&entries);
    void insert_data(data&,indexEntry<data>&,vector<indexEntry<data>>&);
    void insertData(data&,vector<indexEntry<data>>&);
    bool delete_data(indexEntry<data>&,data&,vector<indexEntry<data>>&);
    void deleteData(data&delete_key_value,vector<indexEntry<data>>&entries);
    data Get(data&find_data,vector<indexEntry<data>>&entries);
    bool Find(data&find_data,vector<indexEntry<data>>&entries);
    bool find_data(data& find_data,indexEntry<data> &target,vector<indexEntry<data>>&entries);
    data get_data(data& find_data,indexEntry<data> &target,vector<indexEntry<data>>&entries);
    void cout_all();

private:
    fstream indexfile_storage;
    fstream datafile_storage;

/*##需要构造最小数据(每一种数据类型都需要构造一个最小的数据）！！！*/
};


#endif //STORAGE_H
