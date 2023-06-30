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
      int x, y, w, h;
      SDL_Texture *texture;
   public:
      inline virtual int get_id() { return id; }; const
      inline virtual void set_id(int i) { id = i; }

      inline virtual int get_x() { return x; } const
      inline virtual void set_x(int val) { x = val; }
      inline virtual int get_y() { return y; } const
      inline virtual void set_y(int val) { y = val; }

      inline virtual int get_w() { return w; } const
      inline virtual void set_w(int val) { w = val; }
      inline virtual int get_h() { return h; } const
      inline virtual void set_h(int val) { h = val; }

      inline virtual void move_right(int s) { set_x(get_x() + s); }     
      inline virtual void move_left(int s) { set_x(get_x() - s); }
      inline virtual void move_up(int s) { set_y(get_y() + s); }     
      inline virtual void move_down(int s) { set_y(get_y() - s); }
};
