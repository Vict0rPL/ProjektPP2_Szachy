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

    void initBoard();
    bool movePiece(int startX, int startY, int endX, int endY);
};
