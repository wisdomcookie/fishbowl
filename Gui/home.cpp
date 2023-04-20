#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    ui->page->setCurrentIndex(0);

    ui->edit->hide();
}

Home::~Home()
{
    delete ui;
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
    p.changeUsername("emmarrr");
    p.nameFirst = "Emma";
    p.nameLast = "Raupp";
    p.changeBio("I am cool and also typing a lot maybe taking notes who knows");

    ui->username->setText(QString::fromStdString("@" + p.username));
    ui->name->setText(QString::fromStdString(p.nameFirst + " " + p.nameLast));
    ui->bio->setText(QString::fromStdString("\"" + p.bio + "\""));
}


void Home::on_fishButton_clicked()
{
    ui->page->setCurrentIndex(5);
}

/*******************************
 * FISH BUTTONS
 * ****************************/

void Home::on_toolButton_clicked()
{
    ui->createfish->setFocus();
    ui->page->setCurrentIndex(6);
}


void Home::on_finished_accepted()
{
    //f = p.createFish(ui->createfish->text().toStdString(), ui->createspecies->text().toStdString()); //, ui->createbio->toPlainText().toStdString());
    ui->createfish->clear();
    ui->createspecies->clear();
    ui->createbio->clear();

    ui->page->setCurrentIndex(5);

    addFish(QString::fromStdString(f->name), QString::fromStdString(f->species), QString::fromStdString(f->bio));
}

void Home::on_finished_rejected()
{
    ui->createfish->clear();
    ui->createspecies->clear();
    ui->createbio->clear();
    ui->page->setCurrentIndex(5);
}

void Home::addFish(QString name, QString species, QString bio)
{
    new QListWidgetItem(tr("Name: ") + name + tr("\n") + tr("Species: ") + species + tr("\n")
                        + tr("Bio: ") + bio + tr("\n"), ui->fishlist);
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
    //set information in boxes
    ui->createfish->setText(QString::fromStdString(f->name));
    ui->createspecies->setText(QString::fromStdString(f->species));
    ui->createbio->setPlainText(QString::fromStdString(f->bio));

    //switch to page
    ui->createfish->setFocus();
    ui->page->setCurrentIndex(6);
}


void Home::on_edit_accepted()
{

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

}

