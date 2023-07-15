#pragma once
/*
Entity -
Object that contains
- id
- x, y, w, h positions
*/
class Entity
{
   private:
      int id;
      int frame;
      int x, y, w, h;
      int dy, dx;
      std::vector<SDL_Texture*> stillFrames;
      int last_state;
      bool visited;
   public:
      Entity();
      virtual ~Entity();
      inline virtual int get_id() { return id; }; const
      inline virtual void set_id(int i) { id = i; }

      inline virtual int get_x() { return x; } const
      inline virtual void set_x(int val) { x = val; }
      inline virtual int get_y() { return y; } const
      inline virtual void set_y(int val) { y = val; }

      inline void set_visited() { visited = true; }
      inline void reset_visited() { visited = false; }
      inline bool get_visited() { return visited; }

      inline virtual void set_dx(int d) { dx = d; }
      inline virtual void set_dy(int d) { dy = d; }

      inline virtual int get_w() { return w; } const
      inline virtual void set_w(int val) { w = val; }
      inline virtual int get_h() { return h; } const
      inline virtual void set_h(int val) { h = val; }

      inline virtual int get_last_state() { return last_state; }
      inline virtual void set_last_state(int n) { last_state = n; }


      inline virtual void move_right(int s) { set_x(get_x() + s); }     
      inline virtual void move_left(int s) { set_x(get_x() - s); }
      inline virtual void move_up(int s) { set_y(get_y() - s); }     
      inline virtual void move_down(int s) { set_y(get_y() + s); }

      inline virtual int get_frame() { return frame; }
      inline virtual void set_frame(int f) { frame = f; }

      virtual void set_stillFrame(int n, SDL_Texture*);
      inline virtual SDL_Texture* get_stillFrame(int n) { return stillFrames.at(n); }
};

Entity::Entity()
{
   stillFrames = std::vector<SDL_Texture*>(ENTITY_FRAMES);
   reset_visited();
}

Entity::~Entity()
{
   for (auto &f : stillFrames)
   {
      SDL_DestroyTexture(f);
   }
}

/*
Sets the frame for the enemy.
\param n index
\param t texture
*/
void Entity::set_stillFrame(int n, SDL_Texture* t)
{
   if (n >= this->stillFrames.size() || n < 0)
   {
      std::cout << "stillFrames: argument " << n << " is out of bounds\n";
      exit(1);
   }
   this->stillFrames.at(n) = t;
}