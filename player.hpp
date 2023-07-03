#pragma once
#include "constants.hpp"
#include "utilities.cpp"
#include "entity.hpp"

class Player : public Entity
{
   private:
      int id;
      int x, y, w, h;
      vector<SDL_Texture*> stillFrames;
   public:
      Player();
      Player(int x, int y);
};

Player::Player()
{
   this->set_x((WINDOW_WIDTH / 2)-PLAYER_WIDTH);
   this->set_y((WINDOW_HEIGHT / 2)-PLAYER_HEIGHT);
   stillFrames = vector<SDL_Texture*>(1);
}

Player::Player(int x, int y)
{
   this->set_x(x);
   this->set_y(y);
}