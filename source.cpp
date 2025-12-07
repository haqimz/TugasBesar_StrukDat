#include "header.h"


// CREATE LIST ============================================================================

void initLibrary(Library &lib) {
    lib.firstArtis = nullptr;
    lib.totalSongs = 0;
}

void initPlaylist(Playlist &pl, string nama) {
    pl.namaPlaylist = nama;
    pl.firstSong = nullptr;
}

void initPlayer(Player &player) {
    player.currentSong = nullptr;
    player.isPlaying = false;
    player.currentPlaylistNode = nullptr;
    player.currentPlaylist = nullptr;
}

adrArtis createArtis(string nama) {
    adrArtis p = new Artis;
    p->nama = nama;
    p->firstLagu = nullptr;
    p->nextArtis = nullptr;
    return p;
}

adrLagu createLagu(int id, string judul, string genre, int durasi, int tahun) {
    adrLagu p = new Lagu;
    p->idLagu = id;
    p->judul = judul;
    p->genre = genre;
    p->durasi = durasi;
    p->tahun = tahun;
    p->nextLagu = nullptr;
    return p;
}

// INSERT 

void addArtisToLibrary(Library &lib, adrArtis artis) {
    if (lib.firstArtis == nullptr) {
        lib.firstArtis = artis;
    } else {
        adrArtis p = lib.firstArtis;
        while (p->nextArtis != nullptr) {
            p = p->nextArtis;
        }
        p->nextArtis = artis;
    }
}

void addLaguToArtis(adrArtis artis, adrLagu lagu) {
    if (artis->firstLagu == nullptr) {
        artis->firstLagu = lagu;
    } else {
        adrLagu p = artis->firstLagu;
        while (p->nextLagu != nullptr) {
            p = p->nextLagu;
        }
        p->nextLagu = lagu;
    }
}

void addLaguToPlaylist(Playlist &pl, adrLagu lagu) {
    adrPlaylistNode p = new PlaylistNode;
    p->laguPtr = lagu;
    p->next = nullptr;

    if (pl.firstSong == nullptr) {
        pl.firstSong = p;
    } else {
        adrPlaylistNode q = pl.firstSong;
        while (q->next != nullptr) {
            q = q->next;
        }
        q->next = p;
    }
}

// PRINT =================================================================================

void displayLibrary(const Library &lib) {
    if (lib.firstArtis == nullptr) {
        cout << "Library Kosong" << endl;
        return;
    }
    adrArtis p = lib.firstArtis;
    while (p != nullptr) {
        cout << "Artis: " << p->nama << endl;
        displayArtisWithSongs(p);
        cout << endl;
        p = p->nextArtis;
    }
}

void displayArtisWithSongs(const adrArtis artis) {
    if (artis->firstLagu == nullptr) {
        cout << "Tidak ada lagu" << endl;
    } else {
        adrLagu p = artis->firstLagu;
        while (p != nullptr) {
            cout << p->idLagu << p->judul << p->genre << endl;
            p = p->nextLagu;
        }
    }
}

void displayPlaylist(const Playlist &pl){
    cout << "Playlist: " << pl.namaPlaylist << endl;
    if (pl.firstSong == nullptr) {
        cout << "Playlist Kosong" << endl;
    } else {
        adrPlaylistNode p = pl.firstSong;
        int i = 1;
        while (p != nullptr) {
            cout << "  " << i << ". " << p->laguPtr->judul << " - " << p->laguPtr->genre << endl;
            p = p->next;
            i++;
        }
    }
}

// SEARCH =================================================================================

adrLagu findLaguById(const Library &lib, int idLagu, adrArtis parentArtis) {
    adrArtis p = lib.firstArtis;
    while (p != nullptr) {
        adrLagu q = p->firstLagu;
        while (q != nullptr) {
            if (q->idLagu == idLagu) {
                return q;
            }
            q = q->nextLagu;
        }
        p = p->nextArtis;
    }
    return nullptr;
}

adrLagu findLaguByTitle(const Library &lib, string judul, adrArtis parentArtis) {
    adrArtis p = lib.firstArtis;
    while (p != nullptr) {
        adrLagu q = p->firstLagu;
        while (q != nullptr) {
            if (q->judul == judul) return q;
            q = q->nextLagu;
        }
        p = p->nextArtis;
    }
    return nullptr;
}

// DELETE =================================================================================

void deleteLaguFromArtis(adrArtis artis, int idLagu) {
    if (artis == nullptr || artis->firstLagu == nullptr) return;

    adrLagu p = artis->firstLagu;
    adrLagu q = nullptr;

    while (p != nullptr) {
        if (p->idLagu == idLagu) {
            if (q == nullptr) {
                artis->firstLagu = p->nextLagu;
            } else {
                q->nextLagu = p->nextLagu;
            }
            delete p;
            return;
        }
        q = p;
        p = p->nextLagu;
    }
}

void deleteArtisFromLibrary(Library &lib, string namaArtis) {
    if (lib.firstArtis == nullptr) return;

    adrArtis p = lib.firstArtis;
    adrArtis q = nullptr;

    while (p != nullptr) {
        if (p->nama == namaArtis) {
            adrLagu laguNode = p->firstLagu;
            while (laguNode != nullptr) {
                adrLagu temp = laguNode;
                laguNode = laguNode->nextLagu;
                delete temp;
            }

            if (q == nullptr) {
                lib.firstArtis = p->nextArtis;
            } else {
                q->nextArtis = p->nextArtis;
            }
            delete p;
            return;
        }
        q = p;
        p = p->nextArtis;
    }
}

void removeLaguFromPlaylist(Playlist &pl, int idLagu) {
    if (pl.firstSong == nullptr) return;

    adrPlaylistNode p = pl.firstSong;
    adrPlaylistNode q = nullptr;

    while (p != nullptr) {
        if (p->laguPtr->idLagu == idLagu) {
            if (q == nullptr) {
                pl.firstSong = p->next;
            } else {
                q->next = p->next;
            }
            delete p;
            return;
        }
        q = p;
        p = p->next;
    }
}

// Fitur selanjutnya =================================================================================

void updateLagu(adrLagu lagu, string judul, string genre, int durasi, int tahun) {}
void clearPlaylist(Playlist &pl) {}
void playSong(Player &player, adrLagu lagu) {}
void stopSong(Player &player) {}
void nextSong(Player &player, const Library &lib) {}
void prevSong(Player &player) {}
adrLagu findSimilarSong(const Library &lib, adrLagu currentSong, string currentArtisName) { return nullptr; }
int countLaguInArtis(const adrArtis artis) { return 0; }
void freeLibrary(Library &lib) {}
void freePlaylist(Playlist &pl) {}
int generateRandomId() { return 0; }
void shufflePlaylist(Playlist &pl) {}
