#include "ThrusterDriver.h"

ThrusterDriver::ThrusterDriver(){
  DebugSerial.println("No Pin provided for thruster");
}
ThrusterDriver::ThrusterDriver(const int servoPin){
    thruster.attach(servoPin);

    thruster.write(1500); // send "stop" signal to ESC.

    delay(7000); // delay to allow the ESC to recognize the stopped signal
    DebugSerial.print("Thruster Initialized on Pin ");
    DebugSerial.println(servoPin);
}
void ThrusterDriver::setVelocity(int vel){
  if(vel>=1100&&vel<=1900){
    thruster.write(vel);
  }
  else if(vel>=-100&&vel<=100){
    vel = (vel+100)*4+1100;//scales value from -100 to 100 to 1100 to 1900
    thruster.write(vel);
  }
  else{
    DebugSerial.println("Invalid velocity value given must be in range -100 to 100 or 1100 to 1900");
  }
}
