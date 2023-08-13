#ifndef MAP_H
#define MAP_H
#pragma once
#include <SDL2\SDL.h>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
#include <iostream>

using std::pair;

/*
Handles all the maps and which
textures and blocks should be set
in specified positions.
*/
namespace world_map {
   enum collisions {
      NO_COLLISION = 0,
      BLOCK_COLLISION = 1,
      GROUND_COLLISION = 2,
      WATER_COLLISION = 3,
      BUSH_COLLISION = 4,
      JUICE_COLLISION = 5,
      GRASS_COLLISION = 6,
      BOUNDARY_BUSH_COLLISION = 7,
      BOUNDARY_BUSH_LEFT = 8,
      BOUNDARY_BUSH_RIGHT = 9,
      BOUNDARY_BUSH_UP = 10,
      BOUNDARY_BUSH_DOWN = 11,
      BOUNDARY_BUSH_DOWNRIGHT = 12,
      BOUNDARY_BUSH_DOWNLEFT = 13,
      BOUNDARY_BUSH_UPRIGHT = 14,
      BOUNDARY_BUSH_UPLEFT = 15,
      DIRT_COLLISION = 16,
      DIRT_TRANS_LEFT = 17,
      DIRT_TRANS_RIGHT = 18,
      DIRT_TRANS_UP = 19,
      DIRT_TRANS_DOWN = 20,

      DIRT_TRANS_UPLEFT = 21,
      DIRT_TRANS_DOWNLEFT = 22,
      DIRT_TRANS_UPRIGHT = 23,
      DIRT_TRANS_DOWNRIGHT = 24

   };

    extern int layer3[100][100];

    extern int layer2[100][100];

    extern int layer1[100][100]; 

}


/*
A class that calculates the count
of rows and columns of a CSV file.
*/
class Map
{
   private:
      const char *file_name;
      pair<int, int> dimensions;
   public:
      Map(const char *f);
      pair<int, int> calculateMapSize(const char *fileName, const char delim);
      inline int getColumnCount() { return dimensions.first; }
      inline int getRowCount() { return dimensions.second; }
      pair<int, int> getDimensions() { return dimensions; }
};




#endif