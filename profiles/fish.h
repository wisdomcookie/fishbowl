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
    fish(string name, string species, string bio);
    ~fish();

    //Fish sub-profile information
    string name, location, species, bio;
    profile* owner;

    //  -------- Methods --------  //

    void changeName(string n);
    void changeLocation(string l);
    void changeBio(string b);
    void changeSpecies(string s); //in case of typo, not that your fish can change species!

    //Getter Methods

    string getName();
    string getLocation();
    string getSpecies();
    string getBio();
    profile* getOwner();
};

#endif // FISH_H
