#include <iostream>
#include <SDL2/SDL.h> 

void closeWindow(SDL_Renderer* renderer, SDL_Window* window) {
    // Destroy the renderer created above
    SDL_DestroyRenderer(renderer);

    // Destroy the window created above
    SDL_DestroyWindow(window);

    // Close all the systems of SDL initialized at the top
    SDL_Quit();
}

int main(int argc, char** args) {
    // Initialize all the systems of SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create Window
    SDL_Window* window = SDL_CreateWindow(
        "GameDude", // title
        SDL_WINDOWPOS_UNDEFINED, // x position
        SDL_WINDOWPOS_UNDEFINED, // y position
        800, // window width
        600, // window height
        SDL_WINDOW_SHOWN // flags
    );

    // Create a renderer for the window created above, with the first display driver present
    // and with no additional settings
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Set the draw color of renderer to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    // Clear the renderer with the draw color
    SDL_RenderClear(renderer);

    // Update the renderer which will show the renderer cleared by the draw color which is green
    SDL_RenderPresent(renderer);\

    bool close = false;
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = true;
                    break;
            }
        }
    }

    closeWindow(renderer, window);

    return 0;
}