#include "post.h"
#include "postcomment.h"
#include "../profiles/profile.h"
#include "../groups/group.h"
/**
 * @brief Post::Post
 */
Post::Post() {

}
/**
 * Constructor for creating a new post
 * @brief Post::Post
 * @param id
 * @param creator
 * @param group
 * @param dateCreated
 * @param title
 * @param content
 */
Post::Post(int id, Profile *creator, Group *group, QDateTime dateCreated, QString title, QString content):
    postId(id), posterId(creator->get_id()), groupId(group->get_id()), dateCreated(dateCreated), title(title), content(content), visibility(true), group(group){

} // User creates new post
/**
 * Constructor used to load posts from the database
 * @brief Post::Post
 * @param postData
 */
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
/**
 * @brief Post::~Post
 */
Post::~Post(){

}


/**
 * Sets the post's text
 * @brief Post::set_content
 * @param newContent
 */
void Post::set_content(QString newContent){
    content = newContent;
}
/**
 * Sets a profile that created this post
 * @brief Post::set_creator
 * @param profile
 */
void Post::set_creator(Profile *profile){
    creator = profile;
}
/**
 * Sets the group this post will appear in
 * @brief Post::set_group
 * @param group
 */
void Post::set_group(Group *group){
    this->group = group;
}
/**
 * Sets whether or not this post is visible
 * @brief Post::set_visibility
 * @param visibility is true if visible
 */
void Post::set_visibility(bool visibility){
    this->visibility = visibility;
}


/**
 * Adds a comment to this post's list of comments
 * @brief Post::add_comment
 * @param comment
 */
void Post::add_comment(PostComment *comment){
    comments[comment->get_id()] = comment;
}
/**
 * Removes a comment from this post's list of comments
 * @brief Post::remove_comment
 * @param comment
 */
void Post::remove_comment(PostComment *comment){
    comments.erase(comment->get_id());
}
/**
 * @brief Post::get_id
 * @return this post's id
 */
int Post::get_id(){
    return postId;
}
/**
 * @brief Post::get_creator
 * @return profile of the creator of this post
 */
Profile *Post::get_creator(){
    return creator;
}
/**
 * @brief Post::get_sourceGroup
 * @return group that this post belongs to
 */
Group *Post::get_sourceGroup(){
    return group;
}
/**
 * @brief Post::get_title
 * @return title of this post
 */
QString Post::get_title(){
    return title;
}
/**
 * @brief Post::get_content
 * @return main text of this post
 */
QString Post::get_content(){
    return content;
}
/**
 * @brief Post::get_dateCreated
 * @return date this was posted
 */
QDateTime Post::get_dateCreated(){
    return dateCreated;
}
/**
 * @brief Post::get_visibility
 * @return true if the post is visible
 */
bool Post::get_visibility(){
    return visibility;
}
/**
 * @brief Post::get_comments
 * @return list of comments under this post
 */
std::map<int, PostComment*> Post::get_comments(){
    return comments;
}
