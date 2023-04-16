#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class homepage; }
QT_END_NAMESPACE

class homepage : public QMainWindow
{
    Q_OBJECT

public:
    homepage(QWidget *parent = nullptr);
    ~homepage();

private slots:
    void on_toolButton_5_triggered(QAction *arg1);

private:
    Ui::homepage *ui;
};
#endif // HOMEPAGE_H
