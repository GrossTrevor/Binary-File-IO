#include <iostream>
#include <fstream>
#include "extrafile.h"
using namespace std;

int main()
{
    unsigned int type;
    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl << endl;
    int option;
    cin >> option;

    Ship data;
    if (option == 1) {
        data.AssembleFriendly();
        type = 1;
    }
    else if (option == 2) {
        data.AssembleEnemy();
        type = 2;
    }
    else if (option == 3) {
        data.AssembleAllShips();
        type = 3;
    }


    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl << endl;

    cin >> option;

    if (option == 1) {
        if (type == 1)
            data.PrintFriendly();
        if (type == 2)
            data.PrintEnemy();
        if (type == 3)
            data.PrintAllShips();
    }
    else if (option == 2)
        data.PrintShipStrongestWeapon();
    else if (option == 3)
        data.PrintStrongestShip();
    else if (option == 4)
        data.PrintWeakestShip();
    else if (option == 5)
        data.PrintUnarmedShips();
    else
        cout << "Invalid number!";

    return 0;
}