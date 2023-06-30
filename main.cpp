// John 3:5
#include "utilities.cpp"
#include "player.hpp"
#include "game.hpp"


int main(int argc, char **argv)
{
   GameState game;
   SDL_Window *window = NULL;
   SDL_Renderer *renderer = NULL;

   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

   window = SDL_CreateWindow("Explorer",
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           400,
                           400,
                           0);

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
   SDL_RenderSetLogicalSize(renderer, 400, 400);

   int done = 0;
   while (!done)
   {
      done = game.events(window);


      std::this_thread::sleep_for(std::chrono::milliseconds(10));
   }

   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   return 0;
}