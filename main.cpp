// John 3:5
#include "utilities.cpp"
#include "player.hpp"
#include "player.cpp"
#include "game.hpp"
#include "game.cpp"

int main(int argc, char **argv)
{
   GameState game;
   SDL_Window *window = NULL;
   SDL_Renderer *renderer = NULL;

   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

   window = SDL_CreateWindow("RPG Game",
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           WINDOW_WIDTH,
                           WINDOW_HEIGHT,
                           0);

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   game.set_renderer(renderer);
   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
   SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
   TTF_Init();

   game.load();

   int done = 0;
   while (!done)
   {
      done = game.events(window);

      game.collisions();
      game.animate();
      game.render();

      std::this_thread::sleep_for(std::chrono::milliseconds(3));
      game.inc_time();
   }

   TTF_CloseFont(game.getTopBarFont());
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   return 0;
}