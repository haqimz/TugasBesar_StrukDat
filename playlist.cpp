#include "playlist.h"

void initPlaylist(Playlist &pl) {
    pl.firstSong = NULL;
    pl.namaPlaylist = nullptr;
    pl.count = 0;
}


adrPlaylistHead createPlaylistHeadNode(string namaPlaylist) {
    adrPlaylistHead pHead = new PlaylistHeadNode;

    pHead->playlistData.namaPlaylist = namaPlaylist;
    pHead->playlistData.firstSong = nullptr;
    pHead->playlistData.count = 0;
    pHead->nama = namaPlaylist;
    pHead->nextPlaylist = nullptr;

    return pHead;
}

adrPlaylistNode createPlaylistNode(adrLagu songPtr) {
    adrPlaylistNode pNode = new PlaylistNode;
    pNode->lagu = songPtr;
    pNode->next = nullptr;
    return pNode;
}

void insertNewPlaylist(adrPlaylistHead &head, string namaPlaylist) {
    if (findPlaylist(head, namaPlaylist) != nullptr) {
        cout << "Gagal: Playlist dengan nama '" << namaPlaylist << "' sudah ada." << endl;
        return;
    }

    adrPlaylistHead newHead = createPlaylistHeadNode(namaPlaylist);
    newHead->nextPlaylist = head;
    head = newHead;

    cout << "Playlist '" << namaPlaylist << "' berhasil dibuat." << endl;
}

adrPlaylistHead findPlaylist(adrPlaylistHead head, string namaPlaylist) {
    adrPlaylistHead current = head;
    while (current != NULL) {
        if (current->nama == namaPlaylist) { // Case-Sensitive
            return current;
        }
        current = current->nextPlaylist;
    }
    return NULL;
}

void viewAllUserPlaylists(adrPlaylistHead head) {
    adrPlaylistHead current = head;
    if (current == NULL) {
        cout << "Anda belum memiliki Playlist." << endl;
        return;
    }
    cout << "\n===== LIST PLAYLIST ANDA =====" << endl;
    int count = 1;
    while (current != NULL) {
        cout << count++ << ". " << current->nama
             << " (" << current->playlistData.count << " Lagu)" << endl;
        current = current->nextPlaylist;
    }
}

void addSongToPlaylist(Playlist &pl, adrLagu songPtr) {
    adrPlaylistNode pNode = createPlaylistNode(songPtr);

    pNode->next = pl.firstSong;
    pl.firstSong = pNode;
    pl.count++;

    cout << "Lagu '" << songPtr->judul << "' berhasil ditambahkan ke Playlist." << endl;
}

bool deleteSongFromPlaylist(Playlist &pl, string namaLagu) {
    if (pl.firstSong == NULL) {
        cout << "Playlist kosong." << endl;
        return false;
    }

    adrPlaylistNode current = pl.firstSong;
    adrPlaylistNode prev = NULL;

    while (current != NULL) {
        if (current->lagu->judul == namaLagu) {

            if (prev == NULL) {
                pl.firstSong = current->next;
            } else {
                prev->next = current->next;
            }

            delete current;
            pl.count--;

            cout << "Lagu '" << namaLagu << "' berhasil dihapus dari Playlist." << endl;
            return true;
        }

        prev = current;
        current = current->next;
    }

    cout << "Gagal menghapus: Lagu '" << namaLagu << "' tidak ditemukan di Playlist ini." << endl;
    return false;
}

void viewPlaylistSongs(Playlist pl) {
    adrPlaylistNode current = pl.firstSong;
    if (current == NULL) {
        cout << "Playlist ini kosong." << endl;
        return;
    }

    cout << "ID\t| Judul\t\t| Artis\t\t| Genre" << endl;
    cout << "---------------------------------------------------" << endl;
    while (current != NULL) {
        cout << current->lagu->idLagu << "\t| " << current->lagu->judul
             << "\t\t| " << current->lagu->artis->nama
             << "\t\t| " << current->lagu->genre << endl;
        current = current->next;
    }
}

void deleteSongReferenceFromPlaylist(Playlist &pl, adrLagu deletedSongPtr) {
    adrPlaylistNode current = pl.firstSong;
    adrPlaylistNode prev = NULL;

    while (current != NULL) {
        if (current->lagu == deletedSongPtr) {

            if (prev == NULL) {
                pl.firstSong = current->next;
                adrPlaylistNode temp = current;
                current = pl.firstSong;
                delete temp;
            } else {
                prev->next = current->next;
                adrPlaylistNode temp = current;
                current = prev->next;
                delete temp;
            }
            pl.count--;

        } else {
            prev = current;
            current = current->next;
        }
    }
}

void deleteSongReferenceFromAllPlaylists(Sistem &sys, adrLagu deletedSongPtr) {
    if (sys.firstUser == NULL) return;

    cout << "\n[START] Membersihkan referensi lagu di semua Playlist User..." << endl;

    adrUser pUser = sys.firstUser;
    while (pUser != NULL) {

        adrPlaylistHead pHead = pUser->userData.firstPlaylist;
        while (pHead != NULL) {

            deleteSongReferenceFromPlaylist(pHead->playlistData, deletedSongPtr);

            pHead = pHead->nextPlaylist;
        }

        pUser = pUser->nextUser;
    }
    cout << "[END] Pembersihan referensi selesai." << endl;
}
