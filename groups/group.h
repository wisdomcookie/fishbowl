#ifndef GROUP_H
#define GROUP_H
#include "../profiles/aquarium.h"
#include "../comm/post.h"
#include <set>
#include <string>
#include <vector>

class profile;
#include "../profiles/profile.h"

class Group
{
public:
    Group();
    Group(std::string name);

    ~Group();

    void add_member(profile *profile);
    void remove_member(profile *profile);
    void add_admin(profile *admin);
    void remove_admin(profile *admin);
    void add_post(Post *post);
    void remove_post(Post *post);

    void set_description(std::string newDescription);

    std::string get_name();
    std::string get_description();
    std::set<profile*> get_admin();
    std::set<profile*> get_members();
    Aquarium get_aquarium();

private:
    std::string name;
    std::string description;
    std::set<profile*> admin;
    std::set<profile*> members;
    std::vector<Post*> postHistory;
    Aquarium aquarium;

};

#endif // GROUP_H
