// John 3:5
#include "utilities.cpp"
#include "player.hpp"

class GameState
{
   private:
      std::shared_ptr<Player> player;
   public:
      GameState();
      std::shared_ptr<Player> get_player() { return player; }
      void animate();
      int events(SDL_Window *window);
};

GameState::GameState()
{
   player = std::make_shared<Player>();
}

int GameState::events(SDL_Window *window)
{
   SDL_Event event;
   int done = 0;
   while (SDL_PollEvent(&event))
   {
      switch (event.type)
      {
         case SDL_WINDOWEVENT_CLOSE:
         {
            if (window)
            {
               SDL_DestroyWindow(window);
               window = NULL;
               done = 1;
            }
         }
         break;
         case SDL_QUIT:
            done = 1;
         break;
      }
   }

   const Uint8 *state = SDL_GetKeyboardState(NULL);
   if (state[SDL_SCANCODE_UP])
   {
      this->get_player()->move_up(1);
   }
   else if (state[SDL_SCANCODE_LEFT])
   {
      this->get_player()->move_left(1);
   }
   else if (state[SDL_SCANCODE_RIGHT])
   {
      this->get_player()->move_right(1);
   }
   else if (state[SDL_SCANCODE_DOWN])
   {
      this->get_player()->move_down(1);
   }

   std::cout << this->get_player()->get_x() << " " << this->get_player()->get_y() << "\n";

   return done;
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