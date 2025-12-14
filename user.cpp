#include "user.h"

void initSistem (Sistem &sys){
    sys->firstUser = nullptr;
};

adrUser createNewUser(string uname, string pass){
    adrUser pUser = new UserNode;

    pUser->userData.username = uname;
    pUser->userData.password = pass;
    pUser->userData.firstPlaylist = nullptr;

    pUser->nextUser = nullptr;

    return pUser;
};

void registerAdmin(Sistem &sys, string uname, string pass){
    adrUser pAdmin = createNewUser(uname, pass);

    if (sys.firstUser == nullptr) {
        sys.firstUser = pAdmin;
    } else {
        adrUser current = sys.firstUser;
        while (current->nextUser != nullptr) {
            current = current->nextUser;
        }
        current->nextUser = pAdmin;
    }
};

adrUser findUser(Sistem sys, string uname){
    adrUser current = sys.firstUser;

    while (current != nullptr) {
        if (current->userData.username == uname) {
            return current;
        }
        current = current->nextUser;
    }
    return nullptr;
};

void menuLogin(Sistem &sys, Library lib, Player &player) {
    string username, pass;\
    cout << "===== Music Player Login =====" << endl;
    cout << "Username: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;

    if (uname == "admin" && pass == "admin") {
        cout << "Login berhasil! Selamat datang Admin." << endl;
        menuAdmin();
        return;
    }

    adrUser loggedInUserNode = findUser(sys, username);

    if (loggedInUserNode != nullptr) {
        if (loggedInUserNode->userData.password == pass) {
            cout << "Login berhasil! Selamat datang " << loggedInUserNode->userData.username << "." << endl;
            menuUser();
        }
        else {
            cout << "Password salah." << endl;
        } 
    } else {
        cout << "Username tidak ditemukan." << endl;
    }
}

void menuAdmin(Library &lib) {
    int choice;
    do {
        cout << "\n===== ADMIN MENU =====" << endl;
        cout << "1. Tambah Lagu Baru" << endl;       
        cout << "2. Lihat Semua Lagu (Library)" << endl; 
        cout << "3. Ubah Data Lagu" << endl;         
        cout << "4. Hapus Data Lagu" << endl;        
        cout << "0. Logout" << endl;
        cout << "Pilihan: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {

                break;
            }
            case 2: {

                break;
            }
            case 3: {

                break;
            }
            case 4: {

                break;
            }
            case 0: {
                cout << "Logging out Admin." << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid."
            }
        } while (choice != 0);
    }
};

void menuUser(adrUser currentUserNode, Library &lib, Player &player) {
    int choice;
    
    adrPlaylistHead userPlaylists = currentUserNode->userData.firstPlaylist;

    do {
        cout << "\n===== USER MENU - Welcome, " << currentUserNode->userData.username << " =====" << endl;
        cout << "1. Cari Lagu" << endl;                       
        cout << "2. Kontrol Pemutaran (Play/Stop/Next/Prev)" << endl;  28]
        cout << "3. Kelola Playlist" << endl;                 
        cout << "0. Logout" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 0: {
                cout << "Logging out User." << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid." << endl;
            }
        }
    }
};

