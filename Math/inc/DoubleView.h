#pragma once
class DoubleView
{
public:
	DoubleView();
	void SetPtr(double* ptr);

	void operator=(double d);
	explicit operator double() const;

private:
	double* p;
};

