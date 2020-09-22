/* Teensy Pinout
 * 0) TX1 'ESP8266'
 * 1) RX1 'ESP8266'
 * 2) LED Strip #1
 * 3) do not connect
 * 4) do not connect
 * 5) not used - LED panel #8
 * 6) LED panel #5
 * 7) LED panel #3
 * 8) LED panel #4
 * 9) 
 * 10) 
 * 11)  
 * 12) 
 * 13) LED
 * 14) LED panel #2
 * 15) -|
 * 16) -|
 * 17) 
 * 18) SDA0 I2C 'IMU'
 * 19) SCL0 I2C 'IMU'
 * 20) LED panel #6
 * 21) not used - LED panel #7
 * 22) 
 * 23) 
 * 
*/

//WS2812
#include <OctoWS2811.h>
const int ledsPerStrip = 64;
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
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
  int side;
};
static struct pixel_postions pixel_pos[512];
int side_order[6] = {1, 2, 6, 5, 3, 4};

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
  delay(500);

  //LED sides
  leds.begin();
  leds.show();
  
  //define locations of all leds on a unit cube
  cube_array();
  //define rainbow
  color_rainbow();
  
  delay(500);

  IMU_setup();
  calgyro();

  AHRSfilter.begin(23);

}
/////////////////////////////////////////////////////////////////////////////

int clr=0;
int cntr=0x21;

void loop() {

  //IMU and AHRS filter
  if(imuTime>43){
    //digitalWrite(ledPin, HIGH);
    imuTime=0;
    IMU_update();
    AHRS_update(); 
    //digitalWrite(ledPin, LOW);
    Serial.print(outPitch); Serial.print(", "); Serial.print(outRoll); Serial.print(", "); 
      Serial.print(outYaw); Serial.println(" "); 
    //Serial.print(Ux); Serial.print(", "); Serial.print(Uy); Serial.print(", "); 
    //  Serial.print(Uz); Serial.println(" "); 
  }

  if(ledTime >20){
    
    ledTime=0;
    digitalWrite(ledPin, HIGH);
    
    //color_by_pos();
    //if(charTime>250) {dispChar(cntr, clr, 4); charTime=0; cntr++; if(cntr==0x52) cntr=0x21;}

    side_by_num();

    clr = outYaw/2*(192.0f/180.0f);
    //full_solid(clr);

    //dispSprite(2, blue, 1);

    cntr++;
    //cntr=outYaw*(192.0f/180.0f);
    //rainbow_pattern(cntr);
      
    leds.show();
    digitalWrite(ledPin, LOW); 
  }
  
  //heartbeat and loop time control
  //digitalWrite(ledPin, HIGH); delay(1); digitalWrite(ledPin, LOW); delay(1);

  //stop loop
  //while(1);
  
}
