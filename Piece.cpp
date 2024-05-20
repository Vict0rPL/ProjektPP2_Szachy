#include "Piece.h"
#include <cmath>

// Pawn move logic (simplified), to include: en passant, double move, capture, promotion
bool Pawn::isValidMove(int startX, int startY, int endX, int endY) const {
    int direction = (color == Color::WHITE) ? 1 : -1;
    if (startX == endX && startY + direction == endY) {
        return true;
    }
    return false;
}

// Rook move logic (simplified), to include: castling
bool Rook::isValidMove(int startX, int startY, int endX, int endY) const {
    if (startX == endX || startY == endY) {
        return true;
    }
    return false;
}

// Knight move logic
bool Knight::isValidMove(int startX, int startY, int endX, int endY) const {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

// Bishop move logic (simplified)
bool Bishop::isValidMove(int startX, int startY, int endX, int endY) const {
    return abs(endX - startX) == abs(endY - startY);
}

// Queen move logic (simplified)
bool Queen::isValidMove(int startX, int startY, int endX, int endY) const {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return (dx == dy) || (startX == endX || startY == endY);
}

// King move logic (simplified)
bool King::isValidMove(int startX, int startY, int endX, int endY) const {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return dx <= 1 && dy <= 1;
}
