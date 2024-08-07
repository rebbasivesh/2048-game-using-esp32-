# 2048-game-using-esp32-
2048 game for the ESP32 with an SSD1306 OLED display and 4 buttons for navigation

2048 is a popular single-player sliding block puzzle game where the objective is to combine numbered tiles on a grid to create a tile with the number 2048. Players move tiles in four directions (up, down, left, right), and when two tiles with the same number touch, they merge into one with their sum.

**Circuit:-**

![2048 CIRCUIT](https://github.com/user-attachments/assets/ea312c62-a9c1-49ef-b761-09ffd43713bb)

**Required Libraries:-**
<body>
    Adafruit GFX Library<br>
    Adafruit SSD1306<br>
    Button
</body>

**Wiring:-**
<body>
  
 **Connect the SSD1306 OLED display to the ESP32:** <br>
VCC to 3.3V<br>
GND to GND<br>
SCL to GPIO 22<br>
SDA to GPIO 21<br>
**Connect 4 buttons to GPIO pins** (with pull-up resistors):<br>
Button Up to GPIO 32<br>
Button Down to GPIO 33<br>
Button Left to GPIO 25<br>
Button Right to GPIO 26<br>
</body>
