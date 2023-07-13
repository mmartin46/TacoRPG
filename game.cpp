#include "game.hpp"
#include "collisions.cpp"
#include "loader.cpp"
#include "animation.cpp"


GameState::GameState()
{
   // Intializing Vectors
   set_time(0);
   player = std::make_shared<Player>();
   player_attack = std::make_shared<Attack>(*player);
   water_text = vector<SDL_Texture*>(getDirectorySize("sprites\\water"));
   potion_text = vector<SDL_Texture*>(getDirectorySize("sprites\\potion"));
   waterWalktext = vector<SDL_Texture*>(getDirectorySize("sprites\\waterwalk"));
   points_text = vector<SDL_Texture*>(getDirectorySize("sprites\\points"));
   health_text = vector<SDL_Texture*>(getDirectorySize("sprites\\life"));

   // Intializing Player and Player Frames
   set_waterWalkFrame(4);
   set_pointFrame(6);
   all_players.push_back(player);

   // Setting Enemy Positions
   enemies.reserve(10);
   for (int i = 0; i < 1; ++i)
   {
      try
      {
         enemies.push_back(*(std::make_shared<Enemy>(i * i + 500, i * i + 400)));
      }
      catch (const std::exception &e)
      {
         std::cout << e.what() << std::endl;
      }
   }

   // World Dimensions and Coordinates
   Map dim("files\\try_this.txt");
   row_count = dim.getRowCount();
   col_count = dim.getColumnCount();

   layer1 = Matrix<int> (row_count, vector<int>(col_count));
   layer2 = Matrix<int> (row_count, vector<int>(col_count));
   layer3 = Matrix<int> (row_count, vector<int>(col_count));
   blocks = Matrix<Block> (row_count, vector<Block>(col_count));
   ground = Matrix<Entity> (row_count, vector<Entity>(col_count));
   water = Matrix<Entity> (row_count, vector<Entity>(col_count));
   bushes = Matrix<Entity> (row_count, vector<Entity>(col_count));
   potions = Matrix<Entity> (row_count, vector<Entity>(col_count));
   grass = Matrix<Entity> (row_count, vector<Entity>(col_count));

   healthBar = std::make_shared<Entity>();
   getHealthBar()->set_x(0);
   getHealthBar()->set_y(20);
   getHealthBar()->set_w(getImageDimensions("sprites\\life\\life0.png").first);
   getHealthBar()->set_h(getImageDimensions("sprites\\life\\life0.png").second);
   healthFrame = 0;
   setLife(1000000);

   player->set_id(PLAYER_1);
   set_scrollX(0);
   set_scrollY(0);
   init_tiles();
}




void GameState::render()
{
   SDL_SetRenderDrawColor(this->get_renderer(), 120, 120, 120, 255);

   SDL_RenderClear(this->get_renderer());

   int x, y;



   // Sets rectangles for all the blocks.
   for (x = 0; x < row_count; ++x)
   {
      for (y = 0; y < col_count; ++y)
      {
         // Layer 1
         switch (layer1.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION : {
               SDL_Rect blockRect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_block_texture(), NULL, &blockRect);
               break;
            }
            case world_map::GROUND_COLLISION : {
               SDL_Rect groundRect = { static_cast<int>(this->get_scrollX() + ground.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + ground.at(x).at(y).get_y()), ground.at(x).at(y).get_w(), ground.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_ground_texture(), NULL, &groundRect);
               break;
            }
            case world_map::GRASS_COLLISION : {
               SDL_Rect grassRect = { static_cast<int>(this->get_scrollX() + grass.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + grass.at(x).at(y).get_y()), grass.at(x).at(y).get_w(), grass.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_grass_texture(), NULL, &grassRect);
               break;            
            }
         }
         // Layer 2
         switch (layer2.at(x).at(y))
         {
            case world_map::BOUNDARY_BUSH_COLLISION : {
               SDL_Rect bbRect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(), NULL, &bbRect);
               break;
            }
            case world_map::BOUNDARY_BUSH_LEFT : {
               SDL_Rect bbRect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBushLeft_Texture(), NULL, &bbRect);
               break;
            }
            case world_map::BOUNDARY_BUSH_RIGHT : {
               SDL_Rect bbRect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBushRight_Texture(), NULL, &bbRect);
               break;
            }
            case world_map::BOUNDARY_BUSH_UP : {
               SDL_Rect bbRect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBushUp_Texture(), NULL, &bbRect);
               break;
            }
            case world_map::BOUNDARY_BUSH_DOWN : {
               SDL_Rect bbRect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBushDown_Texture(), NULL, &bbRect);
               break;
            }
            case world_map::POTION_COLLISION : {
               SDL_Rect potionRect = { static_cast<int>(this->get_scrollX() + potions.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + potions.at(x).at(y).get_y()), potions.at(x).at(y).get_w(), potions.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_potion_texture(this->potions.at(x).at(y).get_frame()), NULL, &potionRect);
               break;
            }
            case world_map::WATER_COLLISION : {
               SDL_Rect waterRect = { static_cast<int>(this->get_scrollX() + water.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + water.at(x).at(y).get_y()), water.at(x).at(y).get_w(), water.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_water_texture(this->water.at(x).at(y).get_frame()), NULL, &waterRect);
               break;
            }
            case world_map::BUSH_COLLISION : {
               SDL_Rect bushRect = { static_cast<int>(this->get_scrollX() + bushes.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + bushes.at(x).at(y).get_y()), bushes.at(x).at(y).get_w(), bushes.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_bush_texture(), NULL, &bushRect);
               break;
            }
         }
      }
   }
   

   /*  PLAYER ATTRIBUTES */

   // Health Bar
   SDL_Rect hrect = { this->getHealthBar()->get_x(), this->getHealthBar()->get_y(), this->getHealthBar()->get_h(), this->getHealthBar()->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_health_texture(healthFrame), NULL, &hrect);
  

   // Player Attack Rect
   SDL_Rect parect = { this->get_scrollX() + this->get_player_attack()->get_x(), this->get_scrollY() + this->get_player_attack()->get_y(), this->get_player_attack()->get_h(), this->get_player_attack()->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_player_attack()->get_stillFrame(0), NULL, &parect);

   // Walk On Water Rect
   SDL_Rect wRect = { this->get_scrollX() + this->all_players.at(PLAYER_1)->get_x(), this->get_scrollY() + this->all_players.at(PLAYER_1)->get_y(), this->all_players.at(PLAYER_1)->get_h(), this->all_players.at(PLAYER_1)->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_waterWalkTexture(waterWalkFrame), NULL, &wRect);

   // Player Rect
   SDL_Rect prect = { this->get_scrollX() + this->all_players.at(PLAYER_1)->get_x(), this->get_scrollY() + this->all_players.at(PLAYER_1)->get_y(), this->all_players.at(PLAYER_1)->get_h(), this->all_players.at(PLAYER_1)->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->all_players.at(PLAYER_1)->get_stillFrame(this->all_players.at(PLAYER_1)->get_frame()), NULL, &prect);

   // Points Rect
   SDL_Rect ptRect = { this->get_scrollX() + this->all_players.at(PLAYER_1)->get_x(), this->get_scrollY() + this->all_players.at(PLAYER_1)->get_y(), this->all_players.at(PLAYER_1)->get_h(), this->all_players.at(PLAYER_1)->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_points_texture(pointFrame), NULL, &ptRect);


   /***********************/

   // Enemies
   typename vector<Enemy>::pointer en_ptr, en_end = enemies.data() + enemies.size();
   SDL_Rect enRect;
   for (en_ptr = enemies.data(); en_ptr < en_end; ++en_ptr)
   {
      enRect = { this->get_scrollX() + en_ptr->get_x(), 
                 this->get_scrollY() + en_ptr->get_y(),
                 en_ptr->get_h(),
                 en_ptr->get_w() };
      SDL_RenderCopy(this->get_renderer(), get_enemy_texture(), NULL, &enRect);
   }

   SDL_RenderPresent(this->get_renderer());
}


int GameState::events(SDL_Window *window)
{

   SDL_Event event;
   int done = 0;
   while (SDL_PollEvent(&event))
   {
      switch (event.type)
      {
         case SDL_WINDOWEVENT_CLOSE:
         {
            if (window)
            {
               SDL_DestroyWindow(window);
               window = NULL;
               bitset::set_bit(done, 0);
            }
         }
         break;
         case SDL_QUIT:
               bitset::set_bit(done, 0);
         break;
      }
   }

   if (!this->get_player_attack()->get_shotStatus())
   {
      this->get_player_attack()->set_x(this->all_players.at(PLAYER_1)->get_x());
      this->get_player_attack()->set_y(this->all_players.at(PLAYER_1)->get_y());
   }


   // Player Movement
   const Uint8 *state = SDL_GetKeyboardState(NULL);

   if (state[SDL_SCANCODE_SPACE])
   {
      this->get_player_attack()->set_shotStatus(CANT_SHOOT);
      this->get_player_attack()->run_shotMovement(*this->all_players.at(PLAYER_1));
   }

   if (state[SDL_SCANCODE_UP] /* && notMovingHorizontally(state) */)
   {
      this->all_players.at(PLAYER_1)->up_movement(2);
   }
   else if (state[SDL_SCANCODE_LEFT] /* && notMovingVertically(state) */)
   {
      this->all_players.at(PLAYER_1)->left_movement(2);
   }
   // else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP])
   // {
   //    this->all_players.at(PLAYER_1)->upLeft_movement(2);
   // }
   // else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN])
   // {
   //    this->all_players.at(PLAYER_1)->downLeft_movement(2);
   // }
   // else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP])
   // {
   //    this->all_players.at(PLAYER_1)->upRight_movement(2);
   // }
   // else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN])
   // {
   //    this->all_players.at(PLAYER_1)->downRight_movement(2);
   // }
   else if (state[SDL_SCANCODE_RIGHT]/*&& notMovingVertically(state)*/ )
   {
      this->all_players.at(PLAYER_1)->right_movement(2);
   }
   else if (state[SDL_SCANCODE_DOWN] /*&& notMovingHorizontally(state)*/ )
   {
      this->all_players.at(PLAYER_1)->down_movement(2);
   }
   else
   {
      this->all_players.at(PLAYER_1)->setDirection(0);
   }
   return done;
}

GameState::~GameState()
{
   int index;
   SDL_DestroyTexture(this->get_block_texture());

   for (index = 0; index < ENTITY_FRAMES; ++index)
   {
      SDL_DestroyTexture(this->all_players.at(PLAYER_1)->get_stillFrame(index));
   }



   enemies.clear();
}