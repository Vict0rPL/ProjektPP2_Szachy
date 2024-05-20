#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <memory>
#include <typeinfo>
#include "ChessBoard.h"

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

// Function to load a texture from a file
SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return texture;
}

// Function to initialize SDL and create a window
bool initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        return false;
    }

    *window = SDL_CreateWindow("Chessboard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Load textures
    whitePawnTexture = loadTexture("./Assets/white-pawn.png", *renderer);
    blackPawnTexture = loadTexture("./Assets/black-pawn.png", *renderer);
    whiteRookTexture = loadTexture("./Assets/white-rook.png", *renderer);
    blackRookTexture = loadTexture("./Assets/black-rook.png", *renderer);
    whiteKnightTexture = loadTexture("./Assets/white-knight.png", *renderer);
    blackKnightTexture = loadTexture("./Assets/black-knight.png", *renderer);
    whiteBishopTexture = loadTexture("./Assets/white-bishop.png", *renderer);
    blackBishopTexture = loadTexture("./Assets/black-bishop.png", *renderer);
    whiteQueenTexture = loadTexture("./Assets/white-queen.png", *renderer);
    blackQueenTexture = loadTexture("./Assets/black-queen.png", *renderer);
    whiteKingTexture = loadTexture("./Assets/white-king.png", *renderer);
    blackKingTexture = loadTexture("./Assets/black-king.png", *renderer);

    // Check if all textures are loaded
    if (!whitePawnTexture || !blackPawnTexture || !whiteRookTexture || !blackRookTexture ||
        !whiteKnightTexture || !blackKnightTexture || !whiteBishopTexture || !blackBishopTexture ||
        !whiteQueenTexture || !blackQueenTexture || !whiteKingTexture || !blackKingTexture) {
        return false;
    }

    return true;
}

// Function to free textures
void freeTextures() {
    SDL_DestroyTexture(whitePawnTexture);
    SDL_DestroyTexture(blackPawnTexture);
    SDL_DestroyTexture(whiteRookTexture);
    SDL_DestroyTexture(blackRookTexture);
    SDL_DestroyTexture(whiteKnightTexture);
    SDL_DestroyTexture(blackKnightTexture);
    SDL_DestroyTexture(whiteBishopTexture);
    SDL_DestroyTexture(blackBishopTexture);
    SDL_DestroyTexture(whiteQueenTexture);
    SDL_DestroyTexture(blackQueenTexture);
    SDL_DestroyTexture(whiteKingTexture);
    SDL_DestroyTexture(blackKingTexture);
}

// Function to draw a chessboard
void drawChessboard(SDL_Renderer* renderer) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            // Alternate colors
            if ((x + y) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
            }
            else {
                SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // Grey - on black you cant see pieces
            }
            SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

// Function to draw the chess pieces
void drawPieces(SDL_Renderer* renderer, const ChessBoard& board) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board.board[y][x]) {
                SDL_Texture* texture = nullptr;
                Color color = board.board[y][x]->getColor();
                if (typeid(*board.board[y][x]) == typeid(Pawn)) {
                    texture = (color == Color::WHITE) ? whitePawnTexture : blackPawnTexture;
                }
                else if (typeid(*board.board[y][x]) == typeid(Rook)) {
                    texture = (color == Color::WHITE) ? whiteRookTexture : blackRookTexture;
                }
                else if (typeid(*board.board[y][x]) == typeid(Knight)) {
                    texture = (color == Color::WHITE) ? whiteKnightTexture : blackKnightTexture;
                }
                else if (typeid(*board.board[y][x]) == typeid(Bishop)) {
                    texture = (color == Color::WHITE) ? whiteBishopTexture : blackBishopTexture;
                }
                else if (typeid(*board.board[y][x]) == typeid(Queen)) {
                    texture = (color == Color::WHITE) ? whiteQueenTexture : blackQueenTexture;
                }
                else if (typeid(*board.board[y][x]) == typeid(King)) {
                    texture = (color == Color::WHITE) ? whiteKingTexture : blackKingTexture;
                }

                if (texture) {
                    SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
                    SDL_RenderCopy(renderer, texture, nullptr, &rect);
                }
            }
        }
    }
}

// Helper function to get board coordinates from mouse position
bool getBoardCoordinates(int mouseX, int mouseY, int& boardX, int& boardY) {
    if (mouseX >= 0 && mouseX < SCREEN_WIDTH && mouseY >= 0 && mouseY < SCREEN_HEIGHT) {
        boardX = mouseX / SQUARE_SIZE;
        boardY = mouseY / SQUARE_SIZE;
        return true;
    }
    return false;
}

// Function to handle user input for piece movement
void handleMouseClick(SDL_Event& e, ChessBoard& board, bool& pieceSelected, int& selectedX, int& selectedY, Color& currentTurn) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        cout << "Mouse button down" << endl;
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        int boardX, boardY;
        if (getBoardCoordinates(mouseX, mouseY, boardX, boardY)) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                if (!pieceSelected) {
                    if (board.board[boardY][boardX] && board.board[boardY][boardX]->getColor() == currentTurn) {
                        pieceSelected = true;
                        selectedX = boardX;
                        selectedY = boardY;
                        cout << "Piece selected at (" << boardX << ", " << boardY << ")" << endl;
                    }
                }
                else {
                    if (board.movePiece(selectedX, selectedY, boardX, boardY)) {
                        pieceSelected = false;
                        cout << "Piece moved" << endl;
                        currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE; // Switch turns
                        cout << "Current turn: " << (currentTurn == Color::WHITE ? "White" : "Black") << endl;
                    }
                }
            }
            else if (e.button.button == SDL_BUTTON_RIGHT) {
                pieceSelected = false;
                cout << "Piece deselected" << endl;
            }
        }
    }
}


// Main function
int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initSDL(&window, &renderer)) {
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
                handleMouseClick(e, board, pieceSelected, selectedX, selectedY, currentTurn);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the chessboard
        drawChessboard(renderer);

        // Draw the pieces
        drawPieces(renderer, board);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    freeTextures();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
