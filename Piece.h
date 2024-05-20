#ifndef PIECE_H
#define PIECE_H

enum class Color { WHITE, BLACK };

// Base class for all chess pieces
class Piece {
public:
    // Constructor to initialize a Piece with a specific color
    Piece(Color color) : color(color) {}

    // Virtual destructor to allow derived class destructors to be called
    virtual ~Piece() {}

    // Delete copy constructor to prevent copying of pieces
    Piece(const Piece&) = delete;

    // Delete copy assignment operator to prevent assignment of pieces
    Piece& operator=(const Piece&) = delete;

    // Default move constructor to allow moving of pieces
    Piece(Piece&&) = default;

    // Default move assignment operator to allow move assignment of pieces
    Piece& operator=(Piece&&) = default;

    // Function to get the color of the piece
    Color getColor() const { return color; }

    // Pure virtual function to validate a move; must be implemented by derived classes
    virtual bool isValidMove(int startX, int startY, int endX, int endY) const = 0;

protected:
    // Color of the piece (WHITE or BLACK)
    Color color;
};

// All chess pieces Inherit from Piece

class Pawn : public Piece {
public:
    Pawn(Color color) : Piece(color) {}
    bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class Rook : public Piece {
public:
    Rook(Color color) : Piece(color) {}
    bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class Knight : public Piece {
public:
    Knight(Color color) : Piece(color) {}
    bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(color) {}
    bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class Queen : public Piece {
public:
    Queen(Color color) : Piece(color) {}
    bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class King : public Piece {
public:
    King(Color color) : Piece(color) {}
    bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

#endif // PIECE_H
