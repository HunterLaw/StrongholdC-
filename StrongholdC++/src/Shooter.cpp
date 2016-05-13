/*
 * Shooter.cpp
 *
 *  Created on: May 12, 2016
 *      Author: Hunter
 */

#include <Shooter.h>
#include <cmath>
#include <math.h>

Shooter::Shooter()
{
	rightPitchingMotor = new CANTalon(kRightShooterPitcherMotorCanId);
	leftPitchingMotor = new CANTalon(kLeftShooterPitcherMotorCanId);
	tiltMotor = new CANTalon(kShooterAngleMotorCanId);
	//TODO: Check motor voltage to direction
	tiltMotor->ConfigLimitSwitchOverrides(true, false);

	rightPitchingMotor->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	leftPitchingMotor->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	tiltMotor->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);

	tiltMotor->ConfigMaxOutputVoltage(kShooterTiltMaxVolt);

	ballShooter = new Solenoid(kShooterBallShooterSolenoidChanel);
	ballShooter->Set(false);

	tiltSetpoint = ShooterState::kUnknown;

	// Disable tilt position control until we've reached the home position
	disablePitchingMachineSpeedControl();
	disableTiltPositionControl();
	shooting = false;
	autopilotEnabled = false;
}
void Shooter::setAutoPilot(bool val)
{
	autopilotEnabled = val;
}
void Shooter::shoot2()
{
	if(!shooting)
	{
//			System.out.println("Shooter 2");
		rightPitchingMotor->Set(kShooterShootPitchingMachineSpeed);
		leftPitchingMotor->Set(-kShooterShootPitchingMachineSpeed);
		shooting = true;
		shootAccel = true;
		shootUpToSpeed = false;
		/*timer = new Timer();
		long timeout = Parameters.kShooterPitchingMachineAccelTimeout;
		timer.schedule(new shooter2(),timeout);*/
	}
}
void Shooter::shoot()
{
	rightPitchingMotor->Set(kShooterShootPitchingMachineSpeed);
	leftPitchingMotor->Set(-kShooterShootPitchingMachineSpeed);
	shooting = true;
	shootAccel = true;
	shootUpToSpeed = false;
	/*timer = new Timer();
	long timeout = Parameters.kShooterPitchingMachineAccelTimeout;
	timer.schedule(this,timeout);
	//TODO: Add java timer for shoot up to speed*/
}
void Shooter::reload()
{
	rightPitchingMotor->Set(-kShooterReloadPitchingMachineSpeed);
	leftPitchingMotor->Set(kShooterReloadPitchingMachineSpeed);
}
void Shooter::setShootAngle(ShooterState shooterPosition)
{
	tiltSetpoint = shooterPosition;

}
void Shooter::resetTiltAngle()
{
	tiltMotor->SetPosition(0);
}
void Shooter::manualRunTiltMotor(double value)
{
	disableTiltPositionControl();
	tiltMotor->Set(value);
}
void Shooter::manualRunPitchingMachine(double value)
{
	if (isPitchingMachineSpeedControlEnabled())
	{
		disablePitchingMachineSpeedControl();
	}
	rightPitchingMotor->Set(value);
	leftPitchingMotor->Set(-value);
	autopilotEnabled = false;
}
void Shooter::pushBall(bool push)
{
	ballShooter->Set(push);
}
void Shooter::disableTiltPositionControl()
{
	tiltMotor->Disable();
	tiltMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	tiltMotor->ConfigEncoderCodesPerRev(kEncoderCodesPerRev);
	tiltMotor->SetControlMode(CANTalon::kPercentVbus);
	tiltMotor->Enable();
	autopilotEnabled = false;
}
void Shooter::enableTiltPositionControl()
{
	tiltMotor->Disable();
	tiltMotor->SetControlMode(CANTalon::kPosition);
	tiltMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	tiltMotor->ConfigEncoderCodesPerRev(kEncoderCodesPerRev);
	tiltMotor->SetPID(kShootTiltPositionControlProportional,
			kShootTiltPositionControlIntegral,
			kShootTiltPositionControlDifferential);
	tiltMotor->Enable();
}
void Shooter::disablePitchingMachineSpeedControl()
{
	rightPitchingMotor->Disable();
	leftPitchingMotor->Disable();
	rightPitchingMotor->SetControlMode(CANTalon::kPercentVbus);
	leftPitchingMotor->SetControlMode(CANTalon::kPercentVbus);
	rightPitchingMotor->Enable();
	leftPitchingMotor->Enable();
	autopilotEnabled = false;
}
void Shooter::enablePictchingMachineSpeedControl()
{
	rightPitchingMotor->Disable();
	leftPitchingMotor->Disable();

	rightPitchingMotor->SetControlMode(CANTalon::kSpeed);
	rightPitchingMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	leftPitchingMotor->ConfigEncoderCodesPerRev(kEncoderCodesPerRev);
	rightPitchingMotor->ConfigEncoderCodesPerRev(kEncoderCodesPerRev);

	rightPitchingMotor->SetPID(kShootPitchPositionControlProportional,
			kShootPitchPositionControlIntegral,
			kShootPitchPositionControlDifferential);
	leftPitchingMotor->SetControlMode(CANTalon::kSpeed);
	leftPitchingMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	leftPitchingMotor->SetPID(kShootPitchPositionControlProportional,
			kShootPitchPositionControlIntegral,
			kShootPitchPositionControlDifferential);

	rightPitchingMotor->Enable();
	leftPitchingMotor->Enable();
}
void Shooter::setTiltMemSetpoint(double value)
{
	autopilotEnabled = true;
	memSetpointSet = true;
	tiltMemSetpoint = value;
}
void Shooter::setShooterAngle(double angleSetpoint)
{
	double setpoint = toRadians(angleSetpoint);
	double tang = tan(setpoint);

//    	double constant = Parameters.kGoalHeight/Parameters.kShooterOffSetFromCamera;
	double h = kGoalHeight;
	double d = kShooterOffSetFromCameraZ;
	double hgd = kHeightGoalDifference;

	double angleInRads = atan((h+hgd)/((h/tang)+d));
	double newAngle = toDegrees(angleInRads);
//    	newAngle -= 5;
	double newPosition = (-3.7*newAngle/68.5)+3.7;
//    	System.out.println("Setpoint: "+setpoint);
//    	System.out.println("tan: "+tan);
//    	System.out.println("constant: "+constant);
//    	System.out.println("angle in rads: "+angleInRads);
//    	System.out.println("new angle: "+newAngle);
//    	System.out.println("New position: "+newPosition);
	setTiltMemSetpoint(newPosition);
}
void Shooter::process()
{
	/*SmartDashboard.putNumber("Tilt Voltage", tiltMotor.getOutputVoltage());
	SmartDashboard.putNumber("Tilt Current", tiltMotor.getOutputCurrent());
	SmartDashboard.putNumber("L Volt", leftPitchingMotor.getOutputVoltage());
	SmartDashboard.putNumber("L Current", leftPitchingMotor.getOutputCurrent());
	SmartDashboard.putNumber("R Volt", rightPitchingMotor.getOutputVoltage());
	SmartDashboard.putNumber("R Current",rightPitchingMotor.getOutputCurrent());
	SmartDashboard.putBoolean("Tilt Up Limit",tiltMotor.isFwdLimitSwitchClosed());
	SmartDashboard.putBoolean("Tilt Down Limit",tiltMotor.isRevLimitSwitchClosed());
	SmartDashboard.putNumber("Tilt Pos", tiltMotor.getPosition());
	SmartDashboard.putNumber("Shooter Tilt Angle",((3.7-tiltMotor.getPosition())*68.5/3.7));
	SmartDashboard.putNumber("MemSetpoint", tiltMemSetpoint);
	if(currentPosition != NULL)
		SmartDashboard.putString("Shooter State", currentPosition.name());
	else
		SmartDashboard.putString("Shooter State", "UNKNOWN");
//    	double tiltPosition = tiltMotor.getPosition();
	SmartDashboard.putBoolean("Is at setpoint", isTiltAngleAtSetpoint());*/
	//TODO: Check for fwd or rev if motor power swapped
	if(tiltMotor->IsFwdLimitSwitchClosed())
	{
//    		tiltMotor.setPosition(0);
		currentPosition = ShooterState::kHome;
		memSetpointSet = false;
	}
	//PitchingMachine method just retracts kicker, extends dink and turns motor off
	if(tiltMotor->GetOutputCurrent() > kShooterTiltMaxCurrent)
	{
		disableTiltPositionControl();
		currentPosition = ShooterState::kUnknown;
		tiltMotor->Set(0);
		autopilotEnabled = false;
	}
	if(isAutoPilotEnabled())
	{
		if(currentPosition == ShooterState::kUnknown)
		{
			// We don't know the shooter's tilt angle, run the shooter in reverse at a slow
			// constant speed until we reach the reverse limit switch.
			disableTiltPositionControl();
			tiltMotor->Set(kShooterSeekHomePower);
			if (tiltMotor->IsFwdLimitSwitchClosed());
			{
				currentPosition = ShooterState::kHome;
				tiltMotor->Set(0.0);
				enableTiltPositionControl();
			}

		}
		else if (!memSetpointSet)
		{
			switch (tiltSetpoint)
			{
				case kUnknown:
					std::cout << "SHOULD NEVER HAPPEN IN SHOOTER";
					break;

				case kHome:
				case kLowBar:
					manualRunPitchingMachine(0.0);
					if(isTiltAngleAtSetpoint())
					{
						currentPosition = tiltSetpoint;
						tiltMotor->Set(0.0);
					}
					else
					{
						tiltMotor->Set(getMotorPower());
					}
					break;

				case kReload:
					if(isTiltAngleAtSetpoint())
					{
						currentPosition = tiltSetpoint;
						tiltMotor->Set(0.0);
						manualRunPitchingMachine(kShooterReloadPitchingMachineSpeed);
					}
					else
					{
						tiltMotor->Set(getMotorPower());
					}
					break;

				case kShootBatter:
				case kShootTape:
				case kShootDefense:
					if(isTiltAngleAtSetpoint())
					{
						currentPosition = tiltSetpoint;
						tiltMotor->Set(0.0);
						if(!shootAccel && !shootUpToSpeed && !shooting)
						{
							shoot();
						}
						else if(shooting && isPitchingMachineUpToSpeed())
						{
							pushBall(true);
							/*if(timer != null)
							{
								timer = null;
							}
							timer = new Timer();
							timer.schedule(this, Parameters.kShooterPitchingMachinePushBallTimeout);*/
							shooting = false;
						}
					}
					else
					{
						tiltMotor->Set(getMotorPower());
					}

					break;
			}
		}
		else
		{
			//We are moving to a custom setpoint
			if(isTiltAngleAtSetpoint())
			{
				tiltMotor->Set(0.0);
				memSetpointSet = false;
			}
			else
			{
				tiltMotor->Set(getMotorPower());
			}
		}
	}
}
double Shooter::getMotorPower()
{
	double rc = 0;
	if(isTiltAngleAtSetpoint())
	{
		rc = 0;
	}
	else if(memSetpointSet)
	{
		if(tiltMotor->GetPosition() > tiltMemSetpoint)
		{
			rc = kShooterSeekHomePower;
		}
		else if(tiltMotor->GetPosition() < tiltMemSetpoint)
		{
			rc = -kShooterSeekHomePower*0.65;
		}
	}
	else if(tiltMotor->GetPosition() > tiltSetpoint)
	{
		rc = kShooterSeekHomePower;
	}
	else if(tiltMotor->GetPosition() < tiltSetpoint)
	{
		rc = -kShooterSeekHomePower*0.65;
	}
	return rc;
}
bool Shooter::isPitchingMachineOn()
{
	double volt = leftPitchingMotor->GetOutputVoltage();
	return abs(volt) >= kMotorVoltageDeadband;
}
bool Shooter::isTiltAngleAtSetpoint()
{
	if(memSetpointSet)
	{
		return abs(getTiltAngle()) <= tiltMemSetpoint+kShooterSeekTolerance;
	}
	else
	{
		return abs(getTiltAngle()) <= tiltSetpoint+kShooterSeekTolerance;
	}
	return false;
}
double Shooter::getShooterAngle()
{
	return ((3.7-tiltMotor->GetPosition())*68.5/3.7);
}
bool Shooter::isPitchingMachineSpeedControlEnabled()
{
	return leftPitchingMotor->GetControlMode() == CANTalon::kSpeed;
}
double Shooter::toRadians(double angle)
{
	return (angle*M_PI)/180;
}
double Shooter::toDegrees(double rads)
{
	return (rads*180)/M_PI;
}
