#ifndef FISHLISTING_H
#define FISHLISTING_H

#include <QWidget>

namespace Ui {
class fishListing;
}

class fishListing : public QWidget
{
    Q_OBJECT

public:
    explicit fishListing(QWidget *parent = nullptr);
    ~fishListing();

    void setFishName(QString);

    void setFishSpecies(QString n);

    void setFishBio(QString n);

private:
    Ui::fishListing *ui;
};

#endif // FISHLISTING_H
