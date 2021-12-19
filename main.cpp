#include "spreadsheet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpreadSheet w;
    w.setWindowTitle("spread sheet");

    w.show();
    return a.exec();
}
