#include "user.h"

void initSistem (Sistem &sys){
    sys.firstUser = nullptr;
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

void menuLogin(Sistem &sys, Library &lib, Player &player) {
    string username, pass;\
    cout << "===== Music Player Login =====" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> pass;

    if (username == "admin" && pass == "admin") {
        cout << "Login berhasil! Selamat datang Admin." << endl;
        menuAdmin(lib, sys);
        return;
    }

    adrUser loggedInUserNode = findUser(sys, username);

    if (loggedInUserNode != nullptr) {
        if (loggedInUserNode->userData.password == pass) {
            cout << "Login berhasil! Selamat datang " << loggedInUserNode->userData.username << "." << endl;
            menuUser(loggedInUserNode, lib, player);
        }
        else {
            cout << "Password salah." << endl;
        }
    } else {
        cout << "Username tidak ditemukan." << endl;
    }
}

void menuAdmin(Library &lib, Sistem &sys) {
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
                int id, durasi, tahun;
                string judul, genre, namaArtis;

                // 1. Input Nama Artis (Pakai ws karena sebelumnya pasti ada input angka menu)
                cout << "Nama Artis: ";
                cin >> ws;               // Bersihkan buffer enter dari menu
                getline(cin, namaArtis); // Ambil satu baris full

                // 2. Input ID (Angka biasa, pakai cin)
                cout << "ID Lagu: ";
                cin >> id;

                // 3. Input Judul (Pakai ws lagi karena sebelumnya input angka ID)
                cout << "Judul: ";
                cin >> ws;               // Bersihkan buffer enter dari ID
                getline(cin, judul);     // Ambil satu baris full

                // 4. Input Genre (Langsung getline aman, atau pakai ws biar konsisten)
                cout << "Genre: ";
                // cin >> ws; // (Opsional di sini, tapi aman kalau judul tidak pakai spasi aneh)
                getline(cin, genre);

                // 5. Input Angka sisanya (cin biasa)
                cout << "Durasi (detik): ";
                cin >> durasi;

                cout << "Tahun: ";
                cin >> tahun;

                // Proses Insert
                adrLagu newLagu = createLagu(id, judul, genre, durasi, tahun);
                insertLagu(lib, newLagu, namaArtis);

                cout << "Data berhasil disimpan!" << endl;
                break;
            }
            case 2: {
                viewAllSongs(lib);
                break;
            }
            case 3: {
                int id;
                cout << "Masukkan ID lagu yang ingin diubah: "; cin >> id;
                updateLagu(lib, id);
                break;
            }
            case 4: {
                int id;
                cout << "Masukkan ID lagu yang ingin dihapus: "; cin >> id;
                // Memanggil deleteLagu yang sudah menyertakan pembersihan Playlist
                deleteLagu(lib, id, sys);
                break;
            }
            case 0: {
                cout << "Logging out Admin." << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid." << endl;
                break;
            }
        } // Tutup Switch di sini
    } while (choice != 0); // Tutup Do-While di sini
}

void menuUser(adrUser currentUserNode, Library &lib, Player &player) {
    int choice;
    string namaPl, judul, nama; // Deklarasi di luar agar aman

    do {
        cout << "\n===== USER MENU - Welcome, " << currentUserNode->userData.username << " =====" << endl;
        cout << "1. Cari Lagu & Tambah ke Playlist" << endl;
        cout << "2. Kontrol Pemutaran (Play/Next/Prev)" << endl;
        cout << "3. Kelola Playlist (Buat/Lihat/Hapus Lagu)" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilihan: ";

        // Validasi input angka agar tidak loop tak terhingga jika user input huruf
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "Masukkan Judul Lagu: ";
                cin >> ws; getline(cin, judul);
                adrLagu s = searchSongByJudul(lib, judul);
                if (s != nullptr) {
                    cout << "Lagu ditemukan: " << s->judul << " - " << s->artis->nama << endl;
                    cout << "Tambah ke playlist? (y/n): ";
                    char k; cin >> k;
                    if (k == 'y') {
                        cout << "Nama Playlist Tujuan: ";
                        cin >> ws; getline(cin, namaPl);
                        adrPlaylistHead ph = findPlaylist(currentUserNode->userData.firstPlaylist, namaPl);
                        if (ph != nullptr) {
                            addSongToPlaylist(ph->playlistData, s);
                        } else {
                            cout << "Playlist tidak ditemukan." << endl;
                        }
                    }
                } else {
                    cout << "Lagu tidak ditemukan." << endl;
                }
                break;
            }
            case 2: {
                cout << "1. Play dari Playlist\n2. Next\n3. Prev\nPilih: ";
                int sub; cin >> sub;
                if (sub == 1) {
                    cout << "Nama Playlist: ";
                    cin >> ws; getline(cin, namaPl);
                    adrPlaylistHead ph = findPlaylist(currentUserNode->userData.firstPlaylist, namaPl);
                    if (ph != nullptr && ph->playlistData.firstSong != nullptr) {
                        player.currentPlaylist = &ph->playlistData;
                        player.currentPlaylistNode = ph->playlistData.firstSong;
                        // PASTIKAN namanya songPointer sesuai struct kamu
                        playSong(player, player.currentPlaylistNode->lagu);
                    } else {
                        cout << "Playlist kosong atau tidak ditemukan." << endl;
                    }
                } else if (sub == 2) {
                    nextSong(player, lib);
                } else if (sub == 3) {
                    prevSong(player, lib);
                }
                break;
            }
            case 3: {
                cout << "1. Buat Playlist Baru\n2. Lihat Semua Playlist\n3. Hapus Dari Playlist\nPilih: ";
                int sub; cin >> sub;
                if (sub == 1) {
                    cout << "Masukkan Nama Playlist: ";
                    cin >> ws; // Pembersihan buffer
                    getline(cin, nama);
                    // Langsung kirim pointer asli dari currentUserNode
                    insertNewPlaylist(currentUserNode->userData.firstPlaylist, nama);
                } else if (sub == 2) {
                    viewAllUserPlaylists(currentUserNode->userData.firstPlaylist);
                } else if (sub == 3) {
                    cout << "Masukkan Nama Playlist: ";
                    cin >> ws;
                    getline(cin, namaPl);

                    adrPlaylistHead ph = findPlaylist(currentUserNode->userData.firstPlaylist, namaPl);

                    if (ph != nullptr) {
                        cout << "Masukkan Judul Lagu yang ingin dihapus: ";
                        getline(cin, judul);

                        deleteSongFromPlaylist(ph->playlistData, judul);
                    } else {
                        cout << "Playlist '" << namaPl << "' tidak ditemukan." << endl;
                    }
                }
                break;
            }
            case 0:
                cout << "Logging out User..." << endl;
                break;
        }
    } while (choice != 0);
}
