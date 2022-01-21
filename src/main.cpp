/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// clawMotor            motor         10              
// frontLeft            motor         1               
// frontRight           motor         2               
// backLeft             motor         3               
// backRight            motor         4               
// armLeft              motor         5               
// armRight             motor         6               
// DigitalOutA          digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"



using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  vexcodeInit(); 
}

void stop(){
  /*
  Will set the velocity of motors to stop
  */
  FrontLeft.spin(directionType::fwd, 0, velocityUnits::pct);
  FrontRight.spin(directionType::fwd, 0, velocityUnits::pct);
  BackLeft.spin(directionType::fwd, 0, velocityUnits::pct);
  BackRight.spin(directionType::fwd, 0, velocityUnits::pct);
  ClawMotor.spin(directionType::fwd, 0, velocityUnits::pct);
}

// 0.5 seconds = 1 meter
// 0.480 seconds = 90 degree turn

void run_straight(double seconds, bool straight){
  /*
  Will drive straight based on the direction and seconds

  double seconds: input number of seconds for drive to last
  bool straight: if true, sets motors to forward. Else, sets to reverse
  */
  if(straight){
    int milliseconds = seconds*1000;    // converts seconds to milliseconds
    FrontLeft.spin(directionType::fwd, 100, velocityUnits::pct);
    FrontRight.spin(directionType::fwd, 100, velocityUnits::pct);
    BackLeft.spin(directionType::fwd, 100, velocityUnits::pct);
    BackRight.spin(directionType::fwd, 100, velocityUnits::pct);
    task::sleep(milliseconds);
  }
  else
  {
    int milliseconds = seconds*1000;
    FrontLeft.spin(directionType::rev, 102, velocityUnits::pct);
    FrontRight.spin(directionType::rev, 100, velocityUnits::pct);
    BackLeft.spin(directionType::rev, 102, velocityUnits::pct);
    BackRight.spin(directionType::rev, 100, velocityUnits::pct);
    ClawMotor.spin(directionType::fwd, 100, velocityUnits::pct);    // Claw motor is continuously latching on goal while reverseing
    task::sleep(milliseconds);
  }
}

void latch(){
  /*
  Will latch on a` goal
  */
  ClawMotor.spin(directionType::fwd, 100, velocityUnits::pct);  // run claw motor
  task::sleep(1000);                                            // run 1 second
  ClawMotor.spin(directionType::fwd, 0, velocityUnits::pct);    // stop claw motor
}

void init_aut1(){
  run_straight(1.8, true);      // drive forward for 1.1 seconds
  stop();                       // stop motors
  latch();                      // latch on to the goal
  run_straight(1.8, false);      // reverse for 1.1 seconds. (Claw motor is continuously latching while reversing)
  stop();                       // stop motors
}

void init_aut2(){
  run_straight(1.8, true);   // drive forward for 1.8 seconds
  stop();                       // stop motors
  latch();                      // latch on to the goal
  run_straight(1.8, false);   // reverse for 1.8 seconds. (Claw motor is continuously latching while reversing)
  stop();                       // stop motors
}

void autonomous(void) {
}

void usercontrol(void) {

  while (1) {
    // Drive motors config
    BackLeft.spin(directionType::fwd, Controller1.Axis3.value(),velocityUnits::pct);
    FrontLeft.spin(directionType::fwd,Controller1.Axis3.value(),velocityUnits::pct);
    BackRight.spin(directionType::fwd,Controller1.Axis2.value(),velocityUnits::pct);
    FrontRight.spin(directionType::fwd,Controller1.Axis2.value(),velocityUnits::pct);

    if(Controller1.ButtonA.pressing()){
      DigitalOutA.set(true);
    }else{
      DigitalOutA.set(false);
    }

    //Top left arm motor controller config
    if(Controller1.ButtonL1.pressing())
    {
      LeftArm.spin(directionType::rev, 100, velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing()){
      LeftArm.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    else{
      LeftArm.stop(brakeType::hold);
    }

    //Top right arm motor controller config
    if(Controller1.ButtonL1.pressing())
    {
      RightArm.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing()){
      RightArm.spin(directionType::rev, 100, velocityUnits::pct);
    }
    else{
      RightArm.stop(brakeType::hold);
    }

    //Latch motor controller config
    if(Controller1.ButtonR1.pressing())
    {
      ClawMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    else if(Controller1.ButtonR2.pressing())
    {
      ClawMotor.spin(directionType::rev, 100, velocityUnits::pct);
    }
    else
    {
      ClawMotor.stop(brakeType::hold);
    }


    if(Controller1.ButtonA.pressing())
    {
      DigitalOutA.set(true);
    }
    else
    {
      DigitalOutA.set(false);
    }
  }
}


int main() {

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);


  pre_auton();


  while (true) {
    wait(100, msec);
  }
}