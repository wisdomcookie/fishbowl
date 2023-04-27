#ifndef HOME2_H
#define HOME2_H

#include <QMainWindow>
//#include "../profiles/fish.h"
//#include "../profiles/profile.h"
#include "../groups/group.h"
#include "QtWidgets/qlistwidget.h"

namespace Ui {
class home2;
}

class home2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit home2(QWidget *parent = nullptr);
    ~home2();

private slots:
    void on_homeButton_clicked();

    void on_groupButton_clicked();

    void on_messageButton_clicked();

    void on_friendsButton_clicked();

    void on_profileButton_clicked();

    void on_fishButton_clicked();

    void on_toolButton_clicked();

    void on_finished_accepted();

    void addFish(QString, QString, QString);

    void on_fishlist_itemDoubleClicked(QListWidgetItem *item);

    void on_finished_rejected();

    void on_EditFishProfile_clicked();

private:
    Ui::home2 *ui;
    profile p;
    fish* f;
};

#endif // HOME2_H
