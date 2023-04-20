#ifndef FISH_H
#define FISH_H
#include <string>

using namespace std;

class Profile;
//#include "profile.h"

class Fish
{
public:
    Fish();
    Fish(string name, string species);
    ~Fish();

    //Fish sub-profile information
    string name, location, species, bio;
    Profile* owner;

};

#endif // FISH_H
