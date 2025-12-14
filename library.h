#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include "types.h"

void initLibrary(Library &lib);
adrLagu createLagu(int id, string judul, string genre, int durasi, int tahun);
adrArtis createArtis(string namaArtis);

// --- FITUR ADMIN ---

adrArtis findArtis(Library lib, string namaArtis);
void insertArtis(Library &lib, adrArtis pArtis);
void insertLagu(Library &lib, adrLagu pLagu, string namaArtis);

// --------------------

void viewAllSongs(Library lib);
adrLagu searchSongById(Library lib, int idLagu);
adrLagu searchSongByJudul(Library lib, string judul);
adrLagu searchSongByGenre(Library lib, string genre);
adrArtis searchArtisByName(Library lib, string namaArtis);

// --- FITUR ADMIN ---

bool deleteLagu(Library &lib, int idLagu, Sistem &sys);
bool deleteArtist(Library &lib, string namaArtis, Sistem &sys);
void updateLagu(Library &lib, int idLagu);

// --------------------

adrLagu findSimilarSong(Library lib, adrLagu currentSong);

#endif // LIBRARY_H_INCLUDED
