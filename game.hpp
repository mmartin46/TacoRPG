#pragma once
#include "utilities.cpp"
#include "constants.hpp"
#include "player.hpp"
#include "block.hpp"
#include "attack.hpp"
#include "attack.cpp"



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
      vector<shared_ptr<Player> > entities;
   public:
      GameState();
      virtual ~GameState();

      vector<shared_ptr<Player> > get_entities() { return entities; }
      shared_ptr<Player> get_player() { return player; }
      shared_ptr<Attack> get_player_attack() { return player_attack; }

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

