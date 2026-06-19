#include "SixDOF.h"
#include "Logger.h"
#include "SimplePlatform.h"
#include "Tacview.h"


// todo Will be moved to separate class later
#include <chrono>
#include "Temp_KeyboardReader.h"

int main() {

	// Kinematics init data
	KinematicsInitData kinematic_init;
	kinematic_init.position_llh_ddm = Vector3D(43.6634273, -79.3958470, 1000.0); // LLH _ DDM !
	kinematic_init.velocity_CG_wrt_NED = Vector3D(0.0, 0.0, 0.0); // expressed in body frame! weird. will be fixed todo
	kinematic_init.euler_CGwrtNED = EulerAngles(0.0, 70.0*PI/180.0, 0.0); // Radians
	kinematic_init.rate_CGwrtNED= Vector3D(0,0,0); // Radians/second - todo address the initialization 

	// Create the controls and Platform
	SimplePlatformControls controls;
	SimplePlatform dumb_rocket(&controls);

	// Create an Enviroment. Atmosphere and gravity models are being pulled from the xml config file
	Enviroment env;

	// Create the 6DOF and give it: 1. the environment, 2. the platform, 3. the kinematic init struct, 4. the published state
	PublishedState_6DOF publishedState;
	SixDOF sixdof;
	sixdof.Init(&env, &dumb_rocket, kinematic_init, &publishedState);

	// Tacview. todo make it Singleton. no reason to instantiate..
	Tacview _tacview;
	_tacview.Subscribe(publishedState.GetLLH_ptr(), publishedState.GetEuler_ptr(), Tacview::PlatformType::Missile, "6dof");


	double time = 0.0;
	double DT = Initializer::GetValueAsDouble("Integrator/DT");
	bool RealTime = Initializer::GetValueAsBool("RealTime");

	// Looger init - and subscribe the logged states
	std::filesystem::path filepath("../../out.csv");
	Logger logger(filepath);
	logger.Subsribe(&time, 1, "time_sec");
	logger.Subsribe(publishedState.states, publishedState.NUMBER_OF_STATES, publishedState.header_csv);
	logger.FinilizeInit(); // Dumps the complete header into the csv

	sixdof.PrintState(); // DEBUG PRINT

	std::cout << "\n";

	auto next_tick = std::chrono::steady_clock::now();

	while (time < 100) {

		next_tick += std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>(DT));

		// Ignite the engine
		if (time > 20) {
			controls.ignition = true;
		}

		// UNCOMMENT TO ENABLE COMMANDS FROM KEYBOARD (and remove the line that follows)
		// 
		// GetSurfaceCommands(controls.fins);
		controls.fins[0] = 0.2; controls.fins[1] = 0.2; controls.fins[2] = -0.2; controls.fins[3] = -0.2;


		sixdof.Step(time);
		logger.Step(); // Logging the state at the CURRENT TIME (starting from 0 and goes to 99.99 in this case)
		_tacview.Step(time);
		time += DT;

		// Busy wait in real-time
		if (RealTime)
			while (std::chrono::steady_clock::now() < next_tick) {}

		// Check for termination condition flag
		if (publishedState.termination_flag)
			break;
	}

	sixdof.PrintState();  // DEBUG PRINT

	return 1;
}