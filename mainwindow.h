#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include "tictactoewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setLabelBold(QLabel* label, bool isBold);

private slots:
    void startNewGame();
    void updateNameLabels();
    void handleGameOver(TicTacToeWidget::Player winner);
};

#endif // MAINWINDOW_H
