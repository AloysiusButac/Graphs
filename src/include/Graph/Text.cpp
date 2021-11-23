#include "Text.hpp"

Text::Text() { 
    setText("new Text.\n");
}
Text::Text(const char* _text, int _font_size) { 
    setText(_text);
    setFontSize(_font_size);
}
Text::Text(const char* _text, TTF_Font* _font, int _font_size, SDL_Color* _color) {
    this->text = _text;
    this->font = _font;
    this->font_size =_font_size;
    this->color = _color;
}
Text::~Text() { }

void Text::setText(const char* _text) {
    this->text = _text;
}
void Text::setFont(TTF_Font *_f) { 
    this->font = _f;
}
void Text::setFontSize(int size) { 
    this->font_size = size;
}
void Text::setColor(SDL_Color *_c) { 
    this->color = _c;
}
void Text::setBGColor(SDL_Color *_bg) { 
    this->bg_color = _bg;
}
void Text::setPosition(int _x, int _y) {
   this->x = _x; 
   this->y = _y; 
}

TTF_Font* Text::getFont() { return this->font; }
int Text::getFontSize() { return this->font_size; }
SDL_Color* Text::getColor() { return this->color; }
SDL_Color* Text::getBGColor() { return this->bg_color; }

void Text::displayText(SDL_Renderer *ren) {
    if(this->font && this->color) {
        SDL_Surface *tmp_surface = TTF_RenderText_Solid(this->font, this->text, {255, 255, 255});
        this->texture = SDL_CreateTextureFromSurface(ren, tmp_surface);

        SDL_Rect local_rect = {this->x, this->y, tmp_surface->w, tmp_surface->h};

        SDL_RenderCopy(ren, texture, NULL, &local_rect);

        SDL_DestroyTexture(this->texture);
        SDL_FreeSurface(tmp_surface);
    }
}