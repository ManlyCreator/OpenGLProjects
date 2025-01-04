#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef enum {
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN
} GameState;

typedef struct {
  GameState State;
  bool Keys[1024];
  unsigned Width, Height;
} Game;

void GameInit();
void GameProcessInput(float dt);
void GameUpdate(float dt);
void GameRender();

#endif
