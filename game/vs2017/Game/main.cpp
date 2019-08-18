#include "Core.h"
#include "Includes.h"
#include "Engine.h"

#define UNUSED_PARAM(p) p

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

using namespace ToeEngine;

namespace ToeEngine
{
  extern Engine* ENGINE;
}

int main(int argc, char *args[])
{
  /*UNUSED_PARAM(argc);

  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL could not init" << std::endl;
  }
  else
  {
    window = SDL_CreateWindow("Toe Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
      std::cout << "Window creation failture" << std::endl;
    }
    else
    {
      screenSurface = SDL_GetWindowSurface(window);

      SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      SDL_UpdateWindowSurface(window);

      SDL_Delay(2000);
    }
  }

  SDL_DestroyWindow(window);

  SDL_Quit();*/

  ENGINE = new Engine();

  ENGINE->Init();

  ENGINE->Update();

  ENGINE->Shutdown();

  delete ENGINE;

  return 0;
}