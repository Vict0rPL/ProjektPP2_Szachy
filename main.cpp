#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "ChessBoard.h"
#include "Game.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int SQUARE_SIZE = SCREEN_WIDTH / 8; // Square window for a standard 8x8 chessboard

// Declare global variables to store textures
SDL_Texture* whitePawnTexture = nullptr;
SDL_Texture* blackPawnTexture = nullptr;
SDL_Texture* whiteRookTexture = nullptr;
SDL_Texture* blackRookTexture = nullptr;
SDL_Texture* whiteKnightTexture = nullptr;
SDL_Texture* blackKnightTexture = nullptr;
SDL_Texture* whiteBishopTexture = nullptr;
SDL_Texture* blackBishopTexture = nullptr;
SDL_Texture* whiteQueenTexture = nullptr;
SDL_Texture* blackQueenTexture = nullptr;
SDL_Texture* whiteKingTexture = nullptr;
SDL_Texture* blackKingTexture = nullptr;

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initSDL(&window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        SDL_Quit();
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    ChessBoard board;
    board.initBoard(); // Ensure the board is initialized

    bool pieceSelected = false;
    int selectedX = -1, selectedY = -1;
    Color currentTurn = Color::WHITE; // Start with white's turn
    cout << "Current turn: White" << endl;

    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
            else {
                handleMouseClick(e, board, pieceSelected, selectedX, selectedY, currentTurn, SCREEN_WIDTH, SCREEN_HEIGHT, SQUARE_SIZE);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the chessboard
        drawChessboard(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SQUARE_SIZE);

        // Draw the pieces
        drawPieces(renderer, board, SQUARE_SIZE);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    freeTextures();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
