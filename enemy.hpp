#pragma once
#include "player.hpp"

class Enemy : public Player
{
   private:
      int id;
      int x, y, w, h;
      int frame;

      int direction;
      vector<SDL_Texture*> stillFrames;
   public:
      Enemy(int x, int y);
}

Enemy::Enemy(int x, int y)
{
   this->set_x(x);
   this->set_y(y);
   this->set_h(ENEMY_HEIGHT);
   this->set_w(ENEMY_WIDTH);

   stillFrames = vector<SDL_Texture*>(getDirectorySize("sprites\\enemy"));
   direction = 8;
};
