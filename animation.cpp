#include "game.hpp"

/*
Update the health based
on if the player has collided with
anything that could increase/decrease its health.
*/
void GameState::updateHealth()
{
   if ((abs(getLife()) < ORIGINAL_HEALTH) && (getLife() >= 95))
   {
      set_healthFrame(1);
   }
   else if ((abs(getLife()) < 90) && (abs(getLife()) >= 85))
   {
      set_healthFrame(2);
   }
   else if ((abs(getLife()) < 85) && (abs(getLife()) >= 80))
   {
      set_healthFrame(3);
   }
   else if ((abs(getLife()) < 80) && (abs(getLife()) >= 75))
   {
      set_healthFrame(4);
   }
   else if ((abs(getLife()) < 75) && (abs(getLife()) >= 70))
   {
      set_healthFrame(5);
   }
   else if ((abs(getLife()) < 70) && (abs(getLife()) >= 65))
   {
      set_healthFrame(6);
   }
   else if ((abs(getLife()) < 65) && (abs(getLife()) >= 60))
   {
      set_healthFrame(7);
   }
   else if ((abs(getLife()) < 60) && (abs(getLife()) >= 40))
   {
      set_healthFrame(8);
   }
   else if ((abs(getLife()) < 40) && (abs(getLife()) >= 30))
   {
      set_healthFrame(9);
   }
   else if ((abs(getLife()) < 30) && (abs(getLife()) >= 20))
   {
      set_healthFrame(10);
   }
   else if ((abs(getLife()) < 20) && (abs(getLife()) >= 5))
   {
      set_healthFrame(11);
   }
   else if (abs(getLife()) < 5)
   {
      set_healthFrame(12);
   }
}

/*
Controls the animation of the player
based on the points.
*/
template <typename T>
void GameState::pointsAnimation(shared_ptr<T> p, int row, int col)
{
     // Potion Detection
     if (collide2d(this->all_players.at(PLAYER_1)->get_x(),
                   this->potions.at(row).at(col).get_x(),
                   this->all_players.at(PLAYER_1)->get_y(),
                   this->potions.at(row).at(col).get_y(),
                   PLAYER_HEIGHT,
                   PLAYER_WIDTH,
                   this->potions.at(row).at(col).get_w(),
                   this->potions.at(row).at(col).get_h()) &&
                   !this->potions.at(row).at(col).get_visited())
     {
        if ((this->get_time() % 15) < 3.75)
        {
           set_pointFrame(0);
        }
        else if ((this->get_time() % 15) >= 3.75 && ((this->get_time() % 15) < 5))
        {
           set_pointFrame(1);
        }
        else if ((this->get_time() % 15) >= 5 && ((this->get_time() % 15) < 7.75))
        {
           set_pointFrame(2);
        }
        else if ((this->get_time() % 15) >= 7.75 && ((this->get_time() % 15) < 10))
        {
           set_pointFrame(3);
        } 
        else if ((this->get_time() % 15) >= 10 && ((this->get_time() % 15) < 13))
        {
           set_pointFrame(4);
        }
        else if ((this->get_time() % 15) >= 10 && ((this->get_time() % 15) < 13))
        {
           set_pointFrame(5);
        }
        else
        {
            set_pointFrame(6);
            this->setScore(this->getScore() + 100);
            this->potions.at(row).at(col).set_visited();
        }
        SDL_Rect pRect = { static_cast<int>(this->get_scrollX() + potions.at(row).at(col).get_x()), static_cast<int>(this->get_scrollY() + potions.at(row).at(col).get_y()), potions.at(row).at(col).get_w(), potions.at(row).at(col).get_h() };
        SDL_RenderCopy(this->get_renderer(), NULL, NULL, &pRect);
        layer2.at(row).at(col) = -1;
     }

}

/*
Controls the animation of the player
based on the water.
*/
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

/*
Controls the overall animation
of all the entities within
the GameState.
*/
void GameState::animate()
{
   initTopBar();
   shared_ptr<Player> plyr = this->all_players.at(PLAYER_1);
   shared_ptr<Attack> atk = this->get_player_attack();
   int sX, sY;

   // Block Animations
   set_waterWalkFrame(4);
   set_pointFrame(6);

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

         pointsAnimation(plyr, row, col);
         waterCollisionAnimation(plyr, row, col);
      }
   }

   typename vector<Enemy>::pointer en_ptr, en_end = enemies.data() + enemies.size();
   for (en_ptr = enemies.data(); en_ptr < en_end; ++en_ptr)
   {
      en_ptr->movement(*plyr);
      en_ptr->animation(this->get_time());
   }

   // Player Animation
   updateHealth();
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