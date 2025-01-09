// LED cube 8x8 with WS2812B
// 01/08/2024
//
/* Teensy Pinout
 * 0) TX1 'ESP8266'
 * 1) RX1 'ESP8266'
 * 2) LED panel #1 (+Z, top, 1, 128:191)
 * 3) do not connect
 * 4) do not connect
 * 5) not used - LED panel #8
 * 6) LED panel #5 (-Z, bottom, 5,128:191)
 * 7) LED panel #3 (+X, right, 4, 320:383)
 * 8) LED panel #4 (-X, left, 3, 256:319)
 * 9) 
 * 10) 
 * 11)  
 * 12) 
 * 13) LED
 * 14) LED panel #2 (+Y, front, 6, 192:255)
 * 15) -|
 * 16) -|
 * 17) 
 * 18) SDA0 I2C 'IMU'
 * 19) SCL0 I2C 'IMU'
 * 20) LED panel #6 (-Y, back, 2, 64:127)
 * 21) not used - LED panel #7
 * 22) 
 * 23) Demo Button
 * 
*/

//WS2812
#include <OctoWS2811.h>
const int ledsPerStrip = 64;
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
#define RED    0x0F0000
#define GREEN  0x000F00
#define BLUE   0x00000F
#define YELLOW 0x0F0F00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
#define red    0
#define green  64
#define blue   128
#define yellow 32
#define pink   160
#define orange 16
#define ledPin 13

//led postion structure
struct pixel_postions{
  float x, y, z;
  int xi, yi, zi;
  int side; };
static struct pixel_postions pixel_pos[512];
int side_order[6] = {1, 2, 6, 5, 3, 4};
int x_wrap[32][8];
int y_wrap[32][8];
int z_wrap[32][8];
 int zout1[28] = {0, 1, 2, 3, 4, 5,6 ,7, 
               15, 23, 31, 39, 47, 55, 63,
               62, 61, 60, 59, 58, 57, 56,
               48, 40, 32, 24, 16, 8};
  int zout2[20] = {9, 10, 11, 12, 13, 14, 
                   22, 30, 38, 46, 54, 
                   53, 52, 51, 50, 49, 
                   41, 33, 25, 17};

//led color rainbow structure
struct rainbow{
  char r,g,b;
};
struct rainbow colorc[192];

//custom sprite global
char sprite[64]={ 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0 };

//font ROM 8x8
#include"fontrom.h"

//IMU
//The SFE_LSM9DS1 library requires both Wire and SPI be
//included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SparkFunLSM9DS1.h>
LSM9DS1 imu;
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M 0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW
int gxbias = 0, gybias = 0, gzbias =0;

//AHRS
#include <MadgwickAHRS.h>
Madgwick AHRSfilter;
long axi, ayi, azi;
float Ax, Ay, Az;
float Gx, Gy, Gz;
float outRoll, outPitch, outYaw;
float Ux, Uy, Uz;    //Unit Vector

//Timers
elapsedMillis charTime;
elapsedMillis imuTime;
elapsedMillis ledTime;

/////////////////////////////////////////////////////////////////////////////////

void setup() {

  //LED pin
  pinMode(ledPin, OUTPUT);  
  //Demo Button
  pinMode(23, INPUT_PULLUP);

  //LED sides
  leds.begin();
  leds.show();
    
  //define locations of all leds on a unit cube
  cube_array();
  //define rainbow
  color_rainbow();
    
  IMU_setup();
  calgyro();
  AHRSfilter.begin(23);

  //int idx;
  //for(idx=0; idx<384; idx++) {leds.setPixel(idx,0);} //clear cube
  full_side(red,    0.1f, 1);
  full_side(green,  0.1f, 2);
  full_side(blue,   0.1f, 3);
  full_side(pink,   0.1f, 4);
  full_side(orange, 0.1f, 5);
  full_side(yellow, 0.1f, 6);
  leds.show();
  delay(10);
  
}
/////////////////////////////////////////////////////////////////////////////

int clr=0, clr1=0, clr2=0, clr3=0;
int cntr=0x21;
int idx1=1;
float idx2=1.0;
float b1=1.0;
int boo=1;
int demo_num=6;
void loop() {

  //Update IMU and AHRS filter
  if(imuTime>43){
    //digitalWrite(ledPin, HIGH);
    imuTime=0;
    IMU_update();
    AHRS_update(); 
    //digitalWrite(ledPin, LOW);
    //Serial.print(outPitch); Serial.print(", "); Serial.print(outRoll); Serial.print(", "); 
    //  Serial.print(outYaw); Serial.println(" "); 
    //Serial.print(Ux); Serial.print(", "); Serial.print(Uy); Serial.print(", "); 
    //  Serial.print(Uz); Serial.println(" "); 
  }

  //Update LED Display
  if(ledTime >50){
    
    ledTime=0;
    digitalWrite(ledPin, HIGH);

    // select demo to run
    if(demo_num==6){
      demo6();}
    if(demo_num==5){
      demo5_SpinSides();}
    else if(demo_num==4){
      demo4_RotSides();}
    else if(demo_num==3){
      demo3_RotColor();}
    else if(demo_num==2){
      demo2_AccFade(1);}
    else if(demo_num==1){
      demo1_axisDir();}
    
    //color_by_pos();
    //if(charTime>250) {dispChar(cntr, clr, 4); charTime=0; cntr++; if(cntr==0x52) cntr=0x21;}
        
    //cntr=pixel_pos[300].xi;
        
    //cntr++;
    //cntr=outYaw*(192.0f/180.0f);
    //rainbow_pattern(cntr);
      
    leds.show();
    digitalWrite(ledPin, LOW); 
  }

  //Change demo on button press
  if(digitalRead(23)==LOW){
    while(digitalRead(23)==LOW){}
    demo_num++;
      full_side(red,    0.1f, 1);
      full_side(green,  0.1f, 2);
      full_side(blue,   0.1f, 3);
      full_side(pink,   0.1f, 4);
      full_side(orange, 0.1f, 5);
      full_side(yellow, 0.1f, 6);
    if(demo_num>6){demo_num=1;}
  }
  
}
