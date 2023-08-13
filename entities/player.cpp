#include "player.hpp"
Player::Player()
{
   this->set_x((1280 / 2)-PLAYER_WIDTH);
   this->set_y((720 / 2)-PLAYER_HEIGHT);
   stillFrames = vector<SDL_Texture*>(ENTITY_FRAMES);
   direction = 8;
}


void Player::animation(int time)
{
   Player *plyr = this;
   set_time(time);
   if (plyr->getDirection() == 0)
   {
      vector<state> direct = {
         MOVED_RIGHT,
         MOVED_UP,
         MOVED_DOWN,
         MOVED_LEFT,
      };

      // If the player isn't moving.
      for (int i = 0; i < direct.size(); ++i)
      {
         if (plyr->get_last_state() == direct.at(i))
         {
            plyr->set_frame(i * 4);
         }

      }
   }
   else
   {
      // Movement Animation
      if ((plyr->is_movingLeft()) && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(12);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(13);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(14);
         }
         else if ((this->get_time() % 20) >= 15)
         {
            plyr->set_frame(15);
         }
      }
      if ((plyr->is_movingRight()) && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(0);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(1);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(2);
         }
         else if ((this->get_time() % 20) >= 15)
         {
            plyr->set_frame(3);
         }
      }
      if (plyr->is_movingDown() && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(4);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(5);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(6);
         }
         else if ((this->get_time() % 20) >= 15)
         {
            plyr->set_frame(7);
         }
      }
      if (plyr->is_movingUp() && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(8);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(9);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(10);
         }
         else if ((this->get_time() % 20) >= 15)
         {
            plyr->set_frame(11);
         }
      }
      if (plyr->is_movingLeft() && (this->get_time() % 20 < 20))
      {
         if ((this->get_time() % 20) < 5)
         {
            plyr->set_frame(12);
         }
         else if ((this->get_time() % 20) >= 5 && (this->get_time() % 20) < 10)
         {
            plyr->set_frame(13);
         }
         else if ((this->get_time() % 20) >= 10 && (this->get_time() % 20) < 15)
         {
            plyr->set_frame(14);
         }
         else if ((this->get_time() % 20) >= 15)
         {
            plyr->set_frame(15);
         }
      }
   }
}

Player::Player(int x, int y)
{
   this->set_x(x);
   this->set_y(y);
   this->set_dy(0);
   this->set_dx(0);
   stillFrames = vector<SDL_Texture*>(getDirectorySize("sprites\\player"));
   direction = 8;
}

void Player::set_movingLeft() 
{
   this->setDirection(0);
   bitset::set_bit(direction, LEFT_BIT); 
}
void Player::set_movingRight() 
{
   this->setDirection(0);
   bitset::set_bit(direction, RIGHT_BIT); 
}
void Player::set_movingDown() 
{
   this->setDirection(0);
   bitset::set_bit(direction, DOWN_BIT); 
}

void Player::set_movingUp() 
{
   this->setDirection(0);    
   bitset::set_bit(direction, UP_BIT); 
}



bool Player::is_movingLeft()
{
   return (bitset::get_bit(getDirection(), LEFT_BIT) && 
           !bitset::get_bit(getDirection(), UP_BIT) &&
           !bitset::get_bit(getDirection(), DOWN_BIT));
}
bool Player::is_movingRight()
{
   return (bitset::get_bit(getDirection(), RIGHT_BIT) && 
           !bitset::get_bit(getDirection(), UP_BIT) &&
           !bitset::get_bit(getDirection(), DOWN_BIT));
}
bool Player::is_movingDown()
{
   return (bitset::get_bit(getDirection(), DOWN_BIT) && 
           !bitset::get_bit(getDirection(), RIGHT_BIT) &&
           !bitset::get_bit(getDirection(), LEFT_BIT));
}
bool Player::is_movingUp()
{
   return (bitset::get_bit(getDirection(), UP_BIT) && 
           !bitset::get_bit(getDirection(), RIGHT_BIT) &&
           !bitset::get_bit(getDirection(), LEFT_BIT));
}



void Player::up_movement(const int &dist)
{
   this->set_movingUp();
   this->set_last_state(this->getDirection());
   this->move_up(dist);
   this->set_dy(-dist);
}

void Player::left_movement(const int &dist)
{
   this->set_movingLeft();
   this->set_last_state(this->getDirection());
   this->move_left(dist);   
   this->set_dx(-dist);
}

void Player::down_movement(const int &dist)
{
   this->set_movingDown();
   this->set_last_state(this->getDirection());
   this->move_down(dist);
   this->set_dy(dist);
}

void Player::right_movement(const int &dist)
{
   this->set_movingRight();
   this->set_last_state(this->getDirection());
   this->move_right(dist);
   this->set_dx(dist);   
}