#ifndef GODIALOG_H
#define GODIALOG_H

#include <QDialog>
#include<QString>
namespace Ui {
class Godialog;
}

class Godialog : public QDialog
{
    Q_OBJECT

public:
    explicit Godialog(QWidget *parent = nullptr);
    ~Godialog();

    QString gocell()const ;

private:
    Ui::Godialog *ui;
};

#endif // GODIALOG_H
