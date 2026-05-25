#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

typedef struct {
  int width;
  int height;
} World;

typedef struct Map{
  int width;
  int height;
  int tileSize;
} Map;

typedef struct {
  Vector2 pos;
  Vector2 clonePos;
  float radius;
  float speed;
  bool showClone;
  Vector2 velocity;
} Player;

void checkBoundaries(Player* player, const World* world);

Color GetTileColorFromHeight(float height);

int main(void) {


  const World world = {1900, 1000};
  Player player = {
    .pos = {(float) world.width / 2, (float) world.height / 2},
    .clonePos = {0, 0},
    .radius = 50,
    .speed = 100,
    .showClone = false,
    .velocity = {0, 0}
  };

  Map map = {1520, 800, 5};

  float map2D[map.width][map.height]; 

  Image noiseImage = GenImagePerlinNoise(map.width, map.height, map.tileSize, map.tileSize, 1.5f);
  
  Color *noiseColors = LoadImageColors(noiseImage);

  for(int i = 0; i < map.width; i++){

      for(int j = 0; j < map.height; j++){
      map2D[i][j] = (float)noiseColors[(j * map.width) + i].r / 255.0f;

    }

  }

  UnloadImage(noiseImage);
  UnloadImageColors(noiseColors); 

  InitWindow(world.width, world.height, "Test Window");

  SetTargetFPS(240);

  Color bgGrey = {35, 35, 35, 255}; 
  Color bgLight = {30, 30, 30, 255};

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
   
    for(int i = 0; i < map.width; i++){
    
      for(int j = 0; j < map.height; j++){
        
        Color tileColor = GetTileColorFromHeight(map2D[i][j]);
        
        

        DrawRectangle(i * map.tileSize, j * map.tileSize, map.tileSize, map.tileSize, tileColor);
    
      }
    }

    //DrawCircleV(player.pos, player.radius, BLUE);
    //if(player.showClone)DrawCircleV(player.clonePos, player.radius, BLUE);


    EndDrawing();

  }
   CloseWindow();

  return 0;

}

Color GetTileColorFromHeight(float height){

  Color color;
  
  if(height < 0.3f){
    color = DARKBLUE;
  }else if(height < 0.4f){
    color = BLUE;
  }else if(height < 0.45){
    color = YELLOW;
  }else if(height < 0.47f){
    color = BROWN;
  }else if(height < 0.5f){
    color = GREEN;
  }else if(height < 0.7f){
    color = GRAY;
  }else {
    color = WHITE;
  }

  return color;

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
