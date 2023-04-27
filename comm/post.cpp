#include "post.h"
#include "postcomment.h"
#include "../profiles/profile.h"
#include "../groups/group.h"

Post::Post() {

}

Post::Post(int id, Profile *creator, Group *group, QDateTime dateCreated, QString title, QString content):
    postId(id), posterId(creator->get_id()), groupId(group->get_id()), dateCreated(dateCreated), title(title), content(content), visibility(true), group(group){

} // User creates new post

Post::Post(std::map<QString, QString> postData){
    postId = postData[QString("post_id")].toInt();
    posterId = postData[QString("poster_id")].toInt();
    groupId = postData[QString("group_id")].toInt();

    QString dateString = postData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    title = postData[QString("title")];
    content = postData[QString("content")];
    visibility = postData[QString("visibility")].toInt();
} // load from database

Post::~Post(){

}

void Post::set_content(QString newContent){
    content = newContent;
}

void Post::add_comment(PostComment *comment){
    comments[comment->get_id()] = comment;
}

int Post::get_id(){
    return postId;
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
std::map<int, PostComment*> Post::get_comments(){
    return comments;
}
