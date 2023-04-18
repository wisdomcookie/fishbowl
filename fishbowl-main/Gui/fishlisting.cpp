#include "fishlisting.h"
#include "ui_fishlisting.h"

fishListing::fishListing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fishListing)
{
    ui->setupUi(this);
}

fishListing::~fishListing()
{
    delete ui;
}

void fishListing::setFishName(QString n){
    ui->FishName->setText(n);
}

void fishListing::setFishSpecies(QString n){
    ui->FishSpecies->setText(n);
}

void fishListing::setFishBio(QString n){
    ui->FishBio->setText(n);
}
