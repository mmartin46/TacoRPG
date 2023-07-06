#include "utilities.cpp"
#include "constants.hpp"
#include "player.hpp"
#include "block.hpp"
#include "attack.hpp"

// What was the last movement
// the player made?
enum state {
   MOVED_LEFT = 1,
   MOVED_RIGHT = 2,
   MOVED_UP = 4,
   MOVED_DOWN = 8
};

class GameState
{
   private:
      int row_count;
      int col_count;

      shared_ptr<Player> player;
      SDL_Renderer *renderer;
      int time;
      pair<int, int> scroll;
      Matrix<int> tileMap;
      Matrix<Block> blocks;
      SDL_Texture* block;

      shared_ptr<Attack> player_attack;
   public:
      GameState();
      virtual ~GameState();

      std::shared_ptr<Player> get_player() { return player; }
      std::shared_ptr<Attack> get_player_attack() { return player_attack; }

      inline void set_block_texture(SDL_Texture *b) { block = b; }
      inline SDL_Texture* get_block_texture() { return block; }

      

      void load();
      void render();
      void animate();
      void collisions();

      

      template <typename T> 
      int collision_in_map(T &plyr, Matrix<Block> &blocks, int i, int j, int P_W, int P_H);

      int events(SDL_Window *);

      void init_tiles();
      void run_scroller(int x, int y);

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

template <typename T>
int GameState::collision_in_map(T &plyr, Matrix<Block> &blocks, int i, int j, int P_W, int P_H)
{
   int touched = 0;
   float pw = P_W, ph = P_H;
   float px = plyr.get_x(), py = plyr.get_y();
   float bx = blocks.at(i).at(j).get_x(), by = blocks.at(i).at(j).get_y(), bw = blocks.at(i).at(j).get_w(), bh = blocks.at(i).at(j).get_h();

   if (px+pw/2 > bx && px+pw/2 < bx+bw)
   {
      // Head Bump
      if (py < by+bh && py>by)
      {
         // Correct Y
         plyr.set_y(by+bh);
         py = by+bh;
         touched = 1;
      }
   }
   if (px+pw > bx && px<bx+bw)
   {
      if (py+ph > by && py < by)
      {
         plyr.set_y(by-ph);
         py = by-ph;
         touched = 2;
      }
   }
   if (py+ph > by && py < by+bh)
   {
      // Rubbing against right edge
      if (px < bx+bw && px+pw > bx+bw)
      {
         // Correct X
         plyr.set_x(bx+bw);
         px = bx+bw;
         touched = 3;
      }
      else if (px+pw > bx && px < bx)
      {
         plyr.set_x(bx-pw);
         px = bx-pw;
         touched = 4;
      }
   }
   return touched;
}

void GameState::collisions()
{
   for (int x = 0; x < row_count; ++x)
   {
      for (int y = 0; y < col_count; ++y)
      {
         collision_in_map(*this->get_player(), this->blocks, x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
      }
   }
}


void GameState::load()
{
   SDL_Surface *surface;
   std::string req, err;
   using std::to_string;


   for (int i = 0; i < 16; ++i)
   {
      std::string wPath = "sprites\\player\\walking" + to_string(i) + ".png";
      surface = IMG_Load(wPath.c_str());
      if (surface == NULL)
      {
         printf("load: No texture");
         SDL_Quit();
         exit(1);
      }
      this->get_player()->set_stillFrame(i, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }

   this->get_player()->set_h(PLAYER_HEIGHT);
   this->get_player()->set_w(PLAYER_WIDTH);
   
   const char *path = "sprites\\block.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load: No texture");
      SDL_Quit();
      exit(1);
   }

   this->set_block_texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\attack\\attack.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load: No texture");
      SDL_Quit();
      exit(1);
   }

   
   this->get_player_attack()->set_stillFrame(0, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

}

void GameState::init_tiles()
{
   int x, y;
   for (x = 0; x < row_count; ++x)
   {
      for (y = 0; y < col_count; ++y)
      {
         tileMap.at(x).at(y) = world_map::worldMap[x][y];
      }
   }

   for (x = 0; x < row_count; ++x)
   {
      for (y = 0; y < col_count; ++y)
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
   shared_ptr<Player> plyr = this->get_player();
   int sX, sY;


   if (plyr->getDirection() == 0)
   {
      // If the player isn't moving.
      if (plyr->get_last_state() == MOVED_LEFT)
      {
         plyr->set_frame(12);
      }
      if (plyr->get_last_state() == MOVED_RIGHT)
      {
         plyr->set_frame(0);
      }
      if (plyr->get_last_state() == MOVED_UP)
      {
         plyr->set_frame(4);
      }
      if (plyr->get_last_state() == MOVED_DOWN)
      {
         plyr->set_frame(8);
      }
   }
   else
   {
      // Movement Animation
      if ((plyr->is_movingLeft()) && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(12);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(13);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(14);
         }
         else if ((this->get_time() % 20) >= 15)
         {
            plyr->set_frame(15);
         }
      }
      if ((plyr->is_movingRight()) && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(0);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(1);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(2);
         }
         else if ((this->get_time() % 20) >= 15)
         {
            plyr->set_frame(3);
         }
      }
      if (plyr->is_movingDown() && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(4);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(5);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(6);
         }
         else if ((this->get_time() % 20) >= 15)
         {
            plyr->set_frame(7);
         }
      }
      if (plyr->is_movingUp() && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(8);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(9);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(10);
         }
         else if ((this->get_time() % 20) >= 15 && (this->get_time() % 20) < 20)
         {
            plyr->set_frame(11);
         }
      }
   }

   sX = -plyr->get_x() + SCREEN_WIDTH / 2;
   sY = -plyr->get_y() + SCREEN_HEIGHT / 2;


   auto t1 = std::async(std::launch::async, &GameState::run_scroller, this, sX, sY);
   t1.wait();
}

void GameState::run_scroller(int x, int y)
{ 
   std::this_thread::sleep_for(std::chrono::microseconds(1));
   this->set_scrollX(x);
   this->set_scrollY(y);
   if (this->get_scrollX() > 0)
   {
      this->set_scrollX(0);
   }
}

void GameState::render()
{
   SDL_SetRenderDrawColor(this->get_renderer(), 120, 120, 120, 255);

   SDL_RenderClear(this->get_renderer());

   int x, y;
   for (x = 0; x < row_count; ++x)
   {
      for (y = 0; y < col_count; ++y)
      {
         switch (tileMap.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION : {
               SDL_Rect blockRect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_block_texture(), NULL, &blockRect);
            }
         }
      }
   }



   // Player Rect
   SDL_Rect prect = { this->get_scrollX() + this->get_player()->get_x(), this->get_scrollY() + this->get_player()->get_y(), this->get_player()->get_h(), this->get_player()->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_player()->get_stillFrame(this->get_player()->get_frame()), NULL, &prect);

   // Player Attack Rect
   SDL_Rect parect = { this->get_scrollX() + this->get_player_attack()->get_x(), this->get_scrollY() + this->get_player_attack()->get_y(), this->get_player_attack()->get_h(), this->get_player_attack()->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_player_attack()->get_stillFrame(0), NULL, &parect);


   SDL_RenderPresent(this->get_renderer());
}

GameState::GameState()
{
   set_time(0);
   player = std::make_shared<Player>();
   player_attack = std::make_shared<Attack>(*player);


   Map dim("files\\test.txt");
   row_count = dim.getRowCount();
   col_count = dim.getColumnCount();


   tileMap = Matrix<int> (row_count, vector<int>(col_count));
   blocks = Matrix<Block> (row_count, vector<Block>(col_count));

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

   if (!this->get_player_attack()->get_shotStatus())
   {
      this->get_player_attack()->set_x(this->get_player()->get_x());
      this->get_player_attack()->set_y(this->get_player()->get_y());
   }


   // Player Movement
   const Uint8 *state = SDL_GetKeyboardState(NULL);

   if (state[SDL_SCANCODE_SPACE])
   {
      this->get_player_attack()->set_x(this->get_player()->get_x() + 10);
   }

   if (state[SDL_SCANCODE_UP])
   {
      this->get_player()->up_movement(2);
   }
   else if (state[SDL_SCANCODE_LEFT])
   {
      this->get_player()->left_movement(2);
   }
   else if (state[SDL_SCANCODE_RIGHT])
   {
      this->get_player()->right_movement(2);
   }
   else if (state[SDL_SCANCODE_DOWN])
   {
      this->get_player()->down_movement(2);
   }
   else
   {
      this->get_player()->setDirection(0);
   }
   return done;
}

GameState::~GameState()
{
   SDL_DestroyTexture(this->get_block_texture());
   SDL_DestroyTexture(this->get_player()->get_stillFrame(0));
}