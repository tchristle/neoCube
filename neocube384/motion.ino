
void IMU_update(){
  if(imu.accelAvailable()) imu.readAccel();
  Ax = imu.calcAccel(imu.ax);
  Ay = -imu.calcAccel(imu.ay);
  Az = imu.calcAccel(imu.az);
  if(imu.magAvailable()) imu.readGyro();
  Gx = imu.calcGyro(imu.gx-gxbias);
  Gy = imu.calcGyro(imu.gy-gybias);
  Gz = imu.calcGyro(imu.gz-gzbias);  
}
///////////////////////////////////////////////////////////////////////////////////////

void AHRS_update(){
  AHRSfilter.updateIMU(Gx, Gy, Gz, Ax, Ay, Az);
  outRoll = AHRSfilter.getRoll();
  outPitch = AHRSfilter.getPitch();
  outYaw = AHRSfilter.getYaw();

  Ux = cos(outYaw/57.29578f)*cos(outPitch/57.29578f);
  Uy = sin(outYaw/57.29578f)*cos(outPitch/57.29578f);
  Uz = sin(outPitch/57.29578f);
}
