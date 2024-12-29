#include"tools.h"
void TokenScanner::Initialize(const string &original) {
    line = original;
    pos = 0;
    len = original.size();
}
bool TokenScanner::HasMoreToken() {
    bool check = false;
    for (int i = pos; i < len; i++) {
        if (line[i] != ' ') {
            check = true;
            break;
        }
    }
    return check;
}
std::string TokenScanner::NextToken() {
    while(pos < len && (line[pos] == ' ')) {
        pos++;
    }
    string token = "";
    while(pos < len && line[pos] != ' ') {
        token += line[pos];
        pos++;
    }
    return token;
}
std::string TokenScanner::Left() {
    return line.substr(pos);
}
size_t Size_t(const string & str) {
    int len = str.size();
    size_t tmp = 0;
    for(int i = 0;i < len;i++) {
        tmp = tmp * 10 + (str[i] - '0');
    }
    return tmp;
}
double Double(const string & str) {
    double tmp = 0.00;
    int len = str.size();
    int pos = 0;
    for(; pos < len;pos++) {
        if(str[pos] != '.') {
            tmp = tmp * 10 + (str[pos] - '0');
        }
        if(str[pos] == '.')break;
    }
    pos++;
    double base = 10.00;
    for(;pos < len;pos++) {
        tmp += (str[pos] - '0') / base;
        base *= 10.00;
    }
    return  tmp;
}
bool is_id_password(const string & str) {
    bool flag = true;
    int len = str.size();
    if(str.size() > 30)flag = false;
    for(int i = 0;i < len;i++) {
        if(!isalnum(str[i]) && str[i] != '_') {
            flag = false;
        }
    }
    return flag;
}
bool is_name(const string & str) {
    int len = str.size();
    if(len > 30)return  false;
    return  true;
}
bool is_privilege(const string &str) {
    int len = str.size();
    if(len > 1)return false;
    if(!isdigit(str[0]))return false;
    return true;
}
bool is_isbn(const string &str) {
    int len = str.size();
    if(len > 20)return  false;
    return  true;
}
bool is_bookname_author(const string &str) {
    bool flag = true;
    int len = str .size();
    if(len > 60)flag = false;
    for(char ch: str) {
        if(ch < 32 || ch > 126) flag = false;
        if(ch == '"')flag = false;
    }
    return flag;
}
bool is_keyword(const string &str) {
    bool flag = true;
    int len = str.size();
    if(len > 60)flag = false;
    for(char ch : str) {
        if(!(ch >= 32 && ch <= 126)|| ch =='"') {
            flag = false;
        }
    }
    istringstream stream(str);
    string keyword;
    while(getline(stream,keyword,'|')) {
        if(keyword.empty()) {
            flag = false;
        }
    }
    return flag;
}
bool is_quantity(const string &str) {
    bool flag = true;
    int len = str.size();
    if(len > 10)flag = false;
    for(char ch : str) {
        if(!isdigit(ch))flag = false;
    }
    return flag;
}
bool is_price_totalcost(const string &str) {
    int len = str.size();
    bool flag = true;
    bool dot_found = false;
    if(len > 13)flag = false;
    for(int i = 0;i < len;i++) {
        if(!isdigit(str[i]) && str[i] != '.') {
            flag = false;
            break;
        }
        if (str[i] == '.') {
            if (dot_found) {
                flag = false;
                break;
            }
            dot_found = true;
            if (i == len - 1 || i == len - 2) {
                flag = false;
                break;
            }
        }
    }
    return  flag;
}
bool is_count(const string &str) {
    bool flag = true;
    int len = str.size();
    if(len > 10)flag = false;
    for(char ch : str) {
        if(!isdigit(ch))flag = false;
    }
    return flag;
}
void TokenScanner::skip_index() {
    for(;pos < line.length();pos++) {
        if(line[pos] == '=') {
            break;
        }
    }
    pos++;
}
char* string_to_char(const string & str,int M) {
    int len = str.length();
    char* chararray = new char[M];
    for(int i = 0; i < len;i++) {
        chararray[i] = str[i];
    }
    chararray[len] = '\0';
    return chararray;
}
string skip_string (string & a) {
    string tmp;
    auto it = a.find('=');
    it++;
    tmp = a.substr(it);
}
string char_to_string(char* a,int size) {
    string m;
    for(int i = 0;i < size;i++) {
        m += a[i];
    }
    return m;
}
vector<string> split_string(const string& input, char delimiter) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}
void errorcout() {
    cout<<"Invalid\n";
}

