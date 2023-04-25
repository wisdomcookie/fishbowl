#ifndef GROUP_H
#define GROUP_H

#include <set>
#include <string>
#include <vector>
#include <QDateTime>

class Profile;
#include "../profiles/profile.h"
//#include "../profiles/aquarium.h"
#include "../comm/post.h"

class Group
{
public:
    Group();
    Group(std::string name);

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
    std::vector<Post*> postHistory;
    //Aquarium get_aquarium();

private:
    std::string name;
    std::string description;
    std::set<Profile*> admin;
    std::set<Profile*> members;
    //Aquarium aquarium;

};

#endif // GROUP_H
