#include "Board.hpp"

void Board::takePeg(Position pos) {
    markPeg(pos, currentPlayer_); 

    for (int directionInt = 0; directionInt < DIRECTIONS; directionInt++) {
        Direction direction { static_cast<Direction>(directionInt) };
        Position away { pos + getVector(direction) };

        if ( valid(away) && pegOwner(away) == currentPlayer_ ) {
            if ( linkPossible(pos, direction, currentPlayer_) ) 
                markLink(pos, direction, currentPlayer_);
        }
    }

    currentPlayer_ = opponent(currentPlayer_);
}

void Board::dfs(std::vector<std::vector<int>>& vis, Position pos, int player) {
    vis[pos.row()][pos.col()] = 1;

    for (int directionInt = 0; directionInt < DIRECTIONS; directionInt++) {
        Direction direction { static_cast<Direction>(directionInt) };

        Position next { pos + getVector(direction) };
        if ( valid(next) && !vis[next.row()][next.col()] && pegOwner(next) == player && linkExist(pos, direction, player))
            dfs(vis, next, player);
    }
}

bool Board::isGameOver() {
    std::vector<std::vector<int>> vis(rows_, std::vector<int>(cols_, 0));

    for (int col = 0; col < cols_; col++)
        if ( pegOwner(Position(0, col)) == 1 ) 
            dfs(vis, Position(0, col), 1);

    for (int col = 0; col < cols_; col++)
        if  ( vis[rows_ - 1][col] ) return true;

    for (int row = 0; row < rows_; row++)
        if ( pegOwner(Position(row, 0)) == 2 ) 
            dfs(vis, Position(row, 0), 2);

    for (int row = 0; row < rows_; row++)
        if  ( vis[row][cols_ - 1] ) return true;

    return false;
}

void Board::debug() {
    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {
            std::cerr << pegOwner(Position(r, c)) << " ";
            // std::cerr << index(Position(r, c)) << " ";
        }
        std::cerr << "\n";
    }
} 
constexpr CollisionTable Board::collisionTable_;