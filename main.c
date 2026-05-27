#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <math.h>

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
  float rotation;
  float speed;
  Vector2 velocity;
} Player;

void checkBoundaries(Player* player, const World* world);

Color GetTileColorFromHeight(float height);

int main(void) {


  const World world = {1900, 1000};
  Player player = {
    .pos = {(float) world.width / 2, (float) world.height / 2},
    .speed = 60,
    .velocity = {0, 0}
  };

  Map map = {1520, 800, 2};

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

      float x = cos(player.rotation) * player.speed * GetFrameTime();
      float y = sin(player.rotation) * player.speed * GetFrameTime();

      player.velocity.x += x;
      player.velocity.y += y;

  }

  if(IsKeyDown(KEY_S)){
    player.velocity.x -= 0.1 * player.speed * GetFrameTime();
    player.velocity.y -= 0.1 * player.speed * GetFrameTime();
    }

  if(IsKeyDown(KEY_A)){
    player.rotation -= 0.1f * GetFrameTime() * player.speed;
    }

  if(IsKeyDown(KEY_D)){
      player.rotation += 0.1f * GetFrameTime() * player.speed;
  }

    player.pos.x += player.velocity.x;
    player.pos.y += player.velocity.y;

    player.velocity.x *= 0.9f;
    player.velocity.y *= 0.9f;

  BeginDrawing();

    ClearBackground(RAYWHITE);
   
    for(int i = 0; i < map.width; i++){
    
      for(int j = 0; j < map.height; j++){
        
        Color tileColor = GetTileColorFromHeight(map2D[i][j]);
        
        

        DrawRectangle(i * map.tileSize, j * map.tileSize, map.tileSize, map.tileSize, tileColor);
    
      }
    }

   DrawPoly(player.pos, 3, 20.0f, player.rotation * RAD2DEG, RED); 

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
    // Kommt später evtl. wieder
}
