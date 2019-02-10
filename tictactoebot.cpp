#include "tictactoebot.h"
#include <random>
#include <iostream>

TicTacToeBot::TicTacToeBot()
{

}

TicTacToeBot::TicTacToeBot(int player, int board[])
{
    m_player = player;
    m_opp_player = (m_player == 1) ? 2 : 1;

    for (int i = 0; i < 9; i++) {
        m_board[i] = board[i];
    }
    boards_checked = 0;
    std::cout << "Creating TicTacToeBot for player " << m_player << std::endl;
}

int TicTacToeBot::bestMove()
{
//    std::cout << "Entering TicTacToeBot::bestMove()" << std::endl;
    // as placeholder, generating random valid index:
    int index = 0;
    int threshold = -2;
    // pick the move with the highest value for the current player:
    for(int spot : availSpots(m_board)) {
        //std::cout << spot << " is available" << std::endl;
        // recursively obtain score for this spot
        // set up board for spot
        int new_board[9];
        for (int i = 0; i < 9 ; i++) {
            new_board[i] = m_board[i];
            new_board[spot] = m_player;
        }
        // get other player value:
        int new_player = otherPlayer(m_player);
        // we use the negative because the players are reversed:
        int new_score = -boardScore(new_player, new_board);
        std::cout << "for spot " << spot << " score is " << new_score << std::endl;
        if(new_score > threshold) {
            threshold = new_score;
            index = spot;
//            std::cout << "picking spot " << spot << " with score " << new_score << std::endl;
        }
    }
    std::cout << "bestMove() picking spot " << index << " with score " << threshold << std::endl;

    return index;
}

// If 'player' is certain to win, return 1.
// If 'player' is certain to win, return -1.
// Any board without a destined winner has score 0.
int TicTacToeBot::boardScore(int player, int board[])
{
//    std::cout << "Entering TicTacToeBot::boardScore()" << std::endl;

    int opp_player = (player == 1) ? 2 : 1;
    if(isGameWon(player, board))
        return 1;
    if(isGameWon(opp_player, board))
        return -1;
    if(availSpots(board).size() == 0)
        return 0;
    // for each available spot, we compute the boardScore()
    // for the resulting board, keeping in mind that it will be the
    // other player's turn and thus the recursive call returns the
    // negative of the score when viewed from the perspective of
    // this board. We pick the best one as viewed from our current
    // perspective.
    //std::cout << "number of available spots: " << availSpots(board).size() << std::endl;
    int score = -2;  //ensure that scores of -1 are considered if they appear first
    for(int spot : availSpots(board)) {
        //std::cout << spot << " is available" << std::endl;
        // recursively obtain score for this spot
        // set up board for spot
        int new_board[9];
        for (int i = 0; i < 9 ; i++) {
            new_board[i] = board[i];
            new_board[spot] = player;
        }
        // get other player value:
        int new_player = otherPlayer(player);
        // we use the negative because the players are reversed:
        int new_score = -boardScore(new_player, new_board);
        if(new_score > score)
            score = new_score;
    }
    boards_checked++;
    return score;
}

bool TicTacToeBot::isGameWon(int player, int board[])
{
    return (
        (board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)
            );
}

int TicTacToeBot::numAvailSpots(int board[])
{
    return availSpots(board).size();
}

std::vector<int> TicTacToeBot::availSpots(int board[])
{
//    std::cout << "Entering TicTacToeBot::availSpots()" << std::endl;

    std::vector<int> avail;
    for (int i = 0; i < 9; i++) {
        if(board[i] == 0)
            avail.push_back(i);
    }
    return avail;
}

int TicTacToeBot::otherPlayer(int player)
{
    return (player == 1) ? 2 : 1;
}
