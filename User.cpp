#include<iostream>
#include "User.h"
#include "sqlite3.h"
#include<bits/stdc++.h>

using namespace std;

void User::Register(){

    username = new char;
    birthday = new char;
    password = new char;

	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;
	cout << "Enter birthday: ";
	cin >> birthday;

	ConnectSQlite conn ;
	conn.Open();

    conn.Insert(conn.db,username,password,birthday);

}

void User::Login(){

    username = new char;
    password = new char;
    cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;
	ConnectSQlite conn;
	conn.Open();
	if(conn.Select(conn.db,username,password) > 0) {
        cout << "Hello Bro!\n";
        id = conn.Select(conn.db,username,password);
        flag = 1;
	}
	else {
        cout << "FailFish!\n";
        flag = 0;
	}
}

void User::Logout(){
    flag = 0;
    cout << "Bye! ";
}

bool User::LoginCheck(){
    ConnectSQlite conn;
    if(flag == 1){
        return true;
    }
    else{
        return false;
    }
}

void User::ShowMess(int id){
    if(LoginCheck()){
        ConnectSQlite conn;
        conn.Open();
        conn.SelectMessenger(conn.db,id);
    }
    else{
        cout << "Please login first! \n ";
    }
}

void User::ShowMessDetail(int uid){
    if (LoginCheck()){
        int fid;
        cout << "Chon nguoi dung: ";
        char *_friend;
        _friend = new char;
        cin >> _friend;
        ConnectSQlite conn;
        conn.Open();
        fid = conn.TransNameToId(_friend);
        if(fid > 0){
            conn.ShowMessDetail(conn.db,uid,fid);
        }
        else{
            cout <<  "Incorrect username! \n";
        }
    }else {
        cout << "Please login first! \n";
    }

}
void ConnectSQlite::Open(){
        rc = sqlite3_open("Database.db", &db);
       if( rc ){
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          exit(0);
       }else{

       }
}

int ConnectSQlite::Select(sqlite3 *db,char *username, char *password){
        int id = 0;
        if (!db)return 0;
        szSQL = "SELECT * FROM  user1 WHERE username = ? and password = ? ";
        rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);
       if( rc == SQLITE_OK ) {
            sqlite3_bind_text(stmt, 1, username, strlen(username), 0);
            sqlite3_bind_text(stmt, 2, password, strlen(password), 0);
           while(sqlite3_step(stmt) == SQLITE_ROW) {
                stringstream str;
                str << sqlite3_column_text(stmt, 0);
                str >> id ;
            }
            sqlite3_finalize(stmt);
      }else{
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      }
    return id;
}

void ConnectSQlite::Insert(sqlite3 *db, char *username, char *password,char *birthday){
  if (!db)return;
  szSQL = "insert into user1 (username, password,birthday) values (?,?,?)";
  int rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
  if( rc == SQLITE_OK ) {
    sqlite3_bind_text(stmt, 1, username, strlen(username), 0);
    sqlite3_bind_text(stmt, 2, password, strlen(password), 0);
    sqlite3_bind_text(stmt, 3, birthday, strlen(birthday), 0);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }else{
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
  }
}

int ConnectSQlite::TransNameToId(char *_friend){
    int fid = -1;
    szSQL = "SELECT id FROM user1 WHERE username = ?";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);

    if( rc == SQLITE_OK ){
        sqlite3_bind_text(stmt,1,_friend,strlen(_friend),0);
        if(sqlite3_step(stmt) == SQLITE_ROW) {
            stringstream str;
            str << sqlite3_column_text(stmt, 0);
            str >> fid;
        }
        sqlite3_finalize(stmt);
    }else{
          fprintf(stderr, "SQL error: %s\n",zErrMsg);
          sqlite3_free(zErrMsg);
    }
    return fid;
}

void ConnectSQlite::SelectMessenger(sqlite3 *db, int id){
    if (!db)return ;
    szSQL = "SELECT DISTINCT User.username FROM"
                "(SELECT * FROM messenger where senid = ? ) as A LEFT JOIN user1 ON A.recid = User.id";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
        sqlite3_bind_int(stmt,1,id);
        while(sqlite3_step(stmt) == SQLITE_ROW) {
            answer.push_back(string((const char *) sqlite3_column_text(stmt, 0)));
        }
        sqlite3_finalize(stmt);
        cout <<"MessList \n" ;
        for( list<std::string>::const_iterator it = answer.begin(); it != answer.end(); it++)
            cout << *it << endl;

    }else{

          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      }
}

void ConnectSQlite::ShowMessDetail(sqlite3 *db,int uid,int fid){
    if (!db)return ;
    cout << "--------Detail--------\n";
    szSQL = "SELECT * FROM (SELECT * FROM messenger WHERE (senid = ? OR senid = ?) AND (recid = ? OR recid =?) ) AS B LEFT JOIN  User ON User.id = B.senid";
    rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
    if( rc == SQLITE_OK ) {
        sqlite3_bind_int(stmt,1,uid);
        sqlite3_bind_int(stmt,2,fid);
        sqlite3_bind_int(stmt,3,uid);
        sqlite3_bind_int(stmt,4,fid);
        while(sqlite3_step(stmt) == SQLITE_ROW) {

                cout << "   " << string((const char *) sqlite3_column_text(stmt, 5)) << ": " <<  endl;
                cout << "       "<< string((const char *) sqlite3_column_text(stmt, 2)) << "-" ;
                cout << string((const char *) sqlite3_column_text(stmt, 3)) << endl ;

        }
        sqlite3_finalize(stmt);

    }else{
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
      }
}






