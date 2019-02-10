#ifndef TICTACTOEBOT_H
#define TICTACTOEBOT_H

#include <vector>



class TicTacToeBot
{
public:
    TicTacToeBot();
    TicTacToeBot(int player, int board[9]);
    int bestMove();
private:
    int m_player;
    int m_opp_player;
    int m_board[9];
    int boards_checked;
    std::vector<int> m_avail_spots;
    int boardScore(int player, int board[9]);
    bool isGameWon(int player, int board[9]);
    int numAvailSpots(int board[9]);
    std::vector<int> availSpots(int board[9]);
    int otherPlayer(int player);
};

#endif // TICTACTOEBOT_H
