#include "GoBangBoard.hpp"

GoBangBoard::GoBangBoard() {
    for (int i = 0; i < CHESS_ROW_COUNT; i++) {
        for (int j = 0; j < CHESS_COLUMN_COUNT; j++) {
            mBoard[i][j] = -1;
        }
    }
    mTotalSteps = 0;
}

void GoBangBoard::initBoard() {
      for (int i = 0; i < CHESS_ROW_COUNT; i++) {
        for (int j = 0; j < CHESS_COLUMN_COUNT; j++) {
            mBoard[i][j] = -1;
        }
    }
    mTotalSteps = 0;
}

void GoBangBoard::ClearBoard() {
    initBoard();
}

/** 
 * from left->right  top->bottom
 * 
 * 
 * @return 
 */
std::vector<short> GoBangBoard::GetBoardValues() const {
    std::vector<short> ret;
    for (int i = 0; i < CHESS_ROW_COUNT; i++) {
        for (int j = 0; j < CHESS_COLUMN_COUNT; j++) {
            ret.push_back(mBoard[i][j]);
        }
    }
    return ret;
}

void GoBangBoard::PrintBoard() {
    int blackChessValue = GetChessValue(BLACK_PIECE);
    int whiteChessValue = GetChessValue(WHITE_PIECE);
    for (int i = 0; i < CHESS_ROW_COUNT; i ++) {
        for (int j = 0; j < CHESS_COLUMN_COUNT; j++) {
            if (mBoard[i][j] == blackChessValue) {
                std::cout << "x";
            }
            if (mBoard[i][j] == whiteChessValue) {
                std::cout << "o";
            }
            if (mBoard[i][j] == -1) {
                std::cout << ".";
            }
            std::cout << " ";
             
        }
        std::cout << std::endl;
    }
}

int GoBangBoard::InsertPieces(PieceEnum pieceEnum, int x, int y) {

    /// 检查棋子超出边界
    if (!checkChessOutBound(x, y)) {
        return -2;
    }

    /// 检查位置被占用
    if (checkReplacedPosition(x, y)) {
        return -1;
    }

    switch (pieceEnum) {
        case BLACK_PIECE:
            mBoard[x][y] = GetChessValue(pieceEnum);  // 
            mTotalSteps++;
            return 0;
        case WHITE_PIECE:
            mBoard[x][y] = GetChessValue(pieceEnum);
            mTotalSteps++;
            return 0;
        default:
            return -1;
    }
}

void GoBangBoard::InsertValue2Board(short value, int x, int y) {
    int blackPieceValue = GetChessValue(BLACK_PIECE);
    int whitePieceValue = GetChessValue(WHITE_PIECE);
    
    if (value == blackPieceValue) {
        InsertPieces(BLACK_PIECE, x, y);
    } else {
        std::cout << "valeue != blackPieceValue" << std::endl;;
    }
    if (value == whitePieceValue) {
        InsertPieces(WHITE_PIECE, x, y);
    } else {
        std::cout << "value != whitePieceValue" << std::endl;
    }
}

bool GoBangBoard::CheckWinning(PieceEnum piece) {
    for (int i = 0; i < CHESS_ROW_COUNT; i++) {
        for (int j = 0; j < CHESS_COLUMN_COUNT; j++) {
            if (InFiveChessLine(piece, i, j)) {
                return true;
            }
        }
    }
    return false;
}


int GoBangBoard::GetChessValue(PieceEnum piece) {
    switch (piece) {
        case BLACK_PIECE:
            return 1;
        case WHITE_PIECE:
            return 0;
        default:
            return -1;
    }
}

/** 
 * 检查 (x,y)是否在五子连线上
 * 
 * @param piece 
 * @param x 
 * @param y 
 * 
 * @return 
 */
bool GoBangBoard::InFiveChessLine(PieceEnum piece, int x, int y) {
    int maxCount = 0;
    maxCount = checkVerticalCount(piece, x, y); // 横向
    maxCount = std::max(maxCount, checkHorizontalCount(piece, x, y)); // 竖向
    maxCount = std::max(maxCount, checkSlashCount(piece, x, y)); // 斜线方向
    maxCount = std::max(maxCount, checkBackSlashCount(piece, x, y)); // 反斜线方向
    if (maxCount >= 5) {
        return true;
    }
    return false;
}

bool GoBangBoard::checkChessOutBound(int x, int y) {
    /// x,y 都要在[0,14]区间中
    if (x >= 0 && x < CHESS_COLUMN_COUNT && y >= 0 && y < CHESS_ROW_COUNT) {
        return true;
    }
    return false;
}

bool GoBangBoard::checkReplacedPosition(int x, int y) {
    if (mBoard[x][y] == -1) {
        return false;
    }
    return true;
}


int GoBangBoard::checkVerticalCount(PieceEnum piece, int x, int y) {
    int value = GetChessValue(piece);
    int count = 0;
    // (x,y)和 piece不匹配 或者 是空
    if (mBoard[x][y] != value) {
        return count;
    }
    // from (x,y) to left
    for (int i = 0; i > -5; i--) {
        if (!checkChessOutBound(x+i, y)) {
            break;
        }
        if (value == mBoard[x+i][y]) {
            count ++;
        } else {
            break;
        }
    }

    // from (x, y) to right
    for (int i = 1; i < 5; i++) {
        if (!checkChessOutBound(x+i, y)) {
            break;
        }
        if (value == mBoard[x+i][y]) {
            count ++;
        } else {
            break;
        }
    }
    return count;
}

int GoBangBoard::checkHorizontalCount(PieceEnum piece, int x, int y) {
    int value = GetChessValue(piece);
    int count = 0;
    // (x,y) 和 piece不匹配或者是空
    if (mBoard[x][y] != value) {
        return count;
    }
    // from (x,y) to top
    for (int i = 0; i > -5; i--) {
        if (!checkChessOutBound(x, y+i)) {
            break;
        }
        if (value == mBoard[x][y+i]) {
            count++;
        } else {
            break;
        }
    }

    // from (x,y) to bottom
    for (int i = 1; i < 5; i++) {
        if (!checkChessOutBound(x, y+i)) {
            break;
        }
        if (value == mBoard[x][y+i]) {
            count++;
        } else {
            break;
        }
    }
    return count;
}

int GoBangBoard::checkBackSlashCount(PieceEnum piece, int x, int y) {
    int value = GetChessValue(piece);
    int count = 0;
    // (x,y) 和 piece不匹配
    if (mBoard[x][y] != value) {
        return count;
    }
    // from (x,y) to left-top
    for (int i = 0; i > -5; i--) {
        if (!checkChessOutBound(x+i, y+i)) {
            break;
        }
        if (value == mBoard[x+i][y+i]) {
            count ++;
        } else {
            break;
        }
    }

    // from (x,y) to right-top
    for (int i = 1; i < 5; i++) {
        if (!checkChessOutBound(x+i, y+i)) {
            break;
        }
        if (value == mBoard[x+i][y+i]) {
            count ++;
        } else {
            break;
        }
    }
    return count; 
}

int GoBangBoard::checkSlashCount(PieceEnum piece, int x, int y) {
    int value = GetChessValue(piece);
    int count = 0;
    // (x,y) 和 piece不匹配
    if (mBoard[x][y] != value) {
        return count;
    }
    // from (x,y) to right-top
    for (int i = 0; i > -5; i--) {
        if (!checkChessOutBound(x-i, y+i)) {
            break;
        }
        if (value == mBoard[x-i][y+i]) {
            count ++;
        } else {
            break;
        }
    }
    // from (x,y) to left-down
    for (int i = 1; i < 5; i++) {
        if (!checkChessOutBound(x-i, y+i)) {
            break;
        }
        if (value == mBoard[x-i][y+i]) {
            count ++;
        } else {
            break;
        }
    }
    return count;
}

bool GoBangBoard::IsBoardFull() {
    return mTotalSteps >= (CHESS_COLUMN_COUNT * CHESS_COLUMN_COUNT);
}


short GoBangBoard::GetPieceValue(int x, int y) {
    if (x >= 0 && x < CHESS_COLUMN_COUNT && y >= 0 && y < CHESS_ROW_COUNT) {
        return mBoard[x][y];
    }

    return -1;
}
