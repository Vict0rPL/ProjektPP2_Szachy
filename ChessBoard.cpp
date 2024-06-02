#include "ChessBoard.h"
#include "Piece.h"

// Destructor definition
ChessBoard::~ChessBoard() {
    // Cleanup is handled by unique_ptr
}

// Initialize the chessboard with default pieces
void ChessBoard::initBoard() {
    board.resize(8);
    for (int i = 0; i < 8; ++i) {
        board[i].resize(8);
    }

    // Initialize pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = make_unique<Pawn>(Color::WHITE);
        board[6][i] = make_unique<Pawn>(Color::BLACK);
    }

    // Initialize rooks
    board[0][0] = make_unique<Rook>(Color::WHITE);
    board[0][7] = make_unique<Rook>(Color::WHITE);
    board[7][0] = make_unique<Rook>(Color::BLACK);
    board[7][7] = make_unique<Rook>(Color::BLACK);

    // Initialize knights
    board[0][1] = make_unique<Knight>(Color::WHITE);
    board[0][6] = make_unique<Knight>(Color::WHITE);
    board[7][1] = make_unique<Knight>(Color::BLACK);
    board[7][6] = make_unique<Knight>(Color::BLACK);

    // Initialize bishops
    board[0][2] = make_unique<Bishop>(Color::WHITE);
    board[0][5] = make_unique<Bishop>(Color::WHITE);
    board[7][2] = make_unique<Bishop>(Color::BLACK);
    board[7][5] = make_unique<Bishop>(Color::BLACK);

    // Initialize queens
    board[0][4] = make_unique<Queen>(Color::WHITE);
    board[7][4] = make_unique<Queen>(Color::BLACK);

    // Initialize kings
    board[0][3] = make_unique<King>(Color::WHITE);
    board[7][3] = make_unique<King>(Color::BLACK);
}

// Move a piece from (startX, startY) to (endX, endY)
bool ChessBoard::movePiece(int startX, int startY, int endX, int endY) {
    cout << "Trying to move piece from (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")" << endl;
    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8) {
        cout << "Invalid start position: (" << startX << ", " << startY << ")" << endl;
        return false;
    }

    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        cout << "Invalid end position: (" << endX << ", " << endY << ")" << endl;
        return false;
    }

    unique_ptr<Piece>& piece = board[startY][startX];
    if (piece == nullptr) {
        cout << "No piece at start position: (" << startX << ", " << startY << ")" << endl;
        return false;
    }

    if (!piece->isValidMove(startX, startY, endX, endY, *this)) {
        cout << "Invalid move: (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")" << endl;
        return false;
    }

    // Ensure the destination is either empty or contains an opponent's piece
    unique_ptr<Piece>& destinationPiece = board[endY][endX];
    if (destinationPiece != nullptr && destinationPiece->getColor() == piece->getColor()) {
        cout << "Cannot move to a square occupied by your own piece." << endl;
        return false;
    }

    board[endY][endX] = move(piece);
    board[startY][startX] = nullptr;
    cout << "Piece moved from (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")" << endl;
    return true;
}

bool ChessBoard::isEmpty(int x, int y) const {
    return board[y][x] == nullptr;
}

bool ChessBoard::isOpponentPiece(int x, int y, Color color) const {
    return board[y][x] != nullptr && board[y][x]->getColor() != color;
}

bool ChessBoard::isEnPassantPossible(int x, int y, Color color) const {
    // Logic to check if en passant is possible
    // check if the last move was a double-step move by a pawn adjacent to the current pawn
    // check if the current move is immediately after that move.
    // needed saved information about the last move made and the positions of pawns that moved two steps - implement after the move memory implementation
	return false; // for now, always return false
}

bool ChessBoard::isClearPath(int startX, int startY, int endX, int endY) const {
    int dx = (endX - startX) == 0 ? 0 : (endX - startX) / abs(endX - startX);
    int dy = (endY - startY) == 0 ? 0 : (endY - startY) / abs(endY - startY);

    int x = startX + dx;
    int y = startY + dy;

    while (x != endX || y != endY) {
        if (!isEmpty(x, y)) {
            return false;
        }
        x += dx;
        y += dy;
    }
    return true;
}

