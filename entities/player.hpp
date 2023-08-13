#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include "entity.hpp"



enum whichBit {
   LEFT_BIT = 0,
   RIGHT_BIT = 1,
   DOWN_BIT = 2,
   UP_BIT = 3
};


class Player : public Entity
{
   private:
      int id;
      int x, y, w, h;
      int frame;
      int time;
      /* Left - 1000
      *  Right - 0100
      *  Down - 0010
      *  Up - 0001   
      *  UpLeft - 1001
      *  UpRight - 0101
      *  DownLeft - 0011
      *  DownRight - 0110
      */
      int direction;
      vector<SDL_Texture*> stillFrames;
      inline void set_time(int t){ time = t; }
      inline int get_time() { return time; }
   public:
      Player();
      Player(int x, int y);
      bool is_movingLeft();
      bool is_movingRight();
      bool is_movingDown();
      bool is_movingUp();

      void set_movingLeft();
      void set_movingRight();
      void set_movingDown();
      void set_movingUp(); 


      inline int getDirection() { return direction; }
      inline void setDirection(int d) { direction = d; }

      void up_movement(const int &);
      void down_movement(const int &);
      void left_movement(const int &);
      void right_movement(const int &);

      void animation(int);
};
#endif