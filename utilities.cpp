#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <utility>
#include <algorithm>
#include <future>
#include <dirent.h>
#include <sys/types.h>

template <typename T>
using Matrix = std::vector<std::vector<T> >;
using std::pair;
using std::shared_ptr;
using std::vector;

// What was the last movement
// the player made?
enum state {
   MOVED_LEFT = 1,
   MOVED_RIGHT = 2,
   MOVED_UP = 4,
   MOVED_DOWN = 8
};

// Utilies bit operations to save of space.
namespace bitset
{
   uint8_t get_bit(const int &value, int pos) 
   {
      return (value >> pos) & 1U;
   }

   void set_bit(int &value, int pos)
   {
      value |= (1 << pos);
   }
   void reset_bit(int &value, int pos)
   {
      value &= ~(1 << pos);
   }
}

int collide2d(float x1, float x2, float y1, float y2, float ht1, float wt1, float wt2, float ht2)
{
   return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}



// Counts the # of files within the directory
int getDirectorySize(const char *directName)
{
   DIR *dirPtr;
   int fileCount = 0;
   struct dirent *ep;
   dirPtr = opendir(directName);

   if (dirPtr == NULL)
   {
      perror("getDirectorySize() : No such directory found.\n");
   }
   else
   {
      while (ep = readdir(dirPtr))
      {
         ++fileCount;
      }
      static_cast<void>(closedir(dirPtr));
   }
   return fileCount;
}