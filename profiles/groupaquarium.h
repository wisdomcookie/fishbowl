#ifndef GROUPAQUARIUM_H
#define GROUPAQUARIUM_H


#include <map>

class Profile;
class Aquarium;
class Group;

class GroupAquarium
{
public:
    GroupAquarium();
    GroupAquarium(Group *owner);

    void add_member_aquarium(Profile *member);

private:
    Group *owner;

    std::map<int, Aquarium*> aquariumCollection; // key is the id of the owner's profile

};

#endif // GROUPAQUARIUM_H
