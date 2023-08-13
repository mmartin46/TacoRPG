#ifndef ATTACK_H
#define ATTACK_H
#pragma once
#include "player.hpp"

/*
Controls if a shot can
or cannot be fired.
*/
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
      int pframe;
      std::vector<SDL_Texture*> stillFrames;
      int last_state;
   public:
      Attack();
      Attack(Entity &);

      void reset_position(Entity &);
      void run_shotMovement(Player &);

      void setDirection(Player &e);
      inline int getDirection() { return dir; } const

      inline void setPlayerFrame(int n) { pframe = n; }
      inline int getPlayerFrame() { return pframe; } const

      inline void set_shotStatus(int n) { shotStatus = n; }
      inline int get_shotStatus() { return shotStatus; } 
};
#endif