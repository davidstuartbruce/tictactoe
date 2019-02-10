#include "tictactoebot.h"
#include "tictactoewidget.h"

#include <QGridLayout>
#include <QSignalMapper>
#include <iostream>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{
    // create grid of game buttons with mapped signals:
    QGridLayout* gridLayout = new QGridLayout(this);
    QSignalMapper* mapper = new QSignalMapper(this);
    for(int row = 0; row < 3; ++row) {
        for(int column = 0; column < 3; ++column) {
            QPushButton* button = new QPushButton(" ");
            button->setSizePolicy(QSizePolicy::Preferred,
                                  QSizePolicy::Preferred);
            gridLayout->addWidget(button, row, column);
            m_board.append(button);
            mapper->setMapping(button, m_board.count() - 1);
            connect(button, SIGNAL(clicked()),
                    mapper, SLOT(map()));
        }
    }
    connect(mapper, SIGNAL(mapped(int)),
            this, SLOT(handleButtonClick(int)));
    // We don't have a valid Player yet:
    m_currentPlayer = Player::Invalid;

    connect(this, &TicTacToeWidget::needMove,
            this, &TicTacToeWidget::awaitMove);
    //enable debugging output
    //std::cout << "leaving TicTacToeWidget ctor" << std::endl;
}

TicTacToeWidget::Player TicTacToeWidget::currentPlayer() const
{
    return m_currentPlayer;
}

void TicTacToeWidget::setCurrentPlayer(TicTacToeWidget::Player p)
{
    if(m_currentPlayer == p) {
        return;
    }
    m_currentPlayer = p;
    emit currentPlayerChanged(p);
    emit needMove();   // this allows us to get move for PlayerType::Computer
}

void TicTacToeWidget::initNewGame()
{
    for(QPushButton* button: m_board){
        button->setText(" ");
    }
    setCurrentPlayer(Player::Player1);
}

void TicTacToeWidget::setPlayer1Type(TicTacToeWidget::PlayerType ptype)
{
    m_Player1Type = ptype;
}

void TicTacToeWidget::setPlayer2Type(TicTacToeWidget::PlayerType ptype)
{
    m_Player2Type = ptype;
}

TicTacToeWidget::PlayerType TicTacToeWidget::currentPlayerType()
{
    if (m_currentPlayer == Player::Player1)
        return m_Player1Type;
    else
        return m_Player2Type;
}

TicTacToeWidget::Player TicTacToeWidget::checkWinCondition()
{
    // We need a more generalized function that can be called
    // to test for the win of a specific player for any
    // board configuration, so now this function is mostly just
    // a wrapper

   // See if either player has won:
    if (isGameWon(Player::Player1, m_board))
        return Player::Player1;
    if (isGameWon(Player::Player2, m_board))
        return Player::Player2;

    // Return 'Invalid' for winner if game still in progress,
    // i.e. if no winner and at least one cell still unplayed:
    for (int cell = 0; cell < 9; cell++) {
        if(m_board[cell]->text() == " ")
            return Player::Invalid;
    }

    // If we get to here, all cells are played and there is
    // no winner.
    return Player::Draw;
}

char TicTacToeWidget::playerMarker(TicTacToeWidget::Player player)
{
    switch (player) {
        case Player::Player1:
            return 'X';
        case Player::Player2:
            return 'O';
        default:
            return ' ';
    }
}

bool TicTacToeWidget::isGameWon(TicTacToeWidget::Player player, QVector<QPushButton *> board)
{
    char playerMark = playerMarker(player);
    QString cellMarks[9];
    for (int i = 0; i < 9; i++) {
        cellMarks[i] = board[i]->text();
    }
    return (
        (cellMarks[0] == playerMark && cellMarks[1] == playerMark && cellMarks[2] == playerMark) ||
        (cellMarks[3] == playerMark && cellMarks[4] == playerMark && cellMarks[5] == playerMark) ||
        (cellMarks[6] == playerMark && cellMarks[7] == playerMark && cellMarks[8] == playerMark) ||
        (cellMarks[0] == playerMark && cellMarks[3] == playerMark && cellMarks[6] == playerMark) ||
        (cellMarks[1] == playerMark && cellMarks[4] == playerMark && cellMarks[7] == playerMark) ||
        (cellMarks[2] == playerMark && cellMarks[5] == playerMark && cellMarks[8] == playerMark) ||
        (cellMarks[0] == playerMark && cellMarks[4] == playerMark && cellMarks[8] == playerMark) ||
        (cellMarks[2] == playerMark && cellMarks[4] == playerMark && cellMarks[6] == playerMark)
            );
}

void TicTacToeWidget::makeComputerMove(TicTacToeWidget::Player player)
{
    //placeholder function - pick a random available move:
    int* boardInts = boardAsInt(m_board);
    int playerNum = currentPlayer() == Player::Player1 ? 1 : 2;
    TicTacToeBot* robot = new TicTacToeBot(playerNum, boardInts);
    int index = robot->bestMove();
    delete robot;


    // send the choice to the interface:
    handleButtonClick(index);
}

int *TicTacToeWidget::boardAsInt(QVector<QPushButton *> board)
{
    static int vals[9];
    for(int i = 0; i < 9; i++) {
        QString ltr = board[i]->text();
        if(ltr == "X") {
            vals[i] = 1;
        } else if (ltr == "O") {
            vals[i] = 2;
        } else {
            vals[i] = 0;
        }
    }
    return vals;
}

void TicTacToeWidget::handleButtonClick(int index)
{
    std::cout << "button clicked" << std::endl;
    if(m_currentPlayer == Player::Invalid) {
        return;     // game not started
    }
    if(index < 0 || index > m_board.size()) {
        return;     // out of bounds - perhaps should generate error msg
    }

    QPushButton* button = m_board[index];
    if(button->text() != " ") {
        return;     // invalid move
    }
    // if we get to here we have a real move:
    // set to "X" or "O" depending on whose move it is:
    button->setText(currentPlayer() == Player::Player1 ? "X" : "O");
    button->setStyleSheet(currentPlayer() == Player::Player1
                          ? "color : red; font : bold 60px"
                          : "color : blue; font : bold 60px");
    // see if we have a winner:
    Player winner = checkWinCondition();
    // if no winner, change currentPlayer to other Player:
    if(winner == Player::Invalid) {
        setCurrentPlayer(currentPlayer() == Player::Player1
                       ? Player::Player2
                       : Player::Player1);
    } else {
        emit gameOver(winner);
    }
}

void TicTacToeWidget::awaitMove()
{
    // if the current player is Computer, we get a move
    // from the robot, otherwise we just wait for clicks
    // from the interface:
    if (currentPlayerType() == PlayerType::Computer)
        makeComputerMove(currentPlayer());
}
