#include <iostream>
#include <math.h>
#include <map>
#include "LinearInterpolator.hpp"

using namespace std;

void LinearInterpolator::add(double x, double y)
{
    if(mCoordinates.count(x) != 0)
    {
        map<double, double>::iterator it =
        mCoordinates.find(x);
        it->second = y;
    }
    mCoordinates.insert(pair<double, double>(x,y));
}

double LinearInterpolator::value(double x)
{
    if(mCoordinates.empty())
    {
        cout << "No Prior Data Entered. " << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
    if (mCoordinates.begin()->first > x)
    {
        cout << "Input var is outside points" << endl;
        cout << "closest data points : " << endl;
        return mCoordinates.begin()->second;
    }
    map<double, double>::iterator it;

    it = mCoordinates.find(x);
    if (it != mCoordinates.end())
    {
        return it->second;
    }
    else
    {
        for (it = mCoordinates.begin(); it != mCoordinates.end();++it)
        {
            if (it->first >= x)
            {
                double XUpper = it->first;
                double YUpper = it->second;
                --it;
                double XLower = it->first;
                double YLower = it->second;
                return ((YUpper-YLower)/(XUpper-XLower))*(x-XLower) + YLower;
            }
        }
    }
    map<double, double>::iterator it = mCoordinates.end();
    --it;

    cout << "Input var is outside points" << endl;
    cout << "closest data points : " << endl;
    return it->second;
}
