#include "game.hpp"


void GameState::bulletCollisionAnimation(Enemy *en_ptr)
{
   if (collide2d(
       this->get_player_attack()->get_x(),
       en_ptr->get_x(),
       this->get_player_attack()->get_y(),
       en_ptr->get_y(),
       PLAYER_ATTACK_HEIGHT,
       ENEMY_WIDTH,
       PLAYER_ATTACK_WIDTH,
       ENEMY_HEIGHT
    ))
    {
       /*
       If the enemy's health bar frame is less than 4 and the player
       isn't able to shoot, the enemy's health bar frame will decrease.
       */
       if (en_ptr->get_healthFrame() < 4 && 
       (!this->get_player_attack()->get_shotStatus() == CAN_SHOOT))
       {
          en_ptr->set_healthFrame(en_ptr->get_healthFrame() + 1);
          this->get_player_attack()->set_shotStatus(CAN_SHOOT);
          this->get_player_attack()->reset_position(*this->all_players.at(PLAYER_1));
       }

       /* Relocate the enemy to a random location due
          to the slowdown depending on the number of
          enemies, reset the health bar, and give the player
          100 points */
       if (en_ptr->get_healthFrame() == 4)
       {
          this->setScore(this->getScore() + 100);
          en_ptr->set_x(300 + (rand() % 1000));
          en_ptr->set_y(300 + (rand() % 1000));
          en_ptr->set_healthFrame(0);
       }
    }
}


/*
Detects a collision between an entity
and any of the blocks within the map.
\param i row
\param j col
\param P_W player width
\param P_H player height
*/
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

/*
Controls the collision detection
with all the entities within the 
gamestate.
*/
void GameState::collisions()
{

   typename vector<Enemy>::pointer en_ptr, en_end = this->get_enemies()->data() + this->get_enemies()->size();

   for (int x = 0; x < row_count; ++x)
   {
      for (int y = 0; y < col_count; ++y)
      {

         // Shot detection
         if (collide2d(this->get_player_attack()->get_x(),
                       this->get_blocks()->at(x).at(y).get_x(),
                       this->get_player_attack()->get_y(),
                       this->get_blocks()->at(x).at(y).get_y(),
                       PLAYER_ATTACK_HEIGHT,
                       this->get_blocks()->at(x).at(y).get_w(),
                       PLAYER_ATTACK_WIDTH,
                       this->get_blocks()->at(x).at(y).get_h()))
         {
            this->get_player_attack()->set_shotStatus(CAN_SHOOT);
            this->get_player_attack()->reset_position(*this->all_players.at(PLAYER_1));
         }
         if (collide2d(this->get_player_attack()->get_x(),
                       this->get_bushes()->at(x).at(y).get_x(),
                       this->get_player_attack()->get_y(),
                       this->get_bushes()->at(x).at(y).get_y(),
                       PLAYER_ATTACK_HEIGHT,
                       this->get_bushes()->at(x).at(y).get_w(),
                       PLAYER_ATTACK_WIDTH,
                       this->get_bushes()->at(x).at(y).get_h()))
         {
            this->get_player_attack()->set_shotStatus(CAN_SHOOT);
            this->get_player_attack()->reset_position(*this->all_players.at(PLAYER_1));
         }


         //Enemy Collision
         for (en_ptr = this->get_enemies()->data(); en_ptr < en_end; ++en_ptr)
         {
            collision_in_map(*en_ptr, *this->get_blocks(), x, y, ENEMY_WIDTH, ENEMY_HEIGHT);
            collision_in_map(*en_ptr, *this->get_bushes(), x, y, ENEMY_WIDTH, ENEMY_WIDTH);

            bulletCollisionAnimation(en_ptr);
         }


         collision_in_map(*this->all_players.at(PLAYER_1), *this->get_blocks(), x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
         collision_in_map(*this->all_players.at(PLAYER_1), *this->get_bushes(), x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
      }
   }
   // Enemy Collision
   /*
      If the enemy and the player collide decrease
      the life of the player.
   */
   for (en_ptr = this->get_enemies()->data(); en_ptr < en_end; ++en_ptr)
   {
      if (collide2d(this->all_players.at(PLAYER_1)->get_x(),
                    en_ptr->get_x(),
                    this->all_players.at(PLAYER_1)->get_y(),
                    en_ptr->get_y(),
                    PLAYER_HEIGHT,
                    en_ptr->get_w(),
                    PLAYER_WIDTH,
                    en_ptr->get_h()))
      {
         this->decLife();
      }
   }


}