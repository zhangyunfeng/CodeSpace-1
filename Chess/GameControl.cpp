/**
 * @file   GameControl.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Tue Dec  1 00:26:10 2015
 * 
 * @brief  
 * 
 * 
 */


#include "GameControl.hpp"

GameControl::GameControl() : mBoard(), mBlackPlayer(BLACK_PIECE), mWhitePlayer(WHITE_PIECE) {
    
}

int GameControl::PlaceChess(Player player, int x, int y) {
    int insertResult = mBoard.InsertPieces(player.GetChess(), x, y);
    return insertResult;
}

int GameControl::PlacePiece(PieceEnum piece, int x, int y) {
    int result = mBoard.InsertPieces(piece, x, y);
    return result;
}

GoBangBoard& GameControl::GetBoard() {
    return mBoard;
}

Player& GameControl::GetBlackPlayer() {
    return mBlackPlayer;
}

Player& GameControl::GetWhitePlayer() {
    return mWhitePlayer;
}

void GameControl::StartNewGame() {
    mBoard.ClearBoard();
}



/** 
 * 开始执行游戏
 * 
 */
void GameControl::RunGame() {
    bool blackChess = false;
    int x = 0;
    int y = 0;
    int placeChessResult = 0;
    while (true) {
        mBoard.PrintBoard();
        
        if (blackChess) {
            std::cout << "请输入黑棋坐标： \nx=";
            std::cin >> x;
            std::cout << "y=";
            std::cin >> y;
            placeChessResult = PlaceChess(mBlackPlayer, x-1, y-1);
        } else {
            std::cout << "请输入白棋坐标: \n(第几行)x=";
            std::cin >> x;
            std::cout << "(第几列)y=";
            std::cin >> y;
            placeChessResult = PlaceChess(mWhitePlayer, x-1, y-1);
        }
        
        // error code handle
        if (placeChessResult == -1) {
            std::cerr << "棋子位置被占用!" << std::endl;
            continue;
        }
        if (placeChessResult == -2) {
            std::cerr << "棋子超出棋盘边界!" << std::endl;
            continue;
        }
        if (blackChess && mBoard.InFiveChessLine(mBlackPlayer.GetChess(), x-1, y-1)) {
            std::cout << "黑棋取胜!" << std::endl;
            mBoard.PrintBoard();
            return;
        }
        if (!blackChess && mBoard.InFiveChessLine(mWhitePlayer.GetChess(), x-1, y-1)) {
            std::cout << "白棋取胜!" << std::endl;
            mBoard.PrintBoard();
            return;
        }
        if (mBoard.IsBoardFull()) {
            std::cout << "平局！" << std::endl;
            mBoard.PrintBoard();
            return;
        }
        std::cout << std::endl;
        blackChess = !blackChess;
    }
}

void GameControl::SetBoard(GoBangBoard& board) {
    board.PrintBoard();
    mBoard = board;
}
