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

template <typename T>
using Matrix = std::vector<std::vector<T> >;
using std::pair;
using std::shared_ptr;
using std::vector;

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

