#include <iostream>
#include "User.h"

using namespace std;

int main(){
    while(1){
        cout << "1.Register\n"
                "2.Login\n"
                "3.ShowMess\n"
                "4.ShowMessDetail\n"
                "5.SendMess\n"
                "6.Logout\n";

        char ch;
        cin >> ch;
        User u = User();
        switch(ch){
            case '1':
                u.Register();
                break;
            case '2':
                u.Login();
                break;
            case '3':
                u.ShowMess(u.id);
                break;
            case '4':
                u.ShowMessDetail(u.id);
                break;
            case '5':
                //u.SendMess(u.id);
                break;
            case '6':
                u.Logout();
                break;
            default:
                cout << "\n";
                break;
        }

    }

	return 0;
}
