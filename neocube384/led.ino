// LED cube 8x8 demo patterns
// 01/08/2024

void dispChar(int code, int color, int side)
{
  int n = side_order[side-1]-1;
  int nmax = (n+1)*64;
  for (int i=n*64; i < nmax; i++) {
    if((font8x8[code][(i-n*64)/8]>>(i%8))&1) {leds.setPixel(i, colorc[color].r/4, colorc[color].g/4, colorc[color].b/4);}
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
  
    full_side(colr, 0.25f, 1);
    full_side(colr, 0.25f, 2);
    full_side(colr, 0.25f, 3);
    full_side(colr, 0.25f, 4);
    full_side(colr, 0.25f, 5);
    full_side(colr, 0.25f, 6);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void full_side(int color, float brt, int side){
  for (int i=(side-1)*64; i < (side-1)*64+64; i++){
    leds.setPixel(i, colorc[color].r*brt, colorc[color].g*brt, colorc[color].b*brt);
  }
}

///////////////////////////////////////////////////////////////////////////////////////

void side_by_num(int clr1){
  
    dispChar('1', clr1, 1);
    dispChar('2', clr1, 2);
    dispChar('3', clr1, 3);
    dispChar('4', clr1, 4);
    dispChar('5', clr1, 5);
    dispChar('6', clr1, 6);
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

/* //////////////////////////////////////////////////////////////////////////////////////
void color_by_pos(){
  int r, b, g;
  float brt = 0.25f;
  for (int i=0; i < leds.numPixels(); i++) {
    r=(pixel_pos[i].z*Ax+1.0f)*32.0f;
    g=(pixel_pos[i].z*Ay+1.0f)*32.0f;
    b=(pixel_pos[i].z*Az+1.0f)*32.0f;
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
*/
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

////////////////////////////////////////////////////////////////////////////////////////

void demo1_axisDir(void) {
    
    Serial.println("starting demo1");
    side_by_num(blue);
    leds.show();
    delay(1000);
    
    //leds.setPixel(idx, colorc[clr].r, colorc[clr].g, colorc[clr].b);
    //leds.setPixel(idx-1, 0, 0, 0);
  
    //sweep x
    dispChar('X', blue, 3);
    dispChar('X', blue, 4);
    dispChar(' ', clr, 1);
    dispChar(' ', clr, 2);
    dispChar(' ', clr, 5);
    dispChar(' ', clr, 6);
    leds.show();
    delay(1000);
    clr=blue;
    for(idx2=-1.1; idx2<=1.1; idx2+=0.111)
    {
      for(idx1=0; idx1<384; idx1++)
      {
        if(pixel_pos[idx1].x <= idx2)
        {
          boo=1;
          leds.setPixel(idx1, colorc[clr].r*0.25, colorc[clr].g*0.25, colorc[clr].b*0.25);
        }
        else 
        {
          boo=0;
          leds.setPixel(idx1, 0, 0, 0);
        }
      }
      leds.show();
      delay(50);  
    }   
    
    //sweep y
    dispChar('Y', green, 2);
    dispChar('Y', green, 6);
    leds.show();
    delay(1000);
    clr=green;
    for(idx2=-1.1; idx2<=1.1; idx2+=0.111)
    {
      for(idx1=0; idx1<384; idx1++)
      {
        if(pixel_pos[idx1].y <= idx2)
        {
          boo=1;
          leds.setPixel(idx1, colorc[clr].r*0.25, colorc[clr].g*0.25, colorc[clr].b*0.25);
        }
        else 
        {
          boo=0;
          leds.setPixel(idx1, 0, 0, 0);
        }
      }
      leds.show();
      delay(50);  
    }   

    //sweep z
    dispChar('Z', red, 1);
    dispChar('Z', red, 5);
    leds.show();
    delay(1000);
    clr=red;
    for(idx2=-1.1; idx2<=1.1; idx2+=0.111)
    {
      for(idx1=0; idx1<384; idx1++)
      {
        if(pixel_pos[idx1].z <= idx2)
        {
          boo=1;
          leds.setPixel(idx1, colorc[clr].r*0.25, colorc[clr].g*0.25, colorc[clr].b*0.25);
        }
        else 
        {
          boo=0;
          leds.setPixel(idx1, 0, 0, 0);
        }
      }
      leds.show();
      delay(50);  
    }  
}

////////////////////////////////////////////////////////////////////////////////////////

void demo2_AccFade(int Fade) {
    
    Serial.println("starting demo2");
    //acc z    
    for(idx1=0; idx1<384; idx1++)
      {
        // Set upper/lower accell limits
        if(Ax>=1.0) {Ax=0.99;}
        if(Ax<=-1.0) {Ax=-0.99;}
        if(Ay>=1.0) {Ay=0.99;}
        if(Ay<=-1.0) {Ay=-0.99;}
        if(Az>=1.0) {Az=0.99;}
        if(Az<=-1.0) {Az=-0.99;}
        // Calculate dot prodcut and accel and pixel posistion
        clr1=(pixel_pos[idx1].x*Ax*0.5+0.5)*190+1;
        clr2=(pixel_pos[idx1].y*Ay*0.5+0.5)*190+1;
        clr3=(pixel_pos[idx1].z*Az*0.5+0.5)*190+1;
        // scale results to 0:191 color claue range and convert float to int
        clr=(clr1+clr2+clr3)/2.5-30;
        leds.setPixel(idx1, colorc[clr].r*0.1, colorc[clr].g*0.1, colorc[clr].b*0.1);
        //Serial Print Debug
        //Serial.print(Ax); Serial.print(", "); Serial.print(Ay); Serial.print(", "); 
        //Serial.print(Az); Serial.println(" "); 
      }
      //delay(1);

      
      // scroll color assignment
      if(Fade==1)
      {
        colorc[191]=colorc[0];
        for(idx1=0; idx1<191; idx1++)
        {
          colorc[idx1]=colorc[idx1+1];
        }
      }
}

////////////////////////////////////////////////////////////////////////////////////////

void demo3_RotColor() {

    Serial.println("starting demo3");
    clr = outYaw/2*(192.0f/180.0f);
    full_solid(clr);
  
}

////////////////////////////////////////////////////////////////////////////////////////

void demo4_RotSides() {

    //void Rotate(int axis, int dir, int rows, int steps, int sped)
    // axis, (x, y, z) = (1, 2, 3)
    // direction (left, right) = (-1, 1)
    // rows 1-32
    // steps 1-32
    // speed (slow, fast) = (1 to 1000)
    
    int idx=0, jdx=0, kdx=0;
    int color_temp, color0[8];
    int rows, steps, sped=900;
    Serial.println("starting demo4");

    //rotate around x-wrap
    //rotate right
    steps=random(2)*9-1;
    rows = 8;
    for(kdx=0; kdx<steps; kdx++){
      //store 1st column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(x_wrap[0][jdx]);}
      //rotate remaining columns
      for(idx=0; idx<31; idx++){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(x_wrap[idx+1][jdx]);
          leds.setPixel(x_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(x_wrap[idx][jdx]);
        }
      }
      //move first column to last column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(x_wrap[31][jdx],color0[jdx]);}
      delay(1000-sped);
      leds.show();       
    }
    
    //rotate around x-wrap
    //rotate left
    steps=random(2)*9-1;
    rows = 8;
    for(kdx=0; kdx<steps; kdx++){
      //store last column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(x_wrap[31][jdx]);}
      //rotate remaining columns
      for(idx=31; idx>0; idx--){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(x_wrap[idx-1][jdx]);
          leds.setPixel(x_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(x_wrap[idx][jdx]);
        }
      }
      //move last column to 1st column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(x_wrap[0][jdx],color0[jdx]);}
      delay(1000-sped);
      leds.show();       
    }


    //rotate around y-wrap
    //rotate right
    steps=random(2)*9-1;
    rows = 8;
    for(kdx=0; kdx<steps; kdx++){
      //store 1st column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(y_wrap[0][jdx]);}
      //rotate remaining columns
      for(idx=0; idx<31; idx++){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(y_wrap[idx+1][jdx]);
          leds.setPixel(y_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(y_wrap[idx][jdx]);
        }
      }
      //move first column to last column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(y_wrap[31][jdx],color0[jdx]);}
      delay(1000-sped);
      leds.show();       
    }

    //rotate around y-wrap
    //rotate left
    steps=random(2)*9-1;
    rows = 8;
    for(kdx=0; kdx<steps; kdx++){
      //store last column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(y_wrap[31][jdx]);}
      //rotate remaining columns
      for(idx=31; idx>0; idx--){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(y_wrap[idx-1][jdx]);
          leds.setPixel(y_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(y_wrap[idx][jdx]);
        }
      }
      //move last column to 1st column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(y_wrap[0][jdx],color0[jdx]);}

      delay(1000-sped);
      leds.show();       
    }


    //rotate around z-wrap
    //rotate right
    steps=random(2)*9-1;
    rows = 8;
    for(kdx=0; kdx<steps; kdx++){
      //store 1st column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(z_wrap[0][jdx]);}
      //rotate remaining columns
      for(idx=0; idx<31; idx++){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(z_wrap[idx+1][jdx]);
          leds.setPixel(z_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(z_wrap[idx][jdx]);
        }
      }
      //move first column to last column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(z_wrap[31][jdx],color0[jdx]);}
      delay(1000-sped);
      leds.show();       
    }

    //rotate around z-wrap
    //rotate left
    steps=random(2)*9-1;
    rows = 8;
    for(kdx=0; kdx<steps; kdx++){
      //store last column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(z_wrap[31][jdx]);}
      //rotate remaining columns
      for(idx=31; idx>0; idx--){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(z_wrap[idx-1][jdx]);
          leds.setPixel(z_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(z_wrap[idx][jdx]);
        }
      }
      //move last column to 1st column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(z_wrap[0][jdx],color0[jdx]);}
      
      delay(1000-sped);
      leds.show();       
    }

}

////////////////////////////////////////////////////////////////////////////////////////

void demo5_SpinSides() {
    
    Serial.println("starting demo5");
    color_rainbow();
    full_side(red,    0.1f, 1);
    full_side(green,  0.1f, 2);
    full_side(blue,   0.1f, 3);
    full_side(pink,   0.1f, 4);
    full_side(orange, 0.1f, 5);
    full_side(yellow, 0.1f, 6);
    leds.show();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void demo6() {

    //void Rotate(int axis, int dir, int rows, int steps, int sped)
    // axis, (x, y, z) = (1, 2, 3)
    // direction (left, right) = (-1, 1)
    // rows 1-32
    // steps 1-32
    // speed (slow, fast) = (1 to 1000)
    
    int idx=0, jdx=0, kdx=0, mdx, ndx;
    int color_temp, color0[8];
    int rows, steps, sped=900;
    int temp0, side0;
    Serial.println("starting demo4");
    
    for(idx=0; idx<32; idx++){leds.setPixel(x_wrap[idx][2], 0);}
    for(idx=0; idx<32; idx++){leds.setPixel(x_wrap[idx][5], 0);}
    for(idx=0; idx<32; idx++){leds.setPixel(y_wrap[idx][2], 0);}
    for(idx=0; idx<32; idx++){leds.setPixel(y_wrap[idx][5], 0);}
    for(idx=0; idx<32; idx++){leds.setPixel(z_wrap[idx][2], 0);}
    for(idx=0; idx<32; idx++){leds.setPixel(z_wrap[idx][5], 0);}

    leds.show();
    //while(1);
    
    //rotate around x-wrap
    //rotate right
    steps=random(2)*9-1;
    rows = random(2)*3+3;
    for(kdx=0; kdx<steps; kdx++){
      //store 1st column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(x_wrap[0][jdx]);}
      //rotate remaining columns
      for(idx=0; idx<31; idx++){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(x_wrap[idx+1][jdx]);
          leds.setPixel(x_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(x_wrap[idx][jdx]);
        }
      }
      //move first column to last column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(x_wrap[31][jdx],color0[jdx]);}

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      // rotate face clockwise (+x)
      side0=4; 
      //for(kdx=0; kdx<7; kdx++){
      if(kdx<7){
       temp0=leds.getPixel(zout1[27]+side0*64);
       for(mdx=27; mdx>0; mdx--){leds.setPixel(zout1[mdx]+side0*64, leds.getPixel(zout1[mdx-1]+side0*64));}
       leds.setPixel(zout1[0]+side0*64, temp0);
      
       if(kdx>0 && kdx<6){
        temp0=leds.getPixel(zout2[19]+side0*64);
        for(mdx=19; mdx>0; mdx--){leds.setPixel(zout2[mdx]+side0*64, leds.getPixel(zout2[mdx-1]+side0*64));}
        leds.setPixel(zout2[0]+side0*64, temp0);
       }
      }      
      
      delay(1000-sped);
      leds.show();
    }

    delay(500);
    
    //rotate around x-wrap
    //rotate left
    steps=random(2)*9-1;
    rows = random(2)*3+3;
    for(kdx=0; kdx<steps; kdx++){
      //store last column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(x_wrap[31][jdx]);}
      //rotate remaining columns
      for(idx=31; idx>0; idx--){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(x_wrap[idx-1][jdx]);
          leds.setPixel(x_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(x_wrap[idx][jdx]);
        }
      }
      //move last column to 1st column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(x_wrap[0][jdx],color0[jdx]);}

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      // rotate face counter-clockwise (+x)
      //side0=4; 
      //for(kdx=0; kdx<7; kdx++){
      if(kdx<7){
       temp0=leds.getPixel(zout1[0]+side0*64);
       for(mdx=0; mdx<28; mdx++){leds.setPixel(zout1[mdx]+side0*64, leds.getPixel(zout1[mdx+1]+side0*64));}
       leds.setPixel(zout1[27]+side0*64, temp0);
      
       if(kdx>0 && kdx<6){
        temp0=leds.getPixel(zout2[0]+side0*64);
        for(mdx=0; mdx<20; mdx++){leds.setPixel(zout2[mdx]+side0*64, leds.getPixel(zout2[mdx+1]+side0*64));}
        leds.setPixel(zout2[19]+side0*64, temp0);
       }
      }      
      
      delay(1000-sped);
      leds.show();       
    }

    delay(500);

    //rotate around y-wrap
    //rotate right
    steps= random(2)*9-1;
    rows = random(2)*3+3;
    for(kdx=0; kdx<steps; kdx++){
      //store 1st column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(y_wrap[0][jdx]);}
      //rotate remaining columns
      for(idx=0; idx<31; idx++){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(y_wrap[idx+1][jdx]);
          leds.setPixel(y_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(y_wrap[idx][jdx]);
        }
      }
      //move first column to last column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(y_wrap[31][jdx],color0[jdx]);}

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      // rotate face clockwise (+y)
      side0=3; 
      //for(kdx=0; kdx<7; kdx++){
      if(kdx<7){
       temp0=leds.getPixel(zout1[27]+side0*64);
       for(mdx=27; mdx>0; mdx--){leds.setPixel(zout1[mdx]+side0*64, leds.getPixel(zout1[mdx-1]+side0*64));}
       leds.setPixel(zout1[0]+side0*64, temp0);
      
       if(kdx>0 && kdx<6){
        temp0=leds.getPixel(zout2[19]+side0*64);
        for(mdx=19; mdx>0; mdx--){leds.setPixel(zout2[mdx]+side0*64, leds.getPixel(zout2[mdx-1]+side0*64));}
        leds.setPixel(zout2[0]+side0*64, temp0);
       }
      }      
      
      delay(1000-sped);
      leds.show();       
    }

    delay(500);

    //rotate around y-wrap
    //rotate left
    steps=random(2)*9-1;
    rows =random(2)*3+3;
    for(kdx=0; kdx<steps; kdx++){
      //store last column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(y_wrap[31][jdx]);}
      //rotate remaining columns
      for(idx=31; idx>0; idx--){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(y_wrap[idx-1][jdx]);
          leds.setPixel(y_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(y_wrap[idx][jdx]);
        }
      }
      //move last column to 1st column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(y_wrap[0][jdx],color0[jdx]);}
      
      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      // rotate face counter-clockwise (+y)
      side0=3; 
      //for(kdx=0; kdx<7; kdx++){
      if(kdx<7){
       temp0=leds.getPixel(zout1[0]+side0*64);
       for(mdx=0; mdx<28; mdx++){leds.setPixel(zout1[mdx]+side0*64, leds.getPixel(zout1[mdx+1]+side0*64));}
       leds.setPixel(zout1[27]+side0*64, temp0);
      
       if(kdx>0 && kdx<6){
        temp0=leds.getPixel(zout2[0]+side0*64);
        for(mdx=0; mdx<20; mdx++){leds.setPixel(zout2[mdx]+side0*64, leds.getPixel(zout2[mdx+1]+side0*64));}
        leds.setPixel(zout2[19]+side0*64, temp0);
       }
      }
            
      delay(1000-sped);
      leds.show();       
    }

    delay(500);

    //rotate around z-wrap
    //rotate right
    steps= random(2)*9-1;
    rows = random(2)*3+3;
    for(kdx=0; kdx<steps; kdx++){
      
      //store 1st column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(z_wrap[0][jdx]);}
      //rotate remaining columns
      for(idx=0; idx<31; idx++){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(z_wrap[idx+1][jdx]);
          leds.setPixel(z_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(z_wrap[idx][jdx]);
        }
      }
      //move first column to last column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(z_wrap[31][jdx],color0[jdx]);}
      
      // rotate face clockwise (-z)
      side0=2; 
      //for(kdx=0; kdx<7; kdx++){
      if(kdx<7){
       temp0=leds.getPixel(zout1[27]+side0*64);
       for(mdx=27; mdx>0; mdx--){leds.setPixel(zout1[mdx]+side0*64, leds.getPixel(zout1[mdx-1]+side0*64));}
       leds.setPixel(zout1[0]+side0*64, temp0);
      
       if(kdx>0 && kdx<6){
        temp0=leds.getPixel(zout2[19]+side0*64);
        for(mdx=19; mdx>0; mdx--){leds.setPixel(zout2[mdx]+side0*64, leds.getPixel(zout2[mdx-1]+side0*64));}
        leds.setPixel(zout2[0]+side0*64, temp0);
       }
      }
      delay(1000-sped);
      leds.show();       
    }

    delay(500);

    //rotate around z-wrap
    //rotate left
    steps=random(2)*9-1;
    rows = random(2)*3+3;
    for(kdx=0; kdx<steps; kdx++){
      //store last column
      for(jdx=0; jdx<rows; jdx++){ color0[jdx]=leds.getPixel(z_wrap[31][jdx]);}
      //rotate remaining columns
      for(idx=31; idx>0; idx--){
        for(jdx=0; jdx<rows; jdx++){
          color_temp=leds.getPixel(z_wrap[idx-1][jdx]);
          leds.setPixel(z_wrap[idx][jdx], color_temp);
          //Serial.print(color_temp); Serial.print(" , "); Serial.println(z_wrap[idx][jdx]);
        }
      }
      //move last column to 1st column
      for(jdx=0; jdx<rows; jdx++){ leds.setPixel(z_wrap[0][jdx],color0[jdx]);}

      // rotate face counter-clockwise (-z)
      side0=2; 
      //for(kdx=0; kdx<7; kdx++){
      if(kdx<7){
       temp0=leds.getPixel(zout1[0]+side0*64);
       for(mdx=0; mdx<28; mdx++){leds.setPixel(zout1[mdx]+side0*64, leds.getPixel(zout1[mdx+1]+side0*64));}
       leds.setPixel(zout1[27]+side0*64, temp0);
      
       if(kdx>0 && kdx<6){
        temp0=leds.getPixel(zout2[0]+side0*64);
        for(mdx=0; mdx<20; mdx++){leds.setPixel(zout2[mdx]+side0*64, leds.getPixel(zout2[mdx+1]+side0*64));}
        leds.setPixel(zout2[19]+side0*64, temp0);
       }
      }

      delay(1000-sped);
      leds.show();       
    }
    
    delay(500);

}
