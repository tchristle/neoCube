
void dispChar(int code, int color, int side)
{
  int n = side_order[side-1]-1;
  int nmax = (n+1)*64;
  for (int i=n*64; i < nmax; i++) {
    if((font8x8[code][(i-n*64)/8]>>(i%8))&1) {leds.setPixel(i, colorc[color].r, colorc[color].g, colorc[color].b);}
    else leds.setPixel(i, 0, 0, 0);
  }
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
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void full_solid(int colr){
  
    full_side(colr, 0.5f, 1);
    full_side(colr, 0.5f, 2);
    full_side(colr, 0.5f, 3);
    full_side(colr, 0.5f, 4);
    full_side(colr, 0.5f, 5);
    full_side(colr, 0.5f, 6);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void full_side(int color, float brt, int side){
  for (int i=(side-1)*64; i < (side-1)*64+64; i++){
    leds.setPixel(i, colorc[color].r*brt, colorc[color].g*brt, colorc[color].b*brt);
  }
}

///////////////////////////////////////////////////////////////////////////////////////

void side_by_num(){
  
    dispChar('1', red, 1);
    dispChar('2', blue, 2);
    dispChar('3', green, 3);
    dispChar('4', yellow, 4);
    dispChar('5', pink, 5);
    dispChar('6', orange, 6);
}
///////////////////////////////////////////////////////////////////////////////////////

void rainbow_pattern(int n){
  
    for(int i=0; i<385; i++){
      //leds.setPixel(i, colorc[i%192].r*0.5f, colorc[i%192].g*0.5f, colorc[i%192].b*0.5f);
      n = (int(pixel_pos[i].x*86+86)+cntr)%192;
      leds.setPixel(i, colorc[n].r*0.5f, colorc[n].g*0.5f, colorc[n].b*0.5f);
      Serial.println(int(pixel_pos[i].x*86+86));
    }
}

///////////////////////////////////////////////////////////////////////////////////////
void color_by_pos(){
  int r, b, g, color;
  float brt = 0.25f;
  for (int i=0; i < leds.numPixels(); i++) {
    r=(pixel_pos[i].z*Ax+1.0f)*32.0f;
    g=(pixel_pos[i].z*Ay+1.0f)*32.0f;
    b=(pixel_pos[i].z*Az+1.0f)*32.0f;
    color=(pixel_pos[i].z*Az+1.0f)*190;
    //if(r<g && r<b) r=0;
    //else if(g<r && g<b) g=0;
    //else b=0;
    leds.setPixel(i, r*brt, g*brt, b*brt);
    //Serial.println(color);
    //leds.setPixel(i, colorc[color].r*brt, colorc[color].g*brt, colorc[color].b*brt);
    //if(pixel_pos[i].side==5) Serial.println(pixel_pos[i].y);
  }
  //Serial.print(Ax+1.0f); Serial.print(", "); Serial.print(Ay+1.0f); Serial.print(", "); Serial.print(Az+1.0f); Serial.println(" "); 
  
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
