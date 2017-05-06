#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Servo.h"
#include "LedControl.h"

SoftwareSerial mySoftwareSerial(8, 9); // TX, RX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

// Announce joystick control pin
int joyX = 0;
int joyY = 1;
int xjoyVal, yjoyVal;
int joyX_mp3 = 2;
int joyY_mp3 = 3;
const int joyZ_mp3 = 6;

// Count second
int timeCount = 0;
int count_time = 0;

Servo servo_head;
Servo servo_base;

// LED control
LedControl lc=LedControl(12,4,5,2);  // Pins: DIN,CLK,CS, # of Display connected
unsigned long delayTime=200;  // Delay between Frames

// LED display
byte smile1[] = {
  B00000000,
  B00001000,
  B00001000,
  B10000010,
  B10000001,
  B10100001,
  B00000001,
  B00000001};
   
byte smile2[] = {
  B00000001,
  B00000001,
  B10100001,
  B10000001,
  B10000010,
  B00001000,
  B00001000,
  B00000000};

byte neutral1[] = {
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B10110010,
  B10110010,
  B00000010,
  B00000010};

byte neutral2[] = {
  B00000010,
  B00000010,
  B10110010,
  B10110010,
  B10000000,
  B00000000,
  B00000000,
  B00000000};

byte angry1[] = {
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B01000000,
  B01010001,
  B00000010,
  B00000100};

byte angry2[] = {
  B00000100,
  B00000010,
  B01010001,
  B01000000,
  B10000000,
  B00000000,
  B00000000,
  B00000000};

byte happy_a1[] = {
  B00000100,
  B00000100,
  B00000000,
  B10010000,
  B10100010,
  B10010001,
  B00000001,
  B00000001}; 
  
byte happy_b1[] = {
  B00000100,
  B00000100,
  B00000000,
  B10010000,
  B10100010,
  B10010011,
  B00000011,
  B00000011};
  
byte happy_a2[] = {
  B00000001,
  B00000001,
  B10010001,
  B10100010,
  B10010000,
  B00000000,
  B00000100,
  B00000100};
  
byte happy_b2[] = {
  B00000011,
  B00000011,
  B10010011,
  B10100010,
  B10010000,
  B00000000,
  B00000100,
  B00000100};

byte sad_a1[] = {
  B00000000,
  B00000000,
  B00001000,
  B10100000,
  B10010000,
  B10100001,
  B00000010,
  B00000010};

byte sad_b1[] = {
  B00000000,
  B00000000,
  B00000100,
  B10100000,
  B10010000,
  B10100001,
  B00000010,
  B00000010};

byte sad_c1[] = {
  B00000000,
  B00000000,
  B00000010,
  B10100000,
  B10010000,
  B10100001,
  B00000010,
  B00000010};

byte sad_a2[] = {
  B00000010,
  B00000010,
  B10100001,
  B10010000,
  B10100000,
  B00001000,
  B00000000,
  B00000000};

byte sad_b2[] = {
  B00000010,
  B00000010,
  B10100001,
  B10010000,
  B10100000,
  B00000100,
  B00000000,
  B00000000};

byte sad_c2[] = {
  B00000010,
  B00000010,
  B10100001,
  B10010000,
  B10100000,
  B00000010,
  B00000000,
  B00000000};

byte frame1_1[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame2_1[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_2[] = {
  B01111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_2[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_3[] = {
  B00100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_3[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_4[] = {
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_4[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_5[] = {
  B00001000,
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_5[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_6[] = {
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_6[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_7[] = {
  B01111110,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B00000000};
  
byte frame2_7[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_8[] = {
  B00000000,
  B01111110,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110,
  B00000000};
  
byte frame2_8[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_9[] = {
  B01111110,
  B00000000,
  B01111110,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110};
byte frame2_9[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_10[] = {
  B01010010,
  B01111110,
  B00000000,
  B01111110,
  B00000100,
  B00001000,
  B00010000,
  B00100000};
byte frame2_10[] = {
  B01111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_11[] = {
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111110,
  B00000100,
  B00001000,
  B00010000};
byte frame2_11[] = {
  B00100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_12[] = {
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111110,
  B00000100,
  B00001000};
byte frame2_12[] = {
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_13[] = {
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111110,
  B00000100};
byte frame2_13[] = {
  B00001000,
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte frame1_14[] = {
  B01111110,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111110};
  
byte frame2_14[] = {
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000};

byte frame1_15[] = {
  B01010000,
  B01111110,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000};
  
byte frame2_15[] = {
  B01111110,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110,
  B00000000,
  B00000000};

byte frame1_16[] = {
  B01010000,
  B01010000,
  B01111110,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110};
  
byte frame2_16[] = {
  B00000000,
  B01111110,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110,
  B00000000};

byte frame1_17[] = {
  B01111110,
  B01010000,
  B01010000,
  B01111110,
  B00000000,
  B01010010,
  B01010010,
  B01010010};
  
byte frame2_17[] = {
  B01111110,
  B00000000,
  B01111110,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01111110};

byte frame1_18[] = {
  B00000000,
  B01111110,
  B01010000,
  B01010000,
  B01111110,
  B00000000,
  B01010010,
  B01010010};
  
byte frame2_18[] = {
  B01010010,
  B01111110,
  B00000000,
  B01111110,
  B00000100,
  B00001000,
  B00010000,
  B00100000};

byte frame1_19[] = {
  B01111000,
  B00000000,
  B01111110,
  B01010000,
  B01010000,
  B01111110,
  B00000000,
  B01010010};
  
byte frame2_19[] = {
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111110,
  B00000100,
  B00001000,
  B00010000};

byte frame1_20[] = {
  B00000100,
  B01111000,
  B00000000,
  B01111110,
  B01010000,
  B01010000,
  B01111110,
  B00000000};
  
byte frame2_20[] = {
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111110,
  B00000100,
  B00001000};

byte frame1_21[] = {
  B00000010,
  B00000100,
  B01111000,
  B00000000,
  B01111110,
  B01010000,
  B01010000,
  B01111110};
byte frame2_21[] = {
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111110,
  B00000100};

byte frame1_22[] = {
  B00000100,
  B00000010,
  B00000100,
  B01111000,
  B00000000,
  B01111110,
  B01010000,
  B01010000};
  
byte frame2_22[] = {
  B01111110,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111110};

byte frame1_23[] = {
  B01111000,
  B00000100,
  B00000010,
  B00000100,
  B01111000,
  B00000000,
  B01111110,
  B01010000};
  
byte frame2_23[] = {
  B01010000,
  B01111110,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000};

byte frame1_24[] = {
  B00000000,
  B01111000,
  B00000100,
  B00000010,
  B00000100,
  B01111000,
  B00000000,
  B01111110};
  
byte frame2_24[] = {
  B01010000,
  B01010000,
  B01111110,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110};

byte frame1_25[] = {
  B01111110,
  B00000000,
  B01111000,
  B00000100,
  B00000010,
  B00000100,
  B01111000,
  B00000000};
byte frame2_25[] = {
  B01111110,
  B01010000,
  B01010000,
  B01111110,
  B00000000,
  B01010010,
  B01010010,
  B01010010};

byte frame1_26[] = {
  B01010010,
  B01111110,
  B00000000,
  B01111000,
  B00000100,
  B00000010,
  B00000100,
  B01111000};
  
byte frame2_26[] = {
  B00000000,
  B01111110,
  B01010000,
  B01010000,
  B01111110,
  B00000000,
  B01010010,
  B01010010};

byte frame1_27[] = {
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111000,
  B00000100,
  B00000010,
  B00000100};
  
byte frame2_27[] = {
  B01111000,
  B00000000,
  B01111110,
  B01010000,
  B01010000,
  B01111110,
  B00000000,
  B01010010};

byte frame1_28[] = {
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111000,
  B00000100,
  B00000010};
  
byte frame2_28[] = {
  B00000100,
  B01111000,
  B00000000,
  B01111110,
  B01010000,
  B01010000,
  B01111110,
  B00000000};

byte frame1_29[] = {
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111000,
  B00000100};
byte frame2_29[] = {
  B00000010,
  B00000100,
  B01111000,
  B00000000,
  B01111110,
  B01010000,
  B01010000,
  B01111110};

byte frame1_30[] = {
  B00000000,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111000};
  
byte frame2_30[] = {
  B00000100,
  B00000010,
  B00000100,
  B01111000,
  B00000000,
  B01111110,
  B01010000,
  B01010000};

byte frame1_31[] = {
  B00000000,
  B00000000,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000};
  
byte frame2_31[] = {
  B01111000,
  B00000100,
  B00000010,
  B00000100,
  B01111000,
  B00000000,
  B01111110,
  B01010000};

byte frame1_32[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110};
byte frame2_32[] = {
  B00000000,
  B01111000,
  B00000100,
  B00000010,
  B00000100,
  B01111000,
  B00000000,
  B01111110};

byte frame1_33[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01010010,
  B01010010,
  B01010010};
byte frame2_33[] = {
  B01111110,
  B00000000,
  B01111000,
  B00000100,
  B00000010,
  B00000100,
  B01111000,
  B00000000};

byte frame1_34[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01010010,
  B01010010};
  
byte frame2_34[] = {
  B01010010,
  B01111110,
  B00000000,
  B01111000,
  B00000100,
  B00000010,
  B00000100,
  B01111000};

byte frame1_35[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01010010};
byte frame2_35[] = {
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111000,
  B00000100,
  B00000010,
  B00000100};

byte frame1_36[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_36[] = {
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111000,
  B00000100,
  B00000010};

byte frame1_37[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
byte frame2_37[] = {
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111000,
  B00000100};

byte frame1_38[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_38[] = {
  B00000000,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000,
  B01111000};

byte frame1_39[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_39[] = {
  B00000000,
  B00000000,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110,
  B00000000};

byte frame1_40[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_40[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01010010,
  B01010010,
  B01010010,
  B01111110};

byte frame1_41[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_41[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01010010,
  B01010010,
  B01010010};

byte frame1_42[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
byte frame2_42[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01010010,
  B01010010};

byte frame1_43[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
  
byte frame2_43[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01010010};

byte frame1_44[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};
byte frame2_44[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000};

byte sing_a1[] = {
  B00001000,
  B01010000,
  B00011100,
  B00000100,
  B00100000,
  B01000000,
  B00100110,
  B00001001};
byte sing_a2[] = {
  B00001001,
  B00100110,
  B01000000,
  B00100101,
  B00001000,
  B00001110,
  B11100010,
  B00100000};

byte sing_b1[] = {
  B00000000,
  B00111000,
  B00001000,
  B00000010,
  B00100000,
  B01000000,
  B00100110,
  B00001001};
byte sing_b2[] = {
  B00001001,
  B00100110,
  B01000000,
  B00100001,
  B00001000,
  B01010000,
  B00011100,
  B00000101};

byte sing_c1[] = {
  B01000000,
  B00000100,
  B00101000,
  B00001110,
  B00100010,
  B01000000,
  B00100110,
  B00001001};
byte sing_c2[] = {
  B00001001,
  B00100110,
  B01000000,
  B00101110,
  B00000010,
  B11100000,
  B00101000,
  B00000010};

//Annouce functions
void shappy_a1();
void shappy_a2();
void shappy_b1();
void shappy_b2();
void ssmile1();
void ssmile2();
void sneutral1();
void sneutral2();
void ssad_a1();
void ssad_a2();
void ssad_b1();
void ssad_b2();
void ssad_c1();
void ssad_c2();
void sangry1();
void sangry2();

void neave_display();

void sframe1_1();
void sframe2_1();

void sframe1_2();
void sframe2_2();

void sframe1_3();
void sframe2_3();

void sframe1_4();
void sframe2_4();

void sframe1_5();
void sframe2_5();

void sframe1_6();
void sframe2_6();

void sframe1_7();
void sframe2_7();

void sframe1_8();
void sframe2_8();

void sframe1_9();
void sframe2_9();

void sframe1_10();
void sframe2_10();

void sframe1_11();
void sframe2_11();

void sframe1_12();
void sframe2_12();

void sframe1_13();
void sframe2_13();

void sframe1_14();
void sframe2_14();

void sframe1_15();
void sframe2_15();

void sframe1_16();
void sframe2_16();

void sframe1_17();
void sframe2_17();

void sframe1_18();
void sframe2_18();

void sframe1_19();
void sframe2_19();

void sframe1_20();
void sframe2_20();

void sframe1_21();
void sframe2_21();

void sframe1_22();
void sframe2_22();

void sframe1_23();
void sframe2_23();

void sframe1_24();
void sframe2_24();

void sframe1_25();
void sframe2_25();

void sframe1_26();
void sframe2_26();

void sframe1_27();
void sframe2_27();

void sframe1_28();
void sframe2_28();

void sframe1_29();
void sframe2_29();

void sframe1_30();
void sframe2_30();

void sframe1_31();
void sframe2_31();

void sframe1_32();
void sframe2_32();

void sframe1_33();
void sframe2_33();

void sframe1_34();
void sframe2_34();

void sframe1_35();
void sframe2_35();

void sframe1_36();
void sframe2_36();

void sframe1_37();
void sframe2_37();

void sframe1_38();
void sframe2_38();

void sframe1_39();
void sframe2_39();

void sframe1_40();
void sframe2_40();

void sframe1_41();
void sframe2_41();

void sframe1_42();
void sframe2_42();

void sframe1_43();
void sframe2_43();

void sframe1_44();
void sframe2_44();

void ssing_a1();
void ssing_a2();
void ssing_b1();
void ssing_b2();
void ssing_c1();
void ssing_c2();

void servo_headGo(byte finalAngle);
void servo_baseGo(byte finalAngle);

int joystick_servo(int timeCount);

void mp3_player();

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  pinMode(joyZ_mp3, INPUT);
  
  Serial.println();
  Serial.println(F("NeaveRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  // Set volume
  myDFPlayer.volume(25);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down

  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  
  // Set device, we use SD as default
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  // Read imformation
  Serial.println(myDFPlayer.readState()); //read mp3 state

  // Annouce servos pin
  servo_head.attach(2);
  servo_base.attach(3);

  // LED set
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,5);  // Set intensity levels
  lc.setIntensity(1,5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);

  servo_headGo(0);
  servo_baseGo(120);
  
  myDFPlayer.playFolder(15, 0); //play start music

  // Display the name "NEAVE"
  neave_display();

  digitalWrite(joyZ_mp3, HIGH);

}

int count_mp3=-1;

void loop()
{
  delay(5);
  
  int count, checktimeCount=timeCount;
  count = checktimeCount-timeCount;

  for(int i=0; i<5;i++){
  Serial.println();
  Serial.print("timeCount f1 : ");
  Serial.print(timeCount);
  timeCount = joystick_servo(timeCount);
  Serial.println();
  Serial.print("timeCount f2 : ");
  Serial.print(timeCount);
  
  // Display LED and play the sound, check if joystick is moved or not. If moved, play the sound and display singing face
  if(timeCount <  2) {
    // Happy
    shappy_a1();
    shappy_a2();
    delay(delayTime);
    shappy_b1();
    shappy_b2();
    delay(delayTime);
    myDFPlayer.playFolder(15, 1);
    count_time = joystick_servo(timeCount);
    delay(6000); // music 6 second
    count_time = joystick_servo(timeCount);
    Serial.println();
    Serial.println("Happy");
    Serial.print("joyz : ");
    count_time = digitalRead(joyZ_mp3);
    Serial.print(count_mp3);
    if (analogRead(joyY_mp3) > 650 || analogRead(joyY_mp3) < 450 || analogRead(joyX_mp3) > 900 || analogRead(joyX_mp3) < 300 || digitalRead(joyZ_mp3)==0){
    mp3_player();
    }
  } 
  else if (timeCount <  3) {
    // Smile
    ssmile1();
    ssmile2();
    delay(delayTime);
    myDFPlayer.playFolder(15, 2);
    count_time = joystick_servo(timeCount);
    delay(6000);
    count_time = joystick_servo(timeCount);
    Serial.println();
    Serial.println("Smile");
    if (analogRead(joyY_mp3) > 650 || analogRead(joyY_mp3) < 450 || analogRead(joyX_mp3) > 900 || analogRead(joyX_mp3) < 300 || digitalRead(joyZ_mp3)==0){
    mp3_player();
    }
  } 
  else if (timeCount <  4) {
    // Neutral
    sneutral1();
    sneutral2();
    delay(delayTime);
    myDFPlayer.playFolder(15, 3);
    count_time = joystick_servo(timeCount);
    delay(6000); // music 6 second
    count_time = joystick_servo(timeCount);
    Serial.println();
    Serial.println("Neutral");
    if (analogRead(joyY_mp3) > 650 || analogRead(joyY_mp3) < 450 || analogRead(joyX_mp3) > 900 || analogRead(joyX_mp3) < 300 || digitalRead(joyZ_mp3)==0){
    mp3_player();
    }
  } 
  else if (timeCount <  5) {
    // Sad
    ssad_a1();
    ssad_a2();
    delay(delayTime);
    ssad_b1();
    ssad_b2();
    delay(delayTime);
    ssad_c1();
    ssad_c2();
    delay(delayTime);
    myDFPlayer.playFolder(15, 4);
    count_time = joystick_servo(timeCount);
    delay(6000); // music 6 second
    count_time = joystick_servo(timeCount);
    Serial.println();
    Serial.println("sad");
    if (analogRead(joyY_mp3) > 650 || analogRead(joyY_mp3) < 450 || analogRead(joyX_mp3) > 900 || analogRead(joyX_mp3) < 300 || digitalRead(joyZ_mp3)==0){
    mp3_player();
    }
  } 
  else if (timeCount <  6) {
    // Angry
    sangry1();
    sangry2();
    delay(delayTime);
    myDFPlayer.playFolder(15, 5);
    count_time = joystick_servo(timeCount);
    delay(6000); // music 6 second
    count_time = joystick_servo(timeCount);
    Serial.println();
    Serial.println("Angry");
    if (analogRead(joyY_mp3) > 650 || analogRead(joyY_mp3) < 450 || analogRead(joyX_mp3) > 900 || analogRead(joyX_mp3) < 300 || digitalRead(joyZ_mp3)==0){
    mp3_player();
    }
  }
  else{
    timeCount = 4;
  }
}
  if (count == 0){
    timeCount = timeCount + 1;
  }
  
  // Check MP3 joystick, if moved, servos will move.
  if (analogRead(joyY_mp3) > 650 || analogRead(joyY_mp3) < 450 || analogRead(joyX_mp3) > 900 || analogRead(joyX_mp3) < 300 || digitalRead(joyZ_mp3)==0){
    mp3_player();
    }
  if(timeCount==1){
  servo_headGo(10);
  delay(500);
  servo_baseGo(170);
  delay(500);
  }
  else if(timeCount%2==0){
  servo_headGo(0);
  delay(500);
  servo_baseGo(140);
  delay(500);
  }
  else{
  servo_headGo(10);
  delay(500);
  servo_baseGo(85);
  delay(500);
  }
}

// Check micro SD card
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

// Play sounds
void mp3_player(){
  static unsigned long timer = millis();
  myDFPlayer.playFolder(15, 6); // play mp3 folder 15 file name 006
  Serial.println("mp3 before loop");
  while(true){
    // Display singing face
    ssing_a1();
    ssing_a2();
    delay(200);
    ssing_b1();
    ssing_b2();
    delay(200);
    ssing_c1();
    ssing_c2();
    delay(200);
    
  // check status joystick control mp3
  if (analogRead(joyX_mp3) > 900){
    Serial.println("next");
    myDFPlayer.next();
    }
  else if (analogRead(joyX_mp3) < 350){
    Serial.println("previous");
    myDFPlayer.previous();
    }
  if (analogRead(joyY_mp3) > 600 || analogRead(joyY_mp3) < 450){
    if (analogRead(joyY_mp3) < 450){
      Serial.println("up");
      myDFPlayer.volumeUp();
      }
    else if (analogRead(joyY_mp3) > 650) {
      Serial.println();
      Serial.print("down : ");
      Serial.print(analogRead(joyY_mp3));
      myDFPlayer.volumeDown();
      }
    }
    
   if (millis() - timer > 60000 || digitalRead(joyZ_mp3)==LOW) {
    timer = millis();
    Serial.println("BREAK");
    break;
    }
  }
 }


// Move the base
void servo_baseGo(int finalAngle){
   int currentAngle = servo_base.read();   //servo position
   if (finalAngle > currentAngle) {
   Serial.println();
   Serial.print("base : ");
   Serial.print(currentAngle);
    for (int i = currentAngle; i < finalAngle ; i++){
     servo_base.write(i); 
     delay(10);   
     } 
   }
   else {
   for (int i = currentAngle; i > finalAngle ; i--){
     servo_base.write(i); 
     delay(10);   
     } 
   }
}

// Move the head
void servo_headGo(int finalAngle){
   int currentAngle = servo_head.read();   //servo position
   if (finalAngle > currentAngle) {
    Serial.println();
   Serial.print("head : ");
   Serial.print(currentAngle);
    for (int i = currentAngle; i < finalAngle ; i++){
     servo_head.write(i); 
     delay(20);   
     } 
   }
   else {
   for (int i = currentAngle; i > finalAngle ; i--){
     servo_head.write(i); 
     delay(20);   
     } 
   }
}

// Move servos by a joystick
int joystick_servo(int timeCount) {
  // minus timeCount by count var.
  int count = 0;
  
  xjoyVal = analogRead(joyX);

  // check status joystick
  if(xjoyVal > 600 || xjoyVal < 400){
    Serial.println();
    Serial.print("joyx : ");
    count = 1;
    xjoyVal = map(xjoyVal, 0, 1023, 0, 180);
    Serial.print(xjoyVal);
    servo_base.write(xjoyVal);
  }
  
  yjoyVal = analogRead(joyY);

  // check status joystick
  if(yjoyVal > 600 || yjoyVal < 400){
    Serial.println();
    Serial.print("joyy: ");
      count = 1;
      yjoyVal = map(yjoyVal, 0, 1023, 0, 180);
      Serial.print(yjoyVal);
      servo_base.write(yjoyVal);
    }
  if(timeCount<1){
    count = 0;
  }
  delay(150);
  Serial.println();
  Serial.print("joy servo timecount : ");
  Serial.print(timeCount);
  return (timeCount-count);
}


// Display faces on LED
void ssmile1(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,smile1[i]);
  }
}

void ssmile2(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(1,i,smile2[i]);
  }
}

void sneutral1(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,neutral1[i]);
  }
}

void sneutral2(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(1,i,neutral2[i]);
  }
}

void sangry1(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,angry1[i]);
  }
}

void sangry2(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(1,i,angry2[i]);
  }
}

void shappy_a1(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,happy_a1[i]);
  }
}

void shappy_b1(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,happy_b1[i]);
  }
}

void shappy_a2(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(1,i,happy_a2[i]);
  }
}

void shappy_b2(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(1,i,happy_b2[i]);
  }
}

void ssad_a1(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,sad_a1[i]);
  }
}

void ssad_b1(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,sad_b1[i]);
  }
}

void ssad_c1(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(0,i,sad_c1[i]);
  }
}

void ssad_a2(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(1,i,sad_a2[i]);
  }
}

void ssad_b2(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(1,i,sad_b2[i]);
  }
}

void ssad_c2(){
  for (int i = 0; i < 8; i++) {
    lc.setRow(1,i,sad_c2[i]);
  }
}

void sframe1_1(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_1[i]);
  }
}
void sframe1_2(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_2[i]);
  }
}
void sframe1_3(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_3[i]);
  }
}
void sframe1_4(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_4[i]);
  }
}
void sframe1_5(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_5[i]);
  }
}
void sframe1_6(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_6[i]);
  }
}
void sframe1_7(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_7[i]);
  }
}
void sframe1_8(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_8[i]);
  }
}
void sframe1_9(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_9[i]);
  }
}
void sframe1_10(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_10[i]);
  }
}
void sframe1_11(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_11[i]);
  }
}
void sframe1_12(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_12[i]);
  }
}
void sframe1_13(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_13[i]);
  }
}
void sframe1_14(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_14[i]);
  }
}
void sframe1_15(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_15[i]);
  }
}
void sframe1_16(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_16[i]);
  }
}
void sframe1_17(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_17[i]);
  }
}
void sframe1_18(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_18[i]);
  }
}
void sframe1_19(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_19[i]);
  }
}
void sframe1_20(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_20[i]);
  }
}
void sframe1_21(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_21[i]);
  }
}
void sframe1_22(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_22[i]);
  }
}
void sframe1_23(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_23[i]);
  }
}
void sframe1_24(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_24[i]);
  }
}
void sframe1_25(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_25[i]);
  }
}
void sframe1_26(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_26[i]);
  }
}
void sframe1_27(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_27[i]);
  }
}
void sframe1_28(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_28[i]);
  }
}
void sframe1_29(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_29[i]);
  }
}
void sframe1_30(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_30[i]);
  }
}
void sframe1_31(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_31[i]);
  }
}
void sframe1_32(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_32[i]);
  }
}
void sframe1_33(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_33[i]);
  }
}
void sframe1_34(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_34[i]);
  }
}
void sframe1_35(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_35[i]);
  }
}
void sframe1_36(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_36[i]);
  }
}
void sframe1_37(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_37[i]);
  }
}
void sframe1_38(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_38[i]);
  }
}
void sframe1_39(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_39[i]);
  }
}
void sframe1_40(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_40[i]);
  }
}
void sframe1_41(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_41[i]);
  }
}
void sframe1_42(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_42[i]);
  }
}
void sframe1_43(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_43[i]);
  }
}
void sframe1_44(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame1_44[i]);
  }
}


void sframe2_1(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_1[i]);
  }
}
void sframe2_2(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_2[i]);
  }
}
void sframe2_3(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_3[i]);
  }
}
void sframe2_4(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_4[i]);
  }
}
void sframe2_5(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_5[i]);
  }
}
void sframe2_6(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_6[i]);
  }
}
void sframe2_7(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_7[i]);
  }
}
void sframe2_8(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_8[i]);
  }
}
void sframe2_9(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_9[i]);
  }
}
void sframe2_10(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_10[i]);
  }
}
void sframe2_11(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_11[i]);
  }
}
void sframe2_12(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_12[i]);
  }
}
void sframe2_13(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_13[i]);
  }
}
void sframe2_14(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_14[i]);
  }
}
void sframe2_15(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_15[i]);
  }
}
void sframe2_16(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_16[i]);
  }
}
void sframe2_17(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_17[i]);
  }
}
void sframe2_18(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_18[i]);
  }
}
void sframe2_19(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_19[i]);
  }
}
void sframe2_20(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_20[i]);
  }
}
void sframe2_21(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_21[i]);
  }
}
void sframe2_22(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_22[i]);
  }
}
void sframe2_23(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_23[i]);
  }
}
void sframe2_24(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_24[i]);
  }
}
void sframe2_25(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_25[i]);
  }
}
void sframe2_26(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_26[i]);
  }
}
void sframe2_27(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_27[i]);
  }
}
void sframe2_28(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_28[i]);
  }
}
void sframe2_29(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frame2_29[i]);
  }
}
void sframe2_30(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_30[i]);
  }
}
void sframe2_31(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_31[i]);
  }
}
void sframe2_32(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_32[i]);
  }
}
void sframe2_33(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_33[i]);
  }
}
void sframe2_34(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_34[i]);
  }
}
void sframe2_35(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_35[i]);
  }
}
void sframe2_36(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_36[i]);
  }
}
void sframe2_37(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_37[i]);
  }
}
void sframe2_38(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_38[i]);
  }
}
void sframe2_39(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_39[i]);
  }
}
void sframe2_40(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_40[i]);
  }
}
void sframe2_41(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_41[i]);
  }
}
void sframe2_42(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_42[i]);
  }
}
void sframe2_43(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_43[i]);
  }
}
void sframe2_44(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,frame2_44[i]);
  }
}

void neave_display(){
  sframe1_1();
  sframe2_1();
  delay(150);
  sframe1_2();
  sframe2_2();
  delay(150);
  sframe1_3();
  sframe2_3();
  delay(150);
  sframe1_4();
  sframe2_4();
  delay(150);
  sframe1_5();
  sframe2_5();
  delay(150);
  sframe1_6();
  sframe2_6();
  delay(150);
  sframe1_7();
  sframe2_7();
  delay(150);
  sframe1_8();
  sframe2_8();
  delay(150);
  sframe1_9();
  sframe2_9();
  delay(150);
  sframe1_10();
  sframe2_10();
  delay(150);
  sframe1_11();
  sframe2_11();
  delay(150);
  sframe1_12();
  sframe2_12();
  delay(150);
  sframe1_13();
  sframe2_13();
  delay(150);
  sframe1_14();
  sframe2_14();
  delay(150);
  sframe1_15();
  sframe2_15();
  delay(150);
  sframe1_16();
  sframe2_16();
  delay(150);
  sframe1_17();
  sframe2_17();
  delay(150);
  sframe1_18();
  sframe2_18();
  delay(150);
  sframe1_19();
  sframe2_19();
  delay(150);
  sframe1_20();
  sframe2_20();
  delay(150);
  sframe1_21();
  sframe2_21();
  delay(150);
  sframe1_22();
  sframe2_22();
  delay(150);
  sframe1_23();
  sframe2_23();
  delay(150);
  sframe1_24();
  sframe2_24();
  delay(150);
  sframe1_25();
  sframe2_25();
  delay(150);
  sframe1_26();
  sframe2_26();
  delay(150);
  sframe1_27();
  sframe2_27();
  delay(150);
  sframe1_28();
  sframe2_28();
  delay(150);
  sframe1_29();
  sframe2_29();
  delay(150);
  sframe1_30();
  sframe2_30();
  delay(150);
  sframe1_31();
  sframe2_31();
  delay(150);
  sframe1_32();
  sframe2_32();
  delay(150);
  sframe1_33();
  sframe2_33();
  delay(150);
  sframe1_34();
  sframe2_34();
  delay(150);
  sframe1_35();
  sframe2_35();
  delay(150);
  sframe1_36();
  sframe2_36();
  delay(150);
  sframe1_37();
  sframe2_37();
  delay(150);
  sframe1_38();
  sframe2_38();
  delay(150);
  sframe1_39();
  sframe2_39();
  delay(150);
  sframe1_40();
  sframe2_40();
  delay(150);
  sframe1_41();
  sframe2_41();
  delay(150);
  sframe1_42();
  sframe2_42();
  delay(150);
  sframe1_43();
  sframe2_43();
  delay(150);
  sframe1_44();
  sframe2_44();
  delay(150);
}

void ssing_a1(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,sing_a1[i]);
  }
}
void ssing_a2(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,sing_a2[i]);
  }
}
void ssing_b1(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,sing_b1[i]);
  }
}
void ssing_b2(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,sing_b2[i]);
  }
}
void ssing_c1(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,sing_c1[i]);
  }
}
void ssing_c2(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(1,i,sing_c2[i]);
  }
}
