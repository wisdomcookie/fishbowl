#include "engine.h"

Engine::Engine()
{
    db = new Database();
}


Engine::~Engine(){
    delete db;
}

void Engine::update_data(){

}
void Engine::refresh_data(){

}

void Engine::create_post(Profile *actor, Group *group, QString title, QString content){

}
void Engine::create_comment(Profile *actor, Post *post, QString content){

}
void Engine::create_groupchat(Profile *actor, QString name, std::vector<Profile*> participants){

}
void Engine::create_group(Profile *actor, QString name, std::vector<Profile*> participants, std::vector<Profile*> admin){

}
void Engine::create_message(Profile *actor, Group *group, QString content){

}
void Engine::create_fish(Profile *actor, QString name){

}

void Engine::join_group(Profile *actor, Group *group){

}
void Engine::join_groupchat(Profile *actor, GroupChat *groupchat){

}

void Engine::leave_group(Profile *actor, Group *group){

}
void Engine::leave_groupchat(Profile *actor, GroupChat *groupchat){

}

void Engine::edit_my_profile(Profile *actor, QString newBio /*= 0*/){

}
void Engine::edit_my_fish(Profile *actor, Fish *fish, QString newContent /*= 0*/){

}
void Engine::edit_my_login(Profile *actor, QString newUsername /*= 0*/, QString newPassword /*= 0*/){

}
void Engine::edit_post(Profile *actor, Post *post, QString newContent /*= 0*/){

}
void Engine::edit_comment(Profile *actor, PostComment *comment, QString newContent /*= 0*/){

}

void Engine::remove_from_group(Profile *actor, Group *group, Profile *groupMember){

}
void Engine::remove_from_groupchat(Profile *actor, GroupChat *groupchat, Profile *groupchatParticipant){

}

void Engine::delete_post(Profile *actor, Post *post){

}
void Engine::delete_comment(Profile *actor, PostComment *comment){

}
void Engine::delete_groupchat(Profile *actor, GroupChat *groupchat){

}
void Engine::delete_group(Profile *actor, Group *group){

}

void Engine::ban_user(Profile *actor, Profile *user, Group *group){

}
