#ifndef DISP_H
#define DISP_H

#include <string>
#include "SDL_ttf.h"

enum TextQuality {solid, shaded, blended};

class Disp {
  private:
    TTF_Font *font;
    SDL_Surface *drawText(TTF_Font *, char fgR, char fgG, char fgB, char fgA, char bgR, char bgG, char bgB, char bgA, const char*, TextQuality quality);
    SDL_Surface *screenSurf;
    std::string *lines;
    SDL_Surface **linesSurf;
    int numLines;

  public:

    Disp();

    int init(int nlines);
    void kill();

    void write(std::string, int line);
    void draw();
};

#endif
