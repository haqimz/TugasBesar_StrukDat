#include "player.h"
#include "library.h"
#include "user.h"
#include <iostream>

using namespace std;

void initPlayer(Player &player) {
    player.currentSong = nullptr;
    player.isPlaying = false;
    player.currentPlaylistNode = nullptr;
    player.currentPlaylist = nullptr;
    player.isShufling = false;
}

void playSong(Player &p, adrLagu song) {
    if (song == nullptr) {
        cout << "[Player] Error: Data lagu tidak valid." << endl;
        return;
    }

    p.currentSong = song;
    p.isPlaying = true;

    cout << "\n=======================================" << endl;
    cout << "▶️  SEDANG MEMUTAR:" << endl;
    cout << "   Judul  : " << song->judul << endl;
    cout << "   Artis  : " << song->artis->nama << endl;
    cout << "   Genre  : " << song->genre << endl;
    cout << "   Tahun  : " << song->tahun << endl;
    cout << "=======================================" << endl;
}

void nextSong(Player &p, Library lib) {
    if (p.currentSong == nullptr) {
        cout << "[Player] Tidak ada lagu yang sedang diputar." << endl;
        return;
    }

    if (p.currentPlaylistNode != nullptr && p.currentPlaylistNode->next != nullptr) {
        p.currentPlaylistNode = p.currentPlaylistNode->next;
        playSong(p, p.currentPlaylistNode->lagu);
    }
    else {
        cout << "[Player] Playlist habis. Mencari lagu serupa di Library..." << endl;
        adrLagu similar = findSimilarSong(lib, p.currentSong);

        if (similar != nullptr) {
            p.currentPlaylistNode = nullptr;
            playSong(p, similar);
        } else {
            cout << "[Player] Tidak ada lagu serupa. Pemutaran berhenti." << endl;
            p.isPlaying = false;
        }
    }
}

void prevSong(Player &p, Library lib) {
    if (p.currentSong == nullptr) return;

    cout << "[Player] Mengulang lagu saat ini..." << endl;
    playSong(p, p.currentSong);
}
