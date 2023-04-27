#include "profile.h"
#include "fish.h"
#include "aquarium.h"
#include "../groups/group.h"
#include "../comm/post.h"
#include "../comm/postcomment.h"
#include "../comm/groupchat.h"
#include "../comm/message.h"


Profile::Profile() {
}

//Profile::Profile(string username, string password) {
////    this->username = username;
////    this->password = password;
//    Database d;
//    d.query_exec("select * from profiles");  //make sure name of table is correct
//    id = d.query_size() + 1;
//}

Profile::Profile(int id, QString username, QString password, QString firstName, QString lastName, int age, QString location, QString type, QDateTime dateCreated, QString description):
    profileId(id), username(username), password(password), firstName(firstName), lastName(lastName), location(location), type(type), dateCreated(dateCreated), description(description)
{

    aquarium = new Aquarium(this);
}

Profile::Profile(std::map<QString, QString> profileData){
    profileId = profileData[QString("profile_id")].toInt();
    username = profileData[QString("username")];
    firstName = profileData[QString("first_name")];
    lastName = profileData[QString("last_name")];
    age = profileData[QString("age")].toInt();
    location = profileData[QString("location")];
    type = profileData[QString("type")];

    QString dateString = profileData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    description = profileData[QString("description")];
}

Profile::~Profile() {
    delete aquarium;
}


void Profile::add_fish(Fish *fish){
    aquarium->add_fish(fish);
}
void Profile::add_friend(Profile *profile){
    friends[profile->get_id()] = profile;
}
void Profile::add_group(Group *group){
    groups[group->get_id()] = group;
}
void Profile::add_group_as_admin(Group *g){

}
void Profile::add_groupchat(GroupChat *groupchat){
    groupchats[groupchat->get_id()] = groupchat;
}
void Profile::add_message(Message* message){
    messages[message->get_id()] = message;
}
void Profile::add_post(Post *post){
    posts[post->get_id()] = post;
}
void Profile::add_comment(PostComment *comment){
    comments[comment->get_id()] = comment;
}

void Profile::edit_profile(QString firstName, QString lastName, int age, QString location, QString description){
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    this->location = location;
    this->description = description;
}
void Profile::edit_fish(Fish *fish, QString name, int age, QString location, QString species, QString description){
    fish->edit_data(name, age, location, species, description);
}
void Profile::edit_post(Post *post, QString newContent){
    post->edit_content(newContent);
}
void Profile::edit_comment(PostComment *comment, QString newContent){
    comment->edit_content(newContent);
}

void Profile::remove_fish(Fish *fish){
    aquarium->remove_fish(fish);
}
void Profile::leave_group(Group *group){
    groups.erase(group->get_id());
}
void Profile::leave_groupchat(GroupChat *groupchat){
    groupchats.erase(groupchat->get_id());
}
void Profile::delete_post(Post *post){
    posts.erase(post->get_id());
}
void Profile::delete_comment(PostComment *comment){
    comments.erase(comment->get_id());
}


// --- Getter/Setter Methods --- //

int Profile::get_id(){
    return profileId;
}
QString Profile::get_username(){
    return username;
}
QString Profile::get_firstName(){
    return firstName;
}
QString Profile::get_lastName(){
    return lastName;
}
int Profile::get_age(){
    return age;
}
QString Profile::get_location(){
    return location;
}
QString Profile::get_type(){
    return type;
}
QDateTime Profile::get_dateCreated(){
    return dateCreated;
}
QString Profile::get_description(){
    return description;
}

std::vector<Fish*> Profile::get_fishList(){
    std::map<int, Fish*> fishMap = aquarium->get_fish();
    std::vector<Fish*> res;
    for(auto i = fishMap.begin(); i != fishMap.end(); i++){
        res.push_back(i->second);
    }
    return res;
}

std::vector<Profile*>  Profile::get_friendList(){
    std::vector<Profile*> res;
    for(auto i = friends.begin(); i != friends.end(); i++){
        res.push_back(i->second);
    }
    return res;
}

std::vector<Group*> Profile::get_groupList(){
    std::vector<Group*> res;
    for(auto i = groups.begin(); i != groups.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
std::vector<Post*> Profile::get_postHistory(){
    std::vector<Post*> res;
    for(auto i = posts.begin(); i != posts.end(); i++){
        res.push_back(i->second);
    }
    return res;
}
std::vector<Message*> Profile::get_messageHistory(){
    std::vector<Message*> res;
    for(auto i = messages.begin(); i != messages.end(); i++){
        res.push_back(i->second);
    }
    return res;
}



/**
 * Add a friend to your friends list. Your new friend will need to add you back
 * for the friending process to be completed.
 * @brief profile::addFriend
 * @param x
 */
void Profile::addFriend(Profile* x) {
    friendsList.push_back(x);
}

/**
 * Remove a friend from your friends list. This does not require a signal from
 * the target profile to take effect. This method will call the addendum method
 * removeFriendForeign that will remove you from the ex-friend's friend list
 * without their permission.
 * @brief profile::removeFriend
 * @param x
 */
void Profile::removeFriend(Profile* x) {
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
void Profile::removeFriendForeign(Profile* x) {
    for (unsigned long i=0; i<x->friendsList.size(); i++) {
        if (x->friendsList.at(i) == this) {
            x->friendsList.erase(friendsList.begin() + i);
        }
    }
}

/**
 * This method and changeUsername & changePassword are simple edit
 * methods available to the user to change their profile info.
 */
void Profile::changeBio(string x) {
    bio = x;
}
void Profile::changeUsername(string x) {
    username = x;
}
void Profile::changePassword(string x) {
    password = x;
}

/**
 * The following method will add a fish with the specified name
 * to the profile's collection of fish.
 * @brief profile::createFish
 * @param name
 */
void Profile::createFish(string name, string species) {
    Fish* x = new Fish(name, species);
    collection.push_back(x);
    x->location = this->location;
}

/**
 * Will remove a fish from the profile's collection.
 * @brief profile::removeFish
 * @param x
 */
void Profile::removeFish(Fish* x) {
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
void Profile::changeFishBio(Fish* x, string y) {
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
void Profile::changeFishLocation(Fish* x, string y) {
    x->location = y;
}

void Profile::add_fish(Fish *fish){
    collection.push_back(fish);
}

/**
 * Add group to the adminlist.
 * @brief profile::addAdminGroup
 * @param g
 */
void Profile::addAdminGroup(Group* g) {
    adminList.push_back(g);
}

/**
 * Add a message to the profile's history of messages.
 * @brief profile::addMessage
 * @param m
 */
void Profile::addMessage(Message* m) {
    messageHistory.push_back(m);
}

/**
 * Add a post to the profile's history of posts.
 * @brief profile::addPost
 * @param p
 */
void Profile::addPost(Post* p) {
    postHistory.push_back(p);
}

/**
 * Add a group to the profile's list of groups.
 * @brief profile::addGroup
 * @param g
 */
void Profile::addGroup(Group* g) {
    groupsList.push_back(g);
}


//Getter and setter methods
string Profile::getNameFirst() {
    return nameFirst;
}
string Profile::getNameLast() {
    return nameLast;
}
string Profile::getUsername() {
    return username;
}
string Profile::getBio() {
    return bio;
}
string Profile::getLocation() {
    return location;
}
string Profile::getPreference() {
    return preference;
}
string Profile::getAge() {
    return age;
}









