#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <iostream>
#include <cstdlib>  // ini buat random values
#include <ctime> // ini buat masukin variabel ke

using namespace std;


struct Lagu;
struct Artis;
struct PlaylistNode;

typedef Lagu *adrLagu;
typedef Artis *adrArtis;
typedef PlaylistNode *adrPlaylistNode;

struct Lagu {
    int idLagu;
    string judul;
    string genre;
    int durasi;
    int tahun;
    adrLagu nextLagu;
};

struct Artis {
    string nama;
    adrLagu firstLagu;
    adrArtis nextArtis;
};

struct PlaylistNode {
    adrLagu laguPtr;
    adrPlaylistNode next;
};

struct Playlist {
    string namaPlaylist;
    adrPlaylistNode firstSong;
};

struct Library {
    adrArtis firstArtis;
    int totalSongs;
};

struct Player {
    adrLagu currentSong;
    bool isPlaying;
    adrPlaylistNode currentPlaylistNode;
    Playlist *currentPlaylist;
};

// CREATE LIST ============================================================================
void initLibrary(Library &lib);
void initPlaylist(Playlist &pl, string nama);
void initPlayer(Player &player);


// ALLOCATE ===============================================================================
adrArtis createArtis(string nama);
adrLagu createLagu(int id, string judul, string genre, int durasi, int tahun);


// INSERT ==================================================================================
void addArtisToLibrary(Library &lib, adrArtis artis);
void addLaguToArtis(adrArtis artis, adrLagu lagu);
void addLaguToPlaylist(Playlist &pl, adrLagu lagu);


// PRINT ====================================================================================
void displayLibrary(const Library &lib);
void displayArtisWithSongs(const adrArtis artis);
void displayPlaylist(const Playlist &pl);

// SEARCH ===================================================================================
adrLagu findLaguById(const Library &lib, int idLagu, adrArtis parentArtis);
adrLagu findLaguByTitle(const Library &lib, string judul, adrArtis parentArtis);


// DELETE ====================================================================================
void deleteLaguFromArtis(adrArtis artis, int idLagu);
void deleteArtisFromLibrary(Library &lib, string namaArtis);
void removeLaguFromPlaylist(Playlist &pl, int idLagu);



// FITUR TAMBAHAN ====================================================================================
// dibantu AI untuk menentukan parameter
void updateLagu(adrLagu lagu, string judul, string genre, int durasi, int tahun);
void clearPlaylist(Playlist &pl);
void playSong(Player &player, adrLagu lagu);
void stopSong(Player &player);
void nextSong(Player &player, const Library &lib);
void prevSong(Player &player);
adrLagu findSimilarSong(const Library &lib, adrLagu currentSong, string currentArtisName);
int countLaguInArtis(const adrArtis artis);
void freeLibrary(Library &lib);
void freePlaylist(Playlist &pl);
int generateRandomId();
void shufflePlaylist(Playlist &pl);

#endif
