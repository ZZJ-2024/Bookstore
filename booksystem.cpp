#include"booksystem.h"
booksystem::booksystem()
{
    isbn_ids.Set(ISBN,ISBN_ID);
    bookname_ids.Set(BOOKNAME,BOOKNAME_ID);
    author_ids.Set(AUTHOR,AUTHOR_ID);
    keyword_ids.Set(KEYWORD,KEYWORD_ID);
    id_books.Set(ID,BOOK);
    if(!exist("book_amount"))bookamount.open("book_amount",std::ios::out);
    bookamount.close();
    bookamount.open("book_amount",ios::binary|ios::in|ios::out);
    bookamount.seekg(0,std::ios::end);
    if(bookamount.tellg() == 0) {
        book_amount = 0;
    }
    else {
        bookamount.seekg(0,std::ios::beg);
        bookamount.read(reinterpret_cast<char*>(&book_amount),sizeof(long long ));
    }
}
booksystem::~booksystem() {
    bookamount.seekp(0,std::ios::beg);
    bookamount.write(reinterpret_cast<char*>(&book_amount),sizeof(long long ));
    bookamount.close();
}

void print(const book & book1) {
    for(int i = 0;i < 20;i++) {
        if(book1.ISBN[i] == '\0') {
            break;
        }
        cout<<book1.ISBN[i];
    }
    cout<<"\t";
    for(int i = 0;i < 60;i++) {
        if(book1.BookName[i] == '\0') {
            break;
        }
        cout<<book1.BookName[i];
    }
    cout<<"\t";
    for(int i = 0;i < 60;i ++) {
        if(book1.Author[i] == '\0') {
            break;
        }
        cout<<book1.Author[i];
    }
    cout<<"\t";
    for(int i = 0 ;i < 60;i++) {
        if(book1.Keyword[i] == '\0') {
            break;
        }
        cout<<book1.Keyword[i];
    }
    cout<<"\t";
    cout << std::fixed << std::setprecision(2) <<book1.Price;
    cout<<"\t";
    cout<<book1.Quantity<<endl;
}
void booksystem::Show(const string &line,usersystem&UserSystem) {
  if(UserSystem.login_number() == 0) {
      errorcout();
      return;
  }
  if(UserSystem.get_login_now().privilege <1) {
        errorcout();
        return;
    }
    scanner.Initialize(line);
    string show;
    show = scanner.NextToken();
    if(!scanner.HasMoreToken()) {
        cout_all();
    }
    if(scanner.HasMoreToken()) {
        string original;
        original = scanner.NextToken();
        string index = skip_string(original);
        if(original[1] == 'I') {
            if(index.length() != 0) {
                isbn_id find;
                int len = index.length();
                for(int i = 0;i < 20;i ++) {
                    find.ISBN[i] = index[i];
                }
                find.ISBN[len] = '\0';
                find = isbn_ids.Get(find,isbn_ids.entries);
                if(find == isbn_ids.kv) {
                    cout<<endl;
                }
                else {
                    id_book tmp;
                    tmp.id = find.id;
                    tmp = id_books.Get(tmp,id_books.entries);
                    print(tmp.book_store);
                }
            }
            else {
                errorcout();
                return;
            }
        }
        if(original[1] == 'n') {
            if(index.length() != 0) {
                index =index.substr(1,index.length()-2);
                vector<bookname_id> finds;
                bookname_id find;
                int len = index.length();
                for(int i = 0;i < len;i ++) {
                    find.BookName[i] = index[i];
                }
                find.BookName[len] = '\0';
                finds = bookname_ids.Get_show(find,bookname_ids.entries,finds);
                if(finds.size() == 0) {
                    cout<<endl;
                }
                else {
                    std::set<book> cout_books;
                    for(auto it : finds) {
                        id_book find_id_book;
                        find_id_book.id = it.id;
                        find_id_book = id_books.Get(find_id_book,id_books.entries);
                        cout_books.insert(find_id_book.book_store);
                    }
                    for(auto it: cout_books) {
                        print(it);
                    }
                }
            }
            else {
                errorcout();
                return;
            }
        }
        if(original[1] == 'a') {
            if(index.length() != 0){
                if(index.length() != 0) {
                    index =index.substr(1,index.length()-2);
                    vector<author_id> finds;
                    author_id find;
                    int len = index.length();
                    for(int i = 0;i < len;i ++) {
                        find.Author[i] = index[i];
                    }
                    find.Author[len] = '\0';
                    finds = author_ids.Get_show(find,author_ids.entries,finds);
                    if(finds.size() == 0) {
                        cout<<endl;
                    }
                    else {
                        std::set<book> cout_books;
                        for(auto it : finds) {
                            id_book find_id_book;
                            find_id_book.id = it.id;
                            find_id_book = id_books.Get(find_id_book,id_books.entries);
                            cout_books.insert(find_id_book.book_store);
                        }
                        for(auto it: cout_books) {
                            print(it);
                        }
                    }
                }
                else {
                    errorcout();
                    return;
                }
            }
        }
            if(original[1] == 'k') {
                if(index.length() != 0){
                    if(index.length() != 0) {
                        index =index.substr(1,index.length()-2);
                        vector<keyword_id> finds;
                        keyword_id find;
                        int len = index.length();
                        for(int i = 0;i < len;i ++) {
                            find.Keyword[i] = index[i];
                        }
                        find.Keyword[len] = '\0';
                        finds = keyword_ids.Get_show(find,keyword_ids.entries,finds);
                        if(finds.size() == 0) {
                            cout<<endl;
                        }
                        else {
                            std::set<book> cout_books;
                            for(auto it : finds) {
                                id_book find_id_book;
                                find_id_book.id = it.id;
                                find_id_book = id_books.Get(find_id_book,id_books.entries);
                                cout_books.insert(find_id_book.book_store);
                            }
                            for(auto it: cout_books) {
                                print(it);
                            }
                        }
                    }
                    else {
                        errorcout();
                        return;
                    }
                }
            }

    }
}
void booksystem::Select(const string & line, usersystem &usersystem) {
    if(usersystem.login_number() == 0) {
        errorcout();
        return;
    }
    if(usersystem.get_login_now().privilege < 3) {
        errorcout();
        return;
    }
    scanner.Initialize(line);
    string select_;
    select_ = scanner.NextToken();
    string isbn;
    isbn = scanner.NextToken();
    if(!is_isbn(isbn)) {
        errorcout();
        return;
    }
    if(scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    isbn_id find ;
    int len =  isbn.length();
    for(int i = 0; i < len;i++) {
        find.ISBN[i] = isbn[i];
    }
    find.ISBN[len] = '\0';
    find = isbn_ids.Get(find,isbn_ids.entries);
    if(find == isbn_ids.kv) {
        long long book_id = book_amount;
        book_amount++;
        book store;
        int len = isbn.length();
        for(int i = 0 ; i <len;i++) {
            store.ISBN[i] = isbn[i];
        }
        store.ISBN[len] = '\0';
        id_book insert1;
        insert1.id = book_id;
        insert1.book_store = store;
        id_books.insertData(insert1,id_books.entries);
        isbn_id insert2;
        insert2.id = book_id;
        for(int i = 0 ; i <len;i++) {
            insert2.ISBN[i] = isbn[i];
        }
        insert2.ISBN[len] = '\0';
        isbn_ids.insertData(insert2,isbn_ids.entries);
        usersystem.change_select(isbn);
        /*usersystem.get_login_now().if_select = true;
        usersystem.get_login_now().select = isbn;*/
    }
    else {
        usersystem.change_select(isbn);
        /*usersystem.get_login_now().if_select = true;
        usersystem.get_login_now().select = isbn;*/
    }
}
void booksystem::Buy(const string & line,logsystem&Logsystem,usersystem&UserSystem) {
    if(UserSystem.login_number() == 0 ) {
        errorcout();
        return;
    }
    if(UserSystem.get_login_now().privilege <1) {
        errorcout();
        return;
    }
    scanner.Initialize(line);
    string buy = scanner.NextToken();
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    string isbn = scanner.NextToken();
    if(!is_isbn(isbn)) {
        errorcout();
        return;
    }
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    string quantity = scanner.NextToken();
    if(!is_quantity(quantity)) {
        errorcout();
        return;
    }
    isbn_id find;
    int len = isbn.length();
    for(int i = 0 ; i <len;i++) {
        find.ISBN[i] = isbn[i];
    }
    find.ISBN[len] = '\0';
    find = isbn_ids.Get(find,isbn_ids.entries);
    if(find == isbn_ids.kv) {
        errorcout();
        return;
    }
    else {
        long long  id = find.id;
        id_book tmp;
        tmp.id = id;
        tmp = id_books.Get(tmp,id_books.entries);
        size_t quantity_number = Size_t(quantity);
        if(tmp.book_store.Quantity < quantity_number) {
            errorcout();
            return;
        }
        else {
            tmp.book_store.Quantity -= quantity_number;
            double earnmoney = quantity_number *  tmp.book_store.Price;
            cout<< std::fixed << std::setprecision(2) <<earnmoney<<endl;
            Logsystem.Earn(earnmoney);
            id_books.deleteData(tmp,id_books.entries);
            id_books.insertData(tmp,id_books.entries);
        }
    }
}
void booksystem::Modify(const string &line,usersystem&usersystem) {
    if(usersystem.login_number() == 0) {
        errorcout();
        return;
    }
    if(usersystem.get_login_now().privilege < 3) {
        errorcout();
        return;
    }
    login & now_login = usersystem.get_login_now();
    if(now_login.if_select == false) {
        errorcout();
        return;
    }
    scanner.Initialize(line);
    string modify = scanner.NextToken();
    string Isbn ="";
    string Name ="";
    string Author ="";
    string Keyword ="";
    string Price ="";
    int isbn_cnt = 0;
    int name_cnt = 0;
    int author_cnt = 0;
    int keyword_cnt = 0;
    int price_cnt = 0;
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    while(scanner.HasMoreToken()) {
        string original = scanner.NextToken();
        string processed_string = skip_string(original);
        if(processed_string == "") {
            errorcout();
            return;
        }
        if(original[1] == 'I') {
            isbn_cnt++;
        }
        if(original[1] == 'n') {
            name_cnt++;
        }
        if(original[1] == 'a') {
            author_cnt++;
        }
        if(original[1] == 'k') {
            keyword_cnt++;
        }
        if(original[1] == 'p') {
            price_cnt++;
        }
    }
    if(isbn_cnt > 1|| name_cnt > 1||author_cnt > 1|| keyword_cnt > 1|| price_cnt > 1) {
        errorcout();
        return;
    }
    string isbn = now_login.select;
    isbn_id find;
    int len = isbn.length();
    for(int i = 0 ; i <len;i++) {
        find.ISBN[i] = isbn[i];
    }
    find.ISBN[len] = '\0';
    find = isbn_ids.Get(find,isbn_ids.entries);
    long long id = find.id;
    id_book find_book;
    find_book.id = id;
    find_book = id_books.Get(find_book,id_books.entries);
    book to_store = find_book.book_store;
    scanner.Initialize(line);
    modify = scanner.NextToken();
    while(scanner.HasMoreToken()) {
        string original = scanner.NextToken();
        string processed_string = skip_string(original);
        /*isbn_id check;
        int length = processed_string.length();
        for(int i = 0;i < length; i++) {
            check.ISBN[i] = processed_string[i];
        }
        check.ISBN[length] = '\0';
        if(isbn_ids.Find(check,isbn_ids.entries)) {
            errorcout();
            return;
        }
        string isbn_original = isbn;
        if(processed_string == isbn_original) {
            errorcout();
            return;
        }*/
        if(original[1] == 'I') {
            int length = processed_string.length();
            usersystem.change_select(processed_string);
            if(processed_string == isbn) {
                errorcout();
                return;
            }
            // now_login.select = processed_string;
//所有选了这个书的都得变化isbn
            for(int i = 0; i < length; i ++) {
                to_store.ISBN[i] = processed_string[i];
            }
            to_store.ISBN[length] = '\0';
            find_book.book_store = to_store;
            id_books.deleteData(find_book,id_books.entries);
            id_books.insertData(find_book,id_books.entries);
            isbn_ids.deleteData(find,isbn_ids.entries);
            for(int i = 0; i < length; i ++) {
                find.ISBN[i] = processed_string[i];
            }
            find.ISBN[length] = '\0';
            isbn_ids.insertData(find,isbn_ids.entries);
        }
        if(original[1] == 'n') {
            processed_string = processed_string.substr(1,processed_string.length()-2);
            bookname_id find_bookname;
            find_bookname.id = id;
            for(int i = 0; i < 60;i++) {
                find_bookname.BookName[i] = to_store.BookName[i];
            }
            int length = processed_string.length();
            for(int i = 0; i < length; i ++) {
                to_store.BookName[i] = processed_string[i];
            }
            to_store.BookName[length] = '\0';
            find_book.book_store = to_store;
            vector<bookname_id> originals;
            originals = bookname_ids.Get_show(find_bookname,bookname_ids.entries,originals);
            bookname_ids.deleteData(find_bookname,bookname_ids.entries);
            for(auto it: originals) {
                if(it.id != find_bookname.id) {
                    bookname_ids.insertData(it,bookname_ids.entries);
                }
            }
            for(int i = 0; i < length; i ++) {
                find_bookname.BookName[i] = processed_string[i];
            }
            bookname_ids.insertData(find_bookname,bookname_ids.entries);
            id_books.deleteData(find_book,id_books.entries);
            id_books.insertData(find_book,id_books.entries);
        }
        if(original[1] == 'a') {
            processed_string = processed_string.substr(1,processed_string.length()-2);
            author_id find_author;
            find_author.id = id;
            for(int i = 0; i < 60;i++) {
                find_author.Author[i] = to_store.Author[i];
            }
            int length = processed_string.length();
            for(int i = 0; i < length; i ++) {
                to_store.Author[i] = processed_string[i];
            }
            to_store.Author[length] = '\0';
            find_book.book_store = to_store;
            vector<author_id> originals;
            originals = author_ids.Get_show(find_author,author_ids.entries,originals);
            author_ids.deleteData(find_author,author_ids.entries);
            for(auto it: originals) {
                if(it.id != find_author.id) {
                    author_ids.insertData(it,author_ids.entries);
                }
            }
            for(int i = 0; i < length; i ++) {
                find_author.Author[i] = processed_string[i];
            }
            author_ids.insertData(find_author,author_ids.entries);
            id_books.deleteData(find_book,id_books.entries);
            id_books.insertData(find_book,id_books.entries);
        }
/*##可能得改动*/
        if(original[1] == 'k') {
            processed_string = processed_string.substr(1,processed_string.length()-2);
            string keyword_original =string(to_store.Keyword);
            // keyword_id find_key;
            // find_key.id = id;
            int length = processed_string.length();
            if(has_duplicate(split_string(processed_string,'|'))) {
                errorcout();
                return;
            }
            for(auto it:split_string(keyword_original,'|')) {
                keyword_id find_key;
                 find_key.id = id;
                int length_key = it.length();
                for(int i = 0; i < length_key;i++) {
                    find_key.Keyword[i] = it[i];
                }
                find_key.Keyword[length] = '\0';
                vector<keyword_id> originals;
                originals = keyword_ids.Get_show(find_key,keyword_ids.entries,originals);
                keyword_ids.deleteData(find_key,keyword_ids.entries);
                for(auto it : originals) {
                    if(it.id != find_key.id){
                        keyword_ids.insertData(it,keyword_ids.entries);
                    }
                }
                keyword_ids.insertData(find_key,keyword_ids.entries);
            }
            for(auto it:split_string(processed_string,'|')) {
                keyword_id find_key;
                find_key.id = id;
                int length_key = it.length();
                for(int i = 0; i < length_key;i++) {
                    find_key.Keyword[i] = it[i];
                }
                find_key.Keyword[length] = '\0';
                keyword_ids.insertData(find_key,keyword_ids.entries);
            }
            for(int i = 0; i < length; i ++) {
                to_store.Keyword[i] = processed_string[i];
            }
            to_store.Keyword[length] = '\0';
            find_book.book_store = to_store;
            id_books.deleteData(find_book,id_books.entries);
            id_books.insertData(find_book,id_books.entries);
        }
        if(original[1] == 'p') {
            double price = Double(processed_string);
            to_store.Price = price;
            find_book.book_store  = to_store;
            id_books.deleteData(find_book,id_books.entries);
            id_books.insertData(find_book,id_books.entries);
        }
    }
}
/*##keyword还得改改,一个里面重复的情况没有考虑*/
void booksystem::Import(const string &line,usersystem&usersystem,logsystem&Logsystem) {
    if(usersystem.login_number() == 0) {
        errorcout();
        return;
    }
    if(usersystem.get_login_now().privilege < 3) {
        errorcout();
        return;
    }
    login & now_login = usersystem.get_login_now();
    if(now_login.if_select == false) {
        errorcout();
        return;
    }
    scanner.Initialize(line);
    string import = scanner.NextToken();
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    string quantity = scanner.NextToken();
    if(!scanner.HasMoreToken()) {
        errorcout();
        return;
    }
    string totalcost = scanner.NextToken();
    if(!is_quantity(quantity)) {
        errorcout();
        return;
    }
    if(!is_price_totalcost(totalcost)) {
        errorcout();
        return;
    }
    size_t quantity_number = Size_t(quantity);
    double totalcost_number = Double(totalcost);
    double totalcost_number2 = std::floor(totalcost_number * 100) / 100.0;
    Logsystem.Revenue(totalcost_number2);
    string select = now_login.select;
    isbn_id find;
    int len = select.length();
    for(int i = 0 ; i <len;i++) {
        find.ISBN[i] = select[i];
    }
    find.ISBN[len] = '\0';
    find = isbn_ids.Get(find,isbn_ids.entries);
    long long id  = find.id;
    id_book find_book;
    find_book.id = id;
    find_book = id_books.Get(find_book,id_books.entries);
    book to_store = find_book.book_store;
    to_store.Quantity += quantity_number;
    to_store.TotalCost += totalcost_number;
    find_book.book_store = to_store;
    id_books.deleteData(find_book,id_books.entries);
    id_books.insertData(find_book,id_books.entries);
}
void booksystem::cout_all() {
    auto it = isbn_ids.entries[0];
    while(true) {
        if(it.size > 0) {
            std::array<isbn_id , M> database;
            isbn_ids.datafile_storage.seekg(it.data_offset);
            isbn_id tmp ;
            isbn_ids.datafile_storage.read(reinterpret_cast<char*>(&database),sizeof(database));
            for(int i = 0;i < M;i++) {
                if(database[i] != isbn_ids.kv) {
                    tmp = database[i];
                    id_book find;
                    find.id = tmp.id;
                    find = id_books.Get(find,id_books.entries);
                    print(find.book_store);
                }
            }
        }
        if(it.next != -1) {
            it = isbn_ids. entries[it.next];
        }
        else break;
    }

}