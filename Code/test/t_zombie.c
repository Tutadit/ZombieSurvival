void test_zombie(UINT32 *base ){
  test_zombie_renderer(base);
}

void plot_pixel(char *base int x int y){
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
      *(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
}
void test_zombie_renderer(UINT32 *base){
  struct Player player;
  struct Zombie zombie;

  int x = 200;
  int y = 250;

  zombie.step = 0;
  while(true){
    if(player.move_direction == MOVE_S){
      zombie.speed = 1;
      zombie_set_direction(&zombie,&player);
      y--;
    }
    else if(player.move_direction == MOVE_N ){
      zombie.speed = 1;
      zombie_set_direction(&zombie,&player);
      y++;
    }
    else if(player.move_direction == MOVE_W){
      zombie.speed = 1;
      zombie_set_direction(&zombie,&player);
      x--;
    }
    else if (player.move_direction == MOVE_E) {
      zombie.speed = 1;
      zombie_set_direction(&zombie,&player);
      x++;
    }
    fflush(stdout);
    zombie_update_position(&zombie);
    zombie.speed = 1;
    zombie_set_step(&zombie);
    Vsync();
    clear_screen(base);
    render_zombie(&zombie,base);
    plot_pixel((char *)base, x,y);
  }

}
