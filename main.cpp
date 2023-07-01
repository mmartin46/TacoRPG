// John 3:5
#include "utilities.cpp"
#include "player.hpp"
#include "game.hpp"


namespace BitSet
{
   uint8_t get_bit(const int &value, int pos) 
   {
      return (value >> pos) & 1U;
   }

   void set_bit(int &value, int pos)
   {
      value |= (1 << pos);
   }
   void reset_bit(int &value, int pos)
   {
      value &= ~(1 << pos);
   }
}

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
   game.set_renderer(renderer);
   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
   SDL_RenderSetLogicalSize(renderer, 400, 400);

   game.load();

   int done = 0;
   while (!done)
   {
      done = game.events(window);

      game.animate();
      game.render();

      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      game.inc_time();
   }

   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   return 0;
}