#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include "headers.h"
#include <QVector>

extern QMainWindow* thisptr;
extern Ui::MainWindow* uiptr;
bool menuToggleTable = 0;
bool menuToggleList = 0;
const int ageColumn = 50;
int columnCnt;
QString ss = "QMenu::item {padding: 2px 35px 2px 5px;} \
        QMenu::item:selected {background-color: rgb(0, 85, 127); color: rgb(255, 255, 255);} \
        QMenu::item:hover {background-color: rgb(0, 85, 127); color: rgb(255, 255, 255);} \
        QMenu::separator {background-color: rgb(225, 225, 225); height: 2px; margin: 5px 0px;}";

void initialiseWindow()
{
    thisptr->setWindowTitle("Responsive GUI Test");
    thisptr->setGeometry(0,0, 581, 233);

    // Get the geometry of the screen
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    // Calculate the center position of the window
    int x = (screenWidth - thisptr->width()) / 2;
    int y = (screenHeight - thisptr->height()) / 2;
    thisptr->move(x,y);
}

void initialiseListWidget(QStringList list)
{
    //Initialise the List Widget
    QFont font {"Arial", 12};
    uiptr->listWidget->setFont(font);
    uiptr->listWidget->addItems(list);
    uiptr->listWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    uiptr->listWidget->setMinimumHeight(215);
    uiptr->listWidget->setMaximumWidth(120);
    uiptr->listWidget->setCurrentRow(0); //Set default row
}

void initialiseTableWidget(QVector<QVector<QString>> vec)
{
    //Initialise the Table Widget
    QFont font {"Arial", 12};
    int rowCount = vec.size();
    int colCount = vec[0].size();
    columnCnt = colCount;
    uiptr->tableWidget->setFont(font);
    uiptr->tableWidget->setRowCount(rowCount);
    uiptr->tableWidget->setColumnCount(colCount);
    QStringList Headers {"Name", "Age", "City", "Country"};
    uiptr->tableWidget->setAlternatingRowColors(true);
    uiptr->tableWidget->setHorizontalHeaderLabels(Headers);
    uiptr->tableWidget->verticalHeader()->setVisible(false);
    uiptr->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    uiptr->tableWidget->setMinimumWidth(436);
    uiptr->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    uiptr->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Fill the Table Widget with Data
    for(int i = 0; i < uiptr->tableWidget->rowCount(); i++)
        for(int j = 0; j < uiptr->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            uiptr->tableWidget->setItem(i, j, item);
            uiptr->tableWidget->item(i,j)->setText(vec[i][j]);
        }
}

void initialiseContextMenus()
{

    // Enable the Context Menu on the List and Table Widgets
    uiptr->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    uiptr->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

void refreshTable()
{
    int ageColumnWidth = ageColumn + 4;
    int tableWidth = uiptr->tableWidget->width() - ageColumnWidth;
    uiptr->tableWidget->setColumnWidth(0, tableWidth/(columnCnt-1));    //Name
    uiptr->tableWidget->setColumnWidth(1, ageColumnWidth);              //Age
    uiptr->tableWidget->setColumnWidth(2, tableWidth/(columnCnt-1));    //City
    uiptr->tableWidget->setColumnWidth(3, tableWidth/(columnCnt-1));    // Country
}

void connectStatements(QStringList list)
{
    // Connect for the listWidget Custom Context Menu
    thisptr->connect(uiptr->listWidget, &QListWidget::customContextMenuRequested, [list](const QPoint& pos){

    // Create the context menu
    QMenu contextMenu("Context Menu", thisptr);
    if (menuToggleList)
    contextMenu.addAction(QIcon("://menuIcon.png"), "Alignment Left");
    if (!menuToggleList)
    contextMenu.addAction(QIcon("://menuIcon.png"), "Alignment Centre");

    //Add Style to remove padding
    contextMenu.setStyleSheet(ss);

    // Show the Menu
    QAction* selectedAction = contextMenu.exec(uiptr->listWidget->mapToGlobal(pos));

    //Handle nothing being clicked
    if (selectedAction == nullptr) return;

    // Handle the selected action (if any)
    if (selectedAction->text() == "Alignment Left")
    {
        //Centre the Items
        for (int i = 0; i < list.size(); i++)
        uiptr->listWidget->item(i)->setTextAlignment(Qt::AlignLeft);
        menuToggleList = 0;
    }
    else if (selectedAction->text() == "Alignment Centre")
    {
        //Centre the Items
        for (int i = 0; i < list.size(); i++)
        uiptr->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter);
        menuToggleList = 1;
    }
    else
    {
        // No action was selected
    }

    });

    // Connect the Custom Table Widget Context Menu
    thisptr->connect(uiptr->tableWidget, &QTableWidget::customContextMenuRequested, [](const QPoint& pos){

    // Create the context menu
    QMenu contextMenu("Context Menu", thisptr);
    if (menuToggleTable)
    contextMenu.addAction(QIcon("://menuIcon.png"), "Set Uniform Width");
    contextMenu.addSeparator();
    if (!menuToggleTable)
    contextMenu.addAction(QIcon("://menuIcon.png"), "Set Custom Width");

    //Add Style to remove padding
    contextMenu.setStyleSheet(ss);

    // Show the Menu
    QAction* selectedAction = contextMenu.exec(uiptr->listWidget->mapToGlobal(pos) + QPoint(130,20));

    //Handle nothing being clicked
    if (selectedAction == nullptr) return;

    // Handle the selected action (if any)
    if (selectedAction->text() == "Set Uniform Width")
    {
        uiptr->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        refreshTable();
        menuToggleTable = 0;
        uiptr->listWidget->setFocus();
    }
    else if (selectedAction->text() == "Set Custom Width")
    {
         uiptr->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Custom);
         refreshTable();
         menuToggleTable = 1;
         uiptr->listWidget->setFocus();
    }
    else
    {
        // No action was selected
    }

    });

    thisptr->connect(uiptr->listWidget, &QListWidget::currentTextChanged, [](const QString rowText){
        uiptr->statusBar->showMessage("List Selection: " + rowText);
    });

    thisptr->connect(uiptr->tableWidget, &QTableWidget::itemClicked, [](QTableWidgetItem* item){
        uiptr->statusBar->showMessage("Table Selection: " + item->text());
    });
}

QStringList grabListData()
{
    return {"Matthew", "James", "Michael", "Paul", "Claire", "Luke"};
}

QVector<QVector<QString>> grabTableData()
{
    QVector<QVector<QString>> vec;
    vec.append({"Matthew","42","London","UK"});
    vec.append({"James","22","Beijing","China"});
    vec.append({"John","32","Kingston","Jamaica"});
    vec.append({"Paul","41","Bucharest","Romania"});
    vec.append({"Carl","15","Vienna","Austria"});
    return vec;
}
