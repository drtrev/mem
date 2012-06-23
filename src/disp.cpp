#include "disp.h"
#include <iostream>
#include "SDL_ttf.h"

using namespace std;

Disp::Disp()
{
}

int Disp::init(int nlines)
{
  // stop it sefaulting on my ASUS EEE PC
  std::string tempenv = "SDL_VIDEO_X11_WMCLASS=curses";
  char ctempenv[50];
  strncpy(ctempenv, tempenv.c_str(), tempenv.length() + 1);
  SDL_putenv(ctempenv);

  if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    cout << "Couldn't init window" << endl;
    return 1;
  }
  
  SDL_WM_SetCaption("SDL Window", NULL);

  screenSurf = SDL_SetVideoMode( 800 , 480 , 32 , SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_FULLSCREEN);


  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    return 1;
  }

  font=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 38);
  if(!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    return 1;
  }

  numLines = nlines;
  lines = new string[nlines];
  linesSurf = new SDL_Surface*[nlines];
  for (int i = 0; i < nlines; i++) {
    lines[i] = "";
    linesSurf[i] = 0;
  }

  return 0;
}

void Disp::kill()
{
  // TODO if initialised?
  delete [] lines;
  delete [] linesSurf;
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

void Disp::write(string word, int line)
{
  lines[line] = word;

  if (linesSurf[line] != 0) {
    SDL_FreeSurface(linesSurf[line]);
    linesSurf[line] = 0;
  }
  if (lines[line] != "") linesSurf[line] = drawText(font, 255, 255, 255, 255, 0, 0, 0, 0, lines[line].c_str(), blended);
}

void Disp::draw()
{
  SDL_FillRect(screenSurf, NULL , 0x888888);
  SDL_Rect txtRect;
  txtRect.x = 150;
  for (int i = 0; i < numLines; i++) {
    txtRect.y = 100 + 40 * i;
    SDL_BlitSurface( linesSurf[i], NULL , screenSurf, &txtRect );
  }
  SDL_Flip(screenSurf);
}

SDL_Surface* Disp::drawText(TTF_Font *fonttodraw, char fgR, char fgG, char fgB, char fgA, char bgR, char bgG, char bgB, char bgA, const char* text, TextQuality quality)
  // from http://content.gpwiki.org/index.php/SDL_ttf:Tutorials:Basic_Font_Rendering
{
  SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
  SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
  SDL_Surface *resulting_text;

  if (quality == solid) resulting_text = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
  else if (quality == shaded) resulting_text = TTF_RenderText_Shaded(fonttodraw, text, tmpfontcolor, tmpfontbgcolor);
  else if (quality == blended) resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);

  return resulting_text;
}

