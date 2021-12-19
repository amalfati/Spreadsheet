#include "godialog.h"
#include "ui_godialog.h"
#include<QRegExp>
#include<QRegExpValidator>
Godialog::Godialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Godialog)
{
    ui->setupUi(this);
    QRegExp exp {"[A-Z][1-9][0-9]{0,2}"};
    ui->lineEdit->setValidator(new QRegExpValidator(exp));
}

Godialog::~Godialog()
{
    delete ui;
}
QString Godialog::gocell() const
     {
         return ui->lineEdit->text();
     }
