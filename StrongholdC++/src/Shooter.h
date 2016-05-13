/*
 * Shooter.h
 *
 *  Created on: May 12, 2016
 *      Author: Hunter
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_
#include "Parameters.h"
class Shooter
{
public:
	enum ShooterState { kHome,kUnknown,kShoot,kShootBatter,kShootTape,kShootDefense,kLowBar,kReload};
	Shooter();
	void setAutoPilot(bool val);
	void shoot2();
	void shoot();
	void reload();
	void setShootAngle(ShooterState shooterPosition);
	void resetTiltAngle();
	void manualRunTiltMotor(double value);
	void manualRunPitchingMachine(double value);
	void pushBall(bool push);
	void disableTiltPositionControl();
	void enableTiltPositionControl();
	void disablePitchingMachineSpeedControl();
	void enablePictchingMachineSpeedControl();
	void setTiltMemSetpoint(double value);
	void setShooterAngle(double angleSetpoint);
	void process();
	double getMotorPower();
	bool isPitchingMachineUpToSpeed(){return shootAccel && shootUpToSpeed;};
	double getTiltMemSetpoint(){return tiltMemSetpoint;};
	double getTiltSetpoint(){return tiltMemSetpoint;};
	double getTiltAngle(){return tiltMotor->GetPosition();};
	bool isPitchingMachineOn();
	bool isKnownPosition() {return tiltSetpoint != ShooterState::kUnknown;};
	bool isTiltAngleAtSetpoint();
	bool isShooterHome(){return currentPosition == ShooterState::kHome;};
	double getShooterAngle();
	bool isPitchingMachineSpeedControlEnabled();
	bool isShooting(){return shooting;};
	bool isAutoPilotEnabled(){return autopilotEnabled;};
	double toRadians(double angle);
	double toDegrees(double rad);
private:
	bool shootAccel = false;
	bool shootUpToSpeed = false;
	double tiltMemSetpoint;
	bool memSetpointSet = false;
protected:
	ShooterState tiltSetpoint;
	ShooterState currentPosition;
	CANTalon *rightPitchingMotor;
	CANTalon *leftPitchingMotor;
	CANTalon *tiltMotor;
	Solenoid *ballShooter;
	bool shooting;
	bool autopilotEnabled;
};

#endif /* SRC_SHOOTER_H_ */
