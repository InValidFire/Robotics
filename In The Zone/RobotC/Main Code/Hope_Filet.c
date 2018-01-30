#pragma config(Motor,  port1,           RightFront,    tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveRight)
#pragma config(Motor,  port2,           RightMid,      tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           RightBack,     tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port4,           LeftFront,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           LeftMid,       tmotorVex393HighSpeed_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port6,           LeftBack,      tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port7,           Mobile,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LeftTower,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          RightTower,    tmotorVex393_HBridge, openLoop, reversed, driveRight)
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
  bLCDBacklight = true;
	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
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
int autover;
task autonomous()
{
	if(autover == 1) {
		motor[LeftFront] = 127;
		motor[LeftMid] = 127;
		motor[LeftBack] = 127;
		motor[RightFront] = 127;
		motor[RightMid] = 127;
		motor[RightBack] = 127;
		delay(2000);
	}
	//Simple test function for autonomous until actual code can be created

	if(autover == 2) {
		motor[LeftFront] = 127;
		motor[LeftMid] = 127;
		motor[LeftBack] = 127;
		motor[RightFront] = 127;
		motor[RightMid] = -127;
		motor[RightBack] = -127;
		delay(2000);
	}
	//Testing autonomous selection
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

task usercontrol()
{
  //Plans for this bot:
	//	- LCD Display, will require convincing of Nick
	//	- Quad Encoders, will require further testing before implementation

  while (true)
  {
  	/*
  	 * Basic Tank Controls
  	 *
  	 * RightSides - Controls the FrontRight and BackRight motors.
  	 * LeftSides - Controls the FrontLeft and BackLeft motors.
  	 * LeftMid & RightMid Reversed due to build configuration.
  	 */

		//Left side
		motor[LeftFront] = vexRT[Ch3]; //Assigns Left Front motor to left joystick
		motor[LeftMid] = vexRT[Ch3]; //Assigns Left Mid motor to left joystick
		motor[LeftBack] = vexRT[Ch3]; //Assigns Left Back motor to left joystick

		//Right Side
		motor[RightFront] = vexRT[Ch2]; //Assigns Right Front motor to right joystick
		motor[RightMid] = vexRT[Ch2]; //Assigns Right Mid motor to right joystick
		motor[RightBack] = vexRT[Ch2]; //Assigns Right Back motor to right joystick

		//---- Manipulator Control - WIP --------------------------------------//

		//Claw Controls
		motor[Claw] = vexRT[Btn8D]*127 + vexRT[Btn8R]*-127; //Right (8) side claw control

		//Tower Control
		motor[LeftTower] = vexRT[Btn6U]*127 + vexRT[Btn6D]*-127; //Tower Control using right bumpers
		motor[RightTower] = vexRT[Btn6U]*127 + vexRT[Btn6D]*-127;

		//Mobile Goal Pickup
		motor[Mobile] = vexRT[Btn5D]*-127 + vexRT[Btn5U]*127; //Pickup control using left bumpers

		//---- Autonomous Test Function ---------------------------------------//
		if(vexRT[Btn8U] == 1) { //If both buttons 8U and 7U are pressed simultaneously, run the autonomous() task
			if(vexRT[Btn7U] == 1) {
				startTask(autonomous); //Could possibly shut us out of usercontrol(), would require reboot
			}
		}

		//---- LCD Display Test -----------------------------------------------//
		float batlevel = nAvgBatteryLevel/1000;
		//Sets batlevel to the battery level

		int btnPressed = nLCDButtons;

		clearLCDLine(0);
		clearLCDLine(1);
		//Resets LCD Display

		displayLCDString(0, 1, "1264B Battery: ");
		displayLCDNumber(0, 17, batlevel);
		//Displays battery level on the top line

		displayLCDString(1, 1, "Autonomous Version: ");
		displayLCDNumber(1, 21, autover);
		autover = 1;
		//Setup for Autonomous selection

		if(btnPressed == 1) { //If the left button is pressed, scroll left on autonomous versions
			autover = autover - 1;
			delay(200); //Buffer for time
		}

		if(btnPressed == 4) { //If the right button is pressed, scroll right on autonomous versions
			autover = autover + 1;
			delay(200); //Buffer for time
		}

  }
}
