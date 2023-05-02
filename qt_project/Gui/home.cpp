#include "home.h"
#include "ui_home.h"
#include <iostream>
#include <iterator>
#include <QPixmap>
#include <QFileDialog>
#include <QBuffer>


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
    , msg(new Message)
    , chatModel(new QStandardItemModel(this))
    , cmtModel(new QStandardItemModel(this))
{

    ui->setupUi(this);
    QPixmap pix("../../assets/blue_fish.svg");
//    int w = ui->main_icon->width();
//    int h = ui->main_icon->height();
    ui->main_icon->setPixmap(pix/*.scaled(w, h, Qt::KeepAspectRatio)*/);

//    QPixmap pix1("../../assets/profile_icon.svg");
//    QIcon buttonIcon(pix1);
//    ui->profileIconButton->setIcon(buttonIcon);
//    ui->profileIconButton->setIconSize(pix1.rect().size());
//    QFontDatabase::addApplicationFont("../../assets/lost_fish.ttf");

    ui->groupsList->setAlternatingRowColors(false);

    ui->edit->hide();
    ui->SaveChanges->hide();
    ui->searchBar->setEnabled(false);

    //l = new Login(this);
    l = new Login();
    l->show();
    //this->hide();

    //start(l);
    connect(l, &Login::back, this, &Home::main_menu);

    chatModel->insertColumn(0);
    chatModel->insertColumn(0);
    ui->messageHistLocal->setModel(chatModel);
    ui->messageHistRemote->setModel(chatModel);
    ui->messageHistLocal->setModelColumn(1); //sent messages on right side
    ui->messageHistRemote->setModelColumn(0); //received messages on left side


    ui->comments->setModel(cmtModel);
    cmtModel->insertColumn(0);

    //currGroup = all;


}

Home::~Home()
{
    delete ui;
}
/*******************************
 * LOGIN
 * ****************************/

void Home::start(QWidget* w) {
//    ui->stackedWidget->insertWidget(0, w);
//    ui->stackedWidget->setCurrentWidget(w);
//    w->focusWidget();
}

void Home::main_menu(Profile* p, Engine *e)
{
    this->show();
    l->hide();
    this->p = p;
//    e = new Engine();
//    e->reload_data();
    this->e = e;
    //add information from databases
    for(Group *group: e->get_groupList()){
        if(group->get_id()==0){
            currGroup = group;
            break;
        }
    }
//    currGroup = e->get_groupList().at(0);

    ui->fishlist->clear();
    ui->friendsList->clear();
    ui->allPosts->clear();
    ui->myPosts->clear();

    for(Fish* ff : p->get_fishList()){
        addFish(ff->get_name(), ff->get_species(), ff->get_description());
    }

    for(Profile* ff : p->get_friendList()){
        addFriend(ff);
    }

    for(Post* pp : p->get_postHistory()){
        addMyPost(currGroup, pp);
    }

    for (Group* gg : p->get_groupList()){
        for(Post* pp : gg->get_postHistory()){
            addPost(gg, pp);
        }
    }

//    for (Group* gg : p->get_groupList()){
//        for(Profile* pp : gg->get_members()){
//            addGroupMember(gg, pp);
//        }
//    }

//    for (Group* gg : p->get_groupList()){
//        addGroup(gg);
//    }

//    for (Group* gg : e->get_groupList()){
//        addAllGroup(gg);
//    }
//    ui->centralwidget->show();

    ui->searchBar->setEnabled(true);
//    delete ui->stackedWidget;
    ui->page->setCurrentIndex(0);
}

/*******************************
 * HOME BUTTONS
 * ****************************/

void Home::on_homeButton_clicked()
{
    ui->page->setCurrentIndex(0);
}

void Home::on_groupButton_clicked()
{
    ui->page->setCurrentIndex(1);
    load_groupList();
    ui->groupsList->setCurrentRow(0);
    on_groupsList_itemClicked(ui->groupsList->currentItem());
//    for(Group* iter : p->get_groupList()){
//        //new QListWidgetItem(iter->get_name(), ui->groupsList);
//        ui->groupsList->addItem(new QListWidgetItem(iter->get_name(), ui->groupsList));
//    }
    //if(currGroup != all) ui->groupName->setText(currGroup->get_name());
}

void Home::on_messageButton_clicked()
{
    ui->page->setCurrentIndex(2);
    load_groupchats();
}

void Home::on_friendsButton_clicked()
{
    ui->page->setCurrentIndex(3);
}


void Home::on_profileButton_clicked()
{
    ui->page->setCurrentIndex(4);

    ui->username->setText(tr("@") + p->get_username());
    ui->name->setText(p->get_firstName() + tr(" ") + p->get_lastName());
    ui->pbio->setPlainText(p->get_description());
    ui->plocation->setText(p->get_location());
    if(p->get_age() > 0) ui->age->setText(QString::number(p->get_age()) + tr(" years old"));
}


void Home::on_fishButton_clicked()
{
    ui->page->setCurrentIndex(5);
}

void Home::on_postButton_clicked()
{
    for(Group *group: p->get_groupList()){
        ui->selectGroup->addItem(group->get_name());
    }
    ui->page->setCurrentIndex(8);
    ui->p_titleBox->setFocus();
}

/*******************************
 * FISH BUTTONS
 * ****************************/

void Home::on_toolButton_clicked()
{
    ui->createfish->setFocus();
    ui->createlocation->setText(p->get_location());

    ui->page->setCurrentIndex(6);
}


void Home::on_finished_accepted()
{
    //NOT SURE WHICH CONSTRUCTOR    f = new Fish(ui->createfish->text().toStdString(), ui->createspecies->text().toStdString(), ui->createbio->toPlainText().toStdString());
    e->create_fish(p, ui->createfish->text(), 0, ui->createlocation->text(), ui->createspecies->text(), QDateTime::currentDateTimeUtc(),  ui->createbio->toPlainText());
    f = p->get_fishList().back();
    p->add_fish(f);
    //f->set_location = ui->createlocation->text().toStdString();
    ui->createfish->clear();
    ui->createlocation->clear();
    ui->createspecies->clear();
    ui->createbio->clear();

    ui->page->setCurrentIndex(5);

    addFish(f->get_name(),f->get_species(),f->get_description());
}

void Home::on_finished_rejected()
{
    ui->createfish->clear();
    ui->createlocation->clear();
    ui->createspecies->clear();
    ui->createbio->clear();
    ui->page->setCurrentIndex(5);
}

void Home::addFish(QString name, QString species, QString bio)
{
    (new QListWidgetItem(tr("Name: ") + name + tr("\n") + tr("Species: ") + species
                             + tr("\n") + tr("Bio: ") + bio + tr("\n"), ui->fishlist))->setCheckState(Qt::Unchecked);
}


void Home::on_fishlist_itemDoubleClicked(QListWidgetItem *item)
{
    ui->FishName->clear();
    ui->FishSpecies->clear();
    ui->FishLocation->clear();
    ui->FishBi->clear();

    int i = 0;
    while (ui->fishlist->item(i) != item) i++;
    f = p->get_fishList().at(i);

    ui->page->setCurrentIndex(7);
    ui->FishName->setText(f->get_name());
    ui->FishSpecies->setText(f->get_species());
    ui->FishLocation->setText(f->get_location());
    ui->FishBi->setText(f->get_description());

    QPixmap fishPixMap;
    fishPixMap.loadFromData(f->get_picture());
    int w = ui->FishPic->width();
    int h = ui->FishPic->height();
    ui->FishPic->setPixmap(fishPixMap.scaled(w, h, Qt::KeepAspectRatio));
}


void Home::on_EditFishProfile_clicked()
{
    ui->edit->show();

    //set information in boxes
    ui->createfish->setText(f->get_name());
    ui->createlocation->setText(f->get_location());
    ui->createspecies->setText(f->get_species());
    ui->createbio->setPlainText(f->get_description());

    //switch to page
    ui->createfish->setFocus();
    ui->page->setCurrentIndex(6);
}


void Home::on_edit_accepted()
{
    //find item in list
    int i = 0;
    while (p->get_fishList().at(i) != f) i++;
    QListWidgetItem* it = ui->fishlist->item(i);

    //change fish info
    e->edit_fish(p, f, ui->createfish->text(), 0, ui->createlocation->text(),  ui->createspecies->text(), ui->createbio->toPlainText());

    //display changes
    it->setText(tr("Name: ") + (f->get_name()) + tr("\n") + tr("Species: ") + f->get_species()
                + tr("\n") + tr("Bio: ") + f->get_description() + tr("\n"));

    ui->createfish->clear();
    ui->createspecies->clear();
    ui->createbio->clear();
    ui->page->setCurrentIndex(5);

    ui->edit->hide();
}

void Home::on_fishlist_itemClicked(QListWidgetItem *item)
{
    //int i = 0;
    //while (ui->allPosts->item(i) != item) i++;
    //Post* currPost = currGroup->postHistory.at(i);

    if(item->checkState() == Qt::Checked) item->setCheckState(Qt::Unchecked);
    else item->setCheckState(Qt::Checked);
}


void Home::on_deleteFishButton_clicked()
{
    for (int i = 0; i < ui->fishlist->count(); i++){
        if (ui->fishlist->item(i)->checkState() == Qt::Checked){
            e->delete_my_fish(p, p->get_fishList().at(i));
            ui->fishlist->removeItemWidget(ui->fishlist->item(i));
            delete ui->fishlist->item(i);
            ui->fishlist->update();

        }
    }
}

/*******************************
 * PROFILE BUTTONS
 * ****************************/

void Home::on_friends_clicked()
{
    ui->page->setCurrentIndex(3);
}


void Home::on_groups_clicked()
{
    ui->page->setCurrentIndex(1);
    //if(currGroup != all) ui->groupName->setText(currGroup->get_name());

}


void Home::on_posts_clicked()
{
    ui->page->setCurrentIndex(10);
}


void Home::on_fish_clicked()
{
    ui->page->setCurrentIndex(5);
}


void Home::on_editProfile_clicked()
{
    ui->pbio->setFocus();

    ui->age->setText(QString::number(p->get_age()));
    ui->age->setReadOnly(false);
    ui->pbio->setReadOnly(false);
    ui->plocation->setReadOnly(false);

    ui->age->setStyleSheet("background-color : rgba(255,255,255,100%); color : black;");
    ui->pbio->setStyleSheet("background-color : rgba(255,255,255,100%); color : black;");
    ui->plocation->setStyleSheet("background-color : rgba(255,255,255,100%); color : black;");

    ui->plocation->setReadOnly(false);
    ui->SaveChanges->show();
}


void Home::on_SaveChanges_clicked()
{
    ui->age->setReadOnly(true);
    ui->pbio->setReadOnly(true);
    ui->plocation->setReadOnly(true);

    ui->age->setStyleSheet("background-color : rgba(255,255,255,1%); color : black;");
    ui->pbio->setStyleSheet("background-color : rgba(255,255,255,1%); color : black;");
    ui->plocation->setStyleSheet("background-color : rgba(255,255,255,1%); color : black;");

    p->edit_profile(p->get_firstName(), p->get_lastName(), ui->age->toPlainText().toInt(), ui->plocation->toPlainText(), ui->pbio->toPlainText());
    e->edit_profile(p, p->get_firstName(), p->get_lastName(), ui->age->toPlainText().toInt(), ui->plocation->toPlainText(), ui->pbio->toPlainText());
    ui->age->setText(QString::number(p->get_age()) + tr(" years old"));

    ui->SaveChanges->hide();
}

/*******************************
 * COMM BUTTONS
 * ****************************/

void Home::on_message_returnPressed()
{

    e->create_message(p, currGroupChat, QDateTime::currentDateTimeUtc(), ui->message->text());
    msg->set_content(ui->message->text());
    int newRow = chatModel->rowCount();
    chatModel->insertRow(newRow);


    chatModel->setData(chatModel->index(newRow, 1), msg->get_content());
    chatModel->setData(chatModel->index(newRow, 1), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);

    ui->message->clear();
    ui->messageHistLocal->scrollToBottom();
    ui->messageHistRemote->scrollToBottom();
}

//void Home::loadMessageHelper(int senderId, Message *message){
//    QString content = message->get_content();

//    int newRow = chatModel->rowCount();
//    chatModel->insertRow(newRow);
//    if(senderId != p->get_id()){
//        chatModel->setData(chatModel->index(newRow, 0), content);
//        chatModel->setData(chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
//    }
//    else{
//        chatModel->setData(chatModel->index(newRow, 1), content);
//        chatModel->setData(chatModel->index(newRow, 1), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
//    }

//    ui->message->clear();
//    ui->messageHistLocal->scrollToBottom();
//    ui->messageHistRemote->scrollToBottom();
//}

//void Home::on_publish_clicked()
//{
//    int i = 0;
//    while(p->get_groupList().at(i)->get_name() != ui->titleBox->text()) i++;
//    currGroup = p->get_groupList().at(i);

//    e->create_post(p, currGroup, QDateTime::currentDateTimeUtc(), ui->titleBox->text(), ui->postBox->toPlainText());
//    Post* newPost = e->get_postList().back();
//    currGroup->add_post(newPost);
//    p->add_post(newPost);
//    addPost(currGroup, newPost);
//    addMyPost(currGroup, newPost);

//    ui->page->setCurrentIndex(0);

//    ui->titleBox->clear();
//    ui->postBox->clear();
//}

void Home::addPost(Group* gr, Post* po){
    new QListWidgetItem(po->get_title() + tr("\n") + po->get_content(), ui->allPosts); //fix to add to group
}

void Home::addMyPost(Group* gr, Post* po){
    new QListWidgetItem(po->get_title() + tr("\n") + po->get_content() + tr("\nfrom: ") + gr->get_name(), ui->myPosts);
}

void Home::on_allPosts_itemDoubleClicked(QListWidgetItem *item)
{
    currGroup = e->get_groupList().at(0);

    int i = 0;
    while (ui->groupPosts->item(i) != item) i++;
    currPost = currGroup->get_postHistory().at(i);

    ui->page->setCurrentIndex(9);
    ui->viewTitle->setText(currPost->get_title());
    ui->viewPost->setText(currPost->get_content());
    ui->commentLabel->setText(tr("Comments: ") + QString::number(currPost->get_comments().size()));
    load_postComments();
}

void Home::on_groupPosts_itemDoubleClicked(QListWidgetItem *item)
{
    int i = 0;
    while (ui->groupPosts->item(i) != item) i++;
    currPost = currGroup->get_postHistory().at(i);

    ui->page->setCurrentIndex(9);
    ui->viewTitle->setText(currPost->get_title());
    ui->viewPost->setText(currPost->get_content());
    ui->commentLabel->setText(tr("Comments: ") + QString::number(currPost->get_comments().size()));
    load_postComments();
}


void Home::on_addComment_returnPressed()
{
    e->create_comment(p, currPost, QDateTime::currentDateTimeUtc(), ui->addComment->toPlainText());

    int newRow = cmtModel->rowCount();
    cmtModel->insertRow(newRow);
    cmtModel->setData(cmtModel->index(newRow, 0), ui->addComment->toPlainText() + tr("\nby: ") + p->get_username());
    cmtModel->setData(cmtModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);

    ui->addComment->clear();
    ui->comments->scrollToBottom();
}

void Home::on_chat_itemClicked(QListWidgetItem *item)
{

    for(GroupChat *gc: p->get_groupchats()){
        if(gc->get_name().contains(item->text())){
            currGroupChat = gc;
            break;
        }
    }

    load_messages();

//    int i = 0;
//    while (ui->chat->item(i) != item) i++;
//    Profile *temp = p->get_friendList().at(i);
//    std::vector<Profile*> participants;
//    participants.push_back(temp);
//    e->create_groupchat(p, "", QDateTime::currentDateTimeUtc(), participants);
//    GroupChat* gc = e->get_groupchatList().back();

    //addMessages(gc->get_messageHistory());
}

void Home::addMessages(std::vector<Message*> m){

}

/*************************************
 * GROUPS
 * **********************************/

void Home::on_createGroup_clicked()
{
    ui->page->setCurrentIndex(11);
}


void Home::on_joinGroup_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->g_joinGroup);
}


void Home::on_groupInfo_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->info);

    QString admins;
    for(Profile* iter : currGroup->get_admin()) admins.append(iter->get_username());

    ui->g_infoDisplay->setText(currGroup->get_name() + tr("\nCreated by: ") + admins
                               + tr("\n\n") + currGroup->get_description());
}


void Home::on_groupMembers_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->g_members);
    load_groupMembers();
}


void Home::on_g_publish_clicked()
{

    e->create_group(p, ui->g_titleBox->text(), QDateTime::currentDateTimeUtc(), ui->g_description->toPlainText());
    currGroup = e->get_groupList().back();


    //addGroup(currGroup);



    ui->selectGroup->addItem(currGroup->get_name());
    ui->page->setCurrentIndex(1);

    ui->g_titleBox->clear();
    ui->g_description->clear();

    load_groupList();
}



void Home::addGroup(Group* g){
//    new QListWidgetItem(g->get_name(), ui->groupsList);
//    for(Profile* iter : currGroup->get_members()){
//        new QListWidgetItem(iter->get_username(), ui->membersList);
//    }
}

void Home::addAllGroup(Group* g){
//    new QListWidgetItem(g->get_name(), ui->allGroups);
//    for(Profile* iter : currGroup->get_members()){
//        new QListWidgetItem(iter->get_username(), ui->membersList);
//    }
}

void Home::on_groupsList_itemClicked(QListWidgetItem *item)
{
    int i = 0;
    while (ui->groupsList->item(i) != item) i++;
    currGroup = p->get_groupList().at(i);
    ui->groupName->setText(currGroup->get_name());
    ui->stackedWidget_2->setCurrentWidget(ui->g_posts);
    load_groupPosts();
}


void Home::on_groupsList_itemSelectionChanged()
{
//    ui->groupName->setText(currGroup->get_name());
//    ui->stackedWidget_2->setCurrentWidget(ui->g_posts);
}

void Home::addGroupMember(Group* gg, Profile* pp){
    new QListWidgetItem(pp->get_username(), ui->membersList);
}


void Home::on_membersList_itemDoubleClicked(QListWidgetItem *item)
{
    int i = 0;
    while (ui->membersList->item(i) != item) i++;
    Profile *temp = currGroup->get_members().at(i);

    profilePage(temp);
}

void Home::profilePage(Profile* pp){
    currFriend = pp;
    ui->page->setCurrentWidget(ui->profileView);
    ui->friend_username->setText(tr("@") + pp->get_username());
    ui->friend_name->setText(pp->get_firstName() + " " + pp->get_lastName());
    ui->friend_bio->setPlainText(pp->get_description());
    ui->friend_location->setText(pp->get_location());
    if(pp->get_age() > 0) ui->friend_age->setText(QString::number(pp->get_age()) + tr(" years old"));
}

/****************************
 * FRIENDS
 * ************************/

void Home::addFriend(Profile* f){
    ui->friendsList->addItem(new QListWidgetItem(f->get_username(), ui->friendsList));
    ui->chat->addItem(new QListWidgetItem(f->get_username(), ui->chat));
//    new QListWidgetItem(f->get_username(), ui->friendsList);
//    new QListWidgetItem(f->get_username(), ui->chat);
}


void Home::on_AddFriend_clicked()
{
    e->add_friend(p, currFriend);
    std::vector<Profile*> participants = {p, currFriend};
    e->create_groupchat(p, p->get_username() + "," + currFriend->get_username(), QDateTime::currentDateTime(), participants);
    addFriend(currFriend);
}


void Home::on_groupPostButton_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->g_posts);
    load_groupPosts();
}

void Home::load_groupList(/*std::vector<Group*> groupList*/){
    ui->groupsList->clear();
    for(Group* iter : p->get_groupList()){
        //new QListWidgetItem(iter->get_name(), ui->groupsList);
        ui->groupsList->addItem(new QListWidgetItem(iter->get_name(), ui->groupsList));
    }
}

void Home::load_groupMembers(){
    ui->membersList->clear();
    for(Profile *profile: currGroup->get_members()){
        ui->membersList->addItem(new QListWidgetItem(profile->get_username(), ui->membersList));
    }

}


void Home::load_groupPosts(){
    ui->groupPosts->clear();
    for(Post *post: currGroup->get_postHistory()){
        ui->groupPosts->addItem(new QListWidgetItem(post->get_title() + tr("\n") + post->get_content(), ui->groupPosts));
    }
    //new QListWidgetItem(po->get_title() + tr("\n") + po->get_content(), ui->allPosts); //fix to add to group
}

void Home::load_postComments(){

//    int i = 0;
//    while (ui->groupPosts->item(i) != item) i++;
//    currPost = currGroup->get_postHistory().at(i);

//    ui->page->setCurrentIndex(9);
//    ui->viewTitle->setText(currPost->get_title());
//    ui->viewPost->setText(currPost->get_content());
//    ui->commentLabel->setText(tr("Comments: ") + QString::number(currPost->get_comments().size()));

//    e->create_comment(p, currPost, QDateTime::currentDateTimeUtc(), ui->addComment->text());
    cmtModel->clear();
    cmtModel->insertColumn(0);
    int i = 0;
    for(std::pair<int, PostComment*> comment: currPost->get_comments()){
        cmtModel->insertRow(i);
        cmtModel->setData(cmtModel->index(i, 0), comment.second->get_content() + tr("\nby: ") + comment.second->get_creator()->get_username());
        cmtModel->setData(cmtModel->index(i, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        i += 1;
    }

//    int newRow = cmtModel->rowCount();
//    cmtModel->insertRow(newRow);
//    cmtModel->setData(cmtModel->index(newRow, 0), ui->addComment->text());
//    cmtModel->setData(cmtModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
//    ui->addComment->clear();
//    ui->comments->scrollToBottom();
}

void Home::load_groupchats(){
    ui->chat->clear();
    Profile *friendProfile;
    for(GroupChat *gc: p->get_groupchats()){
        for(std::pair<int, Profile*> profile: gc->get_participants()){
            if(profile.second->get_username() != p->get_username()){ // gc has two participants, user and their friend, the gc is labelled with friend's name to simulate direct messages
                friendProfile = profile.second;
            }
        }

        ui->chat->addItem(new QListWidgetItem(friendProfile->get_username(), ui->chat));
    }

}

void Home::load_messages(){

    chatModel->clear();
    chatModel->insertColumn(0);
    chatModel->insertColumn(0);
    ui->messageHistLocal->setModel(chatModel);
    ui->messageHistRemote->setModel(chatModel);
    ui->messageHistLocal->setModelColumn(1); //sent messages on right side
    ui->messageHistRemote->setModelColumn(0); //received messages on left side

    int row = 0;
    for(std::pair<int, Message*> msg: currGroupChat->get_messageHistory()){
        chatModel->insertRow(row);

        if(msg.second->get_senderId() == p->get_id()){
            chatModel->setData(chatModel->index(row, 1), msg.second->get_content());
            chatModel->setData(chatModel->index(row, 1), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
        }
        else{
            chatModel->setData(chatModel->index(row, 0), msg.second->get_content());
            chatModel->setData(chatModel->index(row, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        }

        row += 1;
    }
    ui->messageHistLocal->scrollToBottom();
    ui->messageHistRemote->scrollToBottom();

}

void Home::reload_data(){
    int profileId = p->get_id();
    int groupchatId = currGroupChat->get_id();
    e->reload_data();
    main_menu(e->get_profiles()[profileId], e);
    p = e->get_profiles()[profileId];
    currGroupChat = e->get_groupchats()[groupchatId];

    on_messageButton_clicked();
    load_messages();
    //holding current profile and reloading data
}

void Home::on_p_publish_clicked()
{
//        int i = 0;
        QString groupName = ui->selectGroup->currentText();
        //Group *postGroup;
        for(Group *group: p->get_groupList()){
            if(group->get_name() == groupName){
                currGroup = group;
                break;
            }
        }

//        while(p->get_groupList().at(i)->get_name() != ui->selectGroup->currentText()) i++;
//        currGroup = p->get_groupList().at(i);

        e->create_post(p, currGroup, QDateTime::currentDateTimeUtc(), ui->p_titleBox->text(), ui->postBox->toPlainText());

        Post* newPost = e->get_postList().back();
//        currGroup->add_post(newPost);
//        p->add_post(newPost);
//        addPost(currGroup, newPost);
        addMyPost(currGroup, newPost);

        load_groupPosts();

        ui->page->setCurrentIndex(0);

        ui->p_titleBox->clear();
        ui->postBox->clear();
}


void Home::on_leaveGroupButton_clicked()
{
        e->leave_group(p, currGroup);
        on_groupButton_clicked();
//        load_groupList();
//        currGroup = e->get_groupList().at(0); // set to the all group
}


void Home::on_EditFishPic_clicked()
{
        QFileDialog dialog(this);
        dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
        dialog.setViewMode(QFileDialog::Detail);

        QStringList fileNames;
        if (dialog.exec()) {
            fileNames = dialog.selectedFiles();
        }

        // Load the selected image file into a QPixmap object and then display as label
        QPixmap fishPixMap(fileNames.first());
        int w = ui->FishPic->width();
        int h = ui->FishPic->height();
        ui->FishPic->clear();
        ui->FishPic->setPixmap(fishPixMap.scaled(w, h, Qt::KeepAspectRatio));


        // Pixmap -> bytearray -> sqlite blob
        QByteArray fishPicBytes;
        QBuffer buffer(&fishPicBytes);
        buffer.open(QIODevice::WriteOnly);
        fishPixMap.toImage().save(&buffer, "PNG");

        e->save_fish_picture(f, fishPicBytes);

}




void Home::on_commentPublishButton_clicked()
{
        e->create_comment(p, currPost, QDateTime::currentDateTimeUtc(), ui->addComment->toPlainText());

        int newRow = cmtModel->rowCount();
        cmtModel->insertRow(newRow);
        cmtModel->setData(cmtModel->index(newRow, 0), ui->addComment->toPlainText() + tr("\nby: ") + p->get_username());
        cmtModel->setData(cmtModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignTop), Qt::TextAlignmentRole);

        ui->addComment->clear();
        ui->comments->scrollToBottom();
}


void Home::on_reloadButton_clicked()
{
        reload_data();
}

