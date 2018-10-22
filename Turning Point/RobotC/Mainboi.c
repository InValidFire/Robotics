#pragma config(Sensor, dgtl1,  PEPower,        sensorDigitalIn)
#pragma config(Sensor, dgtl9,  LedRed,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, LedYel,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, LedGreen,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, LedFull,        sensorLEDtoVCC)
#pragma config(Motor,  port1,           ArmRight,      tmotorVex393_HBridge, openLoop, driveRight)
#pragma config(Motor,  port2,           RightBack,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           LeftBack,      tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port4,           BRightTower,   tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port5,           FRightTower,   tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port6,           FLeftTower,    tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port7,           BLeftTower,    tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port8,           RightFront,    tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port9,           LeftFront,     tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port10,          ArmLeft,       tmotorVex393_HBridge, openLoop, reversed, driveLeft)
#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
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

// ---------- Functions ---------- //
//function cap is 256, do not exceed this limit

void move_pivot_turn(int time, int power) { //Right Turn in place (pos. power = left, neg. = right) ---> 90 degree turn
	motor[LeftFront] = power;
	motor[LeftBack] = power;
	motor[RightFront] = power*-1;
	motor[RightBack] = power*-1;
	wait1Msec(time);
	motor[LeftFront] = 0;
	motor[LeftBack] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}
void move_swing_turn(int time, int lpower, int rpower) { //Adjustable Angle Turns (allows for swing turns by setting one value higher than the other)
	motor[LeftFront] = lpower;
	motor[LeftBack] = lpower;
	motor[RightFront] = rpower;
	motor[RightBack] = rpower;
	wait1Msec(time);
	motor[LeftFront] = 0;
	motor[LeftBack] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}
void move_straight(int time, int power) { //Move straight (positive for forward, negative for reverse)
	motor[LeftFront] = power;
	motor[LeftBack] = power;
	motor[RightFront] = power;
	motor[RightBack] = power;
	wait1Msec(time);
	motor[LeftFront] = 0;
	motor[LeftBack] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}
void move(int lpower,int rpower) {
	motor[LeftFront] = lpower;
	motor[LeftBack] = lpower;
	motor[RightFront] = rpower;
	motor[RightBack] = rpower;
}

void manipulator_tower(int time, int power) { //Raise/Lower Arm Tower
	motor[FLeftTower] = power;
	motor[BLeftTower] = power;
	motor[BRightTower] = power;
	motor[FRightTower] = power;
	wait1Msec(time);
	motor[FLeftTower] = 0;
	motor[BLeftTower] = 0;
	motor[BRightTower] = 0;
	motor[FRightTower] = 0;
}
void manipulator_arm(int time, int power) { //Raise/Lower Arm
	motor[ArmLeft] = power;
	motor[ArmRight] = power;
	wait1Msec(time);
	motor[ArmLeft] = 0;
	motor[ArmRight] = 0;
}
void dab(int time, int power) {
	manipulator_tower(600,127);//#EpicGamesWinSlay2018
	move_pivot_turn(time, power);
	move_pivot_turn(time, -power);
	move_swing_turn(time, power, power*-1);
}
void stop_all() {
	motor[ArmLeft] = 0;
	motor[ArmRight] = 0;
	motor[BLeftTower] = 0;
	motor[BRightTower] = 0;
	motor[FLeftTower] = 0;
	motor[FRightTower] = 0;
	motor[LeftBack] = 0;
	motor[LeftFront] = 0;
	motor[RightBack] = 0;
	motor[RightFront] = 0;
}
int autostart; //Whether or not autonomous has begun.
int auto=0; //Determines selected autonomous
int automin = 0; //Minimum value for autonomous scrolling
int automax = 8; //Maximum value for autonomous scrolling
int powerlevel;
// ------------------------------- //

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
task autoselectled() //LOOK HERE
{
	while(true) {
		if(vexRT[Btn8U]==1) { //Every time this button is pressed, increase 'auto' variable by 1.
			auto++;
			wait1Msec(200); //Keeps variable change from changing too fast.
		}
		if(auto>automax) { //Keeps 'auto' variable within range.
			auto=automin;
		}
		if(autostart==1) {
			stopTask(autoselectled);
		}
		if(auto==0) {
			while(auto==0) {
				SensorValue[LedFull]=1;
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=1;
			}
		}
		if(auto==1) { //Shows autonomous selection based on LED pattern
			while(auto==1) { //LED Full == Auto 1
				SensorValue[LedFull]=1;
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=0;
			}
			} else if(auto==2) {
			while(auto==2) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=1;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=0;
			}
			} else if(auto==3) {
			while(auto==3) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=1;
				SensorValue[LedRed]=0;
			}
			} else if(auto==4) {
			while(auto==4) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=1;
			}
			} else if(auto==5) { //Blinking LEDs to show the other 4 options.
			while(auto==5) {
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedFull]=1;
				wait1Msec(500);
				SensorValue[LedFull]=0;
				wait1Msec(500);
			}
			} else if(auto==6) {
			while(auto==6) {
				SensorValue[LedFull]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedGreen]=1;
				wait1Msec(500);
				SensorValue[LedGreen]=0;
				wait1Msec(500);
			}
			} else if(auto==7) {
			while(auto==7) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedYel]=1;
				wait1Msec(500);
				SensorValue[LedYel]=0;
				wait1Msec(500);
			}
			} else if(auto==8) {
			while(auto==8) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=1;
				wait1Msec(500);
				SensorValue[LedRed]=0;
				wait1Msec(500);
			}
		}
	}
}
task lcd { //For LCD Autonomous Selection
	int leftbutton = 1; //aliases for button numbers on LCD (yes, the LCD has buttons)
	int centerbutton = 2;
	int rightbutton = 4;
	while(true) {
		if(nLCDButtons==leftbutton) { //Scrolling controls
			if(auto>automin) {
				auto--;
				wait1Msec(250);
				} else {
				auto=automax;
			}
		}
		if(nLCDButtons==rightbutton) { //More Scrolling Controls
			if(auto<automax) {
				auto++;
				wait1Msec(250);
				} else {
				auto=automin;
			}
		}
		if(nLCDButtons==centerbutton) { //Lock-in selected autonomous
			clearLCDLine(1);
			stopTask(autoselectled);
			stopTask(lcd);
		}
		switch(auto) { //Sets the LCD to display the name of selected Autonomous.
		case 0:
			displayLCDCenteredString(1, "Auto Off");
			wait1Msec(100); //These waits keep the LCD from hogging up the Cortex CPU.
			break;
		case 1:
			displayLCDCenteredString(1, "Auto 1");
			wait1Msec(100);
			break;
		case 2:
			displayLCDCenteredString(1, "Auto 2");
			wait1Msec(100);
			break;
		case 3:
			displayLCDCenteredString(1, "Auto 3");
			wait1Msec(100);
			break;
		case 4:
			displayLCDCenteredString(1, "Auto 4");
			wait1Msec(100);
			break;
		case 5:
			displayLCDCenteredString(1, "Auto 5");
			wait1Msec(100);
			break;
		case 6:
			displayLCDCenteredString(1, "Auto 6");
			wait1Msec(100);
			break;
		case 7:
			displayLCDCenteredString(1, "Auto 7");
			wait1Msec(100);
			break;
		case 8:
			displayLCDCenteredString(1, "Auto 8");
			wait1Msec(100);
			break;
		}

		//OLD CODE//
		//if(auto==1) {
		//	displayLCDCenteredString(1, "Auto 1");
		//	wait1Msec(100);
		//}
		//if(auto==2) {
		//	displayLCDCenteredString(1, "Auto 2");
		//	wait1Msec(100);
		//}
		//if(auto==3) {
		//	displayLCDCenteredString(1, "Auto 3");
		//	wait1Msec(100);
		//}
		//if(auto==4) {
		//	displayLCDCenteredString(1, "Auto 4");
		//	wait1Msec(100);
		//}
		//if(auto==5) {
		//	displayLCDCenteredString(1, "Auto 5");
		//	wait1Msec(100);
		//}
		//if(auto==6) {
		//	displayLCDCenteredString(1, "Auto 6");
		//	wait1Msec(100);
		//}
		//if(auto==7) {
		//	displayLCDCenteredString(1, "Auto 7");
		//	wait1Msec(100);
		//}
		//if(auto==8) {
		//	displayLCDCenteredString(1, "Auto 8");
		//	wait1Msec(100);
		//}
		//OLD CODE//
	}
}
task batteryled()
{
	while(true) {
		float power=SensorValue[PEPower]/270.0;
		if(nImmediateBatteryLevel/1000>=8.5 && power>=8.5) { //Both full, blink LedFull
			while(true) {
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedFull]=1;
				wait1Msec(500);
				SensorValue[LedFull]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=8.5 && power>=8.0){ //Cortex full, PE good; solid Full, blink Green.
			while(true) {
				SensorValue[LedFull]=1;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedGreen]=1;
				wait1Msec(500);
				SensorValue[LedGreen]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=8.5 && power>=7.5) { //Cortex Full, PE OK; Solid Full, blink Yel
			while(true) {
				SensorValue[LedFull]=1;
				SensorValue[LedGreen]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedYel]=1;
				wait1Msec(500);
				SensorValue[LedYel]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=8.5 && power<7.5) { //Cortex Full, PE Bad; Solid Full, Blink Red
			while(true) {
				SensorValue[LedFull]=1;
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=1;
				wait1Msec(500);
				SensorValue[LedRed]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=8.0 && power>=8.5) { //Cortex Good, PE Full; Solid Green, Blink Full
			while(true) {
				SensorValue[LedGreen]=1;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedFull]=1;
				wait1Msec(500);
				SensorValue[LedFull]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=8.0 && power>=8.0) { //Cortex Good, PE Good; Blink Green
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedGreen]=1;
				wait1Msec(500);
				SensorValue[LedGreen]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=8.0 && power>=7.5) { //Cortex Good, PE OK; Solid Green, Blink Yel
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=1;
				SensorValue[LedRed]=0;
				SensorValue[LedYel]=1;
				wait1Msec(500);
				SensorValue[LedYel]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=8.0 && power<7.5) { //Cortex Good, PE Bad; Solid Green, Blink Red
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=1;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=1;
				wait1Msec(500);
				SensorValue[LedRed]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=7.5 && power>=8.5) { //Cortex OK, PE Full; Solid Yel, Bink Full
			while(true) {
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=1;
				SensorValue[LedRed]=0;
				SensorValue[LedFull]=1;
				wait1Msec(500);
				SensorValue[LedFull]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=7.5 && power>=8.0) { //Cortex OK, PE Good; Solid Yel, Blink Green
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedYel]=1;
				SensorValue[LedRed]=0;
				SensorValue[LedGreen]=1;
				wait1Msec(500);
				SensorValue[LedGreen]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=7.5 && power>=7.5) { //Cortex OK, PE OK; Blink Yel
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=0;
				SensorValue[LedRed]=0;
				SensorValue[LedYel]=1;
				wait1Msec(500);
				SensorValue[LedYel]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000>=7.5 && power<7.5) { //Cortex OK, PE Bad; Solid Yel, Blink Red
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=1;
				SensorValue[LedRed]=1;
				wait1Msec(500);
				SensorValue[LedRed]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000<7.5 && power>=8.5) { //Cortex Bad, PE Full; Solid Red, Blink Full
			while(true) {
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=1;
				SensorValue[LedFull]=1;
				wait1Msec(500);
				SensorValue[LedFull]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000<7.5 && power>=8.0) { //Cortex Bad, PE Good; Solid Red, Blink Green
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=1;
				SensorValue[LedGreen]=1;
				wait1Msec(500);
				SensorValue[LedGreen]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000<7.5 && power>=7.5) { //Cortex Bad, PE OK; Solid Red, Blink Yel
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=0;
				SensorValue[LedRed]=1;
				SensorValue[LedYel]=1;
				wait1Msec(500);
				SensorValue[LedYel]=0;
				wait1Msec(500);
			}
			} else if(nImmediateBatteryLevel/1000<7.5 && power<7.5) { //Cortex Bad, PE Bad; Blink Red
			while(true) {
				SensorValue[LedFull]=0;
				SensorValue[LedGreen]=0;
				SensorValue[LedYel]=0;
				SensorValue[LedRed]=1;
				wait1Msec(500);
				SensorValue[LedRed]=0;
				wait1Msec(500);
			}
		}
	}
}
void pre_auton()
{
	bStopTasksBetweenModes = false;
	startTask(lcd);
	startTask(autoselectled);
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
	autostart=1;
	startTask(batteryled);
	switch(auto) { //Runs different autonomous based on the value of 'auto'
	case 0: //This is if we want to disable autonomous... when auto == 0, do nothing.
		break;
	case 1:
		motor[LeftFront]=127;
		break;
	case 2:
		motor[LeftBack]=127;
		break;
	case 3:
		motor[RightFront]=127;
		break;
	case 4:
		motor[RightBack]=127;
		break;
	case 5:
		motor[LeftFront]=-127;
		break;
	case 6:
		motor[LeftBack]=-127;
		break;
	case 7:
		motor[RightFront]=-127;
		break;
	case 8:
		motor[RightBack]=-127;
		break;
	}
	//OLD CODE//
	//if(auto==1) {
	//	motor[LeftFront]=127;
	//	} else if(auto==2) {
	//	motor[LeftBack]=127;
	//	} else if(auto==3) {
	//	motor[RightFront]=127;
	//	} else if(auto==4) {
	//	motor[RightBack]=127;
	//	} else if(auto==5) {
	//	motor[LeftFront]=-127;
	//	} else if(auto==6) {
	//	motor[LeftBack]=-127;
	//	} else if(auto==7) {
	//	motor[RightFront]=-127;
	//	} else if(auto==8) {
	//	motor[RightBack]=-127;
	//}
	//OLD CODE//
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
	while (true)
	{
		motor[RightFront] = vexRT[Ch3]; //Left Front motor to left joystick
		motor[RightBack] = vexRT[Ch3]; //Left Back motor to left joystick
		motor[LeftFront] = vexRT[Ch2]; //Right Front to right joystick
		motor[LeftBack] = vexRT[Ch2]; //Right Back to right joystick

		//Tower controls
		if(vexRT[Btn6U] == 1) { //Tower one controls (left from front)
			motor[FLeftTower] = 127; //FLeft = Left front tower motor, BRight = Back right tower motor
			motor[BLeftTower] = 127;
			motor[BRightTower] = 127;
			motor[FRightTower] = 127;
			} else if(vexRT[Btn6D] == 1) { //Tower two controls (right from front)
			motor[FLeftTower] = -127;
			motor[BLeftTower] = -127;
			motor[BRightTower] = -127;
			motor[FRightTower] = -127;
			} else { //Stop towers if nothing is pressed
			motor[FLeftTower] = 0;
			motor[BLeftTower] = 0;
			motor[BRightTower] = 0;
			motor[FRightTower] = 0;
		}

		if(vexRT[Btn7U] == 1) { //Tower Up Button
			manipulator_tower(300, 127);
			} else if(vexRT[Btn7D] == 1) { //Tower Down Button
			manipulator_tower(300,-127); //Hopefully this works... and doesn't break anything. =)
		}

		//Arm controls
		if(vexRT[Btn5U] == 1) {
			motor[ArmLeft] = 30;
			motor[ArmRight] = 30;
			} else if(vexRT[Btn5D] == 1) {//Extend Outwards
			motor[ArmLeft] = -90;
			motor[ArmRight] = -90;
			}	else{ //Stop arms if nothing is pressed
			motor[ArmLeft] = 0;
			motor[ArmRight] = 0;
		}
		//OLD CODE//
		//	//Battery Lights
		//	if(nImmediateBatteryLevel/1000>=8.5) {
		//		SensorValue[LedFull]=1;
		//		SensorValue[LedGreen]=1;
		//		SensorValue[LedRed]=0;
		//		SensorValue[LedYel]=0;
		//		} else if(nImmediateBatteryLevel/1000>=8.0){
		//		SensorValue[LedFull]=0;
		//		SensorValue[LedGreen]=1;
		//		SensorValue[LedRed]=0;
		//		SensorValue[LedYel]=0;
		//		} else if(nImmediateBatteryLevel/1000>=7.5){
		//		SensorValue[LedFull]=0;
		//		SensorValue[LedGreen]=0;
		//		SensorValue[LedRed]=0;
		//		SensorValue[LedYel]=1;
		//		} else if(nImmediateBatteryLevel/1000<7.5){
		//		SensorValue[LedFull]=0;
		//		SensorValue[LedGreen]=0;
		//		SensorValue[LedRed]=1;
		//		SensorValue[LedYel]=0;
		//	}
		//OLD CODE//
	}
}
