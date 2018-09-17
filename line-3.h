// David Decker
// 1/12/2017

#include <iostream>
#include "line.h"


double Line::intersect(const Line L) const throw(ParallelLines,
						   EqualLines)
{	
	double x;
	//the following formula is from comparing the two lines in slope intercept form which sets up the equation
	//ax+b = cx+d where the first equation is the lvalue line and the second equation is the line supplied in the argument
	x = (L.Line::getIntercept()-this->Line::getIntercept())/(this->Line::getSlope()-L.Line::getSlope());
	if((L.Line::getSlope() == this->Line::getSlope())&&(L.Line::getIntercept() == this->Line::getIntercept()))	
		throw EqualLines("The lines are equal: infinite intersection");//explicit call of the of the base class constructor
																							//used in the scope of class EqualLines
	if(L.Line::getSlope() == this->Line::getSlope())
		throw ParallelLines("The lines are parallel: no intersection");	

	return x;
}


