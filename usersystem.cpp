#include"usersystem.h"
usersystem::usersystem() {
    userstorage.Set(USERINDEX,USER);
    user_now.Privilege = 0;
    user root{"root","sjtu","",7};
    if(!userstorage.Find(root,userstorage.entries)) {
        userstorage.insertData(root,userstorage.entries);
    }
}
usersystem::~usersystem() {

}
void usersystem::Register(const string &line) {
    scanner.Initialize(line);
    string su;
    su = scanner.NextToken();
    string userid;
    string password;
    string username;
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    else {
        userid = scanner.NextToken();
    }
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    else {
        password = scanner.NextToken();
    }
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    else {
        username = scanner.NextToken();
    }
    if(!is_id_password(userid)||!is_id_password(password)||!is_name(username)) {
        errorcout();
        return;
    }
    if(scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    user find;
    int len1 = userid.length();
    for(int i = 0 ; i < len1 ;i ++) {
        find.Userid[i] = userid[i];
    }
    find.Userid[len1] = '\0';
    if(userstorage.Find(find,userstorage.entries)) {
        errorcout();
        return;
    }
    else {
        int len2 = password.length();
        for(int i = 0 ; i < len2 ;i ++) {
            find.Password[i] = password[i];
        }
        find.Password[len2] = '\0';
        int len3 = username.length();
        for(int i = 0 ; i < len3 ;i ++) {
            find.UserName[i] = username[i];
        }
        find.UserName[len3] = '\0';
        find.Privilege = 1;
        userstorage.insertData(find,userstorage.entries);
    }
}
void usersystem::UserAdd(const string &line) {
    if(get_login_now().privilege < 3) {
        errorcout();
        return;
    }
    scanner.Initialize(line);
    string useradd;
    useradd = scanner.NextToken();
    string userid;
    string password;
    string privilege;
    string username;
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    else {
        userid = scanner.NextToken();
    }
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    else {
        password = scanner.NextToken();
    }
     if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    else {
        privilege = scanner.NextToken();
    }
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    else {
        username = scanner.NextToken();
    }
    if(!is_id_password(userid)||!is_id_password(password)||!is_name(username)||!is_privilege(privilege)) {
        errorcout();
        return;
    }
    user find;
    int len1 = userid.length();
    for(int i = 0 ; i < len1 ;i ++) {
        find.Userid[i] = userid[i];
    }
    find.Userid[len1] = '\0';
    if(userstorage.Find(find,userstorage.entries)) {
        errorcout();
        return;
    }
    else {
        int len2 = password.length();
        for(int i = 0 ; i < len2 ;i ++) {
            find.Password[i] = password[i];
        }
        find.Password[len2] = '\0';
        int len3 = username.length();
        for(int i = 0 ; i < len3 ;i ++) {
            find.UserName[i] = username[i];
        }
        find.UserName[len3] = '\0';
        find.Privilege = privilege[0] - '0';
        if(find.Privilege >= user_now.Privilege) {
            errorcout();
            return;
        }
        if(find.Privilege != 1&&find.Privilege  != 3&&find.Privilege!= 7) {
            errorcout();
            return;
        }
        userstorage.insertData(find,userstorage.entries);

    }
}
void usersystem::Passwd(const string &line) {
    if(login_now.size() == 0) {
        errorcout();
        return;
    }
    if(get_login_now().privilege < 1) {
        errorcout();
        return;
    }
    scanner.Initialize(line);
    string passwd = scanner.NextToken();
    string userid;
    string currentpassword;
    string newpassword;
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    userid = scanner.NextToken();
    if(!is_id_password(userid)) {
        errorcout();
        return;
    }
    if(user_now.Privilege == 7) {
        if(!scanner.HasMoreToken()) {
            errorcout();
            return;
        }
        newpassword = scanner.NextToken();
        if(!is_id_password(newpassword)) {
            errorcout();
            return;
        }
        user find;
        int len1 = userid.length();
        for(int i = 0 ; i < len1 ;i ++) {
            find.Userid[i] = userid[i];
        }
        find.Userid[len1] = '\0';
        find = userstorage.Get(find,userstorage.entries);
        userstorage.deleteData(find,userstorage.entries);
        if(find == userstorage.kv) {
            errorcout();
            return;
        }
        int len2 = newpassword.length();
        for(int i = 0; i < len2;i ++) {
            find.Password[i] = newpassword[i];
        }
        find.Password[len2] = '\0';
        userstorage.insertData(find,userstorage.entries);
    }
    if(user_now.Privilege != 7) {
        if(!scanner.HasMoreToken()) {
            errorcout();
            return;
        }
        currentpassword = scanner.NextToken();
        if(!is_id_password(currentpassword)) {
            errorcout();
            return;
        }
        if(!scanner.HasMoreToken()) {
            errorcout();
            return;
        }
        newpassword = scanner.NextToken();
        if(!is_id_password(newpassword)) {
            errorcout();
            return;
        }
        user find;
        int len1 = userid.length();
        for(int i = 0 ; i < len1 ;i ++) {
            find.Userid[i] = userid[i];
        }
        find.Userid[len1] = '\0';
        find = userstorage.Get(find,userstorage.entries);
        if(find == userstorage.kv) {
            errorcout();
            return;
        }

        if(string(find.Password) != string(currentpassword)) {
                errorcout();
                return;
        }

        userstorage.deleteData(find,userstorage.entries);
        int len2 = newpassword.length();
        for(int i = 0; i < len2;i ++) {
            find.Password[i] = newpassword[i];
        }
        find.Password[len2] = '\0';
        userstorage.insertData(find,userstorage.entries);
    }

}
void usersystem::Su(const string &line) {

    scanner.Initialize(line);
    string su;
    string userid;
    string password;
    su = scanner.NextToken();
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    userid = scanner.NextToken();
    if(!is_id_password(userid)) {
        errorcout();
        return;
    }
    user find;
    int len = userid.length();
    for(int i = 0; i < len;i++) {
        find.Userid[i] = userid[i];
    }
    find.Userid[len] = '\0';
    find = userstorage.Get(find,userstorage.entries);
/*##找到账号信息*/
    if(find == userstorage.kv) {
        errorcout();
        return;
    }
    if(user_now.Privilege >find.Privilege ) {
        login new_login;
        new_login.id = userid;
        new_login.privilege = find.Privilege;
        // auto it = std::find(login_now.begin(),login_now.end(),new_login);
        // if(it != login_now.end()) {
        //     std::iter_swap(it,login_now.end()-1);
        //     login_now.back() = new_login;
        // }
        // else {
            login_now.push_back(new_login);
        // }
        user_now = find;
    }
    else {
        if(!scanner.HasMoreToken()) {
            errorcout();
            return;
        }
        password = scanner.NextToken();
        if(!is_id_password(password)) {
            errorcout();
            return;
        }

        if(string(find.Password) != string(password)) {
                errorcout();
                return;
        }

        login new_login;
        new_login.id = userid;
        new_login.privilege = find.Privilege;
        // auto it = std::find(login_now.begin(),login_now.end(),new_login);
        // if(it != login_now.end()) {
        //     std::iter_swap(it,login_now.end()-1);
        //     login_now.back() = new_login;
        // }
        // else {
            login_now.push_back(new_login);
        // }
        user_now = find;
    }
}
void usersystem::Delete(const string &line) {
    if(get_login_now().privilege < 7) {
        errorcout();
        return;
    }
    scanner.Initialize(line);
    string delete_ = scanner.NextToken();
    string userid;
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    else {
        userid = scanner.NextToken();
    }
    if(!is_id_password(userid)) {
        errorcout();
        return;
    }
    user find;
    int len1 = userid.length();
    for(int i = 0 ; i < len1 ;i ++) {
        find.Userid[i] = userid[i];
    }
    find.Userid[len1] = '\0';
    if(!userstorage.Find(find,userstorage.entries)) {
        errorcout();
        return;
    }
    login login_find;
    login_find.id = userid;
    auto it = std::find(login_now.begin(),login_now.end(),login_find);
    if(it != login_now.end()) {
        errorcout();
        return;
    }
    userstorage.deleteData(find,userstorage.entries);
}
void usersystem::Logout() {
    if(login_now.size() == 0) {
        errorcout();
        return;
    }
    if(get_login_now().privilege < 1) {
        errorcout();
        return;
    }
    login_now.pop_back();
    if(login_now.size() ==  0) {
        user_now = empty;
    }
    else {
        login to_login = login_now.back();
        string id = to_login.id;
        user find;
        int len1 = id.length();
        for(int i = 0 ; i < len1 ;i ++) {
            find.Userid[i] = id[i];
        }
        find.Userid[len1] = '\0';
        find = userstorage.Get(find,userstorage.entries);
        user_now = find;

    }
}
void usersystem::change_select(const string &original, const string new_isbn) {
    for(auto &it : login_now) {
        if(it.select == original) {
            it.select = new_isbn;
        }
    }
}



