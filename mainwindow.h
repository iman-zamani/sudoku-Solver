#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void solveSudoku();
    void onCellTextChanged();
    void resetSudoku();


private:
    QLineEdit* cells[9][9];

    void initializeGrid();
    void readInput(char arr[9][9]);
    void displaySolution(const char arr[9][9]);

};
#endif // MAINWINDOW_H
