#pragma once
#include "entity.hpp"
#include "player.hpp"
#include "constants.hpp"

// Represents an attack an entity makes.
class Attack : public Entity
{
   private:
      int id;
      int frame;
      int x, y, w, h;
      int dy, dx;
      int shotStatus;
      std::vector<SDL_Texture*> stillFrames;
      int last_state;
   public:
      Attack();
      Attack(Entity &);

      void reset_position(Entity &);
      inline void set_shotStatus(int n) { shotStatus = n; }
      inline int get_shotStatus() { return shotStatus; }
};

Attack::Attack()
{
   set_shotStatus(0);
   stillFrames = std::vector<SDL_Texture*>(1);
   this->set_w(PLAYER_ATTACK_WIDTH);
   this->set_h(PLAYER_ATTACK_HEIGHT);   
}

void Attack::reset_position(Entity &e)
{
   set_x(e.get_x());
   set_y(e.get_y());
}

Attack::Attack(Entity &p)
{
   shotStatus = 0;
   stillFrames = std::vector<SDL_Texture*>(1);
   set_w(PLAYER_ATTACK_WIDTH);
   set_h(PLAYER_ATTACK_HEIGHT);
   set_x(p.get_x());
   set_y(p.get_y());
}

