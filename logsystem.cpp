#include"logsystem.h"
logsystem::logsystem() {
    if(!exist(LOGDATA))datafile.open(LOGDATA,std::ios::out);
    datafile.close();
    datafile.open(LOGDATA,ios::binary|ios::in|ios::out);
}
logsystem::~logsystem() {
    datafile.close();
}

void logsystem::Show(usersystem&usersystem) {
    if(usersystem.login_number() == 0 || usersystem.get_login_now().privilege < 7) {
        errorcout();
        return;
    }
    cout << std::fixed << std::setprecision(2) <<"+ "<<income<<" - "<<revenue<<endl;
}
void logsystem::Earn(const double & number) {
    record.push_back(number);
    income += number;
    records ++;
}
void logsystem::Revenue(const double &number) {
    record.push_back(-number);
    revenue += number;
    records++;
}
void logsystem::ShowCount(size_t &count,usersystem&usersystem) {
    if(usersystem.login_number() == 0 || usersystem.get_login_now().privilege < 7) {
        errorcout();
        return;
    }
    if(count == 0) {
        cout<<endl;
    }
    if(count >0) {
        double income_count = 0.00;
        double revenue_count = 0.00;
        if(count > records) {
            errorcout();
            return;
        }
        for(size_t i = record.size() - count;i<record.size();i++) {
            if(record[i] < 0) {
                revenue_count += -record[i];
            }
            else {
                income_count += record[i];
            }
        }
        cout << std::fixed << std::setprecision(2) <<"+ "<<income_count<<" - "<<revenue_count<<endl;
    }
}
