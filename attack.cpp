#include "attack.hpp"
Attack::Attack()
{
   set_shotStatus(CAN_SHOOT);
   stillFrames = std::vector<SDL_Texture*>(1);
   this->set_w(PLAYER_ATTACK_WIDTH);
   this->set_h(PLAYER_ATTACK_HEIGHT);   
}

void Attack::reset_position(Entity &e)
{
   set_shotStatus(CAN_SHOOT);
   set_x(e.get_x());
   set_y(e.get_y());
}

void Attack::setDirection(Player &e) 
{ 
   dir = e.getDirection(); 
};


void Attack::run_shotMovement(Player &e)
{
   Attack *atk = this;

   if (atk->get_shotStatus() == CAN_SHOOT)
   {
      atk->setDirection(e);
      atk->setPlayerFrame(e.get_frame());
   }
   
   if (atk->get_shotStatus() == CANT_SHOOT)
   {
      if (atk->getDirection() != 0)
      {  
         switch (atk->getDirection())
         {
            case MOVED_RIGHT:
               atk->set_x(atk->get_x() + 3);
               break;
            case MOVED_LEFT:
               atk->set_x(atk->get_x() - 3);
               break;
            case MOVED_UP:
               atk->set_y(atk->get_y() + 3);
               break;
            case MOVED_DOWN:
               atk->set_y(atk->get_y() - 3);
               break;
         }
      }
      else
      {
         if (atk->getPlayerFrame() <= 3)
         {
            atk->set_x(atk->get_x() + 3);
         }
         else if ((atk->getPlayerFrame() > 3) && (atk->getPlayerFrame() <= 7))
         {
            atk->set_y(atk->get_y() + 3);
         }
         else if ((atk->getPlayerFrame() > 7) && (atk->getPlayerFrame() <= 11))
         {
            atk->set_y(atk->get_y() - 3);
         }
         else if ((atk->getPlayerFrame() > 11) && (atk->getPlayerFrame() < 15))
         {
            atk->set_x(atk->get_x() - 3);
         }
      }
   }

   // Tracking the distance between the shot and the player.
   Distance d;
   d.p1_x = e.get_x();
   d.p1_y = e.get_y();
   d.p2_x = atk->get_x();
   d.p2_y = atk->get_y();

   double distance = get_distances(d.p1_x, d.p2_x, d.p1_y, d.p2_y);
   // If the distance is too far, reset the position.
   if (abs(distance) > 200)
   {
      atk->set_shotStatus(CAN_SHOOT);
   }
  
}

Attack::Attack(Entity &p)
{
   set_shotStatus(CAN_SHOOT);
   stillFrames = std::vector<SDL_Texture*>(getDirectorySize("sprites\\attack"));
   set_w(PLAYER_ATTACK_WIDTH);
   set_h(PLAYER_ATTACK_HEIGHT);
   set_x(p.get_x());
   set_y(p.get_y());
}

