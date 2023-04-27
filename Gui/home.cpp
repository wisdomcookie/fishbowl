#include "home.h"
#include "ui_home.h"
#include <iostream>
#include <iterator>


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
    , msg(new Message)
    , chatModel(new QStandardItemModel(this))
    , cmtModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    ui->edit->hide();
    ui->SaveChanges->hide();
    ui->searchBar->setEnabled(false);

    l = new Login(this);
    start(l);
    connect(l, &Login::back, this, &Home::main_menu);

    ui->messageHist->setModel(chatModel);
    chatModel->insertColumn(0);

    ui->comments->setModel(cmtModel);
    cmtModel->insertColumn(0);

    ui->pwordlabel->hide();
    ui->oldpword->hide();
    ui->newpword->hide();

    currGroup = all;

    //add information from databases
    for(Fish* ff : p.collection){
        addFish(QString::fromStdString(ff->name), QString::fromStdString(ff->species), QString::fromStdString(ff->bio));
    }

    for(Profile* ff : p.friendsList){
        addFriend(ff);
    }

    for(Post* pp : p.postHistory){
        addMyPost(currGroup, pp);
    }

    for (Group* gg : p.groupsList){
        for(Post* pp : gg->postHistory){
            addPost(gg, pp);
        }
    }

    for (Group* gg : p.groupsList){
        for(Profile* pp : gg->get_members()){
            addGroupMember(gg, pp);
        }
    }

    for (Group* gg : p.groupsList){
        addGroup(gg);
    }
}

Home::~Home()
{
    delete ui;
}
/*******************************
 * LOGIN
 * ****************************/

void Home::start(QWidget* w) {
    ui->stackedWidget->insertWidget(0, w);
    ui->stackedWidget->setCurrentWidget(w);
    w->focusWidget();
}

void Home::main_menu(Profile* p)
{
    this->p = *p;
    ui->searchBar->setEnabled(true);
    delete ui->stackedWidget;
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
    if(currGroup != all) ui->groupName->setText(QString::fromStdString(currGroup->get_name()));
}

void Home::on_messageButton_clicked()
{
    ui->page->setCurrentIndex(2);
}


void Home::on_friendsButton_clicked()
{
    ui->page->setCurrentIndex(3);
}


void Home::on_profileButton_clicked()
{
    ui->page->setCurrentIndex(4);

    ui->username->setText(QString::fromStdString("@" + p.getUsername()));
    ui->name->setText(QString::fromStdString(p.getNameFirst() + " " + p.getNameLast()));
    ui->pbio->setPlainText(QString::fromStdString(p.getBio()));
    ui->plocation->setText(QString::fromStdString(p.getLocation()));
    if(!p.getAge().empty()) ui->age->setText(QString::fromStdString(p.getAge()) + tr(" years old"));
}


void Home::on_fishButton_clicked()
{
    ui->page->setCurrentIndex(5);
}

void Home::on_postButton_clicked()
{
    ui->page->setCurrentIndex(8);
    ui->titleBox->setFocus();
}

/*******************************
 * FISH BUTTONS
 * ****************************/

void Home::on_toolButton_clicked()
{
    ui->createfish->setFocus();
    ui->createlocation->setText(QString::fromStdString(p.getLocation()));

    ui->page->setCurrentIndex(6);
}


void Home::on_finished_accepted()
{
    f = p.createFish(ui->createfish->text().toStdString(), ui->createspecies->text().toStdString(), ui->createbio->toPlainText().toStdString());
    f->location = ui->createlocation->text().toStdString();
    ui->createfish->clear();
    ui->createlocation->clear();
    ui->createspecies->clear();
    ui->createbio->clear();

    ui->page->setCurrentIndex(5);

    addFish(QString::fromStdString(f->name), QString::fromStdString(f->species), QString::fromStdString(f->bio));
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
    f = p.collection.at(i);

    ui->page->setCurrentIndex(7);
    ui->FishName->setText(QString::fromStdString(f->name));
    ui->FishSpecies->setText(QString::fromStdString(f->species));
    ui->FishLocation->setText(QString::fromStdString(f->location));
    ui->FishBi->setText(QString::fromStdString(f->bio));
}


void Home::on_EditFishProfile_clicked()
{
    ui->edit->show();

    //set information in boxes
    ui->createfish->setText(QString::fromStdString(f->name));
    ui->createlocation->setText(QString::fromStdString(f->location));
    ui->createspecies->setText(QString::fromStdString(f->species));
    ui->createbio->setPlainText(QString::fromStdString(f->bio));

    //switch to page
    ui->createfish->setFocus();
    ui->page->setCurrentIndex(6);
}


void Home::on_edit_accepted()
{
    //find item in list
    int i = 0;
    while (p.collection.at(i) != f) i++;
    QListWidgetItem* it = ui->fishlist->item(i);

    //change fish info
    f->name = ui->createfish->text().toStdString();
    f->species = ui->createspecies->text().toStdString();
    p.changeFishLocation(f, ui->createlocation->text().toStdString());
    p.changeFishBio(f, ui->createbio->toPlainText().toStdString());

    //display changes
    it->setText(tr("Name: ") + (QString::fromStdString(f->name)) + tr("\n") + tr("Species: ") + (QString::fromStdString(f->species))
                + tr("\n") + tr("Bio: ") + (QString::fromStdString(f->bio)) + tr("\n"));

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


void Home::on_pushButton_2_clicked()
{
    for (int i = 0; i < ui->fishlist->count(); i++){
        if (ui->fishlist->item(i)->checkState() == Qt::Checked){
            ui->fishlist->removeItemWidget(ui->fishlist->item(i));
            delete ui->fishlist->item(i);
            ui->fishlist->update();
            p.removeFish(p.collection.at(i));
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
    if(currGroup != all) ui->groupName->setText(QString::fromStdString(currGroup->get_name()));
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

    ui->age->setText(QString::fromStdString(p.getAge()));
    ui->age->setReadOnly(false);
    ui->pbio->setReadOnly(false);
    ui->plocation->setReadOnly(false);

    ui->age->setStyleSheet("background-color : rgba(255,255,255,100%); color : black;");
    ui->pbio->setStyleSheet("background-color : rgba(255,255,255,100%); color : black;");
    ui->plocation->setStyleSheet("background-color : rgba(255,255,255,100%); color : black;");

    ui->plocation->setReadOnly(false);
    ui->SaveChanges->show();

    ui->pwordlabel->show();
    ui->oldpword->show();
    ui->newpword->show();

    ui->pwordlabel->setText("Change Password: ");
}


void Home::on_SaveChanges_clicked()
{
    ui->age->setReadOnly(true);
    ui->pbio->setReadOnly(true);
    ui->plocation->setReadOnly(true);

    ui->age->setStyleSheet("background-color : rgba(255,255,255,1%); color : black;");
    ui->pbio->setStyleSheet("background-color : rgba(255,255,255,1%); color : black;");
    ui->plocation->setStyleSheet("background-color : rgba(255,255,255,1%); color : black;");

    p.changeBio(ui->pbio->toPlainText().toStdString());
    p.location = ui->plocation->toPlainText().toStdString();
    p.age = ui->age->toPlainText().toStdString();

    ui->age->setText(QString::fromStdString(p.getAge()) + tr(" years old"));

    ui->SaveChanges->hide();
    ui->pwordlabel->hide();
    ui->oldpword->hide();
    ui->newpword->hide();
}

void Home::on_newpword_returnPressed()
{
    if(ui->oldpword->text().toStdString() == p.password){
        p.changePassword(ui->newpword->text().toStdString());
        ui->pwordlabel->setText("Change Password: Changed!");
        ui->oldpword->clear();
        ui->newpword->clear();
    } else ui->pwordlabel->setText("Change Password: (*OLD PASSWORD DOES NOT MATCH*)");
}


/*******************************
 * COMM BUTTONS
 * ****************************/

void Home::on_message_returnPressed()
{
    //std::vector<Profile*> participants;
    //participants.push_back(&p);
    //GroupChat *g = new GroupChat(QString("test"), participants);
    msg->set_content(ui->message->text());
    int newRow = chatModel->rowCount();
    chatModel->insertRow(newRow);
    chatModel->setData(chatModel->index(newRow, 0), msg->get_content());
    chatModel->setData(chatModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    ui->message->clear();
    ui->messageHist->scrollToBottom();
}

void Home::on_publish_clicked()
{
    currGroup = new Group(ui->selectGroup->currentText().toStdString());
    Post* newPost = new Post(&p, currGroup, ui->titleBox->text(), ui->postBox->toPlainText());
    currGroup->add_post(newPost);
    p.addPost(newPost);
    addPost(currGroup, newPost);
    addMyPost(currGroup, newPost);

    ui->page->setCurrentIndex(0);

    ui->titleBox->clear();
    ui->postBox->clear();
}

void Home::addPost(Group* gr, Post* po){
    new QListWidgetItem(po->get_title() + tr("\n") + po->get_content(), ui->allPosts); //fix to add to group
}

void Home::addMyPost(Group* gr, Post* po){
    new QListWidgetItem(po->get_title() + tr("\n") + po->get_content() + tr("\nfrom: ") + QString::fromStdString(gr->get_name()), ui->myPosts);
}

void Home::on_allPosts_itemDoubleClicked(QListWidgetItem *item)
{
    int i = 0;
    while (ui->allPosts->item(i) != item) i++;
    currPost = currGroup->postHistory.at(i);

    ui->page->setCurrentIndex(9);
    ui->viewTitle->setText(currPost->get_title());
    ui->viewPost->setText(currPost->get_content());
    ui->commentLabel->setText(tr("Comments: ") + QString::number(currPost->get_comments().size()));
}

void Home::on_addComment_returnPressed()
{
    cmt = new PostComment(&p, currPost, cmt, ui->addComment->text());
    int newRow = cmtModel->rowCount();
    cmtModel->insertRow(newRow);
    cmtModel->setData(cmtModel->index(newRow, 0), cmt->get_content());
    cmtModel->setData(cmtModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    ui->addComment->clear();
    ui->comments->scrollToBottom();
    //add comment to currPost
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

}


void Home::on_groupInfo_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->info);
    QString admins;
    for(Profile* iter : currGroup->get_admin()) admins.append(QString::fromStdString(iter->getUsername()));
    ui->g_infoDisplay->setText(QString::fromStdString(currGroup->get_name()) + tr("\nCreated by: ") + admins + tr("\n\n") +
                               QString::fromStdString(currGroup->get_description()));
}


void Home::on_groupMembers_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->g_members);
}


void Home::on_g_publish_clicked()
{
    Group* newGroup = new Group(ui->g_titleBox->text().toStdString());
    p.addGroup(newGroup);
    newGroup->add_admin(&p);
    newGroup->add_member(&p);
    newGroup->set_description(ui->g_description->toPlainText().toStdString());
    currGroup = newGroup;

    addGroup(newGroup);
    addGroupMember(currGroup, &p);

    ui->selectGroup->addItem(QString::fromStdString(newGroup->get_name()));
    ui->page->setCurrentIndex(1);

    ui->g_titleBox->clear();
    ui->g_description->clear();
}

void Home::addGroup(Group* g){
    new QListWidgetItem(QString::fromStdString(g->get_name()), ui->groupsList);
}

void Home::on_groupsList_itemClicked(QListWidgetItem *item)
{
    int i = 0;
    while (ui->groupsList->item(i) != item) i++;
    currGroup = p.groupsList.at(i);
}


void Home::on_groupsList_itemSelectionChanged()
{
    ui->groupName->setText(QString::fromStdString(currGroup->get_name()));
    ui->stackedWidget_2->setCurrentWidget(ui->g_posts);
}

void Home::addGroupMember(Group* gg, Profile* pp){
    new QListWidgetItem(QString::fromStdString(p.getUsername()), ui->membersList);
}


void Home::on_membersList_itemDoubleClicked(QListWidgetItem *item)
{
    int i = 0;
    std::set<Profile*>::iterator it = currGroup->get_members().begin();
    while (ui->allPosts->item(i) != item) i++;
    std::advance(it, i);
    Profile *temp = *it;

    profilePage(temp);
    //NOT WORKING
}

void Home::profilePage(Profile* pp){
    ui->page->setCurrentWidget(ui->profileview);
    ui->p_username->setText(QString::fromStdString("@" + pp->getUsername()));
    ui->p_name->setText(QString::fromStdString(pp->getNameFirst() + " " + pp->getNameLast()));
    ui->p_bio->setPlainText(QString::fromStdString(pp->getBio()));
    ui->p_location->setText(QString::fromStdString(pp->getLocation()));
    if(!pp->getAge().empty()) ui->p_age->setText(QString::fromStdString(pp->getAge()) + tr(" years old"));
}

/****************************
 * FRIENDS
 * ************************/

void Home::addFriend(Profile* f){
    p.addFriend(f);
}
