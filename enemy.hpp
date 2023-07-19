#pragma once
#include "player.hpp"


class Enemy : public Player
{
   private:
      int id;
      int x, y, w, h;
      int frame;
      int healthBarFrame;
      int time;

      int direction;
      vector<SDL_Texture*> stillFrames;
      vector<SDL_Texture*> healthBartext;
   public:
      Enemy(int x, int y);
      void movement(Player &p);

      inline void set_healthBarTexture(int i, SDL_Texture* hb) { healthBartext.at(i) = hb; }
      inline SDL_Texture* get_healthBarTexture(int i) { return healthBartext.at(i); }

      inline void set_healthFrame(int i) { healthBarFrame = i; }
      inline int get_healthFrame() { return healthBarFrame; }
};


