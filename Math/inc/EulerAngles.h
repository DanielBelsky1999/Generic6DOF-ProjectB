#pragma once

// forward delc
class EulerAnglesView;

class EulerAngles {
public:
	EulerAngles();
	EulerAngles(double psi, double theta, double phi);
	explicit EulerAngles(const EulerAnglesView& rhs);

	double psi, theta, phi;
};