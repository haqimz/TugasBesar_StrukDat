#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "types.h"
#include "library.h"
#include "playlist.h"
#include "player.h"


void initSistem (Sistem &sys);
adrUser createNewUser(string uname, string pass);
void registerAdmin(Sistem &sys, string uname, string pass);
adrUser findUser(Sistem sys, string uname);
void menuLogin(Sistem &sys, Library lib, Player &player);
void menuAdmin(Library &lib);
void menuUser(adrUser currentUserNode, Library &lib, Player &player);

#endif // USER_H_INCLUDED
