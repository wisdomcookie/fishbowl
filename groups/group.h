#ifndef GROUP_H
#define GROUP_H

#include "../profiles/aquarium.h"
#include <set>
#include <string>
#include <vector>
#include "QString"

class Profile;
class Post;
class Aquarium;

class Group
{
public:
    Group();
    Group(std::string name);
    Group(QString name, std::vector<Profile*> participants);

    ~Group();

    void add_member(Profile *profile);
    void remove_member(Profile *profile);
    void add_admin(Profile *admin);
    void remove_admin(Profile *admin);
    void add_post(Post *post);
    void remove_post(Post *post);

    void set_description(std::string newDescription);

    std::string get_name();
    std::string get_description();
    std::set<Profile*> get_admin();
    std::set<Profile*> get_members();
    Aquarium get_aquarium();

private:
    std::string name;
    std::string description;
    std::set<Profile*> admin;
    std::set<Profile*> members;
    std::vector<Post*> postHistory;
    Aquarium aquarium;

};

#endif // GROUP_H
