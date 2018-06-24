#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include <bits/stdc++.h>
#include <iostream>
#include "sqlite3.h"

using namespace std;
class User{

public:
    int id;
    char *username;
    char *password;
    char *birthday;
    int flag;
public:
    User(){};
    void Login();
    bool LoginCheck();
    void Logout();
    void Register();
    void ShowMess(int);
    void ShowMessDetail(int);
    void SendMess(int);
};

class ConnectSQlite{
    public:
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        const char *szSQL;
        const char *pzTest;
        sqlite3_stmt *stmt;
        list<string> answer;
        static int callback(void *,int,char **,char **);
        void Open();
        void Insert(sqlite3 *db,char *, char *,char *);
        int Select(sqlite3 *db, char *, char *);
        int TransNameToId(char *_friend);
        void SelectMessenger(sqlite3 *db, int id);
        void ShowMessDetail(sqlite3 *db,int uid,int fid);
};
#endif // USER_H_INCLUDED


