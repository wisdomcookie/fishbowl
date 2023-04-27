#ifndef GROUPAQUARIUM_H
#define GROUPAQUARIUM_H


#include <set>
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

    std::set<Aquarium*> aquariumCollection;

};

#endif // GROUPAQUARIUM_H
