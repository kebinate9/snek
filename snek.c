#include <stdio.h>
#include <raylib.h>

#define WINWIDTH  400
#define WINHEIGHT 400
#define MAXLENGTH 256

typedef struct Snek {
  int x[MAXLENGTH];
  int y[MAXLENGTH];
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
  snek.size = 3;
  for (int i = 0; i < snek.size; i++) {
    snek.x[i] = 200 - i * 10;
    snek.y[i] = 200;
  }

  food.x = GetRandomValue(0, WINWIDTH - 10);
  food.y = GetRandomValue(0, WINHEIGHT - 10);
}

void drawGame()
{

  ClearBackground(BLACK);

  for (int i = 0; i < snek.size; i++) DrawRectangle(snek.x[i], snek.y[i], 10, 10, WHITE);

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
      snek.y[0] -= SPEED;
    }else if (lastKeyPressed == KEY_S) {
      snek.y[0] += SPEED;
    }else if (lastKeyPressed == KEY_A) {
      snek.x[0] -= SPEED;
    }else if (lastKeyPressed == KEY_D) {
      snek.x[0] += SPEED;
    }

    for (int i = snek.size - 1; i > 0; i--) {
      snek.x[i] = snek.x[i-1];
      snek.y[i] = snek.y[i-1];
    }

    if (CheckCollisionCircleRec((Vector2){food.x, food.y}, 5, (Rectangle){snek.x[0], snek.y[0], 10, 10})) {
      food.x = GetRandomValue(0, WINWIDTH);
      food.y = GetRandomValue(0, WINHEIGHT);
      score ++;
      snek.size ++;
    }

    if(snek.x[0] < 0 || snek.x[0] > WINWIDTH || snek.y[0] < 0 || snek.y[0] > WINHEIGHT) {
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
