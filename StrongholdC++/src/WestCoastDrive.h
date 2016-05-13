/*
 * WestCoastDrive.h
 *
 *  Created on: May 12, 2016
 *      Author: Robotics
 */

#ifndef SRC_WESTCOASTDRIVE_H_
#define SRC_WESTCOASTDRIVE_H_
#include "DriveUnit.h"
class WestCoastDrive
{
public:
	enum Gear{kLowGear,kHighGear};
	WestCoastDrive();
	void pidWrite(double output);
	void setSpeedSetpoint(double setPoint);
	void setSpeedSetpoint(double leftSetPoint,double rightSetPoint);
	void setTurnSetpoint(double value);
	void setGear(Gear value);
	void process();
	Gear getGear(){return gear;};
	double getTurnSetpoint(){return leftSide->getTurnSetpoint();};
	double getSpeedSetpoint(){return leftSide->getSpeedSetpoint();};
protected:
	DriveUnit *leftSide;
	DriveUnit *rightSide;
	Gear gear;
	Solenoid *highGear;
	Solenoid *lowGear;
};

#endif /* SRC_WESTCOASTDRIVE_H_ */
