#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Graph/Graph.hpp"
#include "Graph/Text.hpp"
#include <iostream>
#include <cmath>

#define WINDOW_W 600
#define WINDOW_H 500
#define FRAME_DELAY 16

//TODO: 
//      Reconfigure node functions relating to node connections: make it neater
//      Add button... possibly
//      Add a configuration file... maybe
//      Fix mouse lag on moving nodes

enum GraphState { SELECT, CONNECT, REMOVE_CONNECTION, ADD_NODE, DELETE_NODE, END_STATE };

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
    case ADD_NODE:
        return "ADD_NODE";
        break;
    case DELETE_NODE:
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

    // SDL Window and Renderer Initialization

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

    // SDL Font Initialization

    TTF_Font *font;

    if(!TTF_Init()) {
        font = TTF_OpenFont("src/Fonts/OpenSans-Regular.ttf", 12);
    }

    if(!font) {
        SDL_Log("Font Failed to load");
        isRunning = false;
    }

    // Current game state
    GraphState currentnState = SELECT;
    
    // Graph Object Initialization

    Graph *graph = new Graph();

    // Program Object/Elements Initialization

    graph->addElement();
    graph->addElement();
    graph->addElement();
    graph->addElement();

    SDL_Color text_color = {255, 255, 255, 255};
    const char* text = "Press [Q] to move Nodes       Press [W] to add connections";
    Text *text1 = new Text(text, font, 12, &text_color);
    text1->setPosition(10, WINDOW_H - 60);
    text = "Press [E] to remove conenction       Press [R] to add node";
    Text *text2 = new Text(text, font, 12, &text_color);
    text2->setPosition(10, WINDOW_H - 40);
    text = "Press [T] to delete node";
    Text *text3 = new Text(text, font, 12, &text_color);
    text3->setPosition(10, WINDOW_H - 20);

    const char* state_text = state_to_string(currentnState);
    Text *text_state = new Text(state_text, font, 12, &text_color);
    text_state->setPosition(10, 10);

    const char* mouse_click = state_to_string(currentnState);
    Text *mouse_click_text = new Text(mouse_click, font, 12, &text_color);
    mouse_click_text->setPosition(10, 30);

    graph->scanConnections();

    SDL_Color colorBG = { 0, 0, 0, 255 };

    int x = 0, y = 0;
    bool isMouseClicked = false;
    bool isObjectDragged = false;
    int initial_x = 0, initial_y = 0;

    // Program Loop

    while(isRunning) {
        t = SDL_GetTicks();
        // Handle Events
        SDL_Event e;

        while(SDL_PollEvent(&e)) {
            switch (e.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);

                initial_x = x;
                initial_y = y;

                // Select and move nodes
                if(currentnState == SELECT) {
                    if(!graph->isThereElementSelected()) {
                        graph->selectElement(x, y);
                    } else {
                        graph->moveElement(x-10, y-10);
                        graph->unselectElement();
                    }

                // Select nodes and connect them
                } else if(currentnState == CONNECT) {
                    if(!graph->isThereElementSelected()) {
                        graph->selectElement(x, y);
                    } else if(graph->getSelectedElement() == graph->getElement(x, y)) {
                        graph->unselectElement();
                    } else if(graph->isThereElementHere(x, y)) {
                        graph->addTwoWayNodeConnections(graph->getSelectedElement(), graph->getElement(x ,y));
                        graph->scanConnections();
                        graph->unselectElement();
                    } else {
                        graph->unselectElement();
                    }

                // Select nodes annd remove their connections(s)
                } else if(currentnState == REMOVE_CONNECTION) {
                    if(!graph->isThereElementSelected()) {
                        graph->selectElement(x, y);
                    } else if(graph->isThereElementHere(x, y)) {
                        graph->getSelectedElement()->removeConnection(graph->getElement(x, y));
                        graph->getElement(x, y)->removeConnection(graph->getSelectedElement());
                        graph->scanConnections();
                        graph->unselectElement();
                    } else {
                        graph->unselectElement();
                    }

                // Add a new node
                } else if(currentnState == ADD_NODE) {
                    if(!graph->getElement(x, y)) {
                        graph->addElement(new Node(x-10, y-10));
                    }

                // Delete a node and its connections
                } else if(currentnState == DELETE_NODE) {
                    if(graph->getElementCount()) {
                        if(graph->getElement(x, y)) {
                            graph->removeElement(graph->getElement(x, y));
                            graph->scanConnections();
                        }
                    }

                }
                isMouseClicked = true;
                break;
            
            case SDL_MOUSEBUTTONUP:
                isMouseClicked = false;
                if(isObjectDragged) {
                    graph->unselectElement();
                }
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    currentnState = SELECT;    
                    graph->unselectElement();
                    break;
                case SDLK_w:
                    currentnState = CONNECT;    
                    graph->unselectElement();
                    break;
                case SDLK_e:
                    currentnState = REMOVE_CONNECTION;    
                    graph->unselectElement();
                    break;
                case SDLK_r:
                    currentnState = ADD_NODE;    
                    graph->unselectElement();
                    break;
                case SDLK_t:
                    currentnState = DELETE_NODE;    
                    graph->unselectElement();
                    break;

                default:
                    break;
                }
                text_state->setText(state_to_string(currentnState));
                break;

            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);

                if(currentnState == SELECT) {
                    isObjectDragged = std::abs(initial_x - x) > 20 && std::abs(initial_y - y) > 20;

                    if(graph->getSelectedElement() != NULL && isMouseClicked && isObjectDragged) {
                        graph->moveElement(x-10, y-10);
                    }
                }
                break;

            default:
                break;
            }
        }
        // Update
        const char* mouse_text = isMouseClicked ? "True" : "False";
        mouse_click_text->setText(mouse_text);

        // Render
        SDL_SetRenderDrawColor(renderer, colorBG.r, colorBG.g, colorBG.b, colorBG.a);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        graph->Render(renderer);
        text1->displayText(renderer);
        text2->displayText(renderer);
        text3->displayText(renderer);
        text_state->displayText(renderer);
        mouse_click_text->displayText(renderer);

        SDL_RenderPresent(renderer);

        dt = SDL_GetTicks();
        elapsed = (dt - t) / (float)SDL_GetTicks();
        SDL_Delay(std::floor(16.666f - elapsed));
    }

    // Clean-up

    TTF_CloseFont(font);
    delete graph;
    delete text1;
    delete text2;
    delete text3;
    delete text2;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
} 