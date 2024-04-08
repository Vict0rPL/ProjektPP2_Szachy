#include <SDL.h>
#include <iostream>
#include "ChessBoard.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int SQUARE_SIZE = SCREEN_WIDTH / 8; //square window for a standard 8x8 chessboard - change this later to not fill the whole screen

// Function to initialize SDL and create a window
bool initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow("Chessboard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
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
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
            }
            SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    
}

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

    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the chessboard
        drawChessboard(renderer);

        // Update screen
        SDL_RenderPresent(renderer);

        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
