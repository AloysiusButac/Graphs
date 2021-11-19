#include "SDL2/SDL.h"
#include "Graph/Graph.hpp"
#include <iostream>

#define WINDOW_W 600
#define WINDOW_H 500
#define FPS 30
#define FRAME_DELAY 1000 / FPS

int main(int argc, char* argv[]) {

    std::cout << "Shit works.\n";
    bool isRunning = true;

    unsigned int t = 0, dt = 0;

    SDL_Window *window;
    SDL_Renderer *renderer;

    if(!SDL_Init(SDL_INIT_EVERYTHING)) {
        window = SDL_CreateWindow("Graph", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
        if(!window) {
            SDL_Log("Error creating window.\n");
            isRunning = false;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(!renderer) {
            SDL_Log("Error creating renderer.\n");
            isRunning = false;
        }
    }

    Graph *graph = new Graph();

    SDL_Color colorBG = { 0, 0, 0, 255 };

    while(isRunning) {
        t = SDL_GetTicks();
        // Handle Events
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            int x, y;
            switch (e.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                SDL_Log("[%d, %d]", x, y);
            default:
                break;
            }
        }
        // Update
        // Render
        SDL_SetRenderDrawColor(renderer, colorBG.r, colorBG.g, colorBG.b, colorBG.a);
        SDL_RenderClear(renderer);

        graph->Render(renderer);

        SDL_RenderPresent(renderer);

        dt = SDL_GetTicks() - t;
        if(FRAME_DELAY > t) {
            SDL_Delay(FRAME_DELAY - dt);
        }
    }

    delete graph;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
} 