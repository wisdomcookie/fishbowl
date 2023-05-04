#include "profile.h"

Profile::Profile() {
}

//Profile::Profile(string username, string password) {
////    this->username = username;
////    this->password = password;
//    Database d;
//    d.query_exec("select * from profiles");  //make sure name of table is correct
//    id = d.query_size() + 1;
//}


Profile::Profile(int id, QString username, QString firstName, QString lastName, int age, QString location, QDateTime dateCreated, QString description):
    profileId(id), username(username), firstName(firstName), lastName(lastName), age(age), location(location), dateCreated(dateCreated), description(description)
{

    //aquarium = new Aquarium(this);
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
    //delete aquarium;
}


void Profile::add_fish(Fish *fish){
    fishList[fish->get_id()] = fish;
}

/**
 * Add a friend to your friends list. Your new friend will need to add you back
 * for the friending process to be completed.
 * @brief profile::addFriend
 * @param x
 */
void Profile::add_friend(Profile *profile){
    friends[profile->get_id()] = profile;
}
/**
 * Add a group to the profile's list of groups.
 * @brief profile::addGroup
 * @param g
 */
void Profile::add_group(Group *group){
    groups[group->get_id()] = group;
}
void Profile::add_group_as_admin(Group *g){

}
void Profile::add_groupchat(GroupChat *groupchat){
    groupchats[groupchat->get_id()] = groupchat;
}

/**
 * Add a message to the profile's history of messages.
 * @brief profile::addMessage
 * @param m
 */
void Profile::add_message(Message* message){
    messages[message->get_id()] = message;
}
/**
 * Add a post to the profile's history of posts.
 * @brief profile::addPost
 * @param p
 */
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
    post->set_content(newContent);
}
void Profile::edit_comment(PostComment *comment, QString newContent){
    comment->set_content(newContent);
}


/**
 * Remove a friend from your friends list. This does not require a signal from
 * the target profile to take effect. This method will call the addendum method
 * removeFriendForeign that will remove you from the ex-friend's friend list
 * without their permission.
 * @brief profile::removeFriend
 * @param x
 */
void Profile::remove_friend(Profile *profile){
    friends.erase(profile->get_id());
}

/**
 * Will remove a fish from the profile's collection.
 * @brief profile::removeFish
 * @param x
 */
void Profile::remove_fish(Fish *fish){
    fishList.erase(fish->get_id());
   // aquarium->remove_fish(fish);
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

bool Profile::is_friend(Profile *friendProfile){
    return friends.find(friendProfile->get_id()) != friends.end();
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
QDateTime Profile::get_dateCreated(){
    return dateCreated;
}
QString Profile::get_description(){
    return description;
}

std::vector<Fish*> Profile::get_fishList(){

    std::vector<Fish*> res;
    for(auto i = fishList.begin(); i != fishList.end(); i++){
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

std::vector<GroupChat*> Profile::get_groupchats(){
    std::vector<GroupChat*> res;
    for(auto i = groupchats.begin(); i != groupchats.end(); i++){
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



