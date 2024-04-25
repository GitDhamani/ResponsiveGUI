#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <QMainWindow>
#include "./ui_mainwindow.h"

//Globals
QMainWindow* thisptr;
Ui::MainWindow* uiptr;

//Prototypes
void initialiseWindow();
void initialiseListWidget(QStringList list);
void initialiseTableWidget(QVector<QVector<QString>> vec);
void initialiseContextMenus();
void connectStatements(QStringList list);
void refreshTable();
QStringList grabListData();
QVector<QVector<QString>> grabTableData();
#endif // DECLARATIONS_H
