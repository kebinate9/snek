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
static int highScore;

static const int SPEED = 3;

static void initGame();
static void drawGame();
static void updateGame();
static void menu();

int main(void)
{
  InitWindow(WINWIDTH, WINHEIGHT, "Snek");
  SetTargetFPS(60);
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
  score = 0;

  snek.x     = 10;
  snek.y     = 200;
  snek.size  = 1;

  food.x = GetRandomValue(0, WINWIDTH - 10);
  food.y = GetRandomValue(0, WINHEIGHT - 10);
}

void drawGame()
{

  ClearBackground(BLACK);
  DrawRectangle(snek.x, snek.y, 10, 10 * snek.size, WHITE);
  DrawText(TextFormat("Score: %d High Score: %d", score, highScore), 10, 10, 20, WHITE);
  DrawCircle(food.x, food.y, 5, WHITE);
  updateGame();
}

void updateGame()
{
  if (!playing) {
    menu();
    if (GetKeyPressed()) {
      initGame();
      playing = true;
    }
  }
  int key = GetKeyPressed();

  if (key) {
    lastKeyPressed = key;
    playing = true;
  }

  if (playing) {
    if (lastKeyPressed == KEY_W) {
      snek.y -= SPEED;
    }else if (lastKeyPressed == KEY_S) {
      snek.y += SPEED;
    }else if (lastKeyPressed == KEY_A) {
      snek.x -= SPEED;
    }else if (lastKeyPressed == KEY_D) {
      snek.x += SPEED;
    }

    if (CheckCollisionCircleRec((Vector2){food.x, food.y}, 5, (Rectangle){snek.x, snek.y, 10, 10})) {
      food.x = GetRandomValue(0, WINWIDTH);
      food.y = GetRandomValue(0, WINHEIGHT);
      score ++;
    }

    if(snek.x < 0 || snek.x > WINWIDTH || snek.y < 0 || snek.y > WINHEIGHT) {
      playing = false;
      lastKeyPressed = 0;
      key = 0;
      if (score > highScore) highScore = score;
    }
  }
}

void menu()
{
  ClearBackground(BLACK);
  DrawText("Press any key to start", 20, WINHEIGHT/1.1, 20, WHITE);
}
