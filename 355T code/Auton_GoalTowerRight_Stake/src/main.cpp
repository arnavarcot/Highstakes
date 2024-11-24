/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Samantha                                                  */
/*    Created:      11/3/2024, 10:48:59 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

void ReverseIntake(float, bool);
void Intake(float, bool);
void MoveForward(float, int);
void MoveBackward(float, int);
void LeftTurn(float, int);
void RightTurn(float, int);
void down20(float);
void up20(float);

/*600 rpm 6 to 1
200 rpm 18 to 1
100 rpm 36 to 1*/

motor Conveyor = motor(PORT6, ratio18_1, true);
motor StakeIntake = motor(PORT19, ratio18_1, true);
motor RingIntake = motor(PORT5, ratio18_1, true);
motor FrontLeftMotor = motor(PORT10, ratio6_1, false); //600 rpm
motor FrontRightMotor = motor(PORT17, ratio6_1, true); //600 rpm
motor BackLeftMotor = motor(PORT20, ratio6_1, false); //600 rpm
motor BackRightMotor = motor(PORT9, ratio6_1, true); //600 rpm
motor StakeGraber = motor(PORT8, ratio36_1, false);
controller Controller1(primary);

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


  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

/*void autonomous(void) {
MoveBackward(3.49, 125);
StakeGraber.spinFor(reverse, 10, degrees, true);
wait(.5, seconds);
LeftTurn(1.1, 75);*/
void autonomous(void) {

MoveBackward(3.49, 125);
StakeGraber.spinFor(reverse, 10, degrees, true);
Conveyor.setVelocity(160, rpm);
Conveyor.spinFor(forward,-3, turns, false);
wait(1, seconds);
LeftTurn(1.15, 75);
MoveForward(2, 125);
}
//MoveForward(2.49, 600), RightTurn(1.15, 600), MoveForward(4.98, 600), LeftTurn(1.15, 600), MoveBackward(2.3, 600)


  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
/*MoveForward(2.49,125);//move forwards one tile
LeftTurn(1.15,75);//turns 90 degrees
MoveForward(7.47,125);//move forwards 3 tile
RightTurn(1.15,75); 
MoveBackward(2.49,125);
LeftTurn(-1.2, 75); 
MoveForward(7.8,125);
LeftTurn(1.2, 75);
MoveBackward(2.8,125);/*





/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  /*deadband is just an intiger. this will be used later to make sure that any stick inputs 
  will be greater than 5(%) to get rid of stickdrift*/
  int deadband = 5;
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

float Scaledown=0.9; //600 rpm motors

//leftMotorSpeed is equal to the controller's Axis 3 percent
int leftMotorSpeed = Controller1.Axis3.position();
//rightMotorSpeed is equal to the controller's Axis 2 percent
int rightMotorSpeed = Controller1.Axis2.position();

bool up20 = Controller1.ButtonUp.pressing();
bool down20 = Controller1.ButtonDown.pressing();

bool R2 = Controller1.ButtonR2.pressing();
bool R1 = Controller1.ButtonR1.pressing();
bool L1 = Controller1.ButtonL1.pressing();
bool L2 = Controller1.ButtonL2.pressing();



/*
if (Controller1.ButtonR1.pressing())
{
  RingIntake.spin(forward,200,rpm);
  Conveyor.spin(forward,50,rpm);
} else {
    RingIntake.spin(forward,0,rpm);
    Conveyor.spin(forward,0,rpm);
} 
*/
/* R2 button action
if (Controller1.ButtonR2.pressing())
{
  RingIntake.spin(forward,-200,rpm);
  Conveyor.spin(forward,-50,rpm);
} else {
  RingIntake.spin(forward,0,rpm);
  Conveyor.spin(forward,0,rpm);
}
if (Controller1.ButtonX.pressing())
{
  StakeGraber.setPosition(20, degrees);
} else {
  StakeGraber.setPosition(-20, degrees);
}*/

// bool Intake = Controller1.ButtonR1.pressing();


//bool ReverseIntake = Controller1.ButtonR2.pressing();


//int Intake =  Controller1.ButtonR1.pressed();
//int ReverseIntake = Controller1.ButtonR2.pressed();
//int StakeIntake = Controller1.ButtonUp.pressed();



/*these will be set to the left and right motors speeds if they are greater than 
5(%) otherwise they will be ignored*/

/* FrontLeftMotor .setVelocity(leftMotorSpeed*Scaledown, percent);
 BackLeftMotor .setVelocity(leftMotorSpeed*Scaledown, percent);
 FrontRightMotor .setVelocity(rightMotorSpeed*Scaledown, percent);
 BackRightMotor .setVelocity(rightMotorSpeed*Scaledown, percent);*/

//If the leftMotorSpeeds value is below 5(%) then the left motors speeds will be set to 0(%)
if (abs(leftMotorSpeed) < deadband) {
  FrontLeftMotor.setVelocity(0, percent);
  BackLeftMotor.setVelocity(0, percent);
  //FrontLeftMotor.stop(lock);
  //BackLeftMotor.stop(lock);
} else {
  //If leftMotorSpeeds value is above 5(%) it will set the Left Motors to that percent
  FrontLeftMotor.setVelocity(leftMotorSpeed, percent);
  BackLeftMotor.setVelocity(leftMotorSpeed, percent);
}
//If rightMotorSpeed's percent is lower than 5(%) it will change the right motors speed to 0(%)
if (abs(rightMotorSpeed) < deadband) {
  FrontRightMotor.setVelocity(0, percent);
  BackRightMotor.setVelocity(0, percent);
  //FrontRightMotor.stop(lock);
  //BackRightMotor.stop(lock);
} else {
  /*If the rightMotorSpeed's percent is higher than 5(%) it will set the right
   motors speed to that percent*/
  FrontRightMotor.setVelocity(rightMotorSpeed, percent);
  BackRightMotor.setVelocity(rightMotorSpeed, percent);

}
FrontLeftMotor.spin(forward);
FrontRightMotor.spin(forward);
BackLeftMotor.spin(forward);
BackRightMotor.spin(forward);

Conveyor.setVelocity(0, percent);
RingIntake.setVelocity(0, percent);

if (R1) {
  Conveyor.setVelocity(-80,percent);
  RingIntake.setVelocity(100, percent);
} 
 

 if (R2) {
  Conveyor.setVelocity(80,percent);
  RingIntake.setVelocity(-100, percent);
 }
 Conveyor.spin(forward);
RingIntake.spin(forward);

if (L1) {
  StakeGraber.setVelocity(20, rpm);
  StakeGraber.spinFor(forward, 10, degrees, false);
}
if (L2) {
  StakeGraber.setVelocity(20, rpm);
  StakeGraber.spinFor(reverse, 10, degrees, true);
}

 wait(20, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
  
  
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}


void MoveForward(float howfar, int howfast) {

  //units are wheel rotations
  FrontLeftMotor.setVelocity(howfast,rpm);
  FrontRightMotor.setVelocity(howfast,rpm);
  BackLeftMotor.setVelocity(howfast,rpm);
  BackRightMotor.setVelocity(howfast,rpm);
  


  FrontLeftMotor.spinFor(forward,howfar,turns,false); //false keeps turning
  FrontRightMotor.spinFor(forward,howfar,turns,false);
  BackLeftMotor.spinFor(forward,howfar,turns,false);
  BackRightMotor.spinFor(forward,howfar,turns,true);//waits until this one ends


  return;

}


void MoveBackward(float howfar, int howfast) {

  //units are wheel rotations
  FrontLeftMotor.setVelocity(howfast,rpm);
  FrontRightMotor.setVelocity(howfast,rpm);
  BackLeftMotor.setVelocity(howfast,rpm);
  BackRightMotor.setVelocity(howfast,rpm);


  FrontLeftMotor.spinFor(forward,-howfar,turns,false); //false keeps turning
  FrontRightMotor.spinFor(forward,-howfar,turns,false);
  BackLeftMotor.spinFor(forward,-howfar,turns,false);
  BackRightMotor.spinFor(forward,-howfar,turns,true);//waits until this one ends


  return;

}



void LeftTurn(float howfar, int howfast) {

//units are wheel rotations
FrontLeftMotor.setVelocity(howfast,rpm);
FrontRightMotor.setVelocity(howfast,rpm);
BackLeftMotor.setVelocity(howfast,rpm);
BackRightMotor.setVelocity(howfast,rpm);



FrontLeftMotor.spinFor(forward,-howfar,turns,false);//false keeps turning
FrontRightMotor.spinFor(forward,howfar,turns,false);
BackLeftMotor.spinFor(forward,-howfar,turns,false);
BackRightMotor.spinFor(forward,howfar,turns,true);

return;

}

void RightTurn(float howfar, int howfast) {

//units are wheel rotations
FrontLeftMotor.setVelocity(howfast,rpm);
FrontRightMotor.setVelocity(howfast,rpm);
BackLeftMotor.setVelocity(howfast,rpm);
BackRightMotor.setVelocity(howfast,rpm);



FrontLeftMotor.spinFor(forward,howfar,turns,false);//false keeps turning
FrontRightMotor.spinFor(forward,-howfar,turns,false);
BackLeftMotor.spinFor(forward,howfar,turns,false);
BackRightMotor.spinFor(forward,-howfar,turns,true);

return;

}


//this is just so i know all the names of the motors/variables

/*motor Conveyor = motor(PORT6, ratio18_1 true)
motor StakeIntake = motor(PORT19, ratio18_1 true)
motor RingIntake = motor(PORT5, ratio 18_1 true)*/


//void stakeIntake(float, bool)
//void ReverseIntake(float, bool);
//void Intake(float, bool);



//pulls in ring and pulls up onto stake
void Intake(float howfar, bool howfast) {
  RingIntake.setVelocity(howfast,rpm);
  Conveyor.setVelocity(howfast,rpm);
  Conveyor.spinFor(forward,howfar,turns,false);
  RingIntake.spinFor(forward,howfar,turns,false);
  
}
//reverses the intake
void ReverseIntake(float howfar, bool howfast){
  
  RingIntake.setVelocity(howfast,rpm);
  Conveyor.setVelocity(howfast,rpm);
  Conveyor.spinFor(reverse,howfar,turns,false);
  RingIntake.spinFor(reverse,howfar,turns,false);
}

//Motor.spinToPosition(rotation, units, velocity, units_v, wait)

/*void up20(float howfar, int howfast){
  StakeGrab.spinToPosition(rotation, degrees, velocity, units_v, wait);
}

down20(float howfar, int howfast){
  StakeGrab.setVelocity(-howfast,rpm);
}
*/

void up20(float value){
  StakeGraber.setPosition(value, degrees);
}
void down20(float value){
  StakeGraber.setPosition(-value, degrees);
}










