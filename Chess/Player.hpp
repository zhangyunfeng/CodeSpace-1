#ifndef PLAYER_H
#define PLAYER_H

#include "GoBangBoard.hpp"

class Player {
  public:
    Player() = delete;
    Player(PieceEnum piece);
    void SetPiece(PieceEnum piece);
    PieceEnum& GetChess();
  private:
    PieceEnum mPiece;
    
};

#endif /* PLAYER_H */
