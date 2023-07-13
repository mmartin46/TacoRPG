#include "game.hpp"
// Sets sprites that contain only one frame.
void GameState::setConstantSpriteTextures(SDL_Surface *surface)
{
   using std::cout;
   // Make sure the vector sizes are equal.
   if (tSetters.size() != fileMap.size())
   {
      cout << "Error: tSetters() and fileMap() are of unequal size!\n";
      SDL_Quit();
      exit(1);
   }

   tSend = tSetters.data() + tSetters.size();
   typename unordered_map<string, string>::iterator fPtr = fileMap.begin();
   for (tSptr = tSetters.data(); tSptr < tSend; ++tSptr, ++fPtr)
   {
      surface = IMG_Load(fPtr->first.c_str());
      if (surface == NULL)
      {
         printf("%s", fPtr->second.c_str());
         SDL_Quit();
         exit(1);
      }
      (*this.**tSptr)(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }
}

void GameState::load()
{
   SDL_Surface *surface;
   string req, err;
   using std::to_string;
   const char *path;


   for (int i = 0; i < ENTITY_FRAMES; ++i)
   {
      string wPath = "sprites\\player\\walking" + to_string(i) + ".png";
      surface = IMG_Load(wPath.c_str());
      if (surface == NULL)
      {
         printf("load: No texture");
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
      printf("load: No texture");
      SDL_Quit();
      exit(1);
   }

   this->get_player_attack()->set_stillFrame(0, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\enemy\\enemy.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load: No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_enemy_texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\block.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load: No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_block_texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\landscape\\grass.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load: No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_grass_texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);


   path = "sprites\\groundblock.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load: No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_ground_texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   // tSetters.push_back(set_ground_texture);
   // tSetters.push_back(set_bush_texture);
   // tSetters.push_back(set_block_texture);

   // fileMap.insert("sprites\\groundblock.png", "load groundblock(): No texture");
   // fileMap.insert("sprites\\bush.png", "load bush(): No texture");
   // fileMap.insert("sprites\\block.png", "load block(): No texture");
   //setConstantSpriteTextures(surface);


   path = "sprites\\groundblock.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load groundblock(): No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_ground_texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\bush.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load bush(): No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_bush_texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\landscape\\boundary_bush.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load bb(): No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_boundBush_Texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\landscape\\boundary_bush_left.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load bb_l(): No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_boundBushLeft_Texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\landscape\\boundary_bush_right.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load bb_r(): No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_boundBushRight_Texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\landscape\\boundary_bush_up.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load bb_u(): No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_boundBushUp_Texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);

   path = "sprites\\landscape\\boundary_bush_down.png";
   surface = IMG_Load(path);
   if (surface == NULL)
   {
      printf("load bb_d(): No texture");
      SDL_Quit();
      exit(1);      
   }
   this->set_boundBushDown_Texture(SDL_CreateTextureFromSurface(this->get_renderer(), surface));
   SDL_FreeSurface(surface);



   for (int i = 1; i <= 5; i++)
   {
      path = ("sprites\\water\\waterblock" + to_string(i) + ".png").c_str();
      surface = IMG_Load(path);
      if (surface == NULL)
      {
         printf("load: No texture %s\n", path);
         SDL_Quit();
         exit(1);
      }
      this->set_water_texture((i - 1), SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }

   for (int i = 1; i <= 6; i++)
   {
      path = ("sprites\\potion\\potion" + to_string(i) + ".png").c_str();
      surface = IMG_Load(path);
      if (surface == NULL)
      {
         printf("load: No texture %s\n", path);
         SDL_Quit();
         exit(1);
      }
      this->set_potion_texture((i - 1), SDL_CreateTextureFromSurface(this->get_renderer(), surface));
      SDL_FreeSurface(surface);
   }

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


   for (int i = 0; i < 5; i++)
   {
      string p = ("sprites\\waterwalk\\waterwalk" + to_string(i) + ".png");
      surface = IMG_Load(p.c_str());
      if (surface == NULL)
      {
         printf("load: No texture %s\n", p.c_str());
         SDL_Quit();
         exit(1);
      }
      this->set_waterWalkTexture(i, SDL_CreateTextureFromSurface(this->get_renderer(), surface));
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
         layer1.at(x).at(y) = world_map::map[x][y];
         layer2.at(x).at(y) = world_map::bush_map[x][y];
      }
   }

   for (x = 0; x < row_count; ++x)
   {
      for (y = 0; y < col_count; ++y)
      {
         switch (layer1.at(x).at(y))
         {
            case world_map::BLOCK_COLLISION:
               blocks.at(x).at(y).set_y(x*BLOCK_WIDTH);               
               blocks.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               blocks.at(x).at(y).set_w(BLOCK_WIDTH);
               blocks.at(x).at(y).set_h(BLOCK_HEIGHT);
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


         }

         switch (layer2.at(x).at(y))
         {
            case world_map::BOUNDARY_BUSH_COLLISION:
               blocks.at(x).at(y).set_y(x*BLOCK_WIDTH);
               blocks.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               blocks.at(x).at(y).set_w(BLOCK_WIDTH);
               blocks.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::BOUNDARY_BUSH_LEFT:
               blocks.at(x).at(y).set_y(x*BLOCK_WIDTH);
               blocks.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               blocks.at(x).at(y).set_w(BLOCK_WIDTH);
               blocks.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::BOUNDARY_BUSH_RIGHT:
               blocks.at(x).at(y).set_y(x*BLOCK_WIDTH);
               blocks.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               blocks.at(x).at(y).set_w(BLOCK_WIDTH);
               blocks.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::BOUNDARY_BUSH_UP:
               blocks.at(x).at(y).set_y(x*BLOCK_WIDTH);
               blocks.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               blocks.at(x).at(y).set_w(BLOCK_WIDTH);
               blocks.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::BOUNDARY_BUSH_DOWN:
               blocks.at(x).at(y).set_y(x*BLOCK_WIDTH);
               blocks.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               blocks.at(x).at(y).set_w(BLOCK_WIDTH);
               blocks.at(x).at(y).set_h(BLOCK_HEIGHT);
               break;
            case world_map::POTION_COLLISION:
               potions.at(x).at(y).set_y(x*BLOCK_WIDTH);
               potions.at(x).at(y).set_x(y*BLOCK_HEIGHT);
               potions.at(x).at(y).set_w(BLOCK_WIDTH);
               potions.at(x).at(y).set_h(BLOCK_HEIGHT);
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