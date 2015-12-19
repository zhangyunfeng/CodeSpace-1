/**
 * @file   CommonUtils.cpp
 * @author Ken <ken@ken-Ubuntu>
 * @date   Mon Dec  7 23:34:22 2015
 * 
 * @brief  
 * 
 * 
 */


#include <fstream>
#include "CommonUtils.h"

#include "GoBangBoard.hpp"

#ifdef __CPLUSPLUS
extern "C" {
#endif

#include <string.h>
    
#ifdef __CPLUSPLUS    
}
#endif


void CommonUtils::SaveBoard(const GoBangBoard& board, const std::string& path) {
    
    std::vector<short> piecesValues = board.GetBoardValues();
    std::ofstream outFileStream(path, std::ios::out);
    std::vector<short>::iterator itNext = piecesValues.begin();
    std::vector<short>::iterator itEnd = piecesValues.end();
    for (; itNext != itEnd; itNext++) {
        outFileStream << *itNext << "|";
    }
    outFileStream.flush();
    outFileStream.close();
 }

GoBangBoard CommonUtils::LoadBoard(const std::string& boardFile) {
    // TODO:
    std::ifstream inFileStream(boardFile, std::ios::in);
    short pieceValue;
    char sink[3] = {""};
    int size = 3;
    char delim = '|';

    GoBangBoard ret;
    for (int i = 0; i < CHESS_COLUMN_COUNT; i++) {
        for (int j = 0; j < CHESS_ROW_COUNT; j++) {
            if (inFileStream.good() && 0 != inFileStream.getline(sink, size, delim)) {
                ret.InsertValue2Board(atoi(sink), i, j);
            }
            bzero(sink, 3);
        }
    }

    inFileStream.close();

    ret.PrintBoard();

    return ret;
}

