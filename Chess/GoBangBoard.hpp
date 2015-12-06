/**
 * @file   chess.hpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Sun Nov 29 22:18:15 2015
 * 
 * @brief  
 * 
 * 
 */

#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <string>

#define CHESS_ROW_COUNT 19
#define CHESS_COLUMN_COUNT 19

/** 
 * 黑白棋子枚举
 * 
 */
enum PieceEnum {
    WHITE_PIECE,
    BLACK_PIECE
};

/** 
 * player 1: 0   white
 * player 2: 1   black
 */
class GoBangBoard {
  public:
    GoBangBoard();

    /** 
     * 
     * 
     * @param 插入黑白棋子
     * @param x [0, 14]  棋子的x坐标
     * @param y [0, 14]  棋子的y坐标
     * 
     * @return 0: 插入棋子成功; -1: 棋子位置被占用; -2: 超出棋盘界限
     */
    int InsertPieces(PieceEnum pieceEnum, int x, int y);

    /** 
     * 检查棋子是否5连线
     * 
     * 
     * @return 
     */
    bool CheckWinning(PieceEnum piece);

    /** 
     * 
     * 打印棋盘  空位：'.'; 黑棋: 'x';  白棋: 'o'
     */
    void PrintBoard();

    
    /** 
     * (x,y)是否在5子连线上
     * 
     * @param piece 
     * @param x 
     * @param y 
     * 
     * @return 
     */
    bool InFiveChessLine(PieceEnum piece, int x, int y);

    /** 
     * 棋盘是否满子
     * 
     * 
     * @return 
     */
    bool IsBoardFull();

    void ClearBoard();
    
  protected:
    /** 
     * 
     * 检查（x,y)是否也下有棋子  
     * @param x 棋子的x坐标
     * @param y 棋子的y坐标
     * 
     * @return true: 占用  false: 未占用
     */
    bool checkReplacedPosition(int x, int y);

    /** 
     * 
     * 获取棋子的值
     * @param piece 
     * 
     * @return 
     */
    int getChessValue(PieceEnum piece);

    /** 
     * 
     * 检查棋子是否超出边界
     * @param x 
     * @param y 
     * 
     * @return 
     */
    bool checkChessOutBound(int x, int y);


    /** 
     * 
     * 检查棋子横向有多少个
     * @param piece 
     * @param x 
     * @param y 
     * 
     * @return 
     */
    int checkRowCount(PieceEnum piece, int x, int y);

    /** 
     * 检查棋子竖向有多少个
     * 
     * @param piece 
     * @param x 
     * @param y 
     * 
     * @return 
     */
    int checkColumnCount(PieceEnum piece, int x, int y);

    /** 
     * 检查棋子斜线方向有多少个
     * 
     * @param piece 
     * @param x 
     * @param y 
     * 
     * @return 
     */
    int checkSlashCount(PieceEnum piece, int x, int y);

    /** 
     * 检查棋子反斜线有多少个
     * 
     * @param piece 
     * @param x 
     * @param y 
     * 
     * @return 
     */
    int checkBackSlashCount(PieceEnum piece, int x, int y);

    void initBoard();
    
  private:
    short mBoard[CHESS_ROW_COUNT][CHESS_COLUMN_COUNT];
    int mTotalSteps; // 下的所有棋子的个数
};

#endif /* CHESS_H */
