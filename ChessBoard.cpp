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

void ChessBoard::makeMove(int startX, int startY, int endX, int endY, std::unique_ptr<Piece>& capturedPiece) {
    capturedPiece = std::move(board[endY][endX]);
    board[endY][endX] = std::move(board[startY][startX]);
    board[startY][startX] = nullptr;
}

// Move a piece from (startX, startY) to (endX, endY)
bool ChessBoard::movePiece(int startX, int startY, int endX, int endY) {
    cout << "Trying to move piece from (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")" << endl;

    // Check if the start position is within boundaries of the board
    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8) {
        cout << "Invalid start position: (" << startX << ", " << startY << ")" << endl;
        return false;
    }

    // Check if the end position is within boundaries of the board
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        cout << "Invalid end position: (" << endX << ", " << endY << ")" << endl;
        return false;
    }

    // Get the piece at the start position
    unique_ptr<Piece>& piece = board[startY][startX];
    if (piece == nullptr) {
        cout << "No piece at start position: (" << startX << ", " << startY << ")" << endl;
        return false;
    }

    // Get the color of the piece to be moved
    Color currentColor = piece->getColor();

    // Check if the move is valid for the piece and if it leaves the king in check
    if (!piece->isValidMove(startX, startY, endX, endY, *this) || !isMoveValidInCheck(startX, startY, endX, endY, currentColor)) {
        cout << "Invalid move: (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")" << endl;
        return false;
    }

    // Ensure the destination is not occupied by a piece of the same color
    unique_ptr<Piece>& destinationPiece = board[endY][endX];
    if (destinationPiece != nullptr && destinationPiece->getColor() == piece->getColor()) {
        cout << "Cannot move to a square occupied by your own piece." << endl;
        return false;
    }

    // Move the piece
    std::unique_ptr<Piece> capturedPiece;
    makeMove(startX, startY, endX, endY, capturedPiece);
    moveList.addMove(startX, startY, endX, endY, std::move(capturedPiece));
    cout << "Piece moved from (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")" << endl;

    // Check if the current player is still in check after the move
    if (isInCheck(currentColor)) {
        cout << "You are in check!" << endl;
    }

    // Check if the move results in checkmate for the opponent
    if (isCheckmate((currentColor == Color::WHITE) ? Color::BLACK : Color::WHITE)) {
        cout << "Checkmate! " << (currentColor == Color::WHITE ? "White" : "Black") << " wins!" << endl;
    }

    return true;
}

bool ChessBoard::undoMove() {
    MoveNode* move = moveList.undo();
    if (move) {
        board[move->startY][move->startX] = std::move(board[move->endY][move->endX]);
        board[move->endY][move->endX] = std::move(move->capturedPiece);
        return true;
    }
    return false;
}

bool ChessBoard::redoMove() {
    MoveNode* move = moveList.redo();
    if (move) {
        makeMove(move->startX, move->startY, move->endX, move->endY, move->capturedPiece);
        return true;
    }
    return false;
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

bool ChessBoard::isInCheck(Color color) const {
    int kingX = -1, kingY = -1;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (board[y][x] && board[y][x]->getColor() == color && dynamic_cast<King*>(board[y][x].get())) {
                kingX = x;
                kingY = y;
                break;
            }
        }
    }

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (board[y][x] && board[y][x]->getColor() != color) {
                if (board[y][x]->isValidMove(x, y, kingX, kingY, *this)) {
                    return true;
                }
            }
        }
    }

    return false;
}


bool ChessBoard::isMoveValidInCheck(int startX, int startY, int endX, int endY, Color color) {
    cout << "isMoveValid: " << startX << " " << startY << " " << endX << " " << endY << endl;

    // Ensure the destination is either empty or contains an opponent's piece
    if (board[endY][endX] && board[endY][endX]->getColor() == color) {
        return false; // Can't move to a square occupied by own piece
    }

    // Backup the pieces at the start and end positions
    auto backupStart = std::move(board[startY][startX]);
    auto backupEnd = std::move(board[endY][endX]);

    // Move the piece temporarily
    board[endY][endX] = std::move(backupStart);

    // Check if this move puts the current player's king in check
    bool isValid = !isInCheck(color);

    // Move the pieces back to their original positions
    board[startY][startX] = std::move(board[endY][endX]);
    board[endY][endX] = std::move(backupEnd);

    return isValid;
}


bool ChessBoard::isCheckmate(Color color) {
    // Check if the king of the given color is in check
    if (!isInCheck(color)) return false;

    // Iterate through all rows on the chessboard
    for (int y = 0; y < 8; ++y) {
        // Iterate through all columns on the chessboard
        for (int x = 0; x < 8; ++x) {
            // Check if there's a piece at the current position and if it belongs to the given color
            if (board[y][x] && board[y][x]->getColor() == color) {
                // Iterate through all possible end positions on the chessboard
                for (int endY = 0; endY < 8; ++endY) {
                    for (int endX = 0; endX < 8; ++endX) {
                        // Skip if start and end positions are the same
                        if (x == endX && y == endY) continue;

                        // Check if the piece at (x, y) can move to (endX, endY)
                        if (board[y][x]->isValidMove(x, y, endX, endY, *this) && isMoveValidInCheck(x, y, endX, endY, color)) {
                            // If a valid move is found that gets the king out of check, it's not checkmate
                            cout << "Not checkmate, valid move found " + std::to_string(x) + " " + std::to_string(y) << endl;
                            return false;
                        }
                    }
                }
            }
        }
    }

    // If no valid moves were found to get the king out of check, it's checkmate
    cout << "Checkmate!" << endl;
    return true;
}


