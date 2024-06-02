#ifndef PIECE_H
#define PIECE_H

class ChessBoard; // Forward declaration

enum class Color { WHITE, BLACK };

class Piece {
public:
    Color color;
    Piece(Color c) : color(c) {}
    virtual ~Piece() {}
    Color getColor() const { return color; }
    virtual bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const = 0;
};

class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
};

class Rook : public Piece {
public:
    Rook(Color c) : Piece(c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
};

class Knight : public Piece {
public:
    Knight(Color c) : Piece(c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
};

class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
};

class Queen : public Piece {
public:
    Queen(Color c) : Piece(c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
};

class King : public Piece {
public:
    King(Color c) : Piece(c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const ChessBoard& board) const override;
};

#endif // PIECE_H
