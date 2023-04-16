#include "homepage.h"
#include "ui_homepage.h"

homepage::homepage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::homepage)
{
    ui->setupUi(this);
}

homepage::~homepage()
{
    delete ui;
}


void homepage::on_toolButton_5_triggered(QAction *arg1)
{

}

