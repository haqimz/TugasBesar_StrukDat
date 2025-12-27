#include "library.h"
#include "playlist.h"

void initLibrary(Library &lib) {
    lib.firstArtis = nullptr;
    lib.totalSongs = 0;
};

adrLagu createLagu(int id, string judul, string genre, int durasi, int tahun) {
    adrLagu pLagu = new Lagu;
    pLagu->idLagu = id;
    pLagu->judul = judul;
    pLagu->genre = genre;
    pLagu->durasi = durasi;
    pLagu->tahun = tahun;
    pLagu->nextLagu = NULL;
    pLagu->artis = NULL;
    return pLagu;
};

adrArtis createArtis(string namaArtis) {
    adrArtis pArtis = new Artis;
    pArtis->nama = namaArtis;
    pArtis->firstLagu = NULL;
    pArtis->nextArtis = NULL;
    return pArtis;
};

// --- FITUR ADMIN ---

adrArtis findArtis(Library lib, string namaArtis) {
    adrArtis current = lib.firstArtis;
    while (current != nullptr) {
        if (current->nama == namaArtis) {
            return current;
        }
        current = current->nextArtis;
    }
    return nullptr;
};

void insertArtis(Library &lib, adrArtis pArtis) {
    pArtis->nextArtis = lib.firstArtis;
    lib.firstArtis = pArtis;
};

void insertLagu(Library &lib, adrLagu pLagu, string namaArtis) {
    adrArtis pArtis = findArtis(lib, namaArtis);

    if (pArtis == nullptr) {
        pArtis = createArtis(namaArtis);
        insertArtis(lib, pArtis);
    }

    pLagu->artis = pArtis;
    pLagu->nextLagu = pArtis->firstLagu;
    pArtis->firstLagu = pLagu;

    lib.totalSongs++;
    cout << pLagu->judul << " - " << pArtis->nama << " berhasil ditambahkan." << endl;
};

// --------------------

void viewAllSongs(Library lib){
    if (lib.firstArtis == nullptr) {
        cout << "Library kosong." << endl;
        return;
    }
    cout << "===== LIST SEMUA LAGU DI LIBRARY (" << lib.totalSongs << " Lagu Total) =====" << endl;
    adrArtis pArtis = lib.firstArtis;
    while (pArtis != NULL) {
        cout << "\n--- ARTIS: " << pArtis->nama << " ---" << endl;
        adrLagu pLagu = pArtis->firstLagu;
        if (pLagu == NULL) {
            cout << "  (Tidak ada lagu)" << endl;
        } else {
            cout << "ID\t| Judul\t\t| Genre\t| Tahun" << endl;
            cout << "---------------------------------------" << endl;
            while (pLagu != NULL) {
                cout << pLagu->idLagu << "\t| " << pLagu->judul
                     << "\t\t| " << pLagu->genre << "\t| " << pLagu->tahun << endl;
                pLagu = pLagu->nextLagu;
            }
        }
        pArtis = pArtis->nextArtis;
    }
};

adrLagu searchSongById(Library lib, int idLagu){
    adrArtis pArtis = lib.firstArtis;
    while (pArtis != NULL) {
        adrLagu pLagu = pArtis->firstLagu;
        while (pLagu != NULL) {
            if (pLagu->idLagu == idLagu) return pLagu;
            pLagu = pLagu->nextLagu;
        }
        pArtis = pArtis->nextArtis;
    }
    return NULL;
};

adrLagu searchSongByJudul(Library lib, string judul) {
    adrArtis pArtis = lib.firstArtis;
    while (pArtis != nullptr) {
        adrLagu pLagu = pArtis->firstLagu;
        while (pLagu != nullptr) {
            if (pLagu->judul == judul) {
                return pLagu; // Lagu ditemukan
            }
            pLagu = pLagu->nextLagu;
        }
        pArtis = pArtis->nextArtis;
    }
    return nullptr; // ga ketemu di library
}

adrLagu searchSongByGenre(Library lib, string genre) {
    adrArtis pArtis = lib.firstArtis;
    while (pArtis != NULL) {
        adrLagu pLagu = pArtis->firstLagu;
        while (pLagu != NULL) {
            if (pLagu->genre == genre) return pLagu;
            pLagu = pLagu->nextLagu;
        }
        pArtis = pArtis->nextArtis;
    }
    return NULL;
};

adrArtis searchArtisByName(Library lib, string namaArtis) {
    return findArtis(lib, namaArtis);
};

// --- FITUR ADMIN ---

bool deleteLagu(Library &lib, int idLagu, Sistem &sys) {
    if (lib.firstArtis == NULL) {
        cout << "Gagal menghapus lagu: Library kosong." << endl;
        return false;
    }

    adrArtis pArtis = lib.firstArtis;

    while (pArtis != NULL) {

        adrLagu pLagu = pArtis->firstLagu;
        adrLagu prevLagu = NULL;

        while (pLagu != NULL) {

            if (pLagu->idLagu == idLagu) {
                adrLagu deletedSong = pLagu;

                if (prevLagu == NULL) {
                    pArtis->firstLagu = pLagu->nextLagu;
                } else {
                    prevLagu->nextLagu = pLagu->nextLagu;
                }

                deleteSongReferenceFromAllPlaylists(sys, deletedSong);

                delete deletedSong;

                lib.totalSongs--;
                cout << "Lagu ID " << idLagu << " berhasil dihapus dari Library dan semua Playlist." << endl;
                return true;
            }

            prevLagu = pLagu;
            pLagu = pLagu->nextLagu;
        }

        pArtis = pArtis->nextArtis;
    }

    cout << "Gagal menghapus: Lagu dengan ID " << idLagu << " tidak ditemukan." << endl;
    return false;
}

bool deleteArtist(Library &lib, string namaArtis, Sistem &sys) {
    if (lib.firstArtis == NULL) {
        cout << "Gagal menghapus: Library kosong." << endl;
        return false;
    }

    adrArtis currentArtis = lib.firstArtis;
    adrArtis prevArtis = NULL;

    while (currentArtis != NULL) {
        if (currentArtis->nama == namaArtis) {

            cout << "\n[HAPUS] Menghapus artis '" << namaArtis << "' dan semua lagunya..." << endl;

            adrLagu pLagu = currentArtis->firstLagu;
            while (pLagu != NULL) {
                adrLagu tempLagu = pLagu;
                pLagu = pLagu->nextLagu;
                delete tempLagu;
                lib.totalSongs--;
            }

            if (prevArtis == NULL) {
                lib.firstArtis = currentArtis->nextArtis;
            } else {
                prevArtis->nextArtis = currentArtis->nextArtis;
            }

            delete currentArtis;

            cout << "✅ Artis '" << namaArtis << "' berhasil dihapus dari Library." << endl;
            return true;
        }

        prevArtis = currentArtis;
        currentArtis = currentArtis->nextArtis;
    }

    cout << "Gagal menghapus: Artis '" << namaArtis << "' tidak ditemukan." << endl;
    return false;
}

void updateLagu(Library &lib, int idLagu) {
    adrLagu target = searchSongById(lib, idLagu);
    if (target == NULL) {
        cout << "Lagu tidak ditemukan!" << endl;
        return;
    }
    cout << "--- Update Data Lagu ID: " << idLagu << " ---" << endl;
    cout << "Masukkan Judul baru: "; cin >> target->judul;
    cout << "Masukkan Genre baru: "; cin >> target->genre;
    cout << "Masukkan Tahun baru: "; cin >> target->tahun;
    cout << "Data berhasil diperbarui!" << endl;
}

// --------------------

adrLagu findSimilarSong(Library lib, adrLagu currentSong) {
    if (lib.firstArtis == NULL || currentSong == NULL) return NULL;

    string targetGenre = currentSong->genre;
    adrArtis pArtis = lib.firstArtis;

    while (pArtis != NULL) {
        adrLagu pLagu = pArtis->firstLagu;
        while (pLagu != NULL) {
            if (pLagu->genre == targetGenre && pLagu != currentSong) {
                return pLagu;
            }
            pLagu = pLagu->nextLagu;
        }
        pArtis = pArtis->nextArtis;
    }
    return NULL;
}

