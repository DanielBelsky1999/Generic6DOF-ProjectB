#include "EulerAngles.h"
#include "EulerAnglesView.h"

EulerAngles::EulerAngles(): psi(0), theta(0), phi(0) {

}

EulerAngles::EulerAngles(double psi, double theta, double phi) :
	psi(psi), theta(theta), phi(phi) {
}

EulerAngles::EulerAngles(const EulerAnglesView& rhs)
{
	psi = rhs[0];
	theta = rhs[1];
	phi = rhs[2];
}
