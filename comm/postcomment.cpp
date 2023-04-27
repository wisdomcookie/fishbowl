#include "postcomment.h"

PostComment::PostComment()
{

}

PostComment::PostComment(int id, Profile *creator, QDateTime dateCreated, Post *sourcePost, PostComment *sourceComment, std::vector<PostComment*> replies, QString content):
    id(id), creator(creator), dateCreated(dateCreated), sourcePost(sourcePost), sourceComment(sourceComment), replies(replies), content(content){

}
PostComment::PostComment(Profile *creator, Post *sourcePost, PostComment *sourceComment, QString content):
    creator(creator), sourcePost(sourcePost), sourceComment(sourceComment), content(content){

}     //User creates new comment

PostComment::~PostComment(){

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
