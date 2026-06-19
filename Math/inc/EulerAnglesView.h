#pragma once

// forward decl
class EulerAngles;

class EulerAnglesView
{
public:
	// Constructors
	EulerAnglesView();

	// no copying
	EulerAnglesView(const EulerAnglesView& vectorView) = delete;

	inline double operator[](int i) const { return p[i]; }

	void SetPtr(double* ptr);

	// Operator Overlaods Member
	void operator=(const EulerAngles& rhs);

private:
	double* p;
};

