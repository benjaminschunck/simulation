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
  Vector2 velocity;
} Player;

void checkBoundaries(Player* player, const World* world);

int main(void) {


  const World world = {1900, 1000};
  Player player = {
    .pos = {(float) world.width / 2, (float) world.height / 2},
    .clonePos = (0, 0),
    .radius = 50,
    .speed = 100,
    .showClone = false,
    .velocity = {0, 0}
  };

  InitWindow(world.width, world.height, "Test Window");

  SetTargetFPS(240);

  MaximizeWindow();

  while(!WindowShouldClose()){
  
  if(IsKeyDown(KEY_W)){
      player.velocity.y -= GetFrameTime() * player.speed;
    }

  if(IsKeyDown(KEY_S)){
      player.velocity.y += GetFrameTime() * player.speed;
    }

  if(IsKeyDown(KEY_A)){
      player.velocity.x -= GetFrameTime() * player.speed;
    }

  if(IsKeyDown(KEY_D)){
      player.velocity.x += GetFrameTime() * player.speed;
    }

  player.pos.x += player.velocity.x;
  player.pos.y += player.velocity.y;

  player.velocity.x *= 0.99f;
  player.velocity.y *= 0.99f;

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
