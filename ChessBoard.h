#pragma once
#include <vector>
#include<string>
#include <iostream>
using namespace std;


class ChessBoard
{
	// -- constructors and destructors --
public:
	ChessBoard() {
	initBoard();};
	
	//~ChessBoard();

	//------------------- properties --------------
	vector<vector<int>> board;
	
	

	//------------------- methods ----------------

public:
	void initBoard() {

		vector<int> row = { 0, 0, 0, 0, 0, 0, 0, 0 };
		for (int i = 0; i < 8; i++)
		{
			board.push_back(vector<int>(row));
		}

		for (int j = 0; j < 8; j++)
		{
			for (int i = 0; i < 8; i++)
			{
				cout << board[j][i];
			}
			cout << endl;
		}
		///
		//zaznacz pole board[2][2]
		// sprawdz jaka figura
		// pokaz mozliwe ruchy board[3
		// wybierz ruch
		
	}
};

