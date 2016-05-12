#include "WPILib.h"
#include "Parameters.h"
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
	Joystick leftstick;
	Joystick rightstick;
	Joystick buttonstick2;
	Joystick buttonstick3;
	Joystick analogstick;
	Parameters p;

public:
	Telepath()
	{
		leftstick = new Joystick(p.kDriverStationLeftStick);
		rightstick = new Joystick(p.kDriverStationRightStick);
		buttonstick2 = new Joystick(p.kDriverStationButtonStick2);
		buttonstick3 = new Joystick(p.kDriverStationButtonStick3);
		analogstick = new Joystick(p.kDriverStationAnalogStick);

	}

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
		while (IsOperatorControl() && IsEnabled())
		{
			Wait(0.005);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Telepath)
