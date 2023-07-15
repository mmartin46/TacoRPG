#pragma once
#include "player.hpp"


class Enemy : public Player
{
   private:
      int id;
      int x, y, w, h;
      int frame;
      int time;

      int direction;
      vector<SDL_Texture*> stillFrames;
   public:
      Enemy(int x, int y);
      void movement(Player &p);
};


