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
// bool exist(string name) ;
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
    indexEntry<data> index_get(data&target,vector<indexEntry<data>>&entries);
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
    vector<data> Get_show(data&find_data,vector<indexEntry<data>>&entries,vector<data>&);
    vector<data> get_data_show(data& find_data,indexEntry<data> &target,vector<indexEntry<data>>&entries,vector<data>&);
    fstream indexfile_storage;
    fstream datafile_storage;
private:
/*##需要构造最小数据(每一种数据类型都需要构造一个最小的数据）！！！*/
};
#include "storage.h"
#include"booksystem.h"
template<class data>
void storage<data>::Set(const string &name1, const string &name2) {
    if(!exist(name1))indexfile_storage.open(name1,std::ios::out);
    if(!exist(name2))datafile_storage.open(name2,std::ios::out);
    indexfile_storage.close();
    datafile_storage.close();
    indexfile_storage.open(name1,ios::binary|ios::in|ios::out);
    datafile_storage.open(name2,ios::binary|ios::in|ios::out);
    vector<indexEntry<data>>entries;
    indexfile_storage.seekg(0,std::ios::end);
    size_t file_size = indexfile_storage.tellg();
    size_t entry_size = sizeof(indexEntry<data>);
    size_t num_entries = file_size / entry_size;
    indexfile_storage.seekg(0,std::ios::beg);
    for(int i = 0;i < num_entries;i ++) {
        indexEntry<data> tmp;
        indexfile_storage.read(reinterpret_cast<char*>(&tmp),sizeof(indexEntry<data>));
        entries.push_back(tmp);
    }
}
template<class data>
storage<data>::~storage() {
    indexfile_storage.seekp(0,std::ios::beg);
    for(auto&index:entries) {
        indexfile_storage.write(reinterpret_cast<char*>(&index),sizeof(indexEntry<data>));
    }
    indexfile_storage.close();
    datafile_storage.close();
}

template<class data>
indexEntry<data> storage<data>::get_next(indexEntry<data>&target,vector<indexEntry<data>>&entries) {
    return entries[target.next];
}
template<class data>
indexEntry<data> storage<data>::index_get(data&target,vector<indexEntry<data>>&entries) {
    indexEntry<data> fail;
    fail.data_offset = 1;
    indexEntry<data> next_index ;
    int size = entries.size();
    if(size == 0)return fail;
    if(size > 0) {
        for(int i = 0;i < entries.size(); i ++) {
            if(i == 0)next_index = entries[0];
            if(i != 0)next_index = get_next(next_index,entries);
            if(target > next_index.max) {
                if(i == size - 1) {
                    return next_index;
                }

            }
            if(next_index.max > target) {
                return next_index;
            }
            if(next_index.max == target) {
                return next_index;
            }
        }
    }
    return fail;
}
template<class data>
indexEntry<data> storage<data>::create_index(vector<indexEntry<data>>&entries) {
    indexEntry<data> new_index;
    new_index.data_offset = entries.size() * M *sizeof(data);
    new_index.size = 0;
    new_index.position = entries.size();
    new_index.max = kv ;
/*##需要构造最小数据点*/
    entries.push_back(new_index);
    return new_index;
}
template<class data>
void storage<data>::block_fracture(indexEntry<data>& target,data&new_key_value,vector<indexEntry<data>>&entries) {
    indexEntry new_index = create_index(entries);
    // target.next = new_index.position;
    datafile_storage.seekg(target.data_offset);
    std::array<data , M>  database;
    database.fill(kv);
    std::array< data, M> database1 ;
    database1.fill(kv);
    std::array<data , M> database2;
    database2.fill(kv);
    datafile_storage.read(reinterpret_cast<char*>(&database),sizeof(database));
    for(int i = 0;i < 190;i++) {
        database1[i] = database[i];
    }

    for(int i = 0;i < 190;i++) {
        database2[i] = database[i + 190];
    }
    datafile_storage.seekp(target.data_offset);
    datafile_storage.write(reinterpret_cast<char*>(&database1),sizeof(database1));
    datafile_storage.seekp(new_index.data_offset);
    datafile_storage.write(reinterpret_cast<char*>(&database2),sizeof(database2));
    target.max = database1[189];
    target.size  = 190;
    new_index.max = database2[189];
    new_index.size = 190;
    new_index.last = target.position;
    if(target.next != -1) {
        new_index.next = target.next;
        indexEntry next_pre = get_next(target,entries);
        next_pre.last = new_index.position;
        target.next = new_index.position;
        entries[next_pre.position] = next_pre;
    }
    if(target.next == -1) {
        target.next = new_index.position;
    }
    entries[target.position] = target;
    entries[new_index.position] = new_index;
}
template<class data>
void storage<data>::insert_data(data& insert_key_value,indexEntry<data>&target,vector<indexEntry<data>>&entries) {
    if(insert_key_value > target.max)target.max = insert_key_value;
    std::array<data , M> database ;
    database.fill(kv);
    datafile_storage.seekg(target.data_offset);
    datafile_storage.read(reinterpret_cast<char*>(&database),sizeof(database));
    bool insert = false;
    auto it = std::lower_bound(database.begin(), database.begin() + target.size, insert_key_value);
    // if(*it == insert_key_value)return;
    for (int i = target.size; i > (it - database.begin()); --i) {
        database[i] = database[i - 1];
    }
    *it = insert_key_value;
    datafile_storage.seekp(target.data_offset);
    datafile_storage.write(reinterpret_cast<char*>(&database),sizeof(database));
    target.size++;
    entries[target.position] = target;
}
template<class data>
void storage<data>::insertData(data& insert_key_value,vector<indexEntry<data>>&entries) {
    indexEntry target = index_get( insert_key_value,entries);
    if(target.data_offset != 1) {
        if(target.size >= 380) {
            block_fracture(target,insert_key_value,entries);
            indexEntry new_index_entry = index_get(insert_key_value,entries);
            insert_data(insert_key_value,new_index_entry,entries);
        }//裂块处理
        else if(380 > target.size) {
            insert_data(insert_key_value,target,entries);
        }//裂块处理

    }
    else{
        indexEntry new_index = create_index(entries);
        std::array<data,M> database ;
        database.fill(kv);
        database[0] = insert_key_value;
        new_index.max = insert_key_value;
        datafile_storage.seekp(new_index.data_offset);
        datafile_storage.write(reinterpret_cast<char*>(&database),sizeof(database));
        new_index.size++;
        entries[new_index.position] = new_index;
    }
}
template<class data>
bool storage<data>::delete_data(indexEntry<data>& target_index,data&delete_key_value,vector<indexEntry<data>>&entries) {
    std::array<data , M> database;
    database.fill(kv);
    datafile_storage.seekg(target_index.data_offset);
    datafile_storage.read(reinterpret_cast<char*>(&database),sizeof(database));
    auto it = lower_bound(database.begin(),database.begin()+target_index.size,delete_key_value);
    if(it != database.begin() + target_index.size ) {
        if(*it == delete_key_value) {
            *it = database[target_index.size - 1] ;
            database[target_index.size - 1] = kv;
            sort(database.begin(),database.begin()+ target_index.size  - 1);
            target_index.size --;
            if(target_index.size > 0) {
                target_index.max = database[target_index.size - 1];
            }
            if(target_index.size == 0) {
                target_index.max = kv;
            }
            entries[target_index.position] = target_index;
            datafile_storage.seekp(target_index.data_offset);
            datafile_storage.write(reinterpret_cast<char*>(&database),sizeof(database));
            return true;
        }
    }

    return false;
}
template<class data>
void storage<data>::deleteData(data&delete_key_value,vector<indexEntry<data>>&entries) {
    indexEntry target = index_get(delete_key_value,entries);
    if(target.data_offset != 1) {
        delete_data(target,delete_key_value,entries);
    }
}
template<class data>
data storage<data>::Get(data&find_data,vector<indexEntry<data>>&entries) {
    indexEntry<data> target = index_get(find_data,entries);
    if(target.data_offset == 1) {
        return kv;
    }
    else {
        return get_data(find_data,target,entries);
    }
}
template<class data>
data storage<data>::get_data(data& find_data,indexEntry<data> &target,vector<indexEntry<data>>&entries) {
    if(target.size == 0) {
        indexEntry next_index_entry = get_next(target,entries);
        get_data(find_data,next_index_entry,entries);
    }
    else {
        std::array<data , M> database;
        datafile_storage.seekg(target.data_offset);
        datafile_storage.read(reinterpret_cast<char*>(&database),sizeof(database));
        auto it = std::lower_bound(database.begin(), database.begin() + target.size,find_data );
        if(*it == find_data) {
            return *it;
        }
        return kv;
    }
}
template<class data>
bool storage<data>::find_data(data& finddata,indexEntry<data> &target,vector<indexEntry<data>>&entries) {
    if(target.size == 0) {
        indexEntry next_index_entry = get_next(target,entries);
        find_data(finddata,next_index_entry,entries);
    }
    else {
        std::array<data , M> database;
        datafile_storage.seekg(target.data_offset);
        datafile_storage.read(reinterpret_cast<char*>(&database),sizeof(database));
        auto it = std::lower_bound(database.begin(), database.begin() + target.size,finddata );
        if(*it == finddata) {
            return true;
        }
        return false;
    }
}
template<class data>
bool storage<data>::Find(data&finddata,vector<indexEntry<data>>&entries) {
    indexEntry<data> target = index_get(finddata,entries);
    if(target.data_offset == 1) {
        return false;
    }
    else {
        return find_data(finddata,target,entries);
    }
}
template<class data>
vector<data> storage<data>::get_data_show(data& find_data,indexEntry<data> &target,vector<indexEntry<data>>&entries,vector<data>&store) {
    if(target.size == 0) {
        indexEntry next_index_entry = get_next(target,entries);
        return get_data_show(find_data,next_index_entry,entries,store);
    }
    else {
        std::array<data , M> database;
        datafile_storage.seekg(target.data_offset);
        datafile_storage.read(reinterpret_cast<char*>(&database),sizeof(database));
        auto it = std::lower_bound(database.begin(), database.begin() + target.size,find_data );
        for(auto i = it - database.begin();i <target.size;i++ ) {
        if(database[i] == find_data) {
             store.push_back(database[i]);
        }
         if( find_data < database[i])break;
         if(i == target.size - 1) {
             if(target.next != -1){
                indexEntry next_index_entry = get_next(target,entries);
               return  get_data_show(find_data,next_index_entry,entries,store);
             }
           }
         }
        return store;
    }
}
template<class data>
vector<data> storage<data>::Get_show(data&find_data,vector<indexEntry<data>>&entries,vector<data>& store) {
    indexEntry<data> target = index_get(find_data,entries);
    if(target.data_offset == 1) {
        return store;
    }
    else {
        return get_data_show(find_data,target,entries,store);
    }
}



#endif //STORAGE_H
