#include "game.hpp"


template <typename T>
void GameState::waterCollisionAnimation(shared_ptr<T> plyr, int row, int col)
{
   if (collide2d(plyr->get_x(),
                 this->water.at(row).at(col).get_x(),
                 plyr->get_y() - 3,
                 this->water.at(row).at(col).get_y(),
                 PLAYER_HEIGHT - 3,
                 this->water.at(row).at(col).get_w(),
                 PLAYER_WIDTH,
                 this->water.at(row).at(col).get_h()))
   {
      std::this_thread::sleep_for(std::chrono::microseconds(600));
      if (plyr->getDirection() != 0)
      {
         if ((this->get_time() % 13) < 3.75)
         {
            set_waterWalkFrame(0);
         }
         else if ((this->get_time() % 13) >= 3.75 && ((this->get_time() % 13) < 5))
         {
            set_waterWalkFrame(1);
         }
         else if ((this->get_time() % 13) >= 5 && ((this->get_time() % 13) < 7.75))
         {
            set_waterWalkFrame(2);
         }
         else if ((this->get_time() % 13) >= 7.75 && ((this->get_time() % 13) < 10))
         {
            set_waterWalkFrame(3);
         } 
         else if ((this->get_time() % 13) >= 10 && ((this->get_time() % 13) < 13))
         {
            set_waterWalkFrame(4);
         }
      }
   }
}


void GameState::animate()
{
   shared_ptr<Player> plyr = this->all_players.at(PLAYER_1);
   shared_ptr<Attack> atk = this->get_player_attack();
   int sX, sY;


   // Block Animations
   set_waterWalkFrame(4);

   for (int row = 0; row < row_count; ++row)
   {
      for (int col = 0; col < col_count; ++col)
      {
         if ((this->get_time() % 15) < 3.75)
         {
            water.at(row).at(col).set_frame(0);
            potions.at(row).at(col).set_frame(0);
         }
         else if ((this->get_time() % 15) >= 3.75 && ((this->get_time() % 15) < 5))
         {
            water.at(row).at(col).set_frame(1);
            potions.at(row).at(col).set_frame(1);
         }
         else if ((this->get_time() % 15) >= 5 && ((this->get_time() % 15) < 7.25))
         {
            water.at(row).at(col).set_frame(2);
            potions.at(row).at(col).set_frame(2);
         }
         else if ((this->get_time() % 15) >= 7.25 && ((this->get_time() % 15) < 12.18))
         {
            water.at(row).at(col).set_frame(3);
            potions.at(row).at(col).set_frame(3);
         } 
         else if ((this->get_time() % 15) >= 12.18 && ((this->get_time() % 15) < 15))
         {
            water.at(row).at(col).set_frame(3);
            potions.at(row).at(col).set_frame(3);
         }

         waterCollisionAnimation(plyr, row, col);

         // else
         // {
         //    set_waterWalkFrame(4);
         // } 
      }
   }

   typename vector<Enemy>::pointer en_ptr, en_end = enemies.data() + enemies.size();
   for (en_ptr = enemies.data(); en_ptr < en_end; ++en_ptr)
   {
      en_ptr->movement(*plyr);
   }

   // Player Animation
   plyr->animation(this->get_time());
   sX = -plyr->get_x() + SCREEN_WIDTH / 2;
   sY = -plyr->get_y() + SCREEN_HEIGHT / 2;
   auto t1 = std::async(std::launch::async, &GameState::run_scroller, this, sX, sY);
   t1.wait();

   atk->run_shotMovement(*plyr);
}

void GameState::run_scroller(int x, int y)
{ 
   std::this_thread::sleep_for(std::chrono::microseconds(1));
   this->set_scrollX(x);
   this->set_scrollY(y);
   if (this->get_scrollX() > 0)
   {
      this->set_scrollX(0);
   }
}