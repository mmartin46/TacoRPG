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

