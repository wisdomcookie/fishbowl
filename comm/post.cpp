#include "post.h"

Post::Post() {

}

Post::Post(int id, Profile *creator, Group *sourceGroup, QString title, QString content, QDateTime dateCreated, std::vector<PostComment*> comments):
    id(id), creator(creator), sourceGroup(sourceGroup), title(title), content(content), dateCreated(dateCreated), comments(comments){

} // Load from database

Post::Post(Profile *creator, Group *sourceGroup, QString title, QString content):
    creator(creator), sourceGroup(sourceGroup), title(title), content(content), dateCreated(QDateTime::currentDateTime()){

} // User creates new post

Post::~Post(){

}

void Post::set_content(QString newContent){
    content = newContent;
}

int Post::get_id(){
    return id;
}
Profile *Post::get_creator(){
    return creator;
}
QString Post::get_title(){
    return title;
}
QString Post::get_content(){
    return content;
}
QDateTime Post::get_dateCreated(){
    return dateCreated;
}
std::vector<PostComment*> Post::get_comments(){
    return comments;
}
