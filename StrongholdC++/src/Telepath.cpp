#include "WPILib.h"
#include "Parameters.h"
#include <cmath>
#include "WestCoastDrive.h"
#include "PusherArm.h"
#include "Shooter.h"


/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Telepath: public SampleRobot
{
protected:
	Joystick *leftstick,*rightstick,*buttonstick2,*buttonstick3,*analogstick;
	WestCoastDrive *drive;
	PusherArm *pusher;
	Shooter *shooter;
	Solenoid *fan;
	Compressor *compressor;
public:
Telepath()
{
		leftstick = new Joystick(kDriverStationLeftStick);
		rightstick = new Joystick(kDriverStationRightStick);
		buttonstick2 = new Joystick(kDriverStationButtonStick2);
		buttonstick3 = new Joystick(kDriverStationButtonStick3);
		analogstick = new Joystick(kDriverStationAnalogStick);

		fan = new Solenoid(kGyroFanAnalogPort);
		drive = new WestCoastDrive();
		pusher = new PusherArm();
		shooter = new Shooter();
		compressor = new Compressor();
		compressor->SetClosedLoopControl(true);
}
enum ButtonStick3Values {kShooterInfeed=1,kKick=2,kShooterDown=3,kClimberOut=4,kClimberRelease=5,kClimberIn=6,kClimberUp=7,kClimberDown=8,kPusherUp=9,kPusherDown=10,kShooterUp=11,	kShooterShoot=12};

/**
 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
 * below the Gyro
 *
 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
 * If using the SendableChooser make sure to add them to the chooser code above as well.
 */
void Autonomous()
{


}

/**
 * Runs the motors with arcade steering.
 */
void OperatorControl()
{
	double leftval = 0;
	double rightval =0;
	fan->Set(true);
	bool isCamMovingManually = true;
	while (IsOperatorControl() && IsEnabled())
	{
		compressor->Start();
		leftval = joystickValue(leftstick->GetY());
		rightval = joystickValue(rightstick->GetY());
		if(buttonstick3->GetRawButton(ButtonStick3Values::kShooterShoot) || leftstick->GetRawButton(5))
		{
			shooter->manualRunPitchingMachine(kShooterShootPitchingMachineSpeed);
//        		shooter.shoot2();
		}
		else if(buttonstick2->GetRawButton(ButtonStick3Values::kShooterInfeed) || leftstick->GetRawButton(4))
		{
			shooter->manualRunPitchingMachine(kShooterReloadPitchingMachineSpeed);
		}
		else
		{
			shooter->manualRunPitchingMachine(0);
		}
		if(buttonstick3->GetRawButton(ButtonStick3Values::kShooterUp) || leftstick->GetRawButton(3))
		{
			shooter->manualRunTiltMotor(kShooterTiltPowerUp);
		}
		else if(buttonstick2->GetRawButton(ButtonStick3Values::kShooterDown) || leftstick->GetRawButton(2))
		{
			shooter->manualRunTiltMotor(kShooterTiltPowerDown);
		}
		/*else if (buttonstick3.getRawButton(ButtonStick2Values.kFindTarget.getValue()))
		{
			if(isCameraMovingManually)
			{
				cam.getImage();
				cam.centerTarget(gyro.getAngle());
				turncont.enable();
			}
			isCameraMovingManually = false;
			shooter.setShooterAngle(cam.getCameraAngle());
			turncont.setSetpoint(cam.getAngleToMoveFromCamera());
		}
		else if(buttonstick2.getRawButton(ButtonStick2Values.kGoTo.getValue()))
		{
			shooter->setShooterAngle(cam.getCameraAngle());
		}
		else if(buttonstick3->GetRawButton(ButtonStick2Values::kSpare) && !turncont.isEnabled())
		{
			shooter->setShooterAngle(cam.getCameraAngle());
			turncont.setSetpoint(cam.getAngleToMoveFromCamera());
			turncont.enable();
		}*/
		else
		{
			//isCameraMovingManually = true;
			shooter->manualRunTiltMotor(0);
		}
		if(buttonstick2->GetRawButton(ButtonStick3Values::kKick))
		{
			shooter->pushBall(true);
		}
		else
		{
			shooter->pushBall(false);
		}
		if(buttonstick2->GetRawButton(kPusherUp))
		{
			pusher->manualSetTilt(kPusherArmMotorPowerUp);
		}
		else if(buttonstick2->GetRawButton(kPusherDown))
		{
			pusher->manualSetTilt(-kPusherArmHomeMotorPower);
		}
		else
		{
			pusher->manualSetTilt(0);
		}
		if(rightstick->GetRawButton(2))
		{
			drive->setGear(WestCoastDrive::Gear::kLowGear);
		}
		else if(rightstick->GetRawButton(3))
		{
			drive->setGear(WestCoastDrive::Gear::kHighGear);
		}
		if(leftstick->GetRawButton(11))
		{
			drive->setSpeedSetpoint(leftval, leftval);
		}
		else
		{
			drive->setSpeedSetpoint(leftval, rightval);
		}
		drive->process();
		Wait(0.05);				// wait for a motor update time
	}
}

/**
 * Runs during test mode
 */
void Test()
{
}

double joystickValue(double value)
{
	double rc = 0;
	if(abs(value) < 0.05)
	{
		rc = 0;
	}
	else
	{
		rc = value;
	}
	return rc;
}
};
START_ROBOT_CLASS(Telepath)
