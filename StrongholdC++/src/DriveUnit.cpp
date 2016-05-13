#include <DriveUnit.h>
#include "Parameters.h"
DriveUnit::DriveUnit(Placement p)
{
	placement = p;
	speedSetpoint =0;
	turnSetpoint =0;
	if(p == Placement::Right)
	{
		masterMotor = new CANTalon(kRightMasterDriveMotorCanId);
		followerMotor = new CANTalon(kRightFollowerDriveMotorCanId);
		followerMotor->Set(kRightMasterDriveMotorCanId);

	}
	else if(p == Placement::Left)
	{
		masterMotor = new CANTalon(kLeftMasterDriveMotorCanId);
		followerMotor = new CANTalon(kLeftFollowerDriveMotorCanId);
		followerMotor->Set(kLeftMasterDriveMotorCanId);

	}
	masterMotor->SetControlMode(CANSpeedController::kPercentVbus);
	followerMotor->SetControlMode(CANSpeedController::kFollower);


	masterMotor->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake);
	followerMotor->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake);

}

void DriveUnit::process()
{
	/*if(placement == Placement::Left)
	{
		SmartDashboard::PutNumber("Left Top V",masterMotor->GetOutputVoltage());
		SmartDashboard::PutNumber("Left Top C",masterMotor->GetOutputCurrent());
	    SmartDashboard::PutNumber("Left Bot V",followerMotor->GetOutputVoltage());
	    SmartDashboard::PutNumber("Left Bot C",followerMotor->GetOutputCurrent());

	}
	else if(placement == Placement::Right)
	{
	  	SmartDashboard::PutNumber("Right Top V",masterMotor->GetOutputVoltage());
	   	SmartDashboard::PutNumber("Right Top C",masterMotor->GetOutputCurrent());
	   	SmartDashboard::PutNumber("Right Bot V",followerMotor->GetOutputVoltage());
	   	SmartDashboard::PutNumber("Right Bot C",followerMotor->GetOutputCurrent());
	}*/
	double setpoint = speedSetpoint;
	if (placement == Placement::Left)
	{
		turnSetpoint = - turnSetpoint;
	}

	if (turnSetpoint != 0.0)
	{
		// We are turning
		if (speedSetpoint == 0.0)
		{
			// Priority #1
			// We're spinning in place
			if (turnSetpoint < 0.0)
			{
				// We're turning to the left
				if (placement == Placement::Left)
				{
					setpoint = -turnSetpoint;
				}
				else
				{
					setpoint = turnSetpoint;
				}

			}
			else
			{
						// We're turning to the right
				if (placement == Placement::Right)
				{
					setpoint = turnSetpoint;
				}
				else
				{
					setpoint = -turnSetpoint;
				}

			}
		}
		else
		{
			// Priority #2
			// We're turning while moving forward/backwards, subtract the turn setpoint
			// percentage from the inside set of wheels
			if (turnSetpoint < 0.0)
			{
				// We're turning to the left
				if (placement == Placement::Left)
				{
					setpoint = speedSetpoint * (1 - turnSetpoint);
				}
			}
			else
			{
				// We're turning to the right

				if (placement == Placement::Right)
				{
					setpoint = speedSetpoint * (1 - turnSetpoint);
				}
			}
		}
	}

	masterMotor->Set(setpoint);
}

void DriveUnit::setSpeedSetpoint(double value)
{
	if(speedSetpoint != value)
	{
		if(placement == Placement::Left)
			value *=-1;
		speedSetpoint = value;
	}
}

void DriveUnit::setSpeedControl(bool speed)
{
	if(speed != isSpeedControlEnabled())
	{
		if(speed)
		{
			masterMotor->SetControlMode(CANSpeedController::kSpeed);
			//masterMotor->SetPID(kDriveSpeedControlProportional,
			//					kDriveSpeedControlIntegral,
			//					kDriveSpeedControlDifferential);
		}
		else
		{
			masterMotor->SetControlMode(CANSpeedController::kPercentVbus);
		}
	}
}
void DriveUnit::setTurnSetpoint(double value)
{
	if(placement == Placement::Left)
		value *= -1;
	turnSetpoint = value;
}




