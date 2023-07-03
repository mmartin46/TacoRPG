#pragma once
#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 20
#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20

namespace world_map {
   enum collisions {
      NO_COLLISION = 0,
      BLOCK_COLLISION = 1
   };
}