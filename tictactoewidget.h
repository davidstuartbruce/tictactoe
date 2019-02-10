#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QPushButton>
#include <QWidget>

class TicTacToeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TicTacToeWidget(QWidget *parent = nullptr);

    enum class Player {
        Invalid, Player1, Player2, Draw
    };
    Q_ENUM(Player)

    enum class PlayerType {
        Human, Computer
    };
    Q_ENUM(PlayerType)

    Player currentPlayer() const;
    void setCurrentPlayer(Player p);
    void initNewGame();
    void setPlayer1Type(PlayerType ptype);
    void setPlayer2Type(PlayerType ptype);

private:
    QVector<QPushButton*> m_board;
    Player m_currentPlayer;
    PlayerType m_Player1Type;
    PlayerType m_Player2Type;

    PlayerType currentPlayerType();
    Player checkWinCondition();
    static char playerMarker(Player player);
    static bool isGameWon(Player player, QVector<QPushButton*> board);
    void makeComputerMove(Player player);
    int* boardAsInt(QVector<QPushButton*> board);

signals:
    void currentPlayerChanged(Player);
    void needMove();
    void gameOver(Player);

public slots:

private slots:
    void handleButtonClick(int index);
    void awaitMove();
};

#endif // TICTACTOEWIDGET_H
