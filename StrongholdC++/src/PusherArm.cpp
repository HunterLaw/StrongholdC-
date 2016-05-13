/*
 * PusherArm.cpp
 *
 *  Created on: May 12, 2016
 *      Author: Robotics
 */

#include <PusherArm.h>
#include "Parameters.h"

PusherArm::PusherArm()
{
	tiltMotor = new CANTalon(kPusherArmMotorCanId);
	tiltMotor->ConfigLimitSwitchOverrides(true,false);
	tiltMotor->Enable();
	disableTiltPositionControl();
	autopilotEnabled = false;
	positionSetpoint = Position::kHome;
	currentPosition = Position::kUnknown;
}

void PusherArm::enableTiltPositionControl()
{
	tiltMotor->Disable();
	tiltMotor->SetControlMode(CANTalon::kPosition);
	tiltMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	tiltMotor->SetPID(kPusherArmPositionControlProportional,
		 	kPusherArmPositionControlIntegral,
		 	kPusherArmPositionControlDifferential);
	tiltMotor->Enable();
}
void PusherArm::disableTiltPositionControl()
{
	tiltMotor->SetControlMode(CANTalon::kPercentVbus);
	tiltMotor->Enable();
   	tiltMotor->Set(0);
   	autopilotEnabled = false;
}
void PusherArm::setAutopilot(bool enabled)
{
	autopilotEnabled = enabled;
}
void PusherArm::manualSetTilt(double value)
{
	disableTiltPositionControl();
	tiltMotor->Set(value);
}
void PusherArm::setTiltPosition(Position newPosition)
{
	positionSetpoint = newPosition;
}
void PusherArm::processs()
{
	if (tiltMotor->GetOutputCurrent() > kPusherArmMaxMotorCurrent)
	    	{
	    		disableTiltPositionControl();
	    	}

	    	if (autopilotEnabled)
	    	{
	    		if (currentPosition == kUnknown)
	    		{
	    			manualSetTilt(kPusherArmHomeMotorPower);
	    		}
	    		else if (positionSetpoint == kHome)
	    		{
	    			if (!isTiltMotorPositionControlEnabled())
	    			{
	    				enableTiltPositionControl();
	    			}
	    			tiltMotor->Set(kPusherArmHomeSetPoint);
	    		}
	    		else if (positionSetpoint == kDown)
	    		{
	    			if (!isTiltMotorPositionControlEnabled())
	    			{
	    				enableTiltPositionControl();
	    			}
	    			tiltMotor->Set(kPusherArmDownSetPoint);
	    		}

	    	}

	    	if (tiltMotor->IsRevLimitSwitchClosed())
	    	{
	    		currentPosition = kHome;
	    		tiltMotor->SetPosition(0);
	    		tiltMotor->Set(0);
	    	}
}
bool PusherArm::isPositionAtSetpoint()
{
	bool rc = true;
	if(currentPosition == kUnknown || currentPosition != positionSetpoint)
	{
		rc = false;
	}
	return rc;
}
bool PusherArm::isMoving()
{
	double volt = tiltMotor->GetOutputVoltage();
	bool rc = true;
	if(volt <= kMotorVoltageDeadband || volt >= (-kMotorVoltageDeadband))
	{
		rc = false;
	}
	return rc;
}

