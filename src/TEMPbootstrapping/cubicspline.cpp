#include "cubicspline.hpp"

void CubicSpline::add(double x, double y)
{
    map<double, double>::iterator it = mCoordinates.find(x);
    if(it != mCoordinates.end())
    {
        it->second = y;
    }
    else
    {
        mCoordinates.insert(pair<double, double>(x,y));
    }
}

void CubicSpline::UpdateSpline()
{
    int n = static_cast<int> (mCoordinates.size());
}