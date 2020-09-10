
void cube_array(void){
  
  int i=0;
  //Serial.println(" = {");
  //top
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=j;
        pixel_pos[i].y=k;
        pixel_pos[i].z=1;
        pixel_pos[i].side=1;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("1 },");
        i++;
    }
  }
  //front
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=j;
        pixel_pos[i].y=1;
        pixel_pos[i].z=k;
        pixel_pos[i].side=2;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.println("2 },");
        i++;
    }
  }    
  //bottom
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=j;
        pixel_pos[i].y=k;
        pixel_pos[i].z=-1;
        pixel_pos[i].side=6;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("6 },");
        i++;        
    }
  }  
  //back
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=j;
        pixel_pos[i].y=-1;
        pixel_pos[i].z=k;
        pixel_pos[i].side=5;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("5 },");
        i++;        
    }
  }
  //left
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
  //right
  for(float j=-0.777; j<=0.777; j+=0.222){
    for(float k=-0.777; k<=0.777; k+=0.222){
        pixel_pos[i].x=1;
        pixel_pos[i].y=k;
        pixel_pos[i].z=j;
        pixel_pos[i].side=4;
        //Serial.print("{"); Serial.print(j); Serial.print(", "); Serial.print(k); Serial.print(", "); Serial.print(1); Serial.print(", "); Serial.println("4 },");
        i++;        
    }
  }
  //Serial.println(" };");
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
