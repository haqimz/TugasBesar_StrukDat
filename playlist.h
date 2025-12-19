#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED

#include "types.h"

void initPlaylist(Playlist &pl);
adrPlaylistHead createPlaylistHeadNode(string namaPlaylist);
adrPlaylistNode createPlaylistNode(adrLagu songPtr);

void insertNewPlaylist(adrPlaylistHead &head, string namaPlaylist);
adrPlaylistHead findPlaylist(adrPlaylistHead head, string namaPlaylist);
void viewAllUserPlaylists(adrPlaylistHead head);

void addSongToPlaylist(Playlist &pl, adrLagu songPtr);
bool deleteSongFromPlaylist(Playlist &pl, string namaLagu);

void viewPlaylistSongs(Playlist pl);

void deleteSongReferenceFromAllPlaylists(Sistem &sys, adrLagu deletedSongPtr);

#endif // PLAYLIST_H_INCLUDED
