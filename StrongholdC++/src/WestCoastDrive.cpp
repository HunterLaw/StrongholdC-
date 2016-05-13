/*
 * WestCoastDrive.cpp
 *
 *  Created on: May 12, 2016
 *      Author: Robotics
 */

#include <WestCoastDrive.h>
#include "Parameters.h"

WestCoastDrive::WestCoastDrive()
{
	leftSide = new DriveUnit(DriveUnit::Placement::Left);
	rightSide = new DriveUnit(DriveUnit::Placement::Right);
	highGear = new Solenoid(kHighGearSolenoidChanel);
	lowGear = new Solenoid(kLowGearSolenoidChanel);
	setGear(kLowGear);
}

void WestCoastDrive::pidWrite(double output)
{
	std::cout << "PID write:" << output << endl;
	setTurnSetpoint(output);
}
void WestCoastDrive::setSpeedSetpoint(double setPoint)
{
	leftSide->setSpeedSetpoint(setPoint);
	rightSide->setSpeedSetpoint(setPoint);
}
void WestCoastDrive::setSpeedSetpoint(double leftSetPoint,double rightSetPoint)
{
	leftSide->setSpeedSetpoint(leftSetPoint);
	rightSide->setSpeedSetpoint(rightSetPoint);
}
void WestCoastDrive::setTurnSetpoint(double value)
{
	double leftvalue = value;
	double rightvalue = -value;
	leftSide->setTurnSetpoint(leftvalue);
	rightSide->setTurnSetpoint(rightvalue);
}
void WestCoastDrive::setGear(Gear value)
{
	gear = value;
	if(gear == kLowGear)
	{
		highGear->Set(false);
		lowGear->Set(true);
	}
	else
	{
		lowGear->Set(false);
		highGear->Set(true);
	}
}
void WestCoastDrive::process()
{
	leftSide->process();
	rightSide->process();
}

