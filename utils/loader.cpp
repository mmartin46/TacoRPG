#include "../game.hpp"

/*
Intializes the the topBar.
The topBar contains the health, time, and
other features for the GameState.
*/
void GameState::initTopBar()
{
   using namespace std::chrono;
   auto currentTime = high_resolution_clock::now();
   auto time = std::chrono::duration_cast<std::chrono::seconds>(currentTime - start_time);

   char str[200] = "";
   sprintf(str, "Life:           Time: %u             Score: %u", (time), score);

   SDL_Color white = { 255, 255, 255, 255 };
   SDL_Surface *tmp = TTF_RenderText_Blended(this->getTopBarFont(), str, white);
   this->topBar->set_w(tmp->w);
   this->topBar->set_h(tmp->h);
   this->setTopBarTexture(SDL_CreateTextureFromSurface(this->get_renderer(), tmp));
   SDL_FreeSurface(tmp);
}

/*
Loads the rectangle and sets the texture
for the topBar within the GameState.
*/
void GameState::loadRectTopBar(SDL_Rect &rect)
{
   rect = { 0, 0, this->topBar->get_w(), this->topBar->get_h() };
   SDL_RenderCopy(this->get_renderer(), this->getTopBarTexture(), NULL, &rect );
}


// Sets sprites that contain only one frame.
void GameState::setConstantSpriteTextures(SDL_Surface *surface)
{
   using std::cout;
   //Make sure the vector sizes are equal.
   if (tSetters.size() != fileMap.size())
   {
      cout << "Error: tSetters() and fileMap() are of unequal size!\n";
      SDL_Quit();
      exit(1);
   }

   tSend = tSetters.data() + tSetters.size();
   typename vector<pair<const char *, const char *> >::pointer fPtr = fileMap.data();
   for (tSptr = tSetters.data(); tSptr < tSend; ++tSptr, ++fPtr)
   {
      surface = IMG_Load(fPtr->first);
      if (surface == NULL)
      {
         printf("%s", fPtr->second);
         SDL_Quit();
         exit(1);
      }
      (*this.**tSptr)(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }
}

/*
This method is used to load
all the textures to each entity within the
GameState.
*/
void GameState::load()
{
   SDL_Surface *surface;
   string req, err;
   using std::to_string;
   const char *path;

   // Fonts
   setTopBarFont(TTF_OpenFont("sprites\\fonts\\font.ttf", 10));
   if (!this->getTopBarFont())
   {
      std::cout << "topbarFont(): Can't find font label";
      SDL_Quit();
      exit(1);
   }

   // Sounds
   this->set_shotSound(Mix_LoadWAV("sounds\\shot.wav"));
   if (!this->get_shotSound())
   {
      std::cout << "load shotSound(): No song found!\n";
      SDL_Quit();
      exit(1);
   }

   // Textures
   for (int i = 0; i < ENTITY_FRAMES; ++i)
   {
      string wPath = "sprites\\player\\walking" + to_string(i) + ".png";
      surface = IMG_Load(wPath.c_str());
      if (surface == NULL)
      {
         printf("load walking(): No texture for %s", wPath);
         SDL_Quit();
         exit(1);
      }
      this->all_players.at(PLAYER_1)->set_stillFrame(i, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }

   this->all_players.at(PLAYER_1)->set_h(PLAYER_HEIGHT);
   this->all_players.at(PLAYER_1)->set_w(PLAYER_WIDTH);

   path = "sprites\\attack\\attack.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load attack(): No texture for %s", path);
      SDL_Quit();
      exit(1);
   }
   this->get_player_attack()->set_stillFrame(0, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   // All enemies
   for (int i = 0; i < get_enemies()->size(); ++i)
   {
      for (int j = 0; j < ENEMY_COUNT; ++j)
      {
         path = ("sprites\\enemy\\enemy" + to_string(j) + ".png").c_str();
         surface = IMG_Load(path);
         if (surface == NULL)
         {
            printf("load enemy(): No texture %s", path);
            SDL_Quit();
            exit(1);      
         }
         this->get_enemies()->at(i).set_stillFrame(j, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
         SDL_FreeSurface(surface);
      }
   }

   // Enemy Health Bar
   for (int i = 0; i < get_enemies()->size(); ++i)
   {
      for (int j = 0; j < ENEMY_HEALTHBAR_FRAMES; ++j)
      {
         path = ("sprites\\enemybar\\enemybar" + to_string(j) + ".png").c_str();
         surface = IMG_Load(path);
         if (surface == NULL)
         {
            printf("load enemybar(): No texture");
            SDL_Quit();
            exit(1);      
         }
         this->get_enemies()->at(i).set_healthBarTexture(j, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
         SDL_FreeSurface(surface);
      }
   }

   // Setting the constant textures.
   tSetters.push_back(set_ground_texture);
   tSetters.push_back(set_bush_texture);
   tSetters.push_back(set_block_texture);
   tSetters.push_back(set_grass_texture);

   fileMap.push_back({"sprites\\groundblock.png", "load groundblock(): No texture"});
   fileMap.push_back({"sprites\\bush.png", "load bush(): No texture"});
   fileMap.push_back({"sprites\\block.png", "load block(): No texture"});
   fileMap.push_back({"sprites\\landscape\\grass.png", "load grass(): No texture"});
   setConstantSpriteTextures(surface);


   // Background Bush Sprite Paths
   vector<pair<const char*, const char*> > bbPaths = {
      {"sprites\\landscape\\boundary_bush.png", "load bb(): No texture"},
      {"sprites\\landscape\\boundary_bush_left.png" , "load bb_l(): No texture"},
      {"sprites\\landscape\\boundary_bush_right.png" , "load bb_r(): No texture"},
      {"sprites\\landscape\\boundary_bush_up.png", "load bb_u(): No texture"},
      {"sprites\\landscape\\boundary_bush_down.png", "load bb_d(): No texture"},
      {"sprites\\landscape\\boundary_bush_upleft.png" , "load bb_ul(): No texture"},
      {"sprites\\landscape\\boundary_bush_downleft.png" , "load bb_dl(): No texture"},
      {"sprites\\landscape\\boundary_bush_upright.png" , "load bb_ur(): No texture"},
      {"sprites\\landscape\\boundary_bush_downright.png" , "load bb_dr(): No texture"},
   };

   // Dirt and Dirt/Grass Transitional Sprite Paths
   vector<pair<const char*, const char*> > dirtPaths = {
      {"sprites\\landscape\\dirt.png", "load dirt(): No textures"},
      {"sprites\\landscape\\dirt_transleft.png", "load dirttl(): No textures"},
      {"sprites\\landscape\\dirt_transright.png", "load dirttr(): No textures"},
      {"sprites\\landscape\\dirt_transup.png", "load dirttu(): No textures"},
      {"sprites\\landscape\\dirt_transdown.png", "load dirttd(): No textures"},
      {"sprites\\landscape\\dirt_transdownright.png", "load dirttdr(): No textures"},
      {"sprites\\landscape\\dirt_transdownleft.png", "load dirttdl(): No textures"},
      {"sprites\\landscape\\dirt_transupright.png", "load dirttur(): No textures"},
      {"sprites\\landscape\\dirt_transupleft.png", "load dirttul(): No textures"},

   };

   char *bbpath;
   char *dpath;

   for (int i = 0; i < bbPaths.size(); ++i)
   {
      // Setting the paths
      bbpath = const_cast<char*>(bbPaths.at(i).first);
      dpath = const_cast<char*>(dirtPaths.at(i).first);

      // Background Bush
      surface = IMG_Load(bbpath);
      if (surface == NULL)
      {
         printf(bbPaths.at(i).second);
         SDL_Quit();
         exit(1);
      }
      this->set_boundBush_Texture(i, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);

      // Dirt
      surface = IMG_Load(dpath);
      if (surface == NULL)
      {
         printf(dirtPaths.at(i).second);
         SDL_Quit();
         exit(1);
      }
      this->set_dirt_texture(i, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }



   // Animated Textures

   // Water Block
   for (int i = 1; i <= 5; i++)
   {
      path = ("sprites\\water\\waterblock" + to_string(i) + ".png").c_str();
      surface = IMG_Load(path);
      if (surface == NULL)
      {
         printf("load waterblock(): No texture %s\n", path);
         SDL_Quit();
         exit(1);
      }
      this->set_water_texture((i - 1), SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }
   // Juice
   for (int i = 1; i <= 6; i++)
   {
      path = ("sprites\\juice\\juice" + to_string(i) + ".png").c_str();
      surface = IMG_Load(path);
      if (surface == NULL)
      {
         printf("load juice(): No texture %s\n", path);
         SDL_Quit();
         exit(1);
      }
      this->set_juice_texture((i - 1), SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }
   
   // Points
   for (int i = 0; i < 7; i++)
   {
       path = ("sprites\\points\\points" + to_string(i) + ".png").c_str();
       surface = IMG_Load(path);
       if (surface == NULL)
       {
           printf("load points(): No Texture %s\n", path);
           SDL_Quit();
           exit(1);
       }
       this->set_points_texture(i, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
       SDL_FreeSurface(surface);
   }

   // Texture for the player when they are walking in
   // water.
   for (int i = 0; i < 5; i++)
   {
      string p = ("sprites\\waterwalk\\waterwalk" + to_string(i) + ".png");
      surface = IMG_Load(p.c_str());
      if (surface == NULL)
      {
         printf("load waterwalk(): No texture %s\n", p.c_str());
         SDL_Quit();
         exit(1);
      }
      this->set_waterWalkTexture(i, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);     
   }
   // Life
   for (int i = 0; i < 13; i++)
   {
      string p = ("sprites\\life\\life" + to_string(i) + ".png");
      surface = IMG_Load(p.c_str());
      if (surface == NULL)
      {
         printf("load life(): No texture %s\n", p.c_str());
         SDL_Quit();
         exit(1);
      }
      this->set_health_texture(i, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);    
   }
}

void GameState::init_tiles()
{
   int x, y;
   for (x = 0; x < row_count; ++x)
   {
      for (y = 0; y < col_count; ++y)
      {
         this->layer1.at(x).at(y) = world_map::layer1[x][y];
         this->layer2.at(x).at(y) = world_map::layer2[x][y];
         this->layer3.at(x).at(y) = world_map::layer3[x][y];
      }
   }

   for (x = 0; x < row_count; ++x)
   {
      for (y = 0; y < col_count; ++y)
      {
         // Background Layer
         switch (layer1.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION:
               get_blocks()->at(x).at(y).set_y(x*BLOCK_WIDTH);               
               get_blocks()->at(x).at(y).set_x(y*BLOCK_HEIGHT);
               get_blocks()->at(x).at(y).set_w(BLOCK_WIDTH);
               get_blocks()->at(x).at(y).set_h(BLOCK_HEIGHT);
               break;       
            case world_map::GROUND_COLLISION:
               ground.at(x).at(y).set_y(x*BLOCK_WIDTH);               
               ground.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               ground.at(x).at(y).set_w(BLOCK_WIDTH);
               ground.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::GRASS_COLLISION:
               grass.at(x).at(y).set_y(x*BLOCK_WIDTH);
               grass.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               grass.at(x).at(y).set_w(BLOCK_WIDTH);
               grass.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case 16 ... 24:
               grass.at(x).at(y).set_y(x*BLOCK_WIDTH);               
               grass.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               grass.at(x).at(y).set_w(BLOCK_WIDTH);
               grass.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;           
         }
         // Second Layer
         switch (layer2.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION:
               get_blocks()->at(x).at(y).set_y(x*BLOCK_WIDTH);               
               get_blocks()->at(x).at(y).set_x(y*BLOCK_HEIGHT);
               get_blocks()->at(x).at(y).set_w(BLOCK_WIDTH);
               get_blocks()->at(x).at(y).set_h(BLOCK_HEIGHT);
               break;       
            case world_map::GROUND_COLLISION:
               ground.at(x).at(y).set_y(x*BLOCK_WIDTH);               
               ground.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               ground.at(x).at(y).set_w(BLOCK_WIDTH);
               ground.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::GRASS_COLLISION:
               grass.at(x).at(y).set_y(x*BLOCK_WIDTH);
               grass.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               grass.at(x).at(y).set_w(BLOCK_WIDTH);
               grass.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case 16 ... 24:
               grass.at(x).at(y).set_y(x*BLOCK_WIDTH);               
               grass.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               grass.at(x).at(y).set_w(BLOCK_WIDTH);
               grass.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;


            case 7 ... 15:
               get_blocks()->at(x).at(y).set_y(x*BLOCK_WIDTH);
               get_blocks()->at(x).at(y).set_x(y*BLOCK_HEIGHT);
               get_blocks()->at(x).at(y).set_w(BLOCK_WIDTH);
               get_blocks()->at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::JUICE_COLLISION:
               juices.at(x).at(y).set_y(x*BLOCK_WIDTH);
               juices.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               juices.at(x).at(y).set_w(BLOCK_WIDTH);
               juices.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::WATER_COLLISION:
               water.at(x).at(y).set_y(x*BLOCK_WIDTH);
               water.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               water.at(x).at(y).set_w(BLOCK_WIDTH);
               water.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::BUSH_COLLISION:
               bushes.at(x).at(y).set_y(x*BLOCK_WIDTH);
               bushes.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               bushes.at(x).at(y).set_w(BLOCK_WIDTH);
               bushes.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
         }
         // Third Layer
         switch (layer3.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION:
               get_blocks()->at(x).at(y).set_y(x*BLOCK_WIDTH);               
               get_blocks()->at(x).at(y).set_x(y*BLOCK_HEIGHT);
               get_blocks()->at(x).at(y).set_w(BLOCK_WIDTH);
               get_blocks()->at(x).at(y).set_h(BLOCK_HEIGHT);
               break;       
            case world_map::GROUND_COLLISION:
               ground.at(x).at(y).set_y(x*BLOCK_WIDTH);               
               ground.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               ground.at(x).at(y).set_w(BLOCK_WIDTH);
               ground.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::GRASS_COLLISION:
               grass.at(x).at(y).set_y(x*BLOCK_WIDTH);
               grass.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               grass.at(x).at(y).set_w(BLOCK_WIDTH);
               grass.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case 16 ... 24:
               grass.at(x).at(y).set_y(x*BLOCK_WIDTH);               
               grass.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               grass.at(x).at(y).set_w(BLOCK_WIDTH);
               grass.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;


            case 7 ... 15:
               get_blocks()->at(x).at(y).set_y(x*BLOCK_WIDTH);
               get_blocks()->at(x).at(y).set_x(y*BLOCK_HEIGHT);
               get_blocks()->at(x).at(y).set_w(BLOCK_WIDTH);
               get_blocks()->at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::JUICE_COLLISION:
               juices.at(x).at(y).set_y(x*BLOCK_WIDTH);
               juices.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               juices.at(x).at(y).set_w(BLOCK_WIDTH);
               juices.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::WATER_COLLISION:
               water.at(x).at(y).set_y(x*BLOCK_WIDTH);
               water.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               water.at(x).at(y).set_w(BLOCK_WIDTH);
               water.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::BUSH_COLLISION:
               bushes.at(x).at(y).set_y(x*BLOCK_WIDTH);
               bushes.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               bushes.at(x).at(y).set_w(BLOCK_WIDTH);
               bushes.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;            
         }
      }
   }

}