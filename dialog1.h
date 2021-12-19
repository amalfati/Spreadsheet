#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include<QString>
#include<QRegularExpression>


namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = nullptr);
    ~Dialog1();

    QString findcell()const;
private:
    Ui::Dialog1 *ui;
};

#endif // DIALOG1_H
