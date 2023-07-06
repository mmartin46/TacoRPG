#pragma once
#include "entity.hpp"
#include "player.hpp"
#include "constants.hpp"

enum typeShot {
   CAN_SHOOT = 0,
   CANT_SHOOT = 1
};

// Represents an attack an entity makes.
class Attack : public Entity
{
   private:
      int id;
      int frame;
      int x, y, w, h;
      int dy, dx;
      int shotStatus;
      int dir;
      std::vector<SDL_Texture*> stillFrames;
      int last_state;
   public:
      Attack();
      Attack(Entity &);

      void reset_position(Entity &);
      void run_shotMovement(Player &);

      inline void setDirection(int n) { dir = n; };
      inline int getDirection() { return dir; } const
      inline void set_shotStatus(int n) { shotStatus = n; }
      inline int get_shotStatus() { return shotStatus; } 
};

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

