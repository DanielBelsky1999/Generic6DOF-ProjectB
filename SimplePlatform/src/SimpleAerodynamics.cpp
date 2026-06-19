#include "SimpleAerodynamics.h"
#include "SimpleActuators.h"
#include "IKinematics.h"
#include "Enviroment.h"
#include "IAtmosphere.h"

SimpleAerodynamics::SimpleAerodynamics(IPhysicalPlatform* platform) :
	IAerodynamics(platform)
{

}

Vector3D SimpleAerodynamics::GetAeroForceBody()
{
	double d1 = GetActuators().GetActuator(0);
	double d2 = GetActuators().GetActuator(1);
	double d3 = GetActuators().GetActuator(2);
	double d4 = GetActuators().GetActuator(3);
	double roll_command = (d1 + d2 + d3 + d4) * 0.25 * 3.0;
	double pitch_command = (d1 + d2 - d3 - d4) * 0.25 * 3.0;
	double yaw_command = (-d1 + d2 + d3 - d4) * 0.25 * 3.0;

	double aoa = GetAOA();
	double beta = GetBeta();
	Vector3D rates = GetKinematics().GetWNBB();

	constexpr double S = 0.1;

	constexpr double CL0 = 0;
	constexpr double CLalpha = 0.5;
	constexpr double CLdeltaE = -0.01;
	constexpr double CLq = 0;

	constexpr double CY0 = 0;
	constexpr double CYbeta = 0.5;
	constexpr double CYdeltaR = -0.01;
	constexpr double CYr = 0;

	constexpr double CD0 = 0.1;
	constexpr double K = 0.1;

	double CL = CL0 + CLalpha * aoa + CLdeltaE * pitch_command;
	double CY = CY0 + CYbeta * beta + CYdeltaR * yaw_command;
	double CD = CD0 + K * CL * CL + K * CY * CY;

	double alt = GetKinematics().GetAltitude();
	double rho = GetEnviroment().Atmosphere().GetDensity(alt);
	double v = GetKinematics().GetVelocityNED().Norm();

	double L = (-1.0) * 0.5 * rho * v * v * S * CL;
	double Y = (-1.0) *  0.5 * rho * v * v * S * CY;
	double D = (-1.0) * 0.5 * rho * v * v * S * CD;


	// build Rotation matrix that is C = Rz(beta)*Ry(-aoa)
	Matrix33 C_BODY_AERO = MatrixFromEuler(EulerAngles(beta, 0, 0)) * MatrixFromEuler(EulerAngles(0,-aoa,0));

	// Rotate from aero to body axis
	return (C_BODY_AERO.Transpose()) * Vector3D(D, Y, L);
}

Vector3D SimpleAerodynamics::GetAeroMomentAtCG()
{
	double v = GetKinematics().GetVelocityNED().Norm();
	if (v == 0)
		return Vector3D();

	double d1 = GetActuators().GetActuator(0);
	double d2 = GetActuators().GetActuator(1);
	double d3 = GetActuators().GetActuator(2);
	double d4 = GetActuators().GetActuator(3);
	double roll_command = (d1 + d2 + d3 + d4) * 0.25 * 3.0;
	double pitch_command = (d1 + d2 - d3 - d4) * 0.25 * 3.0;
	double yaw_command = (-d1 + d2 + d3 - d4) * 0.25 * 3.0;

	double aoa = GetAOA();
	double beta = GetBeta();
	Vector3D Trates = GetKinematics().GetWNBB();

	// Normalization:
	
	double l = 0.3;
	double d = 0.3;
	Vector3D rates = Vector3D(Trates[0] * d / (2 * v), Trates[1] * l / (2 * v), Trates[2] * l / (2 * v));

	constexpr double S = 0.1;

	constexpr double CL0 = 0;
	constexpr double CLdeltaR = 0.02;
	constexpr double CLp = -8.0;
	
	constexpr double CM0 = 0;
	constexpr double CMalpha = -0.5;
	constexpr double CMdeltaE = 0.25;
	constexpr double CMq = -8.0;


	constexpr double CN0 = 0;
	constexpr double CNbeta = 0.5;
	constexpr double CNdeltaY = 0.25;
	constexpr double CNr = -8.0; 

	double CL = CL0 + CLdeltaR * roll_command + CLp * rates[0];
	double CM = CM0 + CMalpha * aoa + CMdeltaE * pitch_command + CMq * rates[1];
	double CN = CN0 + CNbeta * beta + CNdeltaY * yaw_command + CNr * rates[2];

	double alt = GetKinematics().GetAltitude();
	double rho = GetEnviroment().Atmosphere().GetDensity(alt);


	double L = 0.5 * rho * v * v * S * l * CL;
	double M = 0.5 * rho * v * v * S * l * CM;
	double N = 0.5 * rho * v * v * S * l * CN;


	// build Rotation matrix that is C = Rz(beta)*Ry(-aoa)
	Matrix33 C_BODY_AERO = MatrixFromEuler(EulerAngles(beta, 0, 0)) * MatrixFromEuler(EulerAngles(0, -aoa, 0));

	// Rotate from aero to body axis
	return (C_BODY_AERO.Transpose()) * Vector3D(L, M, N);
}
