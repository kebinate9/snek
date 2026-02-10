#include <stdio.h>
#include <raylib.h>

#define WINWIDTH  400
#define WINHEIGHT 400

typedef struct Snek {
  int x;
  int y;
  int size;
} Snek;

typedef struct Food {
  int x;
  int y;
} Food;

static Snek snek;
static Food food;

static int  lastKeyPressed;
static bool playing;
static int  score;

static void initGame();
static void drawGame();
static void updateGame();

int main(void)
{
  InitWindow(WINWIDTH, WINHEIGHT, "Snek");
  SetTargetFPS(20);
  initGame();

  while (!WindowShouldClose())
  {
    BeginDrawing();

      drawGame();

    EndDrawing();
  }
  CloseWindow();
}

void initGame()
{
  snek.x    = 10;
  snek.y    = 200;
  snek.size = 1;

  food.x = GetRandomValue(0, 400 - 10);
  food.y = GetRandomValue(0, 400 - 10);
}

void drawGame()
{
  ClearBackground(BLACK);
  DrawRectangle(snek.x, snek.y, 10, 10 * snek.size, WHITE);
  DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
  DrawCircle(food.x, food.y, 5, WHITE);
  updateGame();
}

void updateGame()
{
  int key = GetKeyPressed();

  if (key) {
    lastKeyPressed = key;
    playing = true;
  }

  if (playing) {
    if (lastKeyPressed == KEY_W) {
      snek.y -= 10;
    }else if (lastKeyPressed == KEY_S) {
      snek.y += 10;
    }else if (lastKeyPressed == KEY_A) {
      snek.x -= 10;
    }else if (lastKeyPressed == KEY_D) {
      snek.x += 10;
    }

    if (CheckCollisionCircleRec((Vector2){food.x, food.y}, 5, (Rectangle){snek.x, snek.y, 10, 10})) {
      food.x = GetRandomValue(0, 400);
      food.y = GetRandomValue(0, 400);
      score ++;
    }
  }
}
