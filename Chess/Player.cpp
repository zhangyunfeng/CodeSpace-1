#include "Player.hpp"



Player::Player(PieceEnum piece) : mPiece(piece) {
    
}

void Player::SetPiece(PieceEnum piece) {
    mPiece = piece;
}

PieceEnum& Player::GetChess() {
    return mPiece;
}

