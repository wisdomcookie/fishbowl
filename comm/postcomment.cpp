#include "postcomment.h"
#include "../profiles/profile.h"
#include "post.h"


PostComment::PostComment()
{

}

PostComment::PostComment(int id, Profile *creator, QDateTime dateCreated, Post *sourcePost, PostComment *sourceComment, std::vector<PostComment*> replies, QString content):
    id(id), creator(creator), dateCreated(dateCreated), sourcePost(sourcePost), sourceComment(sourceComment), replies(replies), content(content){

}

PostComment::PostComment(int id, Profile *creator, Post *post, PostComment *parentComment, QString content):
    commentId(id), postId(post->get_id()), commenterId(creator->get_id()), parentCommentId(parentComment->get_id()), dateCreated(QDateTime::currentDateTimeUtc()),
    content(content), visibility(true){
}   //User creates new comment

PostComment::PostComment(int id, Profile *creator, Post *post, QString content):
    commentId(id), postId(post->get_id()), commenterId(creator->get_id()), parentCommentId(0), dateCreated(QDateTime::currentDateTimeUtc()),
    content(content), visibility(true){

}     //User creates new comment that is reply

PostComment::PostComment(std::map<QString, QString> commentData){
    commentId = commentData[QString("comment_id")].toInt();
    postId = commentData[QString("post_id")].toInt();
    commenterId = commentData[QString("commenter_id")].toInt();
    parentCommentId = commentData[QString("reply_to_comment_id")].toInt();

    QString dateString = commentData[QString("date_created")];
    QString dateFormat = QString("yyyy-MM-dd hh:mm:ss");
    dateCreated = QDateTime::fromString(dateString, dateFormat);

    content = commentData[QString("content")];
}

PostComment::~PostComment(){

}

void PostComment::add_reply(PostComment *reply){
    replies[reply->get_id()] = reply;
}

int PostComment::get_id(){
    return id;
}
Profile *PostComment::get_creator(){
    return creator;
}
QDateTime PostComment::get_dateCreated(){
    return dateCreated;
}
Post *PostComment::get_sourcePost(){
    return sourcePost;
}
PostComment *PostComment::get_sourceComment(){
    return sourceComment;
}
std::vector<PostComment*> PostComment::get_replies(){
    return replies;
}
QString PostComment::get_content(){
    return content;
}
