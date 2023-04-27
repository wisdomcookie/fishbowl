#include "postcomment.h"
#include "../profiles/profile.h"
#include "post.h"


PostComment::PostComment()
{

}

PostComment::PostComment(int id, Profile *creator, Post *post, QDateTime dateCreated, QString content):
    commentId(id), postId(post->get_id()), commenterId(creator->get_id()), parentCommentId(0), dateCreated(dateCreated), content(content), visibility(true){

}   //User creates new comment, comments that are not replies have a placeholder comment as the parent comment


PostComment::PostComment(int id, Profile *creator, Post *post, PostComment *parentComment, QDateTime dateCreated, QString content):
    commentId(id), postId(post->get_id()), commenterId(creator->get_id()), parentCommentId(parentComment->get_id()), dateCreated(dateCreated), content(content), visibility(true){
}   //User creates new comment that is reply


PostComment::PostComment(std::map<QString, QString> commentData){
    commentId = commentData[QString("comment_id")].toInt();
    postId = commentData[QString("post_id")].toInt();
    commenterId = commentData[QString("commenter_id")].toInt();
    parentCommentId = commentData[QString("parent_comment_id")].toInt();

    QString dateString = commentData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    content = commentData[QString("content")];
    visibility = commentData[QString("visiblity")].toInt();
}

PostComment::~PostComment(){

}



void PostComment::add_reply(PostComment *reply){
    replies[reply->get_id()] = reply;
}

void PostComment::set_content(QString newContent){
    content = newContent;
}

int PostComment::get_id(){
    return commentId;
}
Profile *PostComment::get_creator(){
    return creator;
}
QDateTime PostComment::get_dateCreated(){
    return dateCreated;
}
bool PostComment::get_visibility(){
    return visibility;
}

Post *PostComment::get_post(){
    return post;
}
PostComment *PostComment::get_parentComment(){
    return parentComment;
}
std::map<int, PostComment*> PostComment::get_replies(){
    return replies;
}
QString PostComment::get_content(){
    return content;
}
