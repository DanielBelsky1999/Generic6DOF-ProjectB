#include "EulerAnglesView.h"
#include "EulerAngles.h"

EulerAnglesView::EulerAnglesView()
	:p(nullptr)
{
}

void EulerAnglesView::SetPtr(double* ptr)
{
	p = ptr;
}



void EulerAnglesView::operator=(const EulerAngles& rhs)
{
	p[0] = rhs.psi;
	p[1] = rhs.theta;
	p[2] = rhs.phi;
}
