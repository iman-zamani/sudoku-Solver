#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <iostream>
#include <string>
#include <QFrame>
bool finish = false;
int x=9;

void MainWindow::resetSudoku()
{
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {

            cells[i][j]->clear();
        }
    }
}

void MainWindow::onCellTextChanged()
{
    QLineEdit* senderCell = qobject_cast<QLineEdit*>(sender());
    if (!senderCell || senderCell->text().length() < 1) {
        return; // Do nothing if no sender or text is not complete
    }

    QString senderName = senderCell->objectName();
    int row, col;
    sscanf(senderName.toStdString().c_str(), "cell_%d_%d", &row, &col);

    // Check if it's the last cell
    if (row == 8 && col == 8) {
        // Option 1: Keep the focus on the last cell
        senderCell->setFocus();

        // Option 2: Move the focus to the first cell (uncomment if needed)
        // if (cells[0][0]) {
        //     cells[0][0]->setFocus();
        // }

        return;
    }

    // Calculate next cell's position
    int nextRow = row, nextCol = col + 1;
    if (nextCol >= 9) {
        nextCol = 0;
        nextRow++;
    }

    // Set focus to next cell
    if (cells[nextRow][nextCol]) {
        cells[nextRow][nextCol]->setFocus();
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Setup UI and grid
    initializeGrid();
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

}

MainWindow::~MainWindow()
{
}
int cmToPixels(double cm) {
    const double inchToCm = 2.54;
    int dpi = 96; // This can vary based on the screen, adjust as necessary
    return static_cast<int>((cm / inchToCm) * dpi);
}

void MainWindow::initializeGrid()
{
    auto centralWidget = new QWidget(this);
    auto mainGridLayout = new QGridLayout(centralWidget);

    int squareSize = 40; // Adjust this size as needed
    int leftMargin = cmToPixels(0); // 1.2 cm to pixels
    mainGridLayout->setContentsMargins(leftMargin, 0, 0, 0); // Adjust top, right, bottom margins as needed

    // Create 9 smaller grids (3x3) and add them to the main grid layout
    for (int blockRow = 0; blockRow < 3; ++blockRow) {
        for (int blockCol = 0; blockCol < 3; ++blockCol) {
            QGridLayout* smallGridLayout = new QGridLayout();
            smallGridLayout->setSpacing(0); // Spacing within each 3x3 block

            // Populate the small grid
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int cellRow = blockRow * 3 + i;
                    int cellCol = blockCol * 3 + j;
                    cells[cellRow][cellCol] = new QLineEdit(centralWidget);
                    cells[cellRow][cellCol]->setMaxLength(1); // Single character
                    cells[cellRow][cellCol]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                    cells[cellRow][cellCol]->setMinimumSize(squareSize, squareSize);
                    cells[cellRow][cellCol]->setMaximumSize(squareSize, squareSize);
                    cells[cellRow][cellCol]->setObjectName(QString("cell_%1_%2").arg(cellRow).arg(cellCol));
                    connect(cells[cellRow][cellCol], &QLineEdit::textChanged, this, &MainWindow::onCellTextChanged);
                    cells[cellRow][cellCol]->setAlignment(Qt::AlignCenter);
                    connect(cells[cellRow][cellCol], &QLineEdit::textChanged, this, &MainWindow::onCellTextChanged);
                    smallGridLayout->addWidget(cells[cellRow][cellCol], i, j);
                }
            }

            // Add spacing around each 3x3 block
            int spacing = 10; // Adjust this value as needed
            if (blockRow > 0) {
                mainGridLayout->setVerticalSpacing(spacing);
            }
            if (blockCol > 0) {
                mainGridLayout->setHorizontalSpacing(spacing);
            }

            mainGridLayout->addLayout(smallGridLayout, blockRow, blockCol);
        }
    }

    auto solveButton = new QPushButton("Solve", centralWidget);
    mainGridLayout->addWidget(solveButton, 3, 0, 1, 3); // Adjust as needed
    connect(solveButton, &QPushButton::clicked, this, &MainWindow::solveSudoku);

    auto resetButton = new QPushButton("Reset", centralWidget);
    mainGridLayout->addWidget(resetButton, 4, 0, 1, 3); // Adjust as needed
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetSudoku);

    setCentralWidget(centralWidget);
}


std::string get_legal(char arr[9][9],int save_index_i =0,int save_index_j = 0){
    int root = sqrt(x);
    int start_i = (int(save_index_i/root))*root ,start_j = (int(save_index_j/root))*root ;
    int end_i = start_i + (root-1), end_j = start_j + (root-1);
    bool temp[16] = {false};
    //This is the part for checking the chunk
    for(int i=start_i;i<=end_i;i++){
        for(int j=start_j;j<=end_j;j++){
            if (arr[i][j] >= '1' && arr[i][j]<='9'){
                temp[(arr[i][j]-'1')] = true;
            }
            else if (arr[i][j] != '*' && arr[i][j] != 32){
                temp[(arr[i][j]-'A') + 9] = true;
            }
        }
    }
    //This is the part to check the row
    for(int j=0 ;j<x; j++){
        if (arr[save_index_i][j] >= '1' && arr[save_index_i][j]<='9'){
            temp[(arr[save_index_i][j]-'1')] = true;
        }
        else if (arr[save_index_i][j] != '*' && arr[save_index_i][j] != 32){
            temp[(arr[save_index_i][j]-'A') + 9] = true;
        }
    }
    //This is the part for checking the colum
    for(int i=0;i<x;i++){
        if (arr[i][save_index_j] >= '1' && arr[i][save_index_j]<='9'){
            temp[(arr[i][save_index_j]-'1')] = true;
        }
        else if (arr[i][save_index_j] != '*' && arr[i][save_index_j] != 32){
            temp[(arr[i][save_index_j]-'A') + 9] = true;
        }
    }
    // This is what it will return
    std::string ret;
    char t1 ;
    for (int i=0;i<x;i++){
        if (!temp[i] && i<9){
            t1 =  i + 49 ;
            ret = ret + t1;
        }
        else if (!temp[i]){
            t1 =  (i-9) + 65;
            ret = ret + t1;
        }
    }
    return ret;
}
void solve(char arr[9][9],int save_index_i =0,int save_index_j = 0){
    bool flag = true;
    for (int i=save_index_i;i<x && flag;i++){
        for(int j=save_index_j;j<x;j++){
            if (arr[i][j] == '*'){
                save_index_i = i;
                save_index_j = j;
                flag = false;
                break;
            }
        }
    }
    if (flag){
        finish = true;
        return;
    }
    std::string ligal = get_legal(arr,save_index_i,save_index_j);
    int n = ligal.size();
    for (int i=0;i<n && !finish;i++){
        arr[save_index_i][save_index_j]= ligal[i];
        solve(arr);
    }
    if (!finish)
        arr[save_index_i][save_index_j]= '*';
    return ;
}
void MainWindow::solveSudoku()
{
    char arr[9][9] = {32};
    readInput(arr);
    finish = false;
    solve(arr);
    displaySolution(arr);
}

void MainWindow::readInput(char arr[9][9])
{
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            QString value = cells[i][j]->text();
            if (value.isEmpty() || value.trimmed().isEmpty()) {
                arr[i][j] = '*'; // Set to '*' if the cell is empty or contains only spaces
            } else {
                arr[i][j] = value.at(0).toLatin1();
            }
        }
    }
}

void MainWindow::displaySolution(const char arr[9][9])
{
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            cells[i][j]->setText(QString(arr[i][j]));
        }
    }
}
