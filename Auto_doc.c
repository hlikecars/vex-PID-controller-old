#pragma config(Sensor, port2,  touchled,       sensorVexIQ_LED)
#pragma config(Sensor, port3,  gyro,           sensorVexIQ_Gyro)
#pragma config(Sensor, port7,  Bumper,         sensorVexIQ_Touch)
#pragma config(Sensor, port9,  Color,          sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port11, touch2,         sensorVexIQ_LED)
#pragma config(Motor,  motor1,          left,          tmotorVexIQ, openLoop, reversed, driveLeft, encoder)
#pragma config(Motor,  motor4,          hook,          tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,          right,         tmotorVexIQ, openLoop, driveRight, encoder)
#pragma config(Motor,  motor8,          arm2,          tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor10,         arm,           tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
* Advanced Drive Control
*
* Example:
*  adcMove(forward, 100, 100, gyroSensor);
*  adcMove(leftward, 100, 50, gyroSensor, centerMotor);
*  adcTurn(left, 45, gyroSensor);
*  adcTurn(right, 90, gyroSensor);
*/
#include "Global_Angle_PID.c";

short i;

task raise()
{
	setMotorSpeed(arm, 100);
	setMotorSpeed(arm2,100);
	waitUntil(getBumperValue(bumper)==1);
	stopMotor(arm);
	stopMotor(arm2);
	//armencoder = getMotorEncoder(arm);
}
void lower(){
	setMotorTarget(arm,-10,-100);
	setMotorTarget(arm2,-10,-100);
}
void clamp(){
	setMotor(Hook,-100);
	wait1Msec(350);
	stopMotor(Hook);
}


void unclamp()
{
	setMotorTarget(hook,0,100);
}



void drop()
{
	SetMotorTarget(arm,360,80);
	SetMotorTarget(arm2,360,80);
	wait1Msec(500);
	unclamp();
	waitUntilMotorStop(hook);
}


void reset()
{
	setMotorBrakeMode(hook,motorbrake);
	setMotor(hook,100);
	wait1Msec(800);
	stopMotor(hook);
	wait1Msec(250);
	resetMotorEncoder(hook);
	setMotorBrakeMode(hook,motorhold);
}

task showscreen(){
	double l, r;
	while(true){
		l = getMotorEncoder(left);
		r = getMotorEncoder(right);
		eraseUserScreenArea();
		displayTextLine(1, "Heading: %d",  getgyroheading(gyro));
		displayTextLine(2, "terror: %d",  terror);
		displayTextLine(3, "l: %d", l);
		displayTextLine(4,"r: %d", r);
		wait1Msec(100);

	}
}

void p_left(){
	waitUntil(getTouchLEDValue(touchled)==1);
		resetGyro(gyro);
		wait1Msec(100);
		setMotorTarget(Hook,0,100);
		//first stack
		constant_drive(285,70,0,1.4);
		turn_to(90);
		constant_drive(450,40,91,1.3);
		clamp();
		starttask(raise);
		constant_drive(-100,-70,90,1.3);
		Turn_to(50);
		constant_drive(-290,-70,50,1.3);
		Turn_to(90);
		constant_drive(350,60,86,1.3); //push riser in
		drop();
		constant_drive(-270,-70,90,1.3);
		Turn_to(0);
		setMotorBrakeMode(left,motorCoast);
		setMotorBrakeMode(right,motorCoast);
		resetMotorEncoder(left);
		resetMotorEncoder(right);

		//middle riser
		constant_drive(655,70,0,1.3);
		Turn_to(90);
		constant_drive(280,60,90,1.3);
		constant_drive(-230,-70,90,1.3);
		Turn_to(0);
		lower();
		constant_drive(410,70,0,1.3);
		Turn_to(90);
		//last stack
		constant_drive(260,40,90,1.3);
		clamp();
		starttask(raise);
		constant_drive(-100,-70,90,1.3);
		Turn_to(130);
		constant_drive(-320,-70,130,1.3);
		Turn_to(90);
		constant_drive(345,60,90,1.3);
		drop();
		constant_drive(-590,-100,90,1.3);
		lower();
		constant_drive(50,100,90,1);
}

void p_right(){

		waitUntil(getTouchLEDValue(touchled)==1);
		resetGyro(gyro);
		wait1Msec(100);
		lower();
		setMotorTarget(Hook,0,100);
		//first stack
		constant_drive(285,70,0,1.4);
		turn_to(270);
		constant_drive(450,40,270,1.3);
		clamp();
		starttask(raise);
		constant_drive(-100,-70,270,1.3);
		Turn_to(310);
		constant_drive(-270,-70,310,1.3);
		Turn_to(270);
		constant_drive(300,60,274,1.3); //push riser in
		drop();
		constant_drive(-300,-70,270,1.3);
		Turn_to(0);
		//middle riser
		constant_drive(655,70,0,1.3);
		Turn_to(270);
		constant_drive(280,60,270,1.3);
		constant_drive(-250,-70,270,1.3);
		Turn_to(0);
		lower();
		constant_drive(430,70,0,1.3); //THIS STUPID THING
		Turn_to(270);
		//last stack
		constant_drive(250,40,270,1.3);
		clamp();
		starttask(raise);
		constant_drive(-100,-70,270,1.3);
		Turn_to(230);
		constant_drive(-320,-70,230,1.3);
		Turn_to(270);
		constant_drive(370,60,270,1.3);
		drop();
		constant_drive(-120,-100,270,1.3);
		lower();
}




task main()
{
	///tune///

	///tune///
	setMotorBrakeMode(left,motorBrake);
	setMotorBrakeMode(right,motorBrake);
	setTouchLEDColor(touchled,colorRed);
	setTouchLEDColor(touchled,colorGreen);
	resetGyro(gyro);
	startTask(gyroTask);
	startTask(showscreen);
	//playSoupnd(soundTada);
	//reset();

		//constant_drive(-600,-80,300,1.5);

	p_right();

		////left side

	p_left();






	setMotorBrakeMode(left,motorCoast);
	setMotorBrakeMode(right,motorCoast);
	resetMotorEncoder(left);
	resetMotorEncoder(right);
}