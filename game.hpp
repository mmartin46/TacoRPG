#pragma once
#include "utilities.cpp"
#include "constants.hpp"
#include "player.hpp"
#include "block.hpp"
#include "attack.hpp"
#include "attack.cpp"
#include "enemy.hpp"
#include "enemy.cpp"



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
      SDL_Texture* block_text;
      SDL_Texture* ground_text;


      shared_ptr<Attack> player_attack;

      vector<shared_ptr<Attack> > player_attacks;
      vector<shared_ptr<Player> > all_players;
      vector<Enemy> enemies;

      Matrix<Entity> ground;

      vector<shared_ptr<Attack> > all_player_attacks;
   public:
      GameState();
      virtual ~GameState();

      vector<shared_ptr<Player> > getAllPlayers() { return all_players; }
      shared_ptr<Player> get_player() { return player; }
      shared_ptr<Attack> get_player_attack() { return player_attack; }

      vector<shared_ptr<Attack> >* get_all_player_attacks() { return &all_player_attacks; }


      inline void set_block_texture(SDL_Texture *b) { block_text = b; }
      inline SDL_Texture* get_block_texture() { return block_text; }

      inline void set_ground_texture(SDL_Texture *g) { ground_text = g; }
      inline SDL_Texture* get_ground_texture() { return ground_text; }      

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

