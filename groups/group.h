#ifndef GROUP_H
#define GROUP_H
#include "../admin/administrator.h"
#include "../profiles/aquarium.h"
#include "../profiles/person.h"
#include "../comm/post.h"
#include <set>
#include <string>
#include <vector>

class Group
{
public:
    Group();
    Group(std::string name);

    ~Group();

    void add_member(Person *profile);
    bool remove_member(Person *profile);
    void add_admin(Administrator *admin);
    bool remove_admin(Administrator *admin);
    void add_post(Post *post);
    bool remove_post(Post *post);

    void set_description(std::string newDescription);

    std::string get_name();
    std::string get_description();
    std::set<Administrator*> get_admin();
    std::set<Person*> get_members();
    Aquarium get_aquarium();


private:
    std::string name;
    std::string description;
    std::set<Administrator*> admin;
    std::set<Person*> members;
    std::vector<Post*> postHistory;
    Aquarium aquarium;

};

#endif // GROUP_H
