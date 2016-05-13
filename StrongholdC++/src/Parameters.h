#ifndef SRC_PARAMETERS_H_
#define SRC_PARAMETERS_H_
#include "WPILib.h"
#include <string>

using namespace std;
	static const int kLeftMasterDriveMotorCanId = 11;
	static const int kLeftFollowerDriveMotorCanId = 12;
	static const int kRightMasterDriveMotorCanId = 21;
	static const int kRightFollowerDriveMotorCanId = 22;

	static const int kPusherArmMotorCanId = 43;

	static const int kShooterAngleMotorCanId = 33;
	static const int kLeftShooterPitcherMotorCanId = 42;
	static const int kRightShooterPitcherMotorCanId = 41;

	static const int kClimberAngleMotorCanId = 51;
	static const int kClimberLeftWinchMotorCanId = 31;
	static const int kClimberRightWinchMotor = 32;
	static const int kClimberExtendMotorCanId = 44;

	static const string kCameraIpAddress = "10.20.28.11";

	static const int kGyroAnalogPort = 0;
	static const int kGyroFanAnalogPort = 7;

	static const int kUltraSonicAnalogPort = 1;

	static const int kTapeSensorLeftDigitalPort =0;
	static const int kTapeSensorRightDigitalPort =1;

	static const double delay = 0.1;

	static const double kDriveMotorDownshiftCurrentThreshold = 20.0;

	static const int kLowGearSolenoidChanel =1;
	static const int kHighGearSolenoidChanel =0;

	static const double kShooterShootPitchingMachineSpeed = 0.9;
	static const double kShooterShootBatterSpeed =0.65;
	static const double kShooterTiltMaxVolt = 12*0.6;
	static const double kShooterReloadPitchingMachineSpeed = -0.8;
	static const double kShootTiltPositionControlProportional = 0;
	static const double kShootTiltPositionControlIntegral = 0;
	static const double kShootTiltPositionControlDifferential = 0.0005;
	static const double kShootPitchPositionControlProportional = 0;
	static const double kShootPitchPositionControlIntegral = 0;
	static const double kShootPitchPositionControlDifferential = 0.00005;
	static const int kShooterBallShooterSolenoidChanel = 2;

	static const double kMaxVelocity = 20;

	static const double kShooterTiltShootTapePositionEncoderSetpoint = 1.125;
	static const double kShooterTiltShootDefensePositionEncoderSetpoint = 1.6;
	static const double kShooterTiltShootBatterPositionEncoderSetpoint = 0;
	static const double kShooterTiltReloadPositionEncoderSetpoint = 0;
	static const double kShooterTiltLowBarPositionEncoderSetpoint = 3.7;
	static const double kShooterTiltHomePositionEncoderSetpoint = -17389;
	static const double kShooterTiltPowerDown = 0.8;
	static const double kShooterTiltPowerUp = -0.6;
	static const double kShooterSeekHomePower = 0.35;
	static const double kShooterSeekTolerance = 0.1;
	static const int kEncoderCodesPerRev = 1024;

	static const double kClimbTiltPositionControlProportional = 0;
	static const double kClimbTiltPositionControlIntegral = 0;
	static const double kClimbTiltPositionControlDifferential = 0;
	static const double kClimbTiltPositionControlThrottle = 0;
	static const double kClimbExtendPositionControlProportional = 0;
	static const double kClimbExtendPositionControlIntegral = 0;
	static const double kClimbExtendPositionControlDifferential = 0;
	static const double kClimbExtendPositionControlThrottle = 0;
	static const double kClimberFullyExtendedPositionSetpoint = 0;
	static const double kRaiseLowerMoterHomeSpeed = 0;
	static const double kClimberTiltHomePositionEncSetpoint = 0;
	static const double kClimberTiltLowBarPositionEncSetPoint = 0;
	static const double kClimberRaisedPositionSetPoint = 0;
	static const double kClimberDrawBridgeSetPoint = 0;
	static const double kClimberTiltPower = 0.35;
	static const double kClimberExtendPower = 0.45;


	static const int kRock = 8;
	static const int kRough =9;
	static const int kDraw =6;
	static const int kSally =7;
	static const int kRamp = 5;
	static const int kMoat =4;
	static const int kPort =2;
	static const int kCheval =3;
	static const int kLowBar =1;
	static const int kClimb = 10;
	// pusher arm pid

	static const double kPusherArmPositionControlProportional = 0.0;
	static const double kPusherArmPositionControlIntegral = 0.0;
	static const double kPusherArmPositionControlDifferential = 0.0005;
	static const double kPusherArmPositionControlThrottle = 0.0;
	//pusher arm
	static const double kPusherArmMaxMotorCurrent = 20.0;
	static const double kPusherArmHomeMotorPower = 0.4;
	static const double kPusherArmMotorPowerUp = 0.75;
	static const double kMotorVoltageDeadband = 0.05;
	static const double kPusherArmHomeSetPoint = 0.0;
	static const double kPusherArmDownSetPoint = 0.25;

	static const double kShooterTiltMaxCurrent = 20.0;
	static const long kShooterPitchingMachineAccelTimeout = 2500;
	static const long kShooterPitchingMachinePushBallTimeout = 250;
	static const double kGoalHeight = 77.5;//height from camera to middle of goal, camera is 12 inches high
	static const double kShooterOffSetFromCameraZ = -19.5;

	static const double autonomousDrivePower = -0.75;
	static const int kDriverStationLeftStick = 0;
	static const int kDriverStationRightStick = 1;
	static const int kDriverStationAnalogStick = 4;
	static const int kDriverStationButtonStick2 = 2;
	static const int kDriverStationButtonStick3 = 3;

	static const double kHeightGoalDifference = 0;
	static const double kDistCamToShooterX = 10.5;//inches
	static const double kTotalShooterTiltPositionMoveFromParallel = 8.4;
	static const double kTotalShooterTiltAngleMoveFromParallel = 164;
	static const double kTotalCameraTiltAngle = 164;
	static const double kTotalCameraTiltPos = 0.845;

	static const int kFlashDIO = 9;

#endif /* SRC_PARAMETERS_H_ */
