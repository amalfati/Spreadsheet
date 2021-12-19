#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
//    QRegExp exp {"[A-Z][1-9][0-9]{0,2}"};
//    ui->lineEdit->setValidator(new QRegExpValidator(exp));
}

Dialog1::~Dialog1()
{
    delete ui;
}
QString Dialog1::findcell() const
    {
        return ui->lineEdit->text();
    }
