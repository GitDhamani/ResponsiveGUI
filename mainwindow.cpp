#include "./ui_mainwindow.h"
#include <QMainWindow>
#include "mainwindow.h"
#include "headers.h"
#include "declarations.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thisptr = this;
    uiptr = ui;

    //Some Dummy Data
    QStringList list = grabListData();
    QVector<QVector<QString>> vec = grabTableData();

    initialiseWindow();
    initialiseListWidget(list);
    initialiseTableWidget(vec);
    initialiseContextMenus();
    connectStatements(list);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    refreshTable();
}

