#include <stdio.h>
#include "raylib.h"

typedef struct {
  int width;
  int height;
} World;

typedef struct {
  Vector2 pos;
  Vector2 clonePos;
  float radius;
  float speed;
  bool showClone;
} Player;

void checkBoundaries(Player* player, const World* world);

int main(void) {


  const World world = {800, 450};
  Player player = {
    .pos = {(float) world.width / 2, (float) world.height / 2},
    .clonePos = (0, 0),
    .radius = 50,
    .speed = 400,
    .showClone = false
  };

  InitWindow(world.width, world.height, "Test Window");

  SetTargetFPS(240);

  MaximizeWindow();

  while(!WindowShouldClose()){
  
  if(IsKeyDown(KEY_W)){
      player.pos.y -= GetFrameTime() * player.speed;
    }

  if(IsKeyDown(KEY_S)){
      player.pos.y += GetFrameTime() * player.speed;
    }

  if(IsKeyDown(KEY_A)){
      player.pos.x -= GetFrameTime() * player.speed;
    }

  if(IsKeyDown(KEY_D)){
      player.pos.x += GetFrameTime() * player.speed;
    }


  checkBoundaries(&player, &world);

  BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircleV(player.pos, player.radius, BLUE);
    if(player.showClone)DrawCircleV(player.clonePos, player.radius, BLUE);


    EndDrawing();

  }

  CloseWindow();

  return 0;

}

void checkBoundaries(Player* player, const World* world){
  

  if(player->pos.y > world->height) player->pos.y = 0;
  if(player->pos.y < 0) player->pos.y = world->height;
  if(player->pos.x > world->width) player->pos.x = 0;
  if(player->pos.x < 0) player->pos.x = world->width;


  if((player->pos.x + player->radius) > world->width){
      
      player->clonePos.x = 0 - (world->width - player->pos.x);
      player->clonePos.y = player->pos.y;

      player->showClone = true;
  }else if((player->pos.x - player->radius) < 0){
    player->clonePos.x = world->width - (0 - player->pos.x); 
    
    player->clonePos.y = player->pos.y;

    player->showClone = true;
    }else if((player->pos.y + player->radius) > world->height){

    player->clonePos.y = 0 - (world->height - player->pos.y);
    player->clonePos.x = player->pos.x;

    player->showClone = true;

  }else if((player->pos.y - player->radius) < 0){

    player->clonePos.y = world->height - (0 - player->pos.y);

    player->clonePos.x = player->pos.x;

    player->showClone = true;
    
  }else{
    player->showClone = false;
  }
 
  
}
