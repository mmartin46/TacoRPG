#include "entity.hpp"

Entity::Entity()
{
   stillFrames = std::vector<SDL_Texture*>(ENTITY_FRAMES);
   reset_visited();
}

Entity::~Entity()
{
   for (auto &f : stillFrames)
   {
      SDL_DestroyTexture(f);
   }
}


/*
Sets the frame for the enemy.
\param n index
\param t texture
*/
void Entity::set_stillFrame(int n, SDL_Texture* t)
{
   if (n >= this->stillFrames.size() || n < 0)
   {
      std::cout << "stillFrames: argument " << n << " is out of bounds\n";
      exit(1);
   }
   this->stillFrames.at(n) = t;
}