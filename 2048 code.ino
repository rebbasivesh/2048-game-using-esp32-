#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Button.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button pins
const int UP_BUTTON_PIN = 32;
const int DOWN_BUTTON_PIN = 33;
const int LEFT_BUTTON_PIN = 25;
const int RIGHT_BUTTON_PIN = 26;

// Initialize buttons
Button upButton(UP_BUTTON_PIN);
Button downButton(DOWN_BUTTON_PIN);
Button leftButton(LEFT_BUTTON_PIN);
Button rightButton(RIGHT_BUTTON_PIN);

// Game variables
int grid[4][4];
int score;
bool moved;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  // Initialize buttons
  upButton.begin();
  downButton.begin();
  leftButton.begin();
  rightButton.begin();

  // Initialize game
  randomSeed(analogRead(0));
  initGame();
}

void loop() {
  // Check button presses
  if (upButton.pressed()) {
    moved = moveUp();
    if (moved) addRandomTile();
  } else if (downButton.pressed()) {
    moved = moveDown();
    if (moved) addRandomTile();
  } else if (leftButton.pressed()) {
    moved = moveLeft();
    if (moved) addRandomTile();
  } else if (rightButton.pressed()) {
    moved = moveRight();
    if (moved) addRandomTile();
  }

  // Draw grid
  drawGrid();
  delay(200);

  // Check for game over
  if (isGameOver()) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 10);
    display.print("Game Over");
    display.setTextSize(1);
    display.setCursor(10, 40);
    display.print("Score:");
    display.setCursor(60, 40);
    display.print(score);
    display.display();
    while (true); // Stop the game
  }
}

void initGame() {
  score = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      grid[i][j] = 0;
    }
  }
  addRandomTile();
  addRandomTile();
}

void addRandomTile() {
  int emptyTiles[16][2];
  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (grid[i][j] == 0) {
        emptyTiles[count][0] = i;
        emptyTiles[count][1] = j;
        count++;
      }
    }
  }
  if (count > 0) {
    int r = random(count);
    int x = emptyTiles[r][0];
    int y = emptyTiles[r][1];
    grid[x][y] = (random(10) == 0) ? 4 : 2;
  }
}

bool moveUp() {
  bool moved = false;
  for (int j = 0; j < 4; j++) {
    for (int i = 1; i < 4; i++) {
      if (grid[i][j] != 0) {
        int k = i;
        while (k > 0 && grid[k - 1][j] == 0) {
          grid[k - 1][j] = grid[k][j];
          grid[k][j] = 0;
          k--;
          moved = true;
        }
        if (k > 0 && grid[k - 1][j] == grid[k][j]) {
          grid[k - 1][j] *= 2;
          score += grid[k - 1][j]; // Update score
          grid[k][j] = 0;
          moved = true;
        }
      }
    }
  }
  return moved;
}

bool moveDown() {
  bool moved = false;
  for (int j = 0; j < 4; j++) {
    for (int i = 2; i >= 0; i--) {
      if (grid[i][j] != 0) {
        int k = i;
        while (k < 3 && grid[k + 1][j] == 0) {
          grid[k + 1][j] = grid[k][j];
          grid[k][j] = 0;
          k++;
          moved = true;
        }
        if (k < 3 && grid[k + 1][j] == grid[k][j]) {
          grid[k + 1][j] *= 2;
          score += grid[k + 1][j]; // Update score
          grid[k][j] = 0;
          moved = true;
        }
      }
    }
  }
  return moved;
}

bool moveLeft() {
  bool moved = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 1; j < 4; j++) {
      if (grid[i][j] != 0) {
        int k = j;
        while (k > 0 && grid[i][k - 1] == 0) {
          grid[i][k - 1] = grid[i][k];
          grid[i][k] = 0;
          k--;
          moved = true;
        }
        if (k > 0 && grid[i][k - 1] == grid[i][k]) {
          grid[i][k - 1] *= 2;
          score += grid[i][k - 1]; // Update score
          grid[i][k] = 0;
          moved = true;
        }
      }
    }
  }
  return moved;
}

bool moveRight() {
  bool moved = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 2; j >= 0; j--) {
      if (grid[i][j] != 0) {
        int k = j;
        while (k < 3 && grid[i][k + 1] == 0) {
          grid[i][k + 1] = grid[i][k];
          grid[i][k] = 0;
          k++;
          moved = true;
        }
        if (k < 3 && grid[i][k + 1] == grid[i][k]) {
          grid[i][k + 1] *= 2;
          score += grid[i][k + 1]; // Update score
          grid[i][k] = 0;
          moved = true;
        }
      }
    }
  }
  return moved;
}

void drawGrid() {
  display.clearDisplay();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      drawTile(i, j, grid[i][j]);
    }
  }
  display.display();
}

void drawTile(int row, int col, int value) {
  int x = col * 30 + 2;
  int y = row * 15 + 2;
  display.drawRect(x, y, 28, 13, SSD1306_WHITE);
  if (value != 0) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x + 5, y + 3);
    display.print(value);
  }
}

bool isGameOver() {
  // Check for any empty tile
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (grid[i][j] == 0) {
        return false;
      }
    }
  }

  // Check for any possible move
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((i > 0 && grid[i][j] == grid[i - 1][j]) || 
          (i < 3 && grid[i][j] == grid[i + 1][j]) || 
          (j > 0 && grid[i][j] == grid[i][j - 1]) || 
          (j < 3 && grid[i][j] == grid[i][j + 1])) {
        return false;
      }
    }
  }

  return true;
}

