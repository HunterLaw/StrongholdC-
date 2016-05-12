#include "DriveUnit.h"

DriveUnit::DriveUnit(Placement p)
{
	placement = p;
	speedSetpoint =0;
	turnSetpoint =0;
	if(p == Placement::Right)
	{
		masterMotor = new CANTalon(0);
		followerMotor = new CANTalon(0);
	}
	else if(p == Placement::Left)
	{
		masterMotor = new CANTalon(0);
		followerMotor = new CANTalon(0);
	}
	masterMotor->SetControlMode(CANSpeedController::kPercentVbus);
	followerMotor->SetControlMode(CANSpeedController::kFollower);

	followerMotor->Set(0);

	masterMotor->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake);
	followerMotor->ConfigNeutralMode(CANSpeedController::kNeutralMode_Brake);

}

