#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Graph/Graph.hpp"
#include "Graph/Text.hpp"
#include <iostream>
#include <cmath>

#define WINDOW_W 600
#define WINDOW_H 500
#define FRAME_DELAY 16

//TODO: Roconfigure node functions relating to node connections: make it neater
//      Add interaction modes in the program
//      Add button... possibly

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

    TTF_Font *font;

    if(!TTF_Init()) {
        font = TTF_OpenFont("src/Fonts/OpenSans-Regular.ttf", 20);
    }

    if(!font) {
        SDL_Log("Font Failed to load");
        isRunning = false;
    }
    
    Graph *graph = new Graph();

    Text *text1 = new Text();
    text1->setText("This is a text");
    text1->setFont(font);
    text1->setFontSize(20);
    SDL_Color font_color = {255, 255, 255, 255};
    text1->setColor(&font_color);

    Node* n1 = new Node();
    Node* n2 = new Node();
    Node* n3 = new Node();
    Node* n4 = new Node();

    graph->addElement(n1);
    graph->addElement(n2);
    graph->addElement(n3);
    graph->addElement(n4);

    graph->addNodeConnection(n1, n2);
    graph->addNodeConnection(n2, n3);
    graph->addTwoWayNodeConnections(n4, n3);

    graph->scanConnections();

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
                // SDL_Log("[%d, %d]", x, y);

                if(!graph->isThereElementSelected()) {
                    graph->selectElement(x, y);
                } else {
                    graph->moveElement(x-10, y-10);
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
        text1->displayText(renderer);

        SDL_RenderPresent(renderer);

        dt = SDL_GetTicks();
        elapsed = (dt - t) / (float)SDL_GetTicks();
        SDL_Delay(std::floor(16.666f - elapsed));
    }

    TTF_CloseFont(font);
    delete graph;
    delete text1;
    delete n1;
    delete n2;
    delete n3;
    delete n4;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
} 