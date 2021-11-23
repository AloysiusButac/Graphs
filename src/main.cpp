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
//      Fix interaction modes in the program
//      Add button... possibly
//      Add a configuration file... maybe
//      Implement states.. Properly
//      Check for memory leaks // NOTE: there are definitely memory leaks

enum GraphState { SELECT, CONNECT, REMOVE_CONNECTION, ADD_NONDE, DELETE_NONDE, END_STATE };

static const char* state_to_string(GraphState state) {
    switch (state)
    {
    case SELECT:
        return "SELECT";
        break;
    case REMOVE_CONNECTION:
        return "REMOVE_CONNECTION";
        break;
    case CONNECT:
        return "CONNECT";
        break;
    case ADD_NONDE:
        return "ADD_NODE";
        break;
    case DELETE_NONDE:
        return "DELETE_NODE";
        break;
    default:
        return "NA";
        break;
    }
}

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
        font = TTF_OpenFont("src/Fonts/OpenSans-Regular.ttf", 12);
    }

    if(!font) {
        SDL_Log("Font Failed to load");
        isRunning = false;
    }

    GraphState currentnState = SELECT;
    
    Graph *graph = new Graph();

    SDL_Color text_color = {255, 255, 255, 255};
    const char* text = "Press [Q] to move Nodes       Press [W] to add connections";
    Text *text1 = new Text(text, font, 12, &text_color);
    text1->setPosition(10, WINDOW_H - 30);

    const char* state_text = state_to_string(currentnState);
    Text *text2 = new Text(state_text, font, 12, &text_color);
    text2->setPosition(10 ,WINDOW_H - 50);

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
                if(currentnState == SELECT) {
                    if(!graph->isThereElementSelected()) {
                        graph->selectElement(x, y);
                    } else {
                        graph->moveElement(x-10, y-10);
                        graph->unselectElement();
                    }

                } else if(currentnState == CONNECT) {
                    if(!graph->isThereElementSelected()) {
                        graph->selectElement(x, y);
                    } else if(graph->isThereElementHere(x, y)) {
                        graph->addNodeConnection(graph->getSelectedElement(), graph->getElement(x ,y));
                        graph->scanConnections();
                        graph->unselectElement();
                    } else {
                        graph->unselectElement();
                    }

                } else if(currentnState == REMOVE_CONNECTION) {
                    if(!graph->isThereElementSelected()) {
                        graph->selectElement(x, y);
                    } else if(graph->isThereElementHere(x, y)) {
                        graph->getSelectedElement()->removeConnection();
                        graph->scanConnections();
                        graph->unselectElement();
                    } else {
                        graph->unselectElement();
                    }

                } else if(currentnState == ADD_NONDE) {
                    if(!graph->getElement(x, y)) {
                        graph->addElement();
                    }

                } else if(currentnState == DELETE_NONDE) {
                    if(graph->getElementCount()) {
                        if(graph->getElement(x, y)) {
                            graph->removeElement(graph->getElement(x, y));
                        }
                    }

                }

            case SDL_KEYUP:
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    currentnState = SELECT;    
                    text2->setText(state_to_string(currentnState));
                    break;
                case SDLK_w:
                    currentnState = CONNECT;    
                    text2->setText(state_to_string(currentnState));
                    break;
                case SDLK_e:
                    currentnState = REMOVE_CONNECTION;    
                    text2->setText(state_to_string(currentnState));
                    break;
                case SDLK_r:
                    currentnState = ADD_NONDE;    
                    text2->setText(state_to_string(currentnState));
                    break;
                case SDLK_t:
                    currentnState = DELETE_NONDE;    
                    text2->setText(state_to_string(currentnState));
                    break;

                default:
                    break;
                }
                text2->setText(state_to_string(currentnState));

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
        text2->displayText(renderer);

        SDL_RenderPresent(renderer);

        dt = SDL_GetTicks();
        elapsed = (dt - t) / (float)SDL_GetTicks();
        SDL_Delay(std::floor(16.666f - elapsed));
    }

    TTF_CloseFont(font);
    delete graph;
    delete text1;
    delete text2;
    delete n1;
    delete n2;
    delete n3;
    delete n4;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
} 