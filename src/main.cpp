#include "SDL2/SDL.h"
#include "Graph/Graph.hpp"
#include <iostream>
#include <cmath>

#define WINDOW_W 600
#define WINDOW_H 500
#define FPS 60
// #define FRAME_DELAY 1000 / FPS
#define FRAME_DELAY 16

int main(int argc, char* argv[]) {

    bool isRunning = true;

    unsigned int t = 0, dt = 0;
    float elapsed;

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

    graph->addElement();
    graph->addElement();
    graph->addElement();
    graph->addElement();
    graph->addElement();
    graph->addElement();

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

                if(!graph->isThereElementSelected()) {
                    graph->selectElement(x, y);
                } else {
                    graph->moveElement(x, y);
                    graph->unselectElement();
                }
                
            default:
                break;
            }
        }
        // Update
        // Render
        SDL_SetRenderDrawColor(renderer, colorBG.r, colorBG.g, colorBG.b, colorBG.a);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        graph->Render(renderer);

        SDL_RenderPresent(renderer);

        dt = SDL_GetTicks();
        elapsed = (dt - t) / (float)SDL_GetTicks();
        SDL_Delay(std::floor(16.666f - elapsed));
    }

    delete graph;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
} 