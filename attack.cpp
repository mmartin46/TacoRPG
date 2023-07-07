#include "attack.hpp"
Attack::Attack()
{
   set_shotStatus(CAN_SHOOT);
   stillFrames = std::vector<SDL_Texture*>(1);
   this->set_w(PLAYER_ATTACK_WIDTH);
   this->set_h(PLAYER_ATTACK_HEIGHT);   
}

void Attack::reset_position(Entity &e)
{
   set_shotStatus(CAN_SHOOT);
   set_x(e.get_x());
   set_y(e.get_y());
}

void Attack::setDirection(Player &e) 
{ 
   dir = e.getDirection(); 
};


void Attack::run_shotMovement(Player &e)
{
}

Attack::Attack(Entity &p)
{
   set_shotStatus(CAN_SHOOT);
   stillFrames = std::vector<SDL_Texture*>(1);
   set_w(PLAYER_ATTACK_WIDTH);
   set_h(PLAYER_ATTACK_HEIGHT);
   set_x(p.get_x());
   set_y(p.get_y());
}

