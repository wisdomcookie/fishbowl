#include "profile.h"

profile::profile() {

}

profile::profile(string username, string password) {
    //need access to general database of users' usernames and ID's
    this->username = username;
    this->password = password;
    //generate a unique ID by order of profile creation
}

profile::~profile() {
    delete this;
}

/**
 * Add a friend to your pending friends list. A signal that the target profile
 * has accepted your request will be required for the target profile to be
 * moved from your pending friends list to your friends list.
 * @brief profile::addFriend
 * @param x
 */
void profile::addFriend(profile* x) {

}

/**
 * Remove a friend from your friends list. This does not require a signal from
 * the target profile to take effect. This method will call the addendum method
 * removeFriendForeign that will remove you from the ex-friend's friend list
 * without their permission.
 * @brief profile::removeFriend
 * @param x
 */
void profile::removeFriend(profile* x) {
    for (unsigned long i=0; i<friendsList.size(); i++) {
        if (friendsList.at(i) == x) {
            friendsList.erase(friendsList.begin() + i);
        }
    }
    removeFriendForeign(this);
}

/**
 * Refer to description in removeFriend method.
 * @brief profile::removeFriendForeign
 * @param x
 */
void profile::removeFriendForeign(profile* x) {
    for (unsigned long i=0; i<friendsList.size(); i++) {
        if (friendsList.at(i) == x) {
            friendsList.erase(friendsList.begin() + i);
        }
    }
}

/**
 * This method and changeUsername & changePassword are simple edit
 * methods available to the user to change their profile info.
 */
void profile::changeBio(string x) {
    bio = x;
}
void profile::changeUsername(string x) {
    username = x;
}
void profile::changePassword(string x) {
    password = x;
}

/**
 * The following method will add a fish with the specified name
 * to the profile's collection of fish.
 * @brief profile::createFish
 * @param name
 */
void profile::createFish(string name, string species) {
    fish* x = new fish(name, species);
    collection.push_back(x);
    x->location = this->location;
}

/**
 * Will remove a fish from the profile's collection.
 * @brief profile::removeFish
 * @param x
 */
void profile::removeFish(fish* x) {
    for (unsigned long i=0; i<collection.size(); i++) {
        if (collection.at(i) == x) {
            collection.erase(collection.begin() + i);
        }
    }
}

/**
 * Change bio of particular fish in collection.
 * @brief profile::changeFishBio
 * @param x
 * @param y
 */
void profile::changeFishBio(fish* x, string y) {
    x->bio = y;
}

/**
 * The fish's location will be set to the profile's current
 * location when created. This method will allow that to be
 * changed at any time, at the discretion of the user.
 * @brief profile::changeFishLocation
 * @param x
 * @param y
 */
void profile::changeFishLocation(fish* x, string y) {
    x->location = y;
}










