#include <iostream>
#include <fstream>
#include <limits>
using namespace std;


struct Ship {

    struct Weapon {
        string name;
        unsigned int power;
        float powerCon;
    };

    string name;
    string classShip;
    short length;
    unsigned int shieldCap;
    float warpSpeed;
    unsigned int totalWeapons;
    Weapon* weapons;
    bool fLoad = false;
    bool eLoad = false;

    unsigned int totFriendly;
    unsigned int totEnemy;

    Ship* friendlyShips;

    Ship* enemyShips;


    void AssembleFriendly() {
        ifstream file("friendlyships.shp", ios::in | ios::binary);

        file.read((char*)&totFriendly, 4);
        if (totFriendly != 0)
            friendlyShips = new Ship[totFriendly];
        unsigned int spot;
        for (unsigned int x = 0; x < totFriendly; x++) {
            file.read((char*)&spot, 4);
            char* temp = new char[spot];
            file.read(temp, spot);
            friendlyShips[x].name = temp;
            delete temp;

            file.read((char*)&spot, 4);
            temp = new char[spot];
            file.read(temp, spot);
            friendlyShips[x].classShip = temp;
            delete temp;

            short s;
            file.read((char*)&s, 2);
            friendlyShips[x].length = s;

            file.read((char*)&spot, 4);
            friendlyShips[x].shieldCap = spot;

            float f;
            file.read((char*)&f, 4);
            friendlyShips[x].warpSpeed = f;

            file.read((char*)&spot, 4);
            friendlyShips[x].totalWeapons = spot;
            if (friendlyShips[x].totalWeapons != 0) {
                friendlyShips[x].weapons = new Weapon[friendlyShips[x].totalWeapons];
                for (unsigned int y = 0; y < friendlyShips[x].totalWeapons; y++) {

                    file.read((char*)&spot, 4);
                    temp = new char[spot];
                    file.read(temp, spot);
                    friendlyShips[x].weapons[y].name = temp;
                    delete temp;

                    file.read((char*)&spot, 4);
                    friendlyShips[x].weapons[y].power = spot;

                    file.read((char*)&f, 4);
                    friendlyShips[x].weapons[y].powerCon = f;
                }
            }
        }
        file.close();
        fLoad = true;
    }

    void AssembleEnemy() {
        ifstream file("enemyships.shp", ios::in | ios::binary);

        file.read((char*)&totEnemy, 4);
        if (totEnemy != 0)
            enemyShips = new Ship[totEnemy];
        unsigned int spot;
        for (unsigned int x = 0; x < totEnemy; x++) {
            file.read((char*)&spot, 4);
            char* temp = new char[spot];
            file.read(temp, spot);
            enemyShips[x].name = temp;
            delete temp;

            file.read((char*)&spot, 4);
            temp = new char[spot];
            file.read(temp, spot);
            enemyShips[x].classShip = temp;
            delete temp;

            short s;
            file.read((char*)&s, 2);
            enemyShips[x].length = s;

            file.read((char*)&spot, 4);
            enemyShips[x].shieldCap = spot;

            float f;
            file.read((char*)&f, 4);
            enemyShips[x].warpSpeed = f;

            file.read((char*)&spot, 4);
            enemyShips[x].totalWeapons = spot;
            if (enemyShips[x].totalWeapons != 0) {
                enemyShips[x].weapons = new Weapon[enemyShips[x].totalWeapons];
                for (unsigned int y = 0; y < enemyShips[x].totalWeapons; y++) {

                    file.read((char*)&spot, 4);
                    temp = new char[spot];
                    file.read(temp, spot);
                    enemyShips[x].weapons[y].name = temp;
                    delete temp;

                    file.read((char*)&spot, 4);
                    enemyShips[x].weapons[y].power = spot;

                    file.read((char*)&f, 4);
                    enemyShips[x].weapons[y].powerCon = f;
                }
            }
        }
        file.close();
        eLoad = true;
    }

    void AssembleAllShips() {
        AssembleFriendly();
        AssembleEnemy();
    }

    void PrintFriendly() {
        for (unsigned int x = 0; x < totFriendly; x++) {
            cout << "Name: " << friendlyShips[x].name << endl;
            cout << "Class: " << friendlyShips[x].classShip << endl;
            cout << "Length: " << friendlyShips[x].length << endl;
            cout << "Shield capacity: " << friendlyShips[x].shieldCap << endl;
            cout << "Maximum Warp: " << friendlyShips[x].warpSpeed << endl;
            cout << "Armaments: " << endl;
            unsigned int total = 0;
            for (unsigned int y = 0; y < friendlyShips[x].totalWeapons; y++) {
                cout << friendlyShips[x].weapons[y].name << ", " << friendlyShips[x].weapons[y].power << ", " << friendlyShips[x].weapons[y].powerCon << endl;
                total += friendlyShips[x].weapons[y].power;
            }
            if (total != 0)
                cout << "Total firepower: " << total << endl << endl;
            else
                cout << "Unarmed" << endl << endl;
        }
    }

    void PrintEnemy() {
        for (unsigned int x = 0; x < totEnemy; x++) {
            cout << "Name: " << enemyShips[x].name << endl;
            cout << "Class: " << enemyShips[x].classShip << endl;
            cout << "Length: " << enemyShips[x].length << endl;
            cout << "Shield capacity: " << enemyShips[x].shieldCap << endl;
            cout << "Maximum Warp: " << enemyShips[x].warpSpeed << endl;
            cout << "Armaments: " << endl;
            unsigned int total = 0;
            for (unsigned int y = 0; y < enemyShips[x].totalWeapons; y++) {
                cout << enemyShips[x].weapons[y].name << ", " << enemyShips[x].weapons[y].power << ", " << enemyShips[x].weapons[y].powerCon << endl;
                total += enemyShips[x].weapons[y].power;
            }
            if (total != 0)
                cout << "Total firepower: " << total << endl << endl;
            else
                cout << "Unarmed" << endl << endl;
        }
    }

    void PrintAllShips() {
        PrintFriendly();
        PrintEnemy();
    }

    void PrintShipStrongestWeapon() {
        Ship strongest;
        unsigned int maxPower = 0;
        if (fLoad) {
            for (unsigned int x = 0; x < totFriendly; x++) {
                for (unsigned int y = 0; y < friendlyShips[x].totalWeapons; y++) {
                    if (friendlyShips[x].weapons[y].power > maxPower) {
                        maxPower = friendlyShips[x].weapons[y].power;
                        strongest = friendlyShips[x];
                    }
                }
            }
        }

        if (eLoad) {
            for (unsigned int x = 0; x < totEnemy; x++) {
                for (unsigned int y = 0; y < enemyShips[x].totalWeapons; y++) {
                    if (enemyShips[x].weapons[y].power > maxPower) {
                        maxPower = enemyShips[x].weapons[y].power;
                        strongest = enemyShips[x];
                    }
                }
            }
        }

        if (maxPower == 0)
            cout << "All ships have 0 power" << endl;

        else {
            cout << "Ship With the Strongest Weapon: " << endl;
            cout << "Name: " << strongest.name << endl;
            cout << "Class: " << strongest.classShip << endl;
            cout << "Length: " << strongest.length << endl;
            cout << "Shield capacity: " << strongest.shieldCap << endl;
            cout << "Maximum Warp: " << strongest.warpSpeed << endl;
            cout << "Armaments: " << endl;
            unsigned int totalP = 0;
            for (unsigned int x = 0; x < strongest.totalWeapons; x++) {
                cout << strongest.weapons[x].name << ", " << strongest.weapons[x].power << ", " << strongest.weapons[x].powerCon << endl;
                totalP += strongest.weapons[x].power;
            }
            cout << "Total firepower: " << totalP << endl;
        }
    }

    void PrintStrongestShip() {
        Ship strongest;
        unsigned int maxPower = 0;
        unsigned int tempPower = 0;

        if (fLoad) {
            for (unsigned int x = 0; x < totFriendly; x++) {
                for (unsigned int y = 0; y < friendlyShips[x].totalWeapons; y++) {
                    tempPower += friendlyShips[x].weapons[y].power;
                }
                if (tempPower > maxPower) {
                    maxPower = tempPower;
                    strongest = friendlyShips[x];
                }
                tempPower = 0;
            }
        }

        if (eLoad) {
            for (unsigned int x = 0; x < totEnemy; x++) {
                for (unsigned int y = 0; y < enemyShips[x].totalWeapons; y++) {
                    tempPower += enemyShips[x].weapons[y].power;
                }
                if (tempPower > maxPower) {
                    maxPower = tempPower;
                    strongest = enemyShips[x];
                }
                tempPower = 0;
            }
        }

        if (maxPower == 0)
            cout << "All ships have 0 power" << endl;
        else {
            cout << "Strongest Ship: " << endl;
            cout << "Name: " << strongest.name << endl;
            cout << "Class: " << strongest.classShip << endl;
            cout << "Length: " << strongest.length << endl;
            cout << "Shield capacity: " << strongest.shieldCap << endl;
            cout << "Maximum Warp: " << strongest.warpSpeed << endl;
            cout << "Armaments: " << endl;
            unsigned int totalP = 0;
            for (unsigned int x = 0; x < strongest.totalWeapons; x++) {
                cout << strongest.weapons[x].name << ", " << strongest.weapons[x].power << ", " << strongest.weapons[x].powerCon << endl;
                totalP += strongest.weapons[x].power;
            }
            cout << "Total firepower: " << totalP << endl;
        }
    }

    void PrintWeakestShip() {
        Ship weakest;
        unsigned int minPower = numeric_limits<int>::max();
        unsigned int tempPower = 0;

        if (fLoad) {
            for (unsigned int x = 0; x < totFriendly; x++) {
                for (unsigned int y = 0; y < friendlyShips[x].totalWeapons; y++) {
                    tempPower += friendlyShips[x].weapons[y].power;
                }
                if ((tempPower < minPower) && (tempPower != 0)) {
                    minPower = tempPower;
                    weakest = friendlyShips[x];
                }
                tempPower = 0;
            }
        }

        if (eLoad) {
            for (unsigned int x = 0; x < totEnemy; x++) {
                for (unsigned int y = 0; y < enemyShips[x].totalWeapons; y++) {
                    tempPower += enemyShips[x].weapons[y].power;
                }
                if ((tempPower < minPower) && (tempPower != 0)) {
                    minPower = tempPower;
                    weakest = enemyShips[x];
                }
                tempPower = 0;
            }
        }

        cout << "Weakest Ship: " << endl;
        cout << "Name: " << weakest.name << endl;
        cout << "Class: " << weakest.classShip << endl;
        cout << "Length: " << weakest.length << endl;
        cout << "Shield capacity: " << weakest.shieldCap << endl;
        cout << "Maximum Warp: " << weakest.warpSpeed << endl;
        cout << "Armaments: " << endl;
        unsigned int total = 0;
        for (unsigned int x = 0; x < weakest.totalWeapons; x++) {
            cout << weakest.weapons[x].name << ", " << weakest.weapons[x].power << ", " << weakest.weapons[x].powerCon << endl;
            total += weakest.weapons[x].power;
        }
        cout << "Total firepower: " << total << endl;
    }
    void PrintUnarmedShips() {
        unsigned int tempPower = 0;

        if (fLoad) {
            for (unsigned int x = 0; x < totFriendly; x++) {
                for (unsigned int y = 0; y < friendlyShips[x].totalWeapons; y++) {
                    tempPower += friendlyShips[x].weapons[y].power;
                }
                if (tempPower == 0) {
                    cout << "Name: " << friendlyShips[x].name << endl;
                    cout << "Class: " << friendlyShips[x].classShip << endl;
                    cout << "Length: " << friendlyShips[x].length << endl;
                    cout << "Shield capacity: " << friendlyShips[x].shieldCap << endl;
                    cout << "Maximum Warp: " << friendlyShips[x].warpSpeed << endl;
                    cout << "Armaments: " << endl;
                    cout << "Unarmed" << endl << endl;
                }
                tempPower = 0;
            }
        }

        if (eLoad) {
            for (unsigned int x = 0; x < totEnemy; x++) {
                for (unsigned int y = 0; y < enemyShips[x].totalWeapons; y++) {
                    tempPower += enemyShips[x].weapons[y].power;
                }
                if (tempPower == 0) {
                    cout << "Name: " << enemyShips[x].name << endl;
                    cout << "Class: " << enemyShips[x].classShip << endl;
                    cout << "Length: " << enemyShips[x].length << endl;
                    cout << "Shield capacity: " << enemyShips[x].shieldCap << endl;
                    cout << "Maximum Warp: " << enemyShips[x].warpSpeed << endl;
                    cout << "Armaments: " << endl;
                    cout << "Unarmed" << endl << endl;
                }
                tempPower = 0;
            }
        }
    }
};