#include "home.h"
#include "ui_home.h"
#include <iostream>


Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
    , msg(new Message)
    , chatModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    ui->edit->hide();
    ui->SaveChanges->hide();
    ui->searchBar->setEnabled(false);

    l = new Login(this, &p);
    start(l);
    connect(l, &Login::back, this, &Home::main_menu);

    ui->messageHist->setModel(chatModel);
    chatModel->insertColumn(0);
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

void Home::main_menu()
{
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
}


void Home::on_fishButton_clicked()
{
    ui->page->setCurrentIndex(5);
}

void Home::on_postButton_clicked()
{
    ui->page->setCurrentIndex(8);
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
    new QListWidgetItem(tr("Name: ") + name + tr("\n") + tr("Species: ") + species
                        + tr("\n") + tr("Bio: ") + bio + tr("\n"), ui->fishlist);
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
}


void Home::on_posts_clicked()
{
    //placeholder, should be my posts
    ui->page->setCurrentIndex(0);
}


void Home::on_fish_clicked()
{
    ui->page->setCurrentIndex(5);
}


void Home::on_editProfile_clicked()
{
    ui->pbio->setFocus();
    ui->pbio->setReadOnly(false);

    ui->pbio->setStyleSheet("background-color : rgba(255,255,255,100%); color : black;");
    ui->plocation->setStyleSheet("background-color : rgba(255,255,255,100%); color : black;");

    ui->plocation->setReadOnly(false);
    ui->SaveChanges->show();
}


void Home::on_SaveChanges_clicked()
{
    ui->pbio->setReadOnly(true);
    ui->plocation->setReadOnly(true);

    ui->pbio->setStyleSheet("background-color : rgba(255,255,255,1%); color : black;");
    ui->plocation->setStyleSheet("background-color : rgba(255,255,255,1%); color : black;");

    p.changeBio(ui->pbio->toPlainText().toStdString());
    p.location = ui->plocation->toPlainText().toStdString();

    ui->SaveChanges->hide();

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

    ui->page->setCurrentIndex(0);
    new QListWidgetItem(newPost->get_title() + tr("\n") + newPost->get_content(), ui->allPosts);
}


void Home::on_allPosts_itemDoubleClicked(QListWidgetItem *item)
{
    int i = 0;
    while (ui->allPosts->item(i) != item) i++;
    Post* currPost = currGroup->postHistory.at(i);

    ui->page->setCurrentIndex(9);
    ui->viewTitle->setText(currPost->get_title());
    ui->viewPost->setText(currPost->get_content());

    //ui->FishBi->setText(QString::fromStdString(f->bio));
}

