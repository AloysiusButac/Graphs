#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text {
public:
    Text();
    Text(const char* text, int font_size);
    ~Text();

    void setText(const char* _text);
    void setFont(TTF_Font *_f);
    void setFontSize(int size);
    void setColor(SDL_Color *_c);
    void setBGColor(SDL_Color *_bg);
    void setPosition(int _x, int _y);

    TTF_Font* getFont();
    int getFontSize();
    SDL_Color* getColor();
    SDL_Color* getBGColor();

    void displayText(SDL_Renderer *ren);
private:
    const char* text = "";
    TTF_Font *font = NULL;
    int font_size = 20;
    int x = 0, y = 0;
    SDL_Color *color = NULL;
    SDL_Color *bg_color = NULL;
    SDL_Texture *texture = NULL;
};