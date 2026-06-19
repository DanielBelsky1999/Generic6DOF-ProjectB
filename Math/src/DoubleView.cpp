#include "DoubleView.h"

DoubleView::DoubleView()
	:p(nullptr)
{
}

void DoubleView::SetPtr(double* ptr)
{
	p = ptr;
}

void DoubleView::operator=(double d)
{
	*p = d;
}

DoubleView::operator double() const
{
	return *p;
}
