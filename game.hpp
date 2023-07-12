#pragma once
#include "utilities.cpp"
#include "constants.hpp"
#include "player.hpp"
#include "block.hpp"
#include "attack.hpp"
#include "attack.cpp"
#include "enemy.hpp"
#include "enemy.cpp"

enum id {
   PLAYER_1 = 0
};

class GameState
{
   private:
      int row_count;
      int col_count;

      SDL_Renderer *renderer;
      int time;
      pair<int, int> scroll;
      Matrix<int> layer1;
      Matrix<int> layer2;



      // Textures
      SDL_Texture* block_text;
      SDL_Texture* ground_text;
      SDL_Texture* enemy_text;
      SDL_Texture* bush_text;
      vector<SDL_Texture*> potion_text;
   
      // Player / Player Attributes
      vector<SDL_Texture*> water_text;
      vector<SDL_Texture*> waterWalktext;
      int waterWalkFrame;

      shared_ptr<Attack> player_attack;

      // Players
      shared_ptr<Player> player;
      vector<shared_ptr<Attack> > player_attacks;
      vector<shared_ptr<Player> > all_players;
      vector<Enemy> enemies;
      vector<shared_ptr<Attack> > all_player_attacks;


      // Blocks
      Matrix<Block> blocks;
      Matrix<Entity> ground;
      Matrix<Entity> water;
      Matrix<Entity> bushes;
      Matrix<Entity> potions;

      // File Manipulation
      vector<void (GameState::*)(SDL_Texture *)> tSetters;
      vector<void (GameState::*)(SDL_Texture *)>::pointer tSptr, tSend;


      std::unordered_map<std::string, std::string> fileMap;
   public:
      GameState();
      virtual ~GameState();

      vector<shared_ptr<Player> > getAllPlayers() { return all_players; }
      shared_ptr<Player> get_player() { return player; }
      shared_ptr<Attack> get_player_attack() { return player_attack; }

      vector<shared_ptr<Attack> >* get_all_player_attacks() { return &all_player_attacks; }


      inline void set_enemy_texture(SDL_Texture *e) { enemy_text = e; }
      inline SDL_Texture* get_enemy_texture() { return enemy_text; }

      inline void set_water_texture(int i, SDL_Texture *e) { water_text.at(i) = e;}
      inline SDL_Texture* get_water_texture(int i) { return water_text.at(i); }

      inline void set_block_texture(SDL_Texture *b) { block_text = b; }
      inline SDL_Texture* get_block_texture() { return block_text; }

      inline void set_ground_texture(SDL_Texture *g) { ground_text = g; }
      inline SDL_Texture* get_ground_texture() { return ground_text; }   

      inline void set_bush_texture(SDL_Texture *b) { bush_text = b; }
      inline SDL_Texture* get_bush_texture() { return bush_text; } 

      inline void set_potion_texture(int i, SDL_Texture *p) { potion_text.at(i) = p; }
      inline SDL_Texture* get_potion_texture(int i) { return potion_text.at(i); }

      inline void set_waterWalkTexture(int i, SDL_Texture *e) { waterWalktext.at(i) = e; }
      inline SDL_Texture* get_waterWalkTexture(int i) { return waterWalktext.at(i); }   

      inline void set_waterWalkFrame(int i) { waterWalkFrame = i; }
      inline int get_waterWalkFrame() { return waterWalkFrame; }

      void load();
      void render();
      void animate();
      void collisions();

      void setConstantSpriteTextures(SDL_Surface *);

      template <typename T>
      void waterCollisionAnimation(shared_ptr<T> p, int row, int col);

      template <typename T, typename U> 
      int collision_in_map(T &plyr, Matrix<U> &blocks, int i, int j, int P_W, int P_H);

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

