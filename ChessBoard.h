#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "Piece.h"

using namespace std;

class ChessBoard
{
public:
    ChessBoard() {
        initBoard();
    }

    ~ChessBoard();

    vector<vector<unique_ptr<Piece>>> board;// 8x8 matrix of unique pointers to pieces, change it later to separate class or struct
    int selectedX = -1;
    int selectedY = -1;
    bool pieceSelected = false;

    void initBoard();
    bool movePiece(int startX, int startY, int endX, int endY);
    bool isEmpty(int x, int y) const;
    bool isOpponentPiece(int x, int y, Color color) const;
    bool isEnPassantPossible(int x, int y, Color color) const;
    bool isClearPath(int startX, int startY, int endX, int endY) const;
    bool isInCheck(Color color) const;
    bool isMoveValidInCheck(int startX, int startY, int endX, int endY, Color color);
    bool isCheckmate(Color color);

};
