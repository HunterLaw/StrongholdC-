/*
 * DriveUnit.h
 *
 *  Created on: May 11, 2016
 *      Author: robotics
 */

#ifndef SRC_DRIVEUNIT_H_
#define SRC_DRIVEUNIT_H_

enum Placement {Left,Right};
class DriveUnit
{

public:
	DriveUnit();

protected:
	double speedSetpoint;
	double turnSetpoint;
	const Placement placement;
};
#endif /* SRC_DRIVEUNIT_H_ */
