// LED cube 8x8 setup functions
// 01/08/2024

void cube_array(void){
  // assign x,y,z posistions to each pixel by panel
  // float positions
  int i=0, j=0;
  
  Serial.println("float array starting");
  //top (1, +Z, 0:63)
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=k;
        pixel_pos[i].y=-j;
        pixel_pos[i].z=1;
        pixel_pos[i].side=1;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("1 },");
        i++;
    }
  }
  //back (2, -Y, 64:127)
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=-j;
        pixel_pos[i].y=1;
        pixel_pos[i].z=k;
        pixel_pos[i].side=2;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.println("2 },");
        i++;
    }
  }    
  //bottom (5, -Z, 128:191)
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=k;
        pixel_pos[i].y=j;
        pixel_pos[i].z=-1;
        pixel_pos[i].side=6;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("6 },");
        i++;        
    }
  }  
  //front (6, +Y, 192:255)
  for(float j=0.777; j>=-0.777; j-=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=j;
        pixel_pos[i].y=-1;
        pixel_pos[i].z=-k;
        pixel_pos[i].side=5;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("5 },");
        i++;        
    }
  }
  //left (4, -X, 256:319)
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=-1;
        pixel_pos[i].y=k;
        pixel_pos[i].z=j;
        pixel_pos[i].side=3;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("3 },");
        i++;        
    }
  }  
  //right (3, +X, 320:383)
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=1;
        pixel_pos[i].y=k;
        pixel_pos[i].z=-j;
        pixel_pos[i].side=4;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("4 },");
        i++;        
    }
  }
  Serial.println("float array finished");

  //..............................................................................................
  // integer positions
  i=0;
  
  Serial.println("integer array starting");
  //top (1, +Z, 0:63)
  for(float j=1; j<=8; j++){
    for(float k=1; k<=8; k++){
        pixel_pos[i].xi=k;
        pixel_pos[i].yi=j; //was 9-j
        pixel_pos[i].zi=9;
        pixel_pos[i].side=1;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("1 },");
        i++;
    }
  }
  //back (2, -Y, 64:127)
  for(float j=1; j<=8; j++){
    for(float k=1; k<=8; k++){
        pixel_pos[i].xi=9-j;
        pixel_pos[i].yi=9;
        pixel_pos[i].zi=k;
        pixel_pos[i].side=2;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.println("2 },");
        i++;
    }
  }    
  //bottom (5 -Z, 128:191)
  for(float j=1; j<=8; j++){
    for(float k=1; k<=8; k++){
        pixel_pos[i].xi=k;
        pixel_pos[i].yi=j;
        pixel_pos[i].zi=0;
        pixel_pos[i].side=6;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("6 },");
        i++;        
    }
  }  
  //front (6, +Y, 192:255)
  for(float j=1; j<=8; j++){
    for(float k=1; k<=8; k++){
        pixel_pos[i].xi=9-j; //was j
        pixel_pos[i].yi=0;
        pixel_pos[i].zi=k; //was 9-k
        pixel_pos[i].side=5;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("5 },");
        i++;        
    }
  }
  //left (4, -X, 256:319)
  for(float j=1; j<=8; j++){
    for(float k=1; k<=8; k++){
        pixel_pos[i].xi=0;
        pixel_pos[i].yi=k;
        pixel_pos[i].zi=j;
        pixel_pos[i].side=3;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("3 },");
        i++;        
    }
  }  
  //right (3, +X, 320:383)
  for(float j=1; j<=8; j++){
    for(float k=1; k<=8; k++){
        pixel_pos[i].xi=9;
        pixel_pos[i].yi=9-k;
        pixel_pos[i].zi=9-j;
        pixel_pos[i].side=4;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("4 },");
        i++;        
    }
  }
  Serial.println("integer array finished");

  //..............................................................................................
  //define x,y,z axis wrap around arrays [8]x[32]
  //top (1, +Z, 0:63)
  //bottom (5 -Z, 128:191)
  //left (4, -X, 256:319)
  //right (3, +X, 320:383)
  //front (6, +Y, 192:255)
  //back (2, -Y, 64:127)
  
  // x_wrap, -Y,+Z,+Y,-Z, 0:7,8:15,16:23,24:31
  //-Y
  Serial.println("x_wrap indexes:");
  for(i=64; i<=127; i++){
    x_wrap[pixel_pos[i].zi-1][pixel_pos[i].xi-1]=i;
    Serial.print(i); Serial.print(", "); Serial.print(pixel_pos[i].zi-1); Serial.print(", "); Serial.print(pixel_pos[i].xi-1);Serial.println(", ");
  }
  //+Z
  for(i=0; i<=63; i++){
    x_wrap[pixel_pos[i].yi+8-1][pixel_pos[i].xi-1]=i;
    Serial.print(i); Serial.print(", "); Serial.print(pixel_pos[i].yi+8-1); Serial.print(", "); Serial.print(pixel_pos[i].xi-1);Serial.println(", ");
  }  
  //+Y
  for(i=192; i<=255; i++){
    x_wrap[pixel_pos[i].zi+16-1][pixel_pos[i].xi-1]=i;
    Serial.print(i); Serial.print(", "); Serial.print(pixel_pos[i].zi+16-1); Serial.print(", "); Serial.print(pixel_pos[i].xi-1);Serial.println(", ");
  }
  //-Z
  for(i=128; i<=191; i++){
    x_wrap[pixel_pos[i].yi+24-1][pixel_pos[i].xi-1]=i;
    Serial.print(i); Serial.print(", "); Serial.print(pixel_pos[i].yi+24-1); Serial.print(", "); Serial.print(pixel_pos[i].xi-1);Serial.println(", ");
  }
  
  while(0){
  //test cube wrap array
  for(i=0; i<384; i++) { leds.setPixel(i,0);}
  leds.show();
  for(i=0; i<32; i++){
    for(j=0; j<8; j++){    
      leds.setPixel(x_wrap[i][j], RED);
      leds.show();
      Serial.println(x_wrap[i][j]);
      //delay(10);  
    }
  }}
  
  //..............................................................................................
  // y_wrap, -Z,+X,+Z,-X, 0:7,8:15,16:23,24:31
  //top (1, +Z, 0:63)
  //bottom (5 -Z, 128:191)
  //left (4, -X, 256:319)
  //right (3, +X, 320:383)
  Serial.println("y_wrap indexes:");
  //-Z
  for(i=128; i<=191; i++){
    y_wrap[pixel_pos[i].xi-1][pixel_pos[i].yi-1]=i;
  }
  //+X
  for(i=320; i<=383; i++){
    y_wrap[pixel_pos[i].zi+8-1][9-pixel_pos[i].yi-1]=i;
  }  
  //+Z
  for(i=0; i<=63; i++){
    y_wrap[9-pixel_pos[i].xi+16-1][9-pixel_pos[i].yi-1]=i;
  }
  //-X
  for(i=256; i<=319; i++){
    y_wrap[9-pixel_pos[i].zi+24-1][pixel_pos[i].yi-1]=i;
  }

  while(0){
  //test cube wrap array
  for(i=0; i<384; i++) {leds.setPixel(i,0);}
  leds.show();
  for(i=0; i<32; i++){
    for(j=0; j<8; j++){    
      leds.setPixel(y_wrap[i][j], GREEN);
      leds.show();
      Serial.println(y_wrap[i][j]);
      //delay(10);  
    }
  }}
  
  //..............................................................................................
  // z_wrap, -Y,+X,+Y,-X, 0:7,8:15,16:23,24:31
  Serial.println("z_wrap indexes:");
  //left (4, -X, 256:319)
  //right (3, +X, 320:383)
  //front (6, +Y, 192:255)
  //back (2, -Y, 64:127)
  //-Y
  for(i=64; i<=127; i++){
    z_wrap[pixel_pos[i].xi-1][pixel_pos[i].zi-1]=i;
    Serial.print(i); Serial.print(", "); Serial.print(pixel_pos[i].xi-1); Serial.print(", "); Serial.print(pixel_pos[i].zi-1);Serial.println(", ");
  }
  //+X
  for(i=320; i<=383; i++){
    z_wrap[pixel_pos[i].yi+8-1][pixel_pos[i].zi-1]=i;
    Serial.print(i); Serial.print(", "); Serial.print(pixel_pos[i].yi+8-1); Serial.print(", "); Serial.print(pixel_pos[i].zi-1);Serial.println(", ");
  }  
  //+Y
  for(i=192; i<=255; i++){
    z_wrap[9-pixel_pos[i].xi+16-1][9-pixel_pos[i].zi-1]=i;
    Serial.print(i); Serial.print(", "); Serial.print(pixel_pos[i].xi+16-1); Serial.print(", "); Serial.print(pixel_pos[i].zi-1);Serial.println(", ");
  }
  //-X
  for(i=256; i<=319; i++){
    z_wrap[pixel_pos[i].yi+24-1][pixel_pos[i].zi-1]=i;
    Serial.print(i); Serial.print(", "); Serial.print(pixel_pos[i].yi+24-1); Serial.print(", "); Serial.print(pixel_pos[i].zi-1);Serial.println(", ");
  }

  while(0){
  //test cube wrap array
  for(i=0; i<384; i++) {leds.setPixel(i,0);} //clear cube
  leds.show();
  for(i=0; i<32; i++){
    for(j=0; j<8; j++){    
      leds.setPixel(z_wrap[i][j], BLUE);
      leds.show();
      Serial.println(z_wrap[i][j]);
      //delay(10);  
    }
  }}

  //define x,y,z axis wrap around arrays [8]x[32]
  //top (1, +Z, 0:63)
  //bottom (5 -Z, 128:191)
  //left (4, -X, 256:319)
  //right (3, +X, 320:383)
  //front (6, +Y, 192:255)
  //back (2, -Y, 64:127)

 
}

//////////////////////////////////////////////////////////////////////////////////////

void color_rainbow(void){

  int i=0;
  
  for(i=0; i<64; i++){
    colorc[i].r=64-i;
    colorc[i].g=i;
    colorc[i].b=0;
    //Serial.print(colorc[i].r); Serial.print(", "); Serial.print(colorc[i].g); Serial.print(", "); Serial.print(colorc[i].b); Serial.println(" "); 
  }
  for(i=64; i<128; i++){
    colorc[i].r=0;
    colorc[i].g=128-i;
    colorc[i].b=i-64;
    //Serial.print(colorc[i].r); Serial.print(", "); Serial.print(colorc[i].g); Serial.print(", "); Serial.print(colorc[i].b); Serial.println(" "); 
  }
  for(i=128; i<192; i++){
    colorc[i].r=i-128;
    colorc[i].g=0;
    colorc[i].b=192-i;
    //Serial.print(colorc[i].r); Serial.print(", "); Serial.print(colorc[i].g); Serial.print(", "); Serial.print(colorc[i].b); Serial.println(" "); 
  }
}
///////////////////////////////////////////////////////////////////////////////////////

void load_font_ROM(void){


}

///////////////////////////////////////////////////////////////////////////////////////

void IMU_setup(){
  
  //IMU ---------------------------------------------------------  
  // Before initializing the IMU, there are a few settings
  // we may need to adjust. Use the settings struct to set
  // the device's communication mode and addresses:
  //imu.settings.device.commInterface = IMU_MODE_I2C;
  Wire.begin();
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  // The above lines will only take effect AFTER calling
  // imu.begin(), which verifies communication with the IMU
  // and turns it on.
  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1)
      ;
  }
  Serial.println("imu started...");
  imu.settings.gyro.scale = 245; //245 default
  imu.settings.gyro.sampleRate = 3;  //59Hz
  imu.settings.accel.scale = 2; // Set accel scale to +/-2g.
  imu.settings.accel.sampleRate = 2; // Set accel to 105Hz.
  imu.settings.accel.bandwidth = 3; // BW = 50Hz  
}
///////////////////////////////////////////////////////////////////////////////////////

void calgyro()
{
  Serial.println();
  Serial.println("Hold Still!!");
  for(int i=0 ; i<10 ; i++)
  {
    Serial.print(i);
    imu.readGyro();
    gxbias += imu.gx;
    gybias += imu.gy;
    gzbias += imu.gz;
    delay(100);
  }
  gxbias = gxbias/10;
  gybias = gybias/10;
  gzbias = gzbias/10;
  Serial.println();
  Serial.print("gyro x bias = "); Serial.println(gxbias);
  Serial.print("gyro y bias = "); Serial.println(gybias);
  Serial.print("gyro z bias = "); Serial.println(gzbias);
}
