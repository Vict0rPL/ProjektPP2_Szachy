#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "ChessBoard.h"

using namespace std;

extern SDL_Texture* whitePawnTexture;
extern SDL_Texture* blackPawnTexture;
extern SDL_Texture* whiteRookTexture;
extern SDL_Texture* blackRookTexture;
extern SDL_Texture* whiteKnightTexture;
extern SDL_Texture* blackKnightTexture;
extern SDL_Texture* whiteBishopTexture;
extern SDL_Texture* blackBishopTexture;
extern SDL_Texture* whiteQueenTexture;
extern SDL_Texture* blackQueenTexture;
extern SDL_Texture* whiteKingTexture;
extern SDL_Texture* blackKingTexture;

bool initSDL(SDL_Window** window, SDL_Renderer** renderer, int screenWidth, int screenHeight);
SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);
void freeTextures();
void drawChessboard(SDL_Renderer* renderer, int screenWidth, int screenHeight, int squareSize);
void drawPieces(SDL_Renderer* renderer, const ChessBoard& board, int squareSize);
bool getBoardCoordinates(int mouseX, int mouseY, int& boardX, int& boardY, int screenWidth, int screenHeight, int squareSize);
void handleMouseClick(SDL_Event& e, ChessBoard& board, bool& pieceSelected, int& selectedX, int& selectedY, Color& currentTurn, int screenWidth, int screenHeight, int squareSize);

#endif // GAME_H
