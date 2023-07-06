#pragma once
#include "entity.hpp"

// Represents an attack an entity makes.
class Attack : public Entity
{
   private:
      int id;
      int frame;
      int x, y, w, h;
      int dy, dx;
      std::vector<SDL_Texture*> stillFrames;
      int last_state;
   public:
};