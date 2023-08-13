#ifndef BLOCK_H
#define BLOCK_H
#pragma once

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

#endif