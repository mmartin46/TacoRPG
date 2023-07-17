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

      // Layers
      Matrix<int> layer1;
      Matrix<int> layer2;
      Matrix<int> layer3;



      // Textures
      SDL_Texture* block_text;
      SDL_Texture* ground_text;
      SDL_Texture* grass_text;

      SDL_Texture* bush_text;
      vector<SDL_Texture*> potion_text;
      vector<SDL_Texture*> health_text;
      int healthFrame;
   
      vector<SDL_Texture*> bb_textures = vector<SDL_Texture*>(10);
      vector<SDL_Texture*> dirt_textures = vector<SDL_Texture*>(10);

      TTF_Font* topBarFont;
      SDL_Texture* topBarFontTexture;

      // Time
      system_clock::time_point start_time = high_resolution_clock::now();

      // Player / Player Attributes
      vector<SDL_Texture*> water_text;
      vector<SDL_Texture*> waterWalktext;
      int waterWalkFrame;
      vector<SDL_Texture*> points_text;
      int pointFrame;

      shared_ptr<Attack> player_attack;

      // Players
      shared_ptr<Player> player;
      vector<shared_ptr<Attack> > player_attacks;
      vector<shared_ptr<Player> > all_players;
      vector<Enemy> enemies;
      vector<shared_ptr<Attack> > all_player_attacks;
      double life;
      int score;


      // Blocks
      Matrix<Block> blocks;
      Matrix<Entity> grass;
      Matrix<Entity> ground;
      Matrix<Entity> water;
      Matrix<Entity> bushes;
      Matrix<Entity> potions;

      // Health Info.
      shared_ptr<Entity> topBar;
      shared_ptr<Entity> healthBar;
   

      // File Manipulation
      vector<void (GameState::*)(SDL_Texture *)> tSetters;
      vector<void (GameState::*)(SDL_Texture *)>::pointer tSptr, tSend;
      vector<pair<const char*, const char*> > fileMap;
   public:
      GameState();
      virtual ~GameState();

      // Blocks
      Matrix<Block>* get_blocks() { return &blocks; }
      Matrix<Entity>* get_grass() { return &grass; }
      Matrix<Entity>* get_ground() { return &ground; }
      Matrix<Entity>* get_water() { return &water; }
      Matrix<Entity>* get_bushes() { return &bushes; }
      Matrix<Entity>* get_potions() { return &potions; }

      // Enemies
      vector<Enemy>* get_enemies() { return &enemies; }
      bool isEnemyKilled(Enemy *en_ptr);


      // Player Attributes
      vector<shared_ptr<Player> > getAllPlayers() { return all_players; }
      shared_ptr<Player> get_player() { return player; }
      shared_ptr<Attack> get_player_attack() { return player_attack; }

      shared_ptr<Entity> getHealthBar() { return healthBar; }

      vector<shared_ptr<Attack> >* get_all_player_attacks() { return &all_player_attacks; }

      // Textures

      inline void set_points_texture(int i, SDL_Texture *p) { points_text.at(i) = p; }
      inline SDL_Texture* get_points_texture(int i) { return points_text.at(i); }

      inline void set_water_texture(int i, SDL_Texture *e) { water_text.at(i) = e;}
      inline SDL_Texture* get_water_texture(int i) { return water_text.at(i); }

      inline void set_block_texture(SDL_Texture *b) { block_text = b; }
      inline SDL_Texture* get_block_texture() { return block_text; }

      inline void set_ground_texture(SDL_Texture *g) { ground_text = g; }
      inline SDL_Texture* get_ground_texture() { return ground_text; }   

      inline void set_bush_texture(SDL_Texture *b) { bush_text = b; }
      inline SDL_Texture* get_bush_texture() { return bush_text; } 

      inline void set_grass_texture(SDL_Texture *g) { grass_text = g; }
      inline SDL_Texture* get_grass_texture() { return grass_text; } 

      inline void set_boundBush_Texture(int i, SDL_Texture *b) { bb_textures.at(i) = b; }
      inline SDL_Texture* get_boundBush_Texture(int i) { return bb_textures.at(i); }

      inline void set_dirt_texture(int i, SDL_Texture *t) { dirt_textures.at(i) = t;}
      inline SDL_Texture* get_dirt_texture(int i) { return dirt_textures.at(i); }


      inline void set_health_texture(int i, SDL_Texture *h) { health_text.at(i) = h; }
      inline SDL_Texture* get_health_texture(int i) { return health_text.at(i); }


      inline void set_potion_texture(int i, SDL_Texture *p) { potion_text.at(i) = p; }
      inline SDL_Texture* get_potion_texture(int i) { return potion_text.at(i); }

      inline void set_waterWalkTexture(int i, SDL_Texture *e) { waterWalktext.at(i) = e; }
      inline SDL_Texture* get_waterWalkTexture(int i) { return waterWalktext.at(i); }   

      // Frames
      inline void set_waterWalkFrame(int i) { waterWalkFrame = i; }
      inline int get_waterWalkFrame() { return waterWalkFrame; }

      inline void set_pointFrame(int i) { pointFrame = i; }
      inline int get_PointFrame() { return pointFrame; }

      inline void set_healthFrame(int i) { healthFrame = i; }
      inline int get_healthFrame() { return healthFrame; }


      // Font
      inline TTF_Font* getTopBarFont() { return topBarFont; }
      inline void setTopBarFont(TTF_Font *f) { topBarFont = f; }

      inline SDL_Texture* getTopBarTexture() { return topBarFontTexture; }
      inline void setTopBarTexture(SDL_Texture *t) { topBarFontTexture = t; }


      // Health

      inline void setLife(double i) { life = i; }
      inline double getLife() { return life; }
      inline void decLife() { if (getLife() > 0) { setLife(getLife() - 0.15); } }

      inline void setScore(int s) { score = s; }
      inline int getScore() { return score; }

      void initTopBar();
      void loadRectTopBar(SDL_Rect &);

      // Essential Functions
      void load();
      void render();
      void animate();
      void collisions();
      int events(SDL_Window *);

      // Constant Sprites
      void setConstantSpriteTextures(SDL_Surface *);

      // Aniamtions
      template <typename T>
      void waterCollisionAnimation(shared_ptr<T> p, int row, int col);

      template <typename T>
      void pointsAnimation(shared_ptr<T> p, int row, int col);

      template <typename T, typename U> 
      int collision_in_map(T &plyr, Matrix<U> &blocks, int i, int j, int P_W, int P_H);

      void bulletCollisionAnimation(Enemy *en_ptr);
      void updateHealth();

   
      // Loaders, Renderer, etc.
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

