#include <Arduboy.h>

Arduboy arduboy;
// 128x64

byte x;
byte y;
byte xant;
byte yant;
byte vx;
byte vy;
byte vxant;
byte vyant;
int fx = 0;
int fy = 0;
int points = 1;
int best = 0;
long colfood;
long rowfood;
int tail[101][2];
int itail = 0;
bool booltail = false;
bool walls = true;
#define X_MAX (WIDTH - 10)
#define Y_MAX (HEIGHT - 12)



void foodLocation(int & fx, int & fy) {
  int cols = (WIDTH - 5) / 6;
  int rows = (HEIGHT - 4) / 6;
  colfood = random(3, cols);
  rowfood = random(1, rows) - 1;
  fx = colfood * 6 + 5 + 1;
  fy = rowfood * 6 + 4 + 1;
}

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(10);

  foodLocation(fx, fy);
  x = (128 / 2) - 4;
  y = (64 / 2) - 3;
  vx = 0;
  vy = 0;
}

void loop() {
  arduboy.clear();

  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;;

  if (yant != y || xant != x) {
    yant = y;
    xant = x;
    booltail = true;
  }else{booltail = false;}

  if(walls){
    if ( y <= 5) {
      vy = 0;
    }
    if (x <= 18) {
      vx = 0;
    }
    if (x >= X_MAX) {
      vx = 0;
    }
    if (y >= Y_MAX) {
      vy = 0;
    }
  }else{
    if (x <= 15) {
      x = 120;
    }
    if (x >= 122) {
      x = 18;
    }
    if (y >= 55) {
      y = 5;
    }
    if ( y <= 4) {
      y = 53;
    }
    if (fx == x && fy == y) {
    foodLocation(fx, fy);
    points++;

    }
  }
  arduboy.fillRect(x, y, 6, 6, 1);

  if (arduboy.pressed(B_BUTTON)) {
    if(walls){
    walls = false;
    }else{
    walls = true;}
  }
  
  if (arduboy.pressed(A_BUTTON)) {
    vx = 0;
    vy = 0;
  }
  if (vx == 0) {
    if (arduboy.pressed(RIGHT_BUTTON)) {
      vx = 3;
      vy = 0;
    }
    if (arduboy.pressed(LEFT_BUTTON)) {
      vx = -3;
      vy = 0;
    }
  }
  if (vy == 0) {
    if ((arduboy.pressed(UP_BUTTON))) {
      vy = -3;
      vx = 0;
    }
    if ((arduboy.pressed(DOWN_BUTTON))) {
      vy = 3;
      vx = 0;
    }
  }
  
  if(booltail && points>0){
    for (int i = 0; i < points; i++) {
        tail[i][0] = tail[i + 1][0];
        tail[i][1] = tail[i + 1][1];
    }
    tail[points - 1][0] = x;
    tail[points - 1][1] = y;
  }

  if(vx==3){
    arduboy.drawLine(x+6, y+2, x+7, y+2, 2);
    arduboy.drawLine(x+6, y+3, x+7, y+3, 2);
  }
  if(vx>100){
    arduboy.drawLine(x, y+2, x-2, y+2, 2);
    arduboy.drawLine(x, y+3, x-2, y+3, 2);
  }
  if(vy==3){
    arduboy.drawLine(x,y, x+3, y+7, 2);
    arduboy.drawLine(x,y, x+2, y+7, 2);
  }
  if(vy>100){
    arduboy.drawLine(x+3, y, x+3, y-2, 2);
    arduboy.drawLine(x+2, y, x+2, y-2, 2);
  }
  
  x = x + vx;
  y = y + vy;

  
  
  if (fx == x && fy == y) {
    foodLocation(fx, fy);
    points++;

  }

  for (int i = 0; i < points; i++) {
    if(tail[i][0] == x && tail[i][1] == y){
      memset(tail,0,sizeof(tail));
      if(best<points-1){
        best =  points - 1;
      }
      points = 1;
      x = (128 / 2) - 4;
      y = (64 / 2) - 3;
      vx = 0;
      vy = 0;
    }
    
    arduboy.fillRect(tail[i][0]+1, tail[i][1]+1, 4, 4, 2);
  }


  arduboy.fillRect(fx + 1, fy + 1, 4, 4, 2);
  arduboy.drawRect(0, 0, 17, 64, 1);
  arduboy.drawRect(0, 0, 128, 64, 1);
  arduboy.drawRect(0, 1, 128, 62, 1);
  arduboy.drawRect(0, 2, 128, 60, 1);
  arduboy.drawRect(0, 3, 128, 58, 1);
  arduboy.setCursor(6, 5);
  arduboy.setTextSize(1);
  arduboy.print(F("W"));
  if(walls){
    arduboy.setCursor(6, 14);
    arduboy.setTextSize(1);
    arduboy.print(F("t"));
  }else{
    arduboy.setCursor(6, 14);
    arduboy.setTextSize(1);
    arduboy.print(F("f"));
  }
  arduboy.setCursor(6, 23);
  arduboy.setTextSize(1);
  arduboy.print(F("P"));
  arduboy.setCursor(3, 33);
  arduboy.setTextSize(1);
  arduboy.print(points - 1);
  arduboy.setCursor(6, 42);
  arduboy.setTextSize(1);
  arduboy.print(F("B"));
  if ( y > 254) {
      y = 53;
  }
  arduboy.setCursor(3, 52);
  arduboy.setTextSize(1);
  arduboy.print(best);

  arduboy.display();
}
