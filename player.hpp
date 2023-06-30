#pragma once
#include "utilities.cpp"
#include "entity.hpp"

class Player : public Entity
{
   private:
      int id;
      int x, y, w, h;
      std::vector<SDL_Texture*> frames;
   public:
      Player();
      Player(int x, int y);
};

Player::Player()
{
   this->set_x(0);
   this->set_y(0);
}

Player::Player(int x, int y)
{
   this->set_x(x);
   this->set_y(y);
}
