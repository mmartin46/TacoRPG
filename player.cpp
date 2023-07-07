#include "player.hpp"
Player::Player()
{
   this->set_x((SCREEN_WIDTH / 2)-PLAYER_WIDTH);
   this->set_y((SCREEN_HEIGHT / 2)-PLAYER_HEIGHT);
   stillFrames = vector<SDL_Texture*>(16);
   direction = 8;
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
   direction = 0;
   bitset::set_bit(direction, LEFT_BIT); 
}
void Player::set_movingRight() 
{
   direction = 0;
   bitset::set_bit(direction, RIGHT_BIT); 
}
void Player::set_movingDown() 
{
   direction = 0;
   bitset::set_bit(direction, DOWN_BIT); 
}
void Player::set_movingUp() 
{
   direction = 0;    
   bitset::set_bit(direction, UP_BIT); 
}

bool Player::is_movingLeft()
{
   return bitset::get_bit(getDirection(), LEFT_BIT);
}
bool Player::is_movingRight()
{
   return bitset::get_bit(getDirection(), RIGHT_BIT);
}
bool Player::is_movingDown()
{
   return bitset::get_bit(getDirection(), DOWN_BIT);
}
bool Player::is_movingUp()
{
   return bitset::get_bit(getDirection(), UP_BIT);
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