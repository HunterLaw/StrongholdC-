/*
 * PusherArm.h
 *
 *  Created on: May 12, 2016
 *      Author: Robotics
 */

#ifndef SRC_PUSHERARM_H_
#define SRC_PUSHERARM_H_
#include "WPILib.h"
class PusherArm {
public:
	enum Position {kUnknown,kHome,kDown};
	PusherArm();
	void enableTiltPositionControl();
	void disableTiltPositionControl();
	void setAutopilot(bool enabled);
	void manualSetTilt(double value);
	void setTiltPosition(Position newPosition);
	void processs();
	bool isTiltMotorPositionControlEnabled(){return tiltMotor->GetControlMode() == CANTalon::kPosition;};
	bool isKnownsPosition(){return currentPosition != kUnknown;};
	bool isPositionAtSetpoint();
	bool isMoving();
protected:

	CANTalon *tiltMotor;
	bool autopilotEnabled;
	Position positionSetpoint;
	Position currentPosition;
};

#endif /* SRC_PUSHERARM_H_ */
