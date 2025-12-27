#include <iostream>
#include <string>
#include "library.h"
#include "playlist.h"
#include "user.h"
#include "player.h"

// ==========================================
// DATA GENERATOR: 50+ LAGU (FINAL DEMO)
// ==========================================
void loadDummyData(Library &lib) {
    cout << ">> [SYSTEM] Memuat 50+ Data Dummy ke Library..." << endl;

    // ================= GENRE: POP (Paling Banyak buat Tes Autoplay) =================

    // ARTIS 1: TULUS (Pop Indo)
    insertLagu(lib, createLagu(101, "Hati-Hati di Jalan", "Pop", 242, 2022), "Tulus");
    insertLagu(lib, createLagu(102, "Monokrom", "Pop", 214, 2016), "Tulus");
    insertLagu(lib, createLagu(103, "Sepatu", "Pop", 230, 2014), "Tulus");
    insertLagu(lib, createLagu(104, "Gajah", "Pop", 240, 2014), "Tulus");
    insertLagu(lib, createLagu(105, "Interaksi", "Pop", 190, 2022), "Tulus");

    // ARTIS 2: MAHALINI (Pop Indo)
    insertLagu(lib, createLagu(201, "Sisa Rasa", "Pop", 254, 2021), "Mahalini");
    insertLagu(lib, createLagu(202, "Melawan Restu", "Pop", 220, 2021), "Mahalini");
    insertLagu(lib, createLagu(203, "Bohongi Hati", "Pop", 260, 2023), "Mahalini");
    insertLagu(lib, createLagu(204, "Sial", "Pop", 243, 2023), "Mahalini");

    // ARTIS 3: TAYLOR SWIFT (Pop Barat)
    insertLagu(lib, createLagu(301, "Blank Space", "Pop", 231, 2014), "Taylor Swift");
    insertLagu(lib, createLagu(302, "Anti-Hero", "Pop", 200, 2022), "Taylor Swift");
    insertLagu(lib, createLagu(303, "Cruel Summer", "Pop", 178, 2019), "Taylor Swift");
    insertLagu(lib, createLagu(304, "Shake It Off", "Pop", 219, 2014), "Taylor Swift");
    insertLagu(lib, createLagu(305, "Style", "Pop", 231, 2014), "Taylor Swift");
    insertLagu(lib, createLagu(306, "Love Story", "Pop", 235, 2008), "Taylor Swift");

    // ARTIS 4: MAROON 5 (Pop Rock)
    insertLagu(lib, createLagu(401, "Sugar", "Pop", 235, 2014), "Maroon 5");
    insertLagu(lib, createLagu(402, "Maps", "Pop", 190, 2014), "Maroon 5");
    insertLagu(lib, createLagu(403, "Memories", "Pop", 189, 2019), "Maroon 5");
    insertLagu(lib, createLagu(404, "Payphone", "Pop", 231, 2012), "Maroon 5");

    // ================= GENRE: ROCK (Buat Variasi) =================

    // ARTIS 5: QUEEN (Classic Rock)
    insertLagu(lib, createLagu(501, "Bohemian Rhapsody", "Rock", 354, 1975), "Queen");
    insertLagu(lib, createLagu(502, "Don't Stop Me Now", "Rock", 209, 1978), "Queen");
    insertLagu(lib, createLagu(503, "We Will Rock You", "Rock", 121, 1977), "Queen");
    insertLagu(lib, createLagu(504, "Radio Ga Ga", "Rock", 348, 1984), "Queen");

    // ARTIS 6: DEWA 19 (Rock Indo)
    insertLagu(lib, createLagu(601, "Kangen", "Rock", 300, 1992), "Dewa 19");
    insertLagu(lib, createLagu(602, "Pupus", "Rock", 305, 2002), "Dewa 19");
    insertLagu(lib, createLagu(603, "Risalah Hati", "Rock", 290, 2000), "Dewa 19");
    insertLagu(lib, createLagu(604, "Arjuna", "Rock", 285, 2002), "Dewa 19");

    // ARTIS 7: ARCTIC MONKEYS (Indie Rock)
    insertLagu(lib, createLagu(701, "Do I Wanna Know?", "Rock", 272, 2013), "Arctic Monkeys");
    insertLagu(lib, createLagu(702, "R U Mine?", "Rock", 201, 2013), "Arctic Monkeys");
    insertLagu(lib, createLagu(703, "505", "Rock", 253, 2007), "Arctic Monkeys");

    // ================= GENRE: R&B / FUNK =================

    // ARTIS 8: THE WEEKND
    insertLagu(lib, createLagu(801, "Blinding Lights", "R&B", 200, 2020), "The Weeknd");
    insertLagu(lib, createLagu(802, "Starboy", "R&B", 230, 2016), "The Weeknd");
    insertLagu(lib, createLagu(803, "Save Your Tears", "R&B", 215, 2020), "The Weeknd");
    insertLagu(lib, createLagu(804, "Die For You", "R&B", 260, 2016), "The Weeknd");

    // ARTIS 9: BRUNO MARS
    insertLagu(lib, createLagu(901, "Uptown Funk", "Funk", 269, 2014), "Bruno Mars");
    insertLagu(lib, createLagu(902, "24K Magic", "Funk", 226, 2016), "Bruno Mars");
    insertLagu(lib, createLagu(903, "Treasure", "Funk", 178, 2012), "Bruno Mars");
    insertLagu(lib, createLagu(904, "That's What I Like", "R&B", 206, 2016), "Bruno Mars");

    // ================= GENRE: K-POP & J-POP (Niche Market) =================

    // ARTIS 10: BTS
    insertLagu(lib, createLagu(1001, "Dynamite", "K-Pop", 199, 2020), "BTS");
    insertLagu(lib, createLagu(1002, "Butter", "K-Pop", 164, 2021), "BTS");
    insertLagu(lib, createLagu(1003, "Boy With Luv", "K-Pop", 229, 2019), "BTS");

    // ARTIS 11: YOASOBI
    insertLagu(lib, createLagu(1101, "Idol", "J-Pop", 213, 2023), "YOASOBI");
    insertLagu(lib, createLagu(1102, "Yoru ni Kakeru", "J-Pop", 261, 2019), "YOASOBI");

    // ================= GENRE: JAZZ (Satu-satunya, Tes Negative Case) =================

    // ARTIS 12: ARDHITO PRAMONO
    insertLagu(lib, createLagu(1201, "Bitterlove", "Jazz", 240, 2016), "Ardhito Pramono");
    insertLagu(lib, createLagu(1202, "Cigarettes of Ours", "Jazz", 260, 2018), "Ardhito Pramono");

    cout << ">> [SUCCESS] Library siap digunakan!" << endl;
    cout << "=================================================" << endl;
}

using namespace std;

int main() {
    Library myLibrary;
    initLibrary(myLibrary);

    Sistem mySistem;
    initSistem(mySistem);

    Player myPlayer;
    initPlayer(myPlayer);

    registerAdmin(mySistem, "user1", "123");
    loadDummyData(myLibrary);

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
