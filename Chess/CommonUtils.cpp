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
    return GoBangBoard();
}
