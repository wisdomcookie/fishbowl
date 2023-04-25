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
#include "../comm/chat.h"
#include "../comm/post.h"
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

    void main_menu();

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

    void on_publish_clicked();

    void on_allPosts_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Home *ui;
    Profile p;
    Fish* f;
    Login* l;
    Message *msg;
    QStandardItemModel *chatModel;
    Group* currGroup;
    Group* all = new Group("All");

};
#endif // HOME_H
