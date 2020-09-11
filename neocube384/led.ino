
void dispChar(int code, int color, int side)
{
  for (int i=0; i < leds.numPixels(); i++) {
    if(pixel_pos[i].side==side) {
      if((font8x8[code][i/8]>>(i%8))&1) {leds.setPixel(i, colorc[color].r, colorc[color].g, colorc[color].b);}
      else leds.setPixel(i, 0, 0, 0);
      //Serial.println(i);
    }
  }
  leds.show();  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dispSprite(int num, int color, int side)
{
  load_sprite_ROM(num);
  for (int i=0; i < leds.numPixels(); i++) {
    if(pixel_pos[i].side==side) {
      if(sprite[i]==1) leds.setPixel(i, colorc[color].r, colorc[color].g, colorc[color].b);
      else leds.setPixel(i, 0, 0, 0);
    }
  }
  leds.show();  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void colorRotate(int color, int wait){
  for (int i=0; i < leds.numPixels(); i++) {
    //leds.setPixel(i, color);
    if(pixel_pos[i].side==1) {
      if((font8x8[51][i/8]>>(i%8))&1) leds.setPixel(i, colorc[color].r, colorc[color].g, colorc[color].b);
      else leds.setPixel(i, 0, 0, 0);  
    }
    if(pixel_pos[i].side==2) leds.setPixel(i, 0, 64, 0);
    if(pixel_pos[i].side==3) leds.setPixel(i, 0, 0, 64);
    if(pixel_pos[i].side==4) leds.setPixel(i, 64, 64, 0);
    if(pixel_pos[i].side==5) leds.setPixel(i, 64, 0, 64);
    if(pixel_pos[i].side==6) leds.setPixel(i, 0, 64, 64);
    //delayMicroseconds(wait);
  }
  leds.show();  
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void full_side(int color, int side){
  for (int i=0; i < leds.numPixels(); i++) {
    if(pixel_pos[i].side==side) leds.setPixel(i, colorc[color].r, colorc[color].g, colorc[color].b);
  }
  leds.show();  
  
}

///////////////////////////////////////////////////////////////////////////////////////

void load_sprite_ROM(int num){

  char one[2][64]={{0, 0, 0, 1, 1, 0, 0, 0,
                    0, 0, 1, 1, 1, 0, 0, 0,
                    0, 0, 0, 1, 1, 0, 0, 0,
                    0, 0, 0, 1, 1, 0, 0, 0,
                    0, 0, 0, 1, 1, 0, 0, 0,
                    0, 0, 0, 1, 1, 0, 0, 0,
                    0, 0, 0, 1, 1, 0, 0, 0,
                    0, 0, 1, 1, 1, 1, 0, 0 },
  
  //char two[64] =  
                  { 0, 0, 1, 1, 1, 1, 0, 0,
                    0, 1, 1, 1, 1, 1, 1, 0,
                    0, 1, 1, 0, 0, 1, 1, 0,
                    0, 0, 0, 0, 0, 1, 1, 0,
                    0, 0, 0, 0, 1, 1, 0, 0,
                    0, 0, 0, 1, 1, 0, 0, 0,
                    0, 0, 1, 1, 1, 1, 1, 0,
                    0, 1, 1, 1, 1, 1, 1, 0 }};
  
  //strcpy(sprite,one);
  for(int i=0; i<64; i++) sprite[i]=one[num][i];

}
