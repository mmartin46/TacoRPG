#ifndef UTILITIES_H
#define UTILITIES_H
#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <utility>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>
#include <future>
#include <dirent.h>
#include <sys/types.h>
using std::unordered_map;
using namespace std::chrono;

template <typename T>
using Matrix = std::vector<std::vector<T> >;
using std::pair;
using std::shared_ptr;
using std::vector;
using std::string;
using std::unordered_map;

// What was the last movement
// the player made?
enum state {
   MOVED_LEFT = 1,
   MOVED_RIGHT = 2,

   MOVED_UP = 4,
   MOVED_UPRIGHT = 5,
   MOVED_UPLEFT = 9,

   MOVED_DOWN = 8,
   MOVED_DOWNLEFT = 3,
   MOVED_DOWNRIGHT = 6
};

// Utilies bit operations to save of space.
namespace bitset
{
   extern uint8_t get_bit(const int &value, int pos); 
   extern void set_bit(int &value, int pos);
   extern void reset_bit(int &value, int pos);

}

int collide2d(float x1, float x2, float y1, float y2, float ht1, float wt1, float wt2, float ht2);

bool notMovingHorizontally(const Uint8 *state);

bool notMovingVertically(const Uint8 *state);

// Counts the # of files within the directory
int getDirectorySize(const char *directName);

/*
Utilizes the Manhattan distance to find
the distance between two positions.
*/
double get_distances(double x_1, double x_2, double y_1, double y_2);

/*
Finds the minimum within an unordered map.
*/
template <class K, class V>
V mapMin(std::unordered_map<K, V> &mp);

/*
Gets the image dimensions.
\param filePath path to the image.

\return pair.first -> width

\return pair.second -> height


https://stackoverflow.com/questions/5354459/
c-how-to-get-the-image-size-of-a-png-file-in-directory
*/
pair<int, int> getImageDimensions(const char *filePath);

// Finds the distance between
// two points.
// Finds the distance between
// two points.
struct Distance {
   int p1_x;
   int p1_y;
   int p2_x;
   int p2_y;
};

struct comp
{
   template <typename T>
   bool operator() (const T&lhs, const T&rhs)
   {
      return lhs.second < rhs.second;
   }
};

#endif