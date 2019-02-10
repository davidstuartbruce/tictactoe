#include "configurationdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <qaction.h>
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startNewGame,
            &QAction::triggered,
            this,
            &MainWindow::startNewGame);
    connect(ui->quit,
            &QAction::triggered,
            qApp,
            &QApplication::quit);
    connect(ui->gameBoard,
            &TicTacToeWidget::currentPlayerChanged,
            this,
            &MainWindow::updateNameLabels);
    connect(ui->gameBoard,
            &TicTacToeWidget::gameOver,
            this,
            &MainWindow::handleGameOver);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabelBold(QLabel *label, bool isBold)
{
    QFont f = label->font();
    f.setBold(isBold);
    label->setFont(f);
}

void MainWindow::startNewGame()
{
    ConfigurationDialog dialog(this);
    if(dialog.exec() == QDialog::Rejected) {
        return;  // do nothing if dialog rejected
    }
    ui->player1Name->setText(dialog.player1Name());
    ui->player2Name->setText(dialog.player2Name());
    ui->gameBoard->setPlayer1Type(dialog.player1Type());
    ui->gameBoard->setPlayer2Type(dialog.player2Type());
    ui->gameBoard->initNewGame();
}

void MainWindow::updateNameLabels()
{
    setLabelBold(ui->player1Name,
                 ui->gameBoard->currentPlayer() ==
                 TicTacToeWidget::Player::Player1);
    setLabelBold(ui->player2Name,
                 ui->gameBoard->currentPlayer() ==
                 TicTacToeWidget::Player::Player2);
}

void MainWindow::handleGameOver(TicTacToeWidget::Player winner)
{
    QString message;
    QString winnerName;
    if(winner == TicTacToeWidget::Player::Draw) {
        message = tr("Game ended with a draw.");
    } else {
        if(winner == TicTacToeWidget::Player::Player1)
            winnerName = ui->player1Name->text();
        else
            winnerName = ui->player2Name->text();
        message = tr("%1 wins").arg(winnerName);
    }
    QMessageBox::information(this,
                             tr("Info"),
                             message);
}
