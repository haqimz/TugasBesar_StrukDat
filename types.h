#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
#include <iostream>

using namespace std;

typedef struct Lagu *adrLagu;
typedef struct Artis *adrArtis;
typedef struct PlaylistNode *adrPlaylistNode;
typedef struct PlaylistHeadNode* adrPlaylistHead;
typedef struct UserNode *adrUser;

struct User {
    string username;
    string password;
    adrPlaylistHead firstPlaylist;
};

struct UserNode {
    User userData;
    adrUser nextUser;
};

struct Sistem {
    adrUser firstUser;
};

struct Lagu {
    int idLagu;
    string judul;
    string genre;
    int durasi;
    int tahun;
    adrLagu nextLagu;
    adrArtis artis;
};

struct Artis {
    string nama;
    adrLagu firstLagu;
    adrArtis nextArtis;
};

struct PlaylistNode {
    adrLagu lagu;
    adrPlaylistNode next;
};

struct Playlist {
    string namaPlaylist;
    adrPlaylistNode firstSong;
};

struct PlaylistHeadNode {
    Playlist playlistData;
    adrPlaylistHead nextPlaylist;
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
    bool isShufling;
};

void initLibrary(Library &lib);
void initPlayer(Player &Player);
void initPlaylist(Playlist &pl);


#endif // TYPES_H_INCLUDED
