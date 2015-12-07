/**
 * @file   GameControl.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Nov 30 23:50:06 2015
 * 
 * @brief  
 * 
 * 
 */

#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <vector>
#include "GoBangBoard.hpp"
#include "Player.hpp"

class GameControl {
  public:
    GameControl();
    
    GoBangBoard& GetBoard();
    int PlaceChess(Player player, int x, int y);
    Player& GetBlackPlayer();
    Player& GetWhitePlayer();

    void RunGame();

    int PlacePiece(PieceEnum piece, int x, int y);

    void StartNewGame();

  private:
    GoBangBoard mBoard;
    Player mBlackPlayer;
    Player mWhitePlayer;
};

#endif /* GAMECONTROL_H */
