#include "Piece.h"
#include "ChessBoard.h"
#include <cmath>

// Pawn move logic (simplified), to include: en passant, double move, capture, promotion
bool Pawn::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    int direction = (color == Color::WHITE) ? 1 : -1;
    int startRow = (color == Color::WHITE) ? 1 : 6;

    // Single move forward
    if (startX == endX && startY + direction == endY) {
        return board.isEmpty(endX, endY);
    }

    // Double move forward from start position
    if (startX == endX && startY == startRow && startY + 2 * direction == endY) {
        return board.isEmpty(endX, endY) && board.isEmpty(startX, startY + direction);
    }

    // Capturing an opponent's piece
    if ((startX + 1 == endX || startX - 1 == endX) && startY + direction == endY) {
        return board.isOpponentPiece(endX, endY, color);
    }

    // En passant
    if ((startX + 1 == endX || startX - 1 == endX) && startY == (color == Color::WHITE ? 4 : 3) && endY == (color == Color::WHITE ? 5 : 2)) {
        return board.isEnPassantPossible(endX, endY, color);
    }

    // Promotion
    if (endY == (color == Color::WHITE ? 7 : 0) && startX == endX && startY + direction == endY) {
        return board.isEmpty(endX, endY);
    }

    return false;
}

// Rook move logic (simplified), to include: castling
bool Rook::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    if (startX == endX || startY == endY) {
        return board.isClearPath(startX, startY, endX, endY);
    }
    return false;
}

// Knight move logic
bool Knight::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

// Bishop move logic 
bool Bishop::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    return abs(endX - startX) == abs(endY - startY) && board.isClearPath(startX, startY, endX, endY);
}

// Queen move logic 
bool Queen::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return ((dx == dy) || (startX == endX || startY == endY)) && board.isClearPath(startX, startY, endX, endY);
}

// King move logic 
bool King::isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const {
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    return dx <= 1 && dy <= 1;
}
