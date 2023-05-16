#include "postcomment.h"
#include "../profiles/profile.h"
#include "post.h"

/**
 * @brief PostComment::PostComment
 */
PostComment::PostComment()
{

}

/**
 * Constructor used when a new comment is created under a post
 * @brief PostComment::PostComment
 * @param id
 * @param creator
 * @param post
 * @param dateCreated
 * @param content
 */
PostComment::PostComment(int id, Profile *creator, Post *post, QDateTime dateCreated, QString content):
    commentId(id), postId(post->get_id()), commenterId(creator->get_id()), parentCommentId(0), dateCreated(dateCreated), content(content), visibility(true){

}   //User creates new comment, comments that are not replies have a placeholder comment as the parent comment

/**
 * Constructor used when a new reply is added to a comment
 * @brief PostComment::PostComment
 * @param id
 * @param creator
 * @param post
 * @param parentComment
 * @param dateCreated
 * @param content
 */
PostComment::PostComment(int id, Profile *creator, Post *post, PostComment *parentComment, QDateTime dateCreated, QString content):
    commentId(id), postId(post->get_id()), commenterId(creator->get_id()), parentCommentId(parentComment->get_id()), dateCreated(dateCreated), content(content), visibility(true){
}   //User creates new comment that is reply

/**
 * Constructor used by engine to populate comments and comment replies from database
 * @brief PostComment::PostComment
 * @param commentData
 */
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

/**
 * @brief PostComment::~PostComment
 */
PostComment::~PostComment(){

}


/**
 * Adds a reply to list of replies
 * @brief PostComment::add_reply
 * @param reply
 */
void PostComment::add_reply(PostComment *reply){
    replies[reply->get_id()] = reply;
}
/**
 * Sets the content of a comment
 * @brief PostComment::set_content
 * @param newContent
 */
void PostComment::set_content(QString newContent){
    content = newContent;
}
/**
 * Checks whether this comment is a reply
 * @brief PostComment::is_reply
 * @return true if it is a reply
 */
bool PostComment::is_reply(){
    return parentCommentId != 0;
}
/**
 * Sets the creator of this comment to the profile that made it
 * @brief PostComment::set_creator
 * @param profile
 */
void PostComment::set_creator(Profile *profile){
    creator = profile;
}
/**
 * Sets parent comment, sets one with id of 0 if this is not a reply
 * @brief PostComment::set_parentComment
 * @param parent
 */
void PostComment::set_parentComment(PostComment *parent){
    parentComment = parent;
}
/**
 * Sets this comment's source post
 * @brief PostComment::set_sourcePost
 * @param sourcePost
 */
void PostComment::set_sourcePost(Post *sourcePost){
    post = sourcePost;
}
/**
 * Sets this post to be visible or non visible
 * @brief PostComment::set_visibility
 * @param visibility is true if visible to others
 */
void PostComment::set_visibility(bool visibility){
    this->visibility = visibility;
}
/**
 * @brief PostComment::get_id
 * @return comment's id
 */
int PostComment::get_id(){
    return commentId;
}
/**
 * @brief PostComment::get_creator
 * @return profile that created this comment
 */
Profile *PostComment::get_creator(){
    return creator;
}
/**
 * @brief PostComment::get_dateCreated
 * @return date this comment was created
 */
QDateTime PostComment::get_dateCreated(){
    return dateCreated;
}
/**
 * @brief PostComment::get_visibility
 * @return true if the post is visible
 */
bool PostComment::get_visibility(){
    return visibility;
}
/**
 * @brief PostComment::get_post
 * @return returns the post this was commented under
 */
Post *PostComment::get_post(){
    return post;
}
/**
 * @brief PostComment::get_parentComment
 * @return comment with id 0 if main comment, otherwise returns parent comment
 */
PostComment *PostComment::get_parentComment(){
    return parentComment;
}
/**
 * @brief PostComment::get_replies
 * @return returns a map of this comment's replies
 */
std::map<int, PostComment*> PostComment::get_replies(){
    return replies;
}
/**
 * @brief PostComment::get_content
 * @return returns this comment's text
 */
QString PostComment::get_content(){
    return content;
}
