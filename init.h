#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <iostream>

enum Status
{
    Default,
    Mousemotion,
    Line,
    Total
};

//Kích thước màn hình
const int SCREEN_WIDTH = 740;
const int SCREEN_HEIGHT = 440;

//Kích thước ô vuông
const int CELL_WIDTH = 40;
const int CELL_HEIGHT = 40;

//Kích thước bàn chơi
const int CELL_NUMW = 10;
const int CELL_NUMH = 10;

//Kích thước Dot
const int DOT_WIDTH = 30;
const int DOT_HEIGHT = 30;

//Load file ảnh thành Texture
SDL_Texture* loadTexture( SDL_Renderer* gRenderer, std::string path );

//Load chữ ra hình ảnh
SDL_Texture* loadFromRenderedText( SDL_Renderer* gRenderer, std::string textureText, TTF_Font* gFont, SDL_Color textColor );
