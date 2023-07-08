#pragma once
#include "player.hpp"

// Finds the distance between
// two points.
typedef struct {
   int p1_x;
   int p1_y;
   int p2_x;
   int p2_y;
} Distance;

struct comp
{
   template <typename T>
   bool operator() (const T&lhs, const T&rhs)
   {
      return lhs.second < rhs.second;
   }
};

class Enemy : public Player
{
   private:
      int id;
      int x, y, w, h;
      int frame;

      int direction;
      vector<SDL_Texture*> stillFrames;
   public:
      Enemy(int x, int y);
      void movement(Player &p);
};

Enemy::Enemy(int x, int y)
{
   this->set_x(x);
   this->set_y(y);
   this->set_h(ENEMY_HEIGHT);
   this->set_w(ENEMY_WIDTH);

   stillFrames = vector<SDL_Texture*>(getDirectorySize("sprites\\enemy"));
   direction = 8;
};

void Enemy::movement(Player &p)
{
   // Heuristic
   Distance h;
   h.p1_x = this->get_x();
   h.p1_y = this->get_y();
   h.p2_x = p.get_x();
   h.p2_y = p.get_y();

   double heuristic =  get_distances(h.p1_x, h.p2_x, h.p1_y, h.p2_y);

   std::unordered_map<std::string, double> states;
   states["LEFT"] = get_distances(h.p1_x - 10, h.p2_x, h.p1_y, h.p2_y);
   states["RIGHT"] = get_distances(h.p1_x + 10, h.p2_x, h.p1_y, h.p2_y);
   states["DOWN"] = get_distances(h.p1_x, h.p2_x, h.p1_y + 10, h.p2_y);
   states["UP"] = get_distances(h.p1_x, h.p2_x, h.p1_y - 10, h.p2_y);
   states["UP_RIGHT"] = get_distances(h.p1_x + 10, h.p2_x, h.p1_y + 10, h.p2_y);
   states["UP_LEFT"] = get_distances(h.p1_x - 10, h.p2_x, h.p1_y + 10, h.p2_y);
   states["DOWN_RIGHT"] = get_distances(h.p1_x + 10, h.p2_x, h.p1_y - 10, h.p2_y);
   states["DOWN_LEFT"] = get_distances(h.p1_x - 10, h.p2_x, h.p1_y - 10, h.p2_y);


   std::min_element(states.begin(), states.end(), comp());
   
}
