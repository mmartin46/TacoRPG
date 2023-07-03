#include "utilities.cpp"
#include "entity.hpp"

class Block : public Entity
{
   private:
      int id;
      int x, y, w, h;
      std::vector<SDL_Texture*> stillFrames;
}