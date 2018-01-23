#pragma config(Motor,  port1,           FrontLeft,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           FrontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           BackRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LeftSecond,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           RightSecond,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           ClawControl,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RightLiftAll,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LeftLiftBottom, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LeftLiftTop,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          BackLeft,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want t-he LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

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

task autonomous()
{
	motor[FrontLeft] = 127;
	motor[BackLeft] = 127;
	motor[FrontRight] = 127;
	motor[BackRight] = 127;
	delay(1000);
	motor[FrontLeft] = 0;
	motor[BackLeft] = 0;
	motor[FrontRight] = 0;
	motor[BackRight] = 0;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

/*
 *NOTICE: This code is for the incorrect claw configuration, thanks Nick...
*/
task usercontrol()
{
	//connect the cortex too your computer with the orange a to a cable
  // press f5
  // User control code here, inside the loop
while(true)
	{
		//leftSide
		motor[FrontLeft] = vexRT[Ch3];
		motor[BackLeft] = vexRT[Ch3];

		//rightSide
		motor[FrontRight] = vexRT[Ch2];
		motor[BackRight] = vexRT[Ch2];

		//liftControl
		motor[LeftLiftBottom] = vexRT[Btn6U]*127 + vexRT[Btn6D]*-127;
		motor[LeftLiftTop] = vexRT[Btn6U]*127 + vexRT[Btn6D]*-127;
		motor[RightLiftAll] = vexRT[Btn6U]*127 + vexRT[Btn6D]*-127;

		//clawControl
		if(vexRT[Btn8D] == 1) {
			motor[ClawControl] = 127;
		}
		if(vexRT[Btn8R] == 1) {
			motor[ClawControl] = -127;
		}

		//clawLift
			motor[LeftSecond] = vexRT[Btn5U]*127 + vexRT[Btn5D]*-127;
			motor[RightSecond] = vexRT[Btn5U]*127 + vexRT[Btn5D]*-127;

/*
Autonomous Steps Needed
1. Drive to loading zone
2. Grab Cone
3. Load Mobile Goal
4. Move To Far Scoring Goal
*/

	if(vexRT[Btn8U] == 1){
		if(vexRT[Btn7U] == 1) {
			motor[FrontLeft] = 127;
			motor[BackLeft] = 127;
			motor[FrontRight] = 127;
			motor[BackRight] = 127;
			wait1Msec(2000);
			motor[FrontLeft] = 0;
			motor[BackLeft] = 0;
			motor[FrontRight] = 0;
			motor[BackRight] = 0;
			}
		}
	}
}