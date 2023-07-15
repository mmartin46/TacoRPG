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
   for (int i = 0; i < 3; ++i)
   {
      try
      {
         enemies.push_back(*(std::make_shared<Enemy>(i * rand() % 2000, i * rand() % 2000)));
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
   getHealthBar()->set_y(10);
   getHealthBar()->set_w(getImageDimensions("sprites\\life\\life0.png").first);
   getHealthBar()->set_h(getImageDimensions("sprites\\life\\life0.png").second);
   healthFrame = 0;
   setLife(ORIGINAL_HEALTH);
   setScore(0);
   topBar = std::make_shared<Entity>();

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

   SDL_Rect rect;

   // Sets rectangles for all the blocks.
   for (x = 0; x < row_count; ++x)
   {
      for (y = 0; y < col_count; ++y)
      {
         // Layer 1
         switch (layer1.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION : {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_block_texture(), NULL, &rect);
               break;
            }
            case world_map::GROUND_COLLISION : {
               rect = { static_cast<int>(this->get_scrollX() + ground.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + ground.at(x).at(y).get_y()), ground.at(x).at(y).get_w(), ground.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_ground_texture(), NULL, &rect);
               break;
            }
            case world_map::GRASS_COLLISION : {
               rect = { static_cast<int>(this->get_scrollX() + grass.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + grass.at(x).at(y).get_y()), grass.at(x).at(y).get_w(), grass.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_grass_texture(), NULL, &rect);
               break;            
            }
            default: {
               if (layer1.at(x).at(y) >= 16 && layer1.at(x).at(y) <= 24)
               {
                  rect = { static_cast<int>(this->get_scrollX() + grass.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + grass.at(x).at(y).get_y()), grass.at(x).at(y).get_w(), grass.at(x).at(y).get_h() };
                  SDL_RenderCopy(this->get_renderer(), this->get_dirt_texture(layer1.at(x).at(y) - 16), NULL, &rect);
               }
               break;
            }
         }
         // Layer 2
         switch (layer2.at(x).at(y))
         {
            case world_map::BOUNDARY_BUSH_COLLISION : {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(0), NULL, &rect);
               break;
            }
            case world_map::BOUNDARY_BUSH_LEFT : {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(1), NULL, &rect);
               break;
            }
            case world_map::BOUNDARY_BUSH_RIGHT : {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(2), NULL, &rect);
               break;
            }
            case world_map::BOUNDARY_BUSH_UP : {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(3), NULL, &rect);
               break;
            }
            case world_map::BOUNDARY_BUSH_DOWN : {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(4), NULL, &rect);
               break;
            }

            case world_map::BOUNDARY_BUSH_UPLEFT: {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(5), NULL, &rect);
               break;
            }  

            case world_map::BOUNDARY_BUSH_DOWNLEFT: {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(6), NULL, &rect);
               break;
            } 

            case world_map::BOUNDARY_BUSH_UPRIGHT: {
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(7), NULL, &rect);
               break;
            }          

            case world_map::BOUNDARY_BUSH_DOWNRIGHT: { 
               rect = { static_cast<int>(this->get_scrollX() + blocks.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + blocks.at(x).at(y).get_y()), blocks.at(x).at(y).get_w(), blocks.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_boundBush_Texture(8), NULL, &rect);
               break;
            }                                         
                                                 
                                        


            case world_map::POTION_COLLISION : {
               rect = { static_cast<int>(this->get_scrollX() + potions.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + potions.at(x).at(y).get_y()), potions.at(x).at(y).get_w(), potions.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_potion_texture(this->potions.at(x).at(y).get_frame()), NULL, &rect);
               break;
            }
            case world_map::WATER_COLLISION : {
               rect = { static_cast<int>(this->get_scrollX() + water.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + water.at(x).at(y).get_y()), water.at(x).at(y).get_w(), water.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_water_texture(this->water.at(x).at(y).get_frame()), NULL, &rect);
               break;
            }
            case world_map::BUSH_COLLISION : {
               rect = { static_cast<int>(this->get_scrollX() + bushes.at(x).at(y).get_x()), static_cast<int>(this->get_scrollY() + bushes.at(x).at(y).get_y()), bushes.at(x).at(y).get_w(), bushes.at(x).at(y).get_h() };
               SDL_RenderCopy(this->get_renderer(), this->get_bush_texture(), NULL, &rect);
               break;
            }
         }
      }
   }
   

   /*  PLAYER ATTRIBUTES */

   // Health Bar
   rect = { this->getHealthBar()->get_x(), this->getHealthBar()->get_y(), this->getHealthBar()->get_h(), this->getHealthBar()->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_health_texture(healthFrame), NULL, &rect);
  

   // Player Attack Rect
   rect = { this->get_scrollX() + this->get_player_attack()->get_x(), this->get_scrollY() + this->get_player_attack()->get_y(), this->get_player_attack()->get_h(), this->get_player_attack()->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_player_attack()->get_stillFrame(0), NULL, &rect);

   // Walk On Water Rect
   rect = { this->get_scrollX() + this->all_players.at(PLAYER_1)->get_x(), this->get_scrollY() + this->all_players.at(PLAYER_1)->get_y(), this->all_players.at(PLAYER_1)->get_h(), this->all_players.at(PLAYER_1)->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_waterWalkTexture(waterWalkFrame), NULL, &rect);

   // Player Rect
   rect = { this->get_scrollX() + this->all_players.at(PLAYER_1)->get_x(), this->get_scrollY() + this->all_players.at(PLAYER_1)->get_y(), this->all_players.at(PLAYER_1)->get_h(), this->all_players.at(PLAYER_1)->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->all_players.at(PLAYER_1)->get_stillFrame(this->all_players.at(PLAYER_1)->get_frame()), NULL, &rect);

   // Points Rect
   rect = { this->get_scrollX() + this->all_players.at(PLAYER_1)->get_x(), this->get_scrollY() + this->all_players.at(PLAYER_1)->get_y(), this->all_players.at(PLAYER_1)->get_h(), this->all_players.at(PLAYER_1)->get_w() };
   SDL_RenderCopy(this->get_renderer(), this->get_points_texture(pointFrame), NULL, &rect);


   /***********************/

   // Enemies
   typename vector<Enemy>::pointer en_ptr, en_end = enemies.data() + enemies.size();
   SDL_Rect enRect, hbRect;
   for (en_ptr = enemies.data(); en_ptr < en_end; ++en_ptr)
   {
      enRect = { this->get_scrollX() + en_ptr->get_x(), 
                 this->get_scrollY() + en_ptr->get_y(),
                 en_ptr->get_h(),
                 en_ptr->get_w() };
      SDL_RenderCopy(this->get_renderer(), en_ptr->get_stillFrame(en_ptr->get_frame()), NULL, &enRect);

      hbRect = { this->get_scrollX() + en_ptr->get_x(), 
                 this->get_scrollY() + (en_ptr->get_y() - 12),
                 en_ptr->get_h(),
                 en_ptr->get_w() };
      SDL_RenderCopy(this->get_renderer(), en_ptr->get_healthBarTexture(en_ptr->get_healthFrame()), NULL, &hbRect);
   }


   loadRectTopBar(rect);

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