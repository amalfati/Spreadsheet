#include "spreadsheet.h"
#include"godialog.h"
#include"dialog1.h"
#include <QPixmap>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include<QString>
#include<QFileDialog>
#include<QTextStream>
#include<QIODevice>




SpreadSheet::SpreadSheet(QWidget *parent)
    : QMainWindow(parent)
{
    //Seting the spreadsheet

    setupMainWidget();

    // Creaeting Actions
    createActions();

    // Creating Menus
    createMenus();


    //Creating the tool bar
    createToolBars();

    //making the connexions
    makeConnexions();


    //Creating the labels for the status bar (should be in its proper function)
    cellLocation = new QLabel("(1, 1)");
    cellFormula = new QLabel("");
    statusBar()->addPermanentWidget(cellLocation);
    statusBar()->addPermanentWidget(cellFormula);

    //intier non du fichier
    currentFile=nullptr;


    QStringList labels;
    for(auto letter = 'A';letter<='Z';letter++)
        labels<< QString(letter);
    spreadsheet->setVerticalHeaderLabels(labels);
}

void SpreadSheet::setupMainWidget()
{
    spreadsheet = new QTableWidget;
    spreadsheet->setRowCount(100);
    spreadsheet->setColumnCount(10);
    setCentralWidget(spreadsheet);

}

SpreadSheet::~SpreadSheet()
{
    delete spreadsheet;

    // --------------- Actions       --------------//
    delete  newFile;
    delete  open;
    delete  save;
    delete  saveAs;
    delete  exit;
    delete cut;
    delete copy;
    delete paste;
    delete deleteAction;
    delete find;
    delete row;
    delete Column;
    delete all;
    delete goCell;
    delete recalculate;
    delete sort;
    delete showGrid;
    delete auto_recalculate;
    delete about;
    delete aboutQt;

    // ---------- Menus ----------
    delete FileMenu;
    delete editMenu;
    delete toolsMenu;
    delete optionsMenu;
    delete helpMenu;
}

void SpreadSheet::createActions()
{
    // --------- New File -------------------
   QPixmap newIcon(":/new_file.png");
   newFile = new QAction(newIcon, "&New", this);
   newFile->setShortcut(tr("Ctrl+N"));


    // --------- open file -------------------
   open = new QAction("&Open", this);
   open->setShortcut(tr("Ctrl+O"));

   save = new QAction("&Save", this);
   save->setShortcut(tr("Ctrl+S"));

    
   saveAs = new QAction("save &As", this);

   QPixmap cutIcon(":/cut_icon.png");
   cut = new QAction(newIcon, "Cu&t", this);
   cut->setShortcut(tr("Ctrl+X"));

   
   copy = new QAction( "&Copy", this);
   copy->setShortcut(tr("Ctrl+C"));


   paste = new QAction( "&Paste", this);
   paste->setShortcut(tr("Ctrl+V"));


   deleteAction = new QAction( "&Delete", this);
   deleteAction->setShortcut(tr("Del"));


   row  = new QAction("&Row", this);
   Column = new QAction("&Column", this);
   all = new QAction("&All", this);
   all->setShortcut(tr("Ctrl+A"));



   QPixmap searchIcon(":/resources/icons/search_icon.png");
   find= new QAction(searchIcon, "&find", this);
   find->setShortcut(tr("Ctrl+F"));

   QPixmap goCellIcon(":/go_to_icon.png");
   goCell = new QAction( goCellIcon, "&Go to Cell", this);
   deleteAction->setShortcut(tr("f5"));


   recalculate = new QAction("&Recalculate",this);
   recalculate->setShortcut(tr("F9"));


   sort = new QAction("&Sort");



   showGrid = new QAction("&Show Grid");
   showGrid->setCheckable(true);
   showGrid->setChecked(spreadsheet->showGrid());

   auto_recalculate = new QAction("&Auto-recalculate");
   auto_recalculate->setCheckable(true);
   auto_recalculate->setChecked(true);



   about =  new QAction("&About");
   aboutQt = new QAction("About &Qt");

    // --------- exit -------------------
   QPixmap exitIcon(":/quit_icon.png");
   exit = new QAction(exitIcon,"E&xit", this);
   exit->setShortcut(tr("Ctrl+Q"));
}

void SpreadSheet::close()
{

    auto reply = QMessageBox::question(this, "Exit",
                                       "Do you really want to quit?");
    if(reply == QMessageBox::Yes)
        qApp->exit();
}

void SpreadSheet::createMenus()
{
    // --------  File menu -------//
    FileMenu = menuBar()->addMenu("&File");
    FileMenu->addAction(newFile);
 FileMenu->addAction(open);

    FileMenu->addAction(save);
    FileMenu->addAction(saveAs);
    FileMenu->addSeparator();
    FileMenu->addAction(exit);


    //------------- Edit menu --------/
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(cut);
    editMenu->addAction(copy);
    editMenu->addAction(paste);
    editMenu->addAction(deleteAction);

    editMenu->addSeparator();
    auto select = editMenu->addMenu("&Select");
    select->addAction(row);
    select->addAction(Column);
    select->addAction(all);

    editMenu->addAction(find);
    editMenu->addAction(goCell);



    //-------------- Toosl menu ------------
    toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction(recalculate);
    toolsMenu->addAction(sort);



    //Optins menus
    optionsMenu = menuBar()->addMenu("&Options");
    optionsMenu->addAction(showGrid);
    optionsMenu->addAction(auto_recalculate);


    //----------- Help menu ------------
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);
}

void SpreadSheet::createToolBars()
{

    //Crer une bare d'outils
    auto toolbar1 = addToolBar("File");


    //Ajouter des actions acette bar
    toolbar1->addAction(newFile);
    toolbar1->addAction(save);
    toolbar1->addSeparator();
    toolbar1->addAction(exit);


    //Creer une autre tool bar
    auto toolbar2  = addToolBar("ToolS");
    toolbar2->addAction(goCell);
}

void SpreadSheet::updateStatusBar(int row, int col)
{
    QString cell{"(%0, %1)"};
   cellLocation->setText(cell.arg(row+1).arg(col+1));
   QString find1{"(%0,%1"};
   cellLocation->setText(find1.arg(row+1).arg(col+1));
}



void SpreadSheet::makeConnexions()
{

   // --------- Connexion for the  select all action ----/
connect(all, &QAction::triggered,
           spreadsheet, &QTableWidget::selectAll);
   // Connection for the  show grid
connect(showGrid, &QAction::triggered,
           spreadsheet, &QTableWidget::setShowGrid);
   //Connection for the exit button
connect(exit, &QAction::triggered, this, &SpreadSheet::close);
   //connectting the chane of any element in the spreadsheet with the update status bar
connect(spreadsheet, &QTableWidget::cellClicked, this,  &SpreadSheet::updateStatusBar);
connect(goCell,&QAction::triggered,this,&SpreadSheet::gocellslot);
connect(find,&QAction::triggered,this,&SpreadSheet::finddialog);
connect(save,&QAction::triggered,this,&SpreadSheet::saveSlot);
connect(saveAs,&QAction::triggered,this,&SpreadSheet::saveasslot);
connect(open,&QAction::triggered,this,&SpreadSheet::openslot);
connect(about,&QAction::triggered,this,&SpreadSheet::aboutslot);
connect(aboutQt,&QAction::triggered,this,&SpreadSheet::aboutQtslot);


}


void SpreadSheet::gocellslot(){
    statusBar()->showMessage("Go Dialog",2000);
   Godialog D;
   auto reply =D.exec();
   if(reply==QDialog::Accepted){
       QString cell=D.gocell();
       int row=cell[0].toLatin1() -'A';
        cell=cell.remove(0,1);
        int col =cell.toInt()-1;
        spreadsheet->setCurrentCell(row,col);


   }
}



void SpreadSheet::finddialog(){
  Dialog1 D;
    auto replay=D.exec();
    if(replay== QDialog::Accepted){

        auto pattern =D.findcell();

        for(int i=0;i<spreadsheet->rowCount();i++)
            for(int j=0;j<spreadsheet->columnCount();j++){
                auto content = spreadsheet->item(i,j);
if(content){
    if(content->text().contains(pattern)){
        spreadsheet->setCurrentCell(i,j);
        return;
        }
    }
            }
    }
}
void SpreadSheet::saveSlot(){
    //obtenir nom de fichier
    if(!currentFile){
        QFileDialog D;
        auto filename=D.getSaveFileName();
        currentFile=new QString(filename);
        setWindowTitle(filename);
    }
    saveContent(*currentFile);
}
void SpreadSheet::saveContent(QString filename) const{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){

        QTextStream out(&file);
    for(int i=0;i<spreadsheet->rowCount();i++)
        for(int j=0;j<spreadsheet->columnCount();j++){
            auto cell=spreadsheet->item(i,j);
            if(cell)
                out <<i<<","<< j <<','<<cell->text() <<endl;
        }

    file.close();
    }
}
void SpreadSheet::saveasslot(){
    //obtenir nom de fichier
    if(!currentFile){
        QFileDialog D;
        auto filename=D.getSaveFileName();
        currentFile=new QString(filename);
        setWindowTitle(filename);
    }
    saveContent(*currentFile);
}
void SpreadSheet::saveasContent(QString filename) const{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){

        QTextStream out(&file);
    for(int i=0;i<spreadsheet->rowCount();i++)
        for(int j=0;j<spreadsheet->columnCount();j++){
            auto cell=spreadsheet->item(i,j);
            if(cell)
                out <<i<<","<< j <<','<<cell->text() <<endl;
        }

    file.close();
    }
}
void SpreadSheet::openslot(){
    if(!currentFile){
        QFileDialog D;
        auto filename=D.getOpenFileName();
        currentFile=new QString(filename);
        setWindowTitle(filename);
    }
    loadContent(*currentFile);
}
void SpreadSheet::loadContent(QString filename) const{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly )){

        QTextStream out(&file);
    for(int i=0;i<spreadsheet->rowCount();i++)
        for(int j=0;j<spreadsheet->columnCount();j++){
            auto cell=spreadsheet->item(i,j);
            if(cell)
                out <<i<<","<< j <<','<<cell->text() <<endl;
        }

    file.close();
    }
}

void SpreadSheet::aboutslot()
{
    QMessageBox::about(this, tr("About Spreadsheet"),
            tr("<h2>Spreadsheet </h2>"

               "<p>Spreadsheet is a small application that "
               "demonstrates QAction, QMainWindow, QMenuBar, "
               "QStatusBar, QTableWidget, QToolBar, and many other "
               "Qt classes."));
}
void SpreadSheet::aboutQtslot(){
    QMessageBox::aboutQt(this, "about QT");
}
