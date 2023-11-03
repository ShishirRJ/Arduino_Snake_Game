# Snake Game with Arduino and Joystick

## Table of Contents:
* [Project Title](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#1-project-title)
* [Project Description](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#2-project-description)
* [Devices Used](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#3-devices-used)
* [Wiring Diagram](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#4-wiring-diagram)
* [Installation](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#5-installation)
* [How to Play](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#6-how-to-play)
* [Customization](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#7-customization)
* [Credits](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#8-credits)
* [License](https://github.com/ShishirRJ/Arduino_Snake_Game/blob/main/README.md#9-license)

### 1. Project Title
Snake Game using Arduino Controlled by Joystick

### 2. Project Description
A classic Snake game implemented on Arduino, controlled with an analog joystick and displayed on an LED matrix. Keep track of your score on a 7-segment display, and enjoy sound effects with a Piezo Buzzer.

### 3. Devices Used
To bring this Snake Game to life, we've utilized the following components:
**Arduino UNO**: The microcontroller used here is Arduino UNO. Arduino NANO will also work instead.

**LED Matrix with MAX7219 driver**: The game grid, snake, food, and obstacles are displayed here.

**Analog Joystick (Arduino Dual Axis JoyStick Module)**: Control the snake's movements (up, down, left, right) with this.

**Piezo Buzzer (YL-44)**: Experience an opening and closing tune when you start and end the game.

**7-Segment Display with TM1637 driver**: Keep track of your score throughout the game and display highscore.

**Potentiometer**: Adjust the game's difficulty by controlling the speed of the snake.

**Jumper cables and Resistors**: Used to connect the components to the breadboard and Arduino.

### 4. Wiring Diagram
|Device|Pin Number|
|---|---|
|Matrix CLK|5|
|Matrix CS|7|
|Matrix DIN|6|
|7 Segment Display DIO|11|
|7 Segment Display CLK|12|
|Piezo Buzzer|10|
|Joystick SW|2|
|Joystick X|A1|
|Joystick Y|A2|
|Potentiometer|A0|

### 5. Installation
#### **1. Hardware Setup:**
* Connect the LED Matrix (MAX7219) to your Arduino following manufacturer guidelines.
* Connect the Analog Joystick to your Arduino.
* Incorporate the Piezo Buzzer for sound effects.
* Display your score using the 7-Segment Display (TM1637).
* Use the Potentiometer to adjust the snake's speed.
#### **2. Software Setup:**
* Install the Arduino IDE if not already installed.
* Download the Snake Game code and upload it to your Arduino board.

### 6. How to Play
* Upon uploading the code to your Arduino, the game will begin, with an opening song played by the piezo buzzer.
* Use the joystick to guide the snake, collecting food represented as dots on the LED matrix.
* Each time the snake eats, it grows in length.
* Be cautious and avoid collisions the snake's own body, as this will terminate the game.
* Your score is displayed on the 7-segment display.
* The game ends with a closing song played by the piezo buzzer when you lose. You can restart the game by resetting the Arduino or by pressing the button on the Analog Joystick.

### 7. Customization
Feel free to personalize this project by modifying the code. Adjust the game's rules, add new features, or change the visuals and sounds to suit your preferences.

### 8. Credits
**LedControl Library**: Credit goes to Eberhard Fahle for developing the LedControl library, which makes it easy to control LED matrices.

**TM1637 Library**: We would like to express our gratitude to Avishay for the TM1637 library, which simplifies the use of 7-segment displays.

### 9. License
This project is open-source and distributed under the MIT License, which allows you to use, modify, and distribute the code while giving appropriate credit to the original work.

Enjoy playing your Snake Game with Arduino and Joystick!

### 10. Contributions
1. Shishir Ravi Jois (23EC01042) Github- ShishirRJ
2. B Ganesh (23EC01009) Github- BommisettyGanesh
3. Shrinivas B M (23EC01043) Github- Air-36
5. Sandeep K (23EC01041) Github- SandeepK2023
