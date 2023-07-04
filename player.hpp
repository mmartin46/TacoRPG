#pragma once
#include "constants.hpp"
#include "utilities.cpp"
#include "entity.hpp"

class Player : public Entity
{
   private:
      int id;
      int x, y, w, h;

      /* Left - 1000
      *  Right - 0100
      *  Down - 0010
      *  Up - 0001   
      */
      int direction;
      vector<SDL_Texture*> stillFrames;
   public:
      Player();
      Player(int x, int y);
      bool is_movingLeft();
      bool is_movingRight();
      bool is_movingDown();
      bool is_movingUp();

      void set_movingLeft();
      void set_movingRight();
      void set_movingDown();
      void set_movingUp();      
      inline int getDirection() { return direction; }
      inline void setDirection(int d) { direction = d; }
};



Player::Player()
{
   this->set_x((SCREEN_WIDTH / 2)-PLAYER_WIDTH);
   this->set_y((SCREEN_HEIGHT / 2)-PLAYER_HEIGHT);
   stillFrames = vector<SDL_Texture*>(1);
   direction = 8;
}

Player::Player(int x, int y)
{
   this->set_x(x);
   this->set_y(y);
}

void Player::set_movingLeft() 
{
   direction = 0;
   bitset::set_bit(direction, 3); 
}
void Player::set_movingRight() 
{
   direction = 0;
   bitset::set_bit(direction, 2); 
}
void Player::set_movingDown() 
{
   direction = 0;
   bitset::set_bit(direction, 1); 
}
void Player::set_movingUp() 
{
   direction = 0;    
   bitset::set_bit(direction, 0); 
}

bool Player::is_movingLeft()
{
   return bitset::get_bit(getDirection(), 3);
}
bool Player::is_movingRight()
{
   return bitset::get_bit(getDirection(), 2);
}
bool Player::is_movingDown()
{
   return bitset::get_bit(getDirection(), 1);
}
bool Player::is_movingUp()
{
   return bitset::get_bit(getDirection(), 0);
}