#include "utilities.cpp"
#include "constants.hpp"
#include "player.hpp"

class GameState
{
   private:
      std::shared_ptr<Player> player;
      SDL_Renderer *renderer;
      int time;
   public:
      GameState();
      std::shared_ptr<Player> get_player() { return player; }
      void load();
      void render();
      void animate();
      int events(SDL_Window *window);

      inline int get_time() { return time; };
      inline void set_time(int t) { time = t; }
      inline void inc_time() { set_time(get_time() + 1); }
      inline SDL_Renderer *get_renderer() { return renderer; }
      inline void set_renderer(SDL_Renderer *rend) { renderer = rend; }
};

void GameState::load()
{
   SDL_Surface *surface;
   std::string req, err;
   using std::to_string;

   const char *path = "sprites\\player.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load: No texture");
      SDL_Quit();
      exit(1);
   }
   this->get_player()->set_stillFrame(0, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   this->get_player()->set_h(PLAYER_HEIGHT);
   this->get_player()->set_w(PLAYER_WIDTH);
}


void GameState::render()
{
   SDL_SetRenderDrawColor(this->get_renderer(), 20, 20, 20, 255);

   SDL_RenderClear(this->get_renderer());

   // Player Rect
   SDL_Rect prect = { this->get_player()->get_x(), this->get_player()->get_y(), this->get_player()->get_h(), this->get_player()->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_player()->get_stillFrame(0), NULL, &prect);

   SDL_RenderPresent(this->get_renderer());
}

GameState::GameState()
{
   set_time(0);
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

