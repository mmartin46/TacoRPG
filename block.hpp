#include "utilities.cpp"
#include "entity.hpp"

class Block : public Entity
{
   private:
      int id;
      int x, y, w, h;
      vector<SDL_Texture*> stillFrames;
   public:
      Block();
};

Block::Block()
{
   stillFrames = vector<SDL_Texture*>(1);
}