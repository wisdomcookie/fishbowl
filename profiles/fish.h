#ifndef FISH_H
#define FISH_H
#include <string>

using namespace std;

class profile;
#include "profile.h"

class fish
{
public:
    fish();
    fish(string name, string species);
    ~fish();

    //Fish sub-profile information
    string name, location, species, bio;
    profile* owner;

};

#endif // FISH_H
