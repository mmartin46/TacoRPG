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

// Returns a pair that caluclates the size of a map.
// \param fileName The name of the file.
// \param delim The delimiter.
pair<int, int> calculateMapSize(const char *fileName, const char delim)
{
   std::ifstream f(fileName);
   pair<int, int> mapSize;

   int c = 0;
   int r = 0;
   std::string line;
   // Counting Rows;
   while (f.peek() != EOF)
   {
      std::getline(f, line);
      ++r;
   }
   mapSize.second = r;

   f.clear(); 
   f.seekg(0, std::ios::beg); // seek to beginning of the file.

   // Counting Columns
   int row_counter = 0;
   int spec_row = 1;
   size_t count;
   while (std::getline(f, line))
   {
      row_counter++;
      if (row_counter == spec_row) {
         count = std::count_if( line.begin(), line.end(), [](char c) { return c == ','; });
         break;
      }
   }
   mapSize.first = ++count;

   return mapSize;
}