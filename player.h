#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "types.h"

void initPlayer(Player &player);
void playSong(Player &p, adrLagu song);
void nextSong(Player &p, Library lib);
void prevSong(Player &p, Library lib);

#endif // PLAYER_H_INCLUDED
