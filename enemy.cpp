#include "enemy.hpp"
Enemy::Enemy(int x, int y)
{
   this->set_x(x);
   this->set_y(y);
   this->set_h(ENEMY_HEIGHT);
   this->set_w(ENEMY_WIDTH);

   stillFrames = vector<SDL_Texture*>(getDirectorySize("sprites\\enemy"));
   healthBartext = vector<SDL_Texture*>(getDirectorySize("sprites\\enemybar"));
   
   set_healthFrame(0);
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


   // Evaluating all states
   std::unordered_map<std::string, double> states;
   states["LEFT"] = get_distances(h.p1_x - 20, h.p2_x, h.p1_y, h.p2_y);
   states["RIGHT"] = get_distances(h.p1_x + 1, h.p2_x, h.p1_y, h.p2_y);
   states["DOWN"] = get_distances(h.p1_x, h.p2_x, h.p1_y + 1, h.p2_y);
   states["UP"] = get_distances(h.p1_x, h.p2_x, h.p1_y - 1, h.p2_y);
   states["DOWN_RIGHT"] = get_distances(h.p1_x + 1, h.p2_x, h.p1_y + 1, h.p2_y);
   states["DOWN_LEFT"] = get_distances(h.p1_x - 1, h.p2_x, h.p1_y - 1, h.p2_y);
   states["UP_RIGHT"] = get_distances(h.p1_x + 1, h.p2_x, h.p1_y - 1, h.p2_y);
   states["UP_LEFT"] = get_distances(h.p1_x - 1, h.p2_x, h.p1_y - 1, h.p2_y);

   std::pair<std::string, double> heuristic = *std::min_element(states.begin(), states.end(), comp());
   // std::cout << heuristic.first << " " << heuristic.second << std::endl;


   if (heuristic.first == "LEFT")
   {
      this->set_movingLeft();
      this->move_left(ENEMY_SPEED);
   }
   else if (heuristic.first == "RIGHT")
   {
      this->set_movingRight();
      this->move_right(ENEMY_SPEED);
   }
   else if (heuristic.first == "DOWN")
   {
      this->set_movingDown();
      this->move_down(ENEMY_SPEED);
   } 
   else if (heuristic.first == "UP")
   {
      this->set_movingUp();
      this->move_up(ENEMY_SPEED);
   }
   else if (heuristic.first == "UP_LEFT")
   {
      this->set_movingLeft();
      this->move_left(ENEMY_SPEED);
   }
   else if (heuristic.first == "UP_RIGHT")
   {
      this->set_movingRight();
      this->move_right(ENEMY_SPEED);
   }
   else if (heuristic.first == "DOWN_RIGHT")
   {
      this->set_movingRight();
      this->move_right(ENEMY_SPEED);
   }
   else if (heuristic.first == "DOWN_LEFT")
   {
      this->set_movingLeft();
      this->move_left(ENEMY_SPEED);
   }
}
