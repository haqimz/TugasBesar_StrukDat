#include <iostream>
#include <string>
#include "library.h"
#include "playlist.h"
#include "user.h"
#include "player.h"

using namespace std;

int main() {
    Library myLibrary;
    initLibrary(myLibrary);

    Sistem mySistem;
    initSistem(mySistem);

    Player myPlayer;
    initPlayer(myPlayer);

    registerAdmin(mySistem, "user1", "123");

    int mainChoice;
    do {
        cout << "\n=======================================" << endl;
        cout << "   WELCOME TO JETT REVIVE ME PLAYER    " << endl;
        cout << "=======================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register User Baru" << endl;
        cout << "0. Keluar Aplikasi" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Pilih menu: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                menuLogin(mySistem, myLibrary, myPlayer);
                break;
            case 2: {
                string u, p;
                cout << "Masukkan Username baru: "; cin >> u;
                cout << "Masukkan Password baru: "; cin >> p;
                registerAdmin(mySistem, u, p);
                cout << "User berhasil terdaftar!" << endl;
                break;
            }
            case 0:
                cout << "Terima kasih telah menggunakan aplikasi ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (mainChoice != 0);

    return 0;
}
