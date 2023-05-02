#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QLayout>
#include <QObject>
#include <QVector>
#include <vector>
#include <QStandardItemModel>

#include "../profiles/fish.h"
#include "../profiles/profile.h"
#include "../groups/group.h"
#include "../comm/message.h"
#include "../comm/post.h"
#include "../comm/postcomment.h"
#include "../engine/engine.h"
#include "QtWidgets/qlistwidget.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Home; }
QT_END_NAMESPACE

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void start(QWidget*);

    void main_menu(Profile* p/*, Engine* e*/);

    void on_homeButton_clicked();

    void on_groupButton_clicked();

    void on_messageButton_clicked();

    void on_friendsButton_clicked();

    void on_profileButton_clicked();

    void on_fishButton_clicked();

    void on_postButton_clicked();

    void on_toolButton_clicked();

    void on_finished_accepted();

    void addFish(QString, QString, QString);

    void on_fishlist_itemDoubleClicked(QListWidgetItem *item);

    void on_finished_rejected();

    void on_EditFishProfile_clicked();

    void on_edit_accepted();

    void on_friends_clicked();

    void on_groups_clicked();

    void on_posts_clicked();

    void on_fish_clicked();

    void on_editProfile_clicked();

    void on_SaveChanges_clicked();

    void on_message_returnPressed();

//    void on_publish_clicked();

    void on_allPosts_itemDoubleClicked(QListWidgetItem *item);

    void on_fishlist_itemClicked(QListWidgetItem *item);

    void on_deleteFishButton_clicked();

    void addPost(Group*, Post*);

    void addMyPost(Group*, Post*);

    void on_addComment_returnPressed();

    void on_createGroup_clicked();

    void on_joinGroup_clicked();

    void on_groupInfo_clicked();

    void on_groupMembers_clicked();

    void on_g_publish_clicked();

    void addGroup(Group*);

    void on_groupsList_itemClicked(QListWidgetItem *item);

    void on_groupsList_itemSelectionChanged();

    void addGroupMember(Group*, Profile* );

    void on_membersList_itemDoubleClicked(QListWidgetItem *item);

    void profilePage(Profile*);

    void addFriend(Profile*);

    void addAllGroup(Group*);

    void on_AddFriend_clicked();

    void on_chat_itemClicked(QListWidgetItem *item);

    void addMessages(std::vector<Message*> m);

    void on_groupPostButton_clicked();

    void on_p_publish_clicked();

    void on_leaveGroupButton_clicked();

    void on_EditFishPic_clicked();

    void on_groupPosts_itemDoubleClicked(QListWidgetItem *item);

    void on_commentPublishButton_clicked();

private:

    void load_groupList(); /*std::vector<Group*> groupList*/
    void load_groupMembers();
    void load_groupPosts();
    void load_postComments();
    void load_groupchats();
    void load_messages();
    //void load_friends();

    Ui::Home *ui;
    Profile *p;
    Engine* e;
    Fish* f;
    Login* l;
    GroupChat *currGroupChat;
    Message *msg;
    QStandardItemModel *chatModel;
    Post* currPost;
    PostComment *cmt;
    QStandardItemModel *cmtModel;
    Group* currGroup;
    Group* all;
    Profile* currFriend;

};
#endif // HOME_H
