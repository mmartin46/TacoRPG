#include "game.hpp"

template <typename T, typename U>
int GameState::collision_in_map(T &plyr, Matrix<U> &blocks, int i, int j, int P_W, int P_H)
{
   int touched = 0;
   float pw = P_W, ph = P_H;
   float px = plyr.get_x(), py = plyr.get_y();
   float bx = blocks.at(i).at(j).get_x(), by = blocks.at(i).at(j).get_y(), bw = blocks.at(i).at(j).get_w(), bh = blocks.at(i).at(j).get_h();

   if (px+pw/2 > bx && px+pw/2 < bx+bw)
   {
      // Head Bump
      if (py < by+bh && py>by)
      {
         // Correct Y
         plyr.set_y(by+bh);
         py = by+bh;
         touched = 1;
      }
   }
   if (px+pw > bx && px<bx+bw)
   {
      if (py+ph > by && py < by)
      {
         plyr.set_y(by-ph);
         py = by-ph;
         touched = 2;
      }
   }
   if (py+ph > by && py < by+bh)
   {
      // Rubbing against right edge
      if (px < bx+bw && px+pw > bx+bw)
      {
         // Correct X
         plyr.set_x(bx+bw);
         px = bx+bw;
         touched = 3;
      }
      else if (px+pw > bx && px < bx)
      {
         plyr.set_x(bx-pw);
         px = bx-pw;
         touched = 4;
      }
   }
   return touched;
}

void GameState::collisions()
{

   typename vector<Enemy>::pointer en_ptr, en_end = enemies.data() + enemies.size();

   for (int x = 0; x < row_count; ++x)
   {
      for (int y = 0; y < col_count; ++y)
      {
         if (collide2d(this->get_player_attack()->get_x(),
                       this->blocks.at(x).at(y).get_x(),
                       this->get_player_attack()->get_y(),
                       this->blocks.at(x).at(y).get_y(),
                       PLAYER_ATTACK_HEIGHT,
                       this->blocks.at(x).at(y).get_w(),
                       PLAYER_ATTACK_WIDTH,
                       this->blocks.at(x).at(y).get_h()))
         {
            this->get_player_attack()->set_shotStatus(CAN_SHOOT);
            this->get_player_attack()->reset_position(*this->all_players.at(PLAYER_1));
         }
         if (collide2d(this->get_player_attack()->get_x(),
                       this->bushes.at(x).at(y).get_x(),
                       this->get_player_attack()->get_y(),
                       this->bushes.at(x).at(y).get_y(),
                       PLAYER_ATTACK_HEIGHT,
                       this->bushes.at(x).at(y).get_w(),
                       PLAYER_ATTACK_WIDTH,
                       this->bushes.at(x).at(y).get_h()))
         {
            this->get_player_attack()->set_shotStatus(CAN_SHOOT);
            this->get_player_attack()->reset_position(*this->all_players.at(PLAYER_1));
         }

         if (collide2d(this->all_players.at(PLAYER_1)->get_x(),
                       this->potions.at(x).at(y).get_x(),
                       this->all_players.at(PLAYER_1)->get_y(),
                       this->potions.at(x).at(y).get_y(),
                       PLAYER_HEIGHT,
                       PLAYER_WIDTH,
                       this->potions.at(x).at(y).get_w(),
                       this->potions.at(x).at(y).get_h()))
        {
            SDL_Rect pRect = { static_cast<int>(this->get_scrollX() + potions.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + potions.at(x).at(y).get_y()), potions.at(x).at(y).get_w(), potions.at(x).at(y).get_h() };
            SDL_RenderCopy(this->get_renderer(), NULL, NULL, &pRect);
            layer2.at(x).at(y) = -1;
        }
        

         // Enemy Collision
         for (en_ptr = enemies.data(); en_ptr < en_end; ++en_ptr)
         {
            collision_in_map(*en_ptr, this->blocks, x, y, ENEMY_WIDTH, ENEMY_HEIGHT);
            collision_in_map(*en_ptr, this->bushes, x, y, ENEMY_WIDTH, ENEMY_WIDTH);
         }


         collision_in_map(*this->all_players.at(PLAYER_1), this->blocks, x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
         collision_in_map(*this->all_players.at(PLAYER_1), this->bushes, x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
      }
   }
}