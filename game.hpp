#include "utilities.cpp"
#include "constants.hpp"
#include "player.hpp"
#include "block.hpp"



class GameState
{
   private:
      shared_ptr<Player> player;
      SDL_Renderer *renderer;
      int time;
      pair<int, int> scroll;
      Matrix<int> tileMap;
      Matrix<Block> blocks;
      SDL_Texture* block;
   public:
      GameState();
      virtual ~GameState();

      std::shared_ptr<Player> get_player() { return player; }
      
      inline void set_block(SDL_Texture *b) { block = b; }
      inline SDL_Texture* get_block() { return block; }
      void load();
      void render();
      void animate();
      int events(SDL_Window *);

      void init_tiles();

      inline int get_time() { return time; };
      inline void set_time(int t) { time = t; }
      inline void inc_time() { set_time(get_time() + 1); }

      inline void set_scrollX(int n) { scroll.first = n; }
      inline void set_scrollY(int n) { scroll.second = n; }
      inline int get_scrollX() { return scroll.first; }
      inline int get_scrollY() { return scroll.second; }

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
   
   path = "sprites\\block.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load: No texture");
      SDL_Quit();
      exit(1);
   }

   this->set_block(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);
}

void GameState::init_tiles()
{
   int x, y;
   for (x = 0; x < 28; ++x)
   {
      for (y = 0; y < 100; ++y)
      {
         tileMap.at(x).at(y) = world_map::worldMap[x][y];
      }
   }

   for (x = 0; x < 28; ++x)
   {
      for (y = 0; y < 100; ++y)
      {
         switch (tileMap.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION:
               blocks.at(x).at(y).set_y(x*BLOCK_WIDTH);               
               blocks.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               blocks.at(x).at(y).set_w(BLOCK_WIDTH);
               blocks.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;               
         }
      }
   }

}


void GameState::animate()
{
}

void GameState::render()
{
   SDL_SetRenderDrawColor(this->get_renderer(), 20, 20, 20, 255);

   SDL_RenderClear(this->get_renderer());

   int x, y;
   for (x = 0; x < 28; ++x)
   {
      for (y = 0; y < 100; ++y)
      {
         switch (tileMap.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION : {
               SDL_Rect blockRect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_y()), static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_w()), static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_h()) };
               SDL_RenderCopy(this->get_renderer(), this->get_block(), NULL, &blockRect);
            }
         }
      }
   }

   // Player Rect
   SDL_Rect prect = { this->get_scrollX() + this->get_player()->get_x(), this->get_scrollX() + this->get_player()->get_y(), this->get_player()->get_h(), this->get_player()->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_player()->get_stillFrame(0), NULL, &prect);

   SDL_RenderPresent(this->get_renderer());
}

GameState::GameState()
{
   set_time(0);
   player = std::make_shared<Player>();
   tileMap = Matrix<int> (28, vector<int>(100));
   blocks = Matrix<Block> (28, vector<Block>(100));
   player->set_id(0);
   set_scrollX(0);
   set_scrollY(0);
   init_tiles();
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
               bitset::set_bit(done, 0);
            }
         }
         break;
         case SDL_QUIT:
               bitset::set_bit(done, 0);
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

GameState::~GameState()
{
   SDL_DestroyTexture(this->get_block());
   SDL_DestroyTexture(this->get_player()->get_stillFrame(0));
}