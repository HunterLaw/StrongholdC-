/*
 * DriveUnit.h
 *
 *  Created on: May 12, 2016
 *      Author: Hunter
 */

#ifndef SRC_DRIVEUNIT_H_
#define SRC_DRIVEUNIT_H_
#include "WPILib.h"
class DriveUnit
{
public:
	enum Placement {Left,Right};
	DriveUnit(Placement p);
	double getSpeedSetpoint(){return speedSetpoint;}
	void setSpeedSetpoint(double value);
	void process();
	bool isCurrentThresholdExceeded(){return masterMotor->GetOutputCurrent() >=0;};
	bool isSpeedControlEnabled() {return masterMotor->GetControlMode() == CANSpeedController::kSpeed;};
	void setSpeedControl(bool speed);
	Placement getPlacement() {return placement;};
	void setTurnSetpoint(double value);
	double getTurnSetpoint(){return turnSetpoint;};
protected:
	int speedSetpoint;
	int turnSetpoint;
	Placement placement;
	CANTalon *masterMotor;
	CANTalon *followerMotor;
};



#endif /* SRC_DRIVEUNIT_H_ */
