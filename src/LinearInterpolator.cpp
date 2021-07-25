#include <iostream>
#include <math.h>
#include <map>
#include "LinearInterpolator.hpp"

using namespace std;

void LinearInterpolator::add(double x, double y)
{
    if(DataPoints.count(x) != 0)
    {
        map<double, double>::iterator it =
        DataPoints.find(x);
        it->second = y;
    }
    DataPoints.insert(pair<double, double>(x,y));
}

double LinearInterpolator::value(double x)
{
    if(DataPoints.empty())
    {
        cout << "No Prior Data Entered. " << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }
    if (DataPoints.begin()->first > x)
    {
        cout << "Input var is outside points" << endl;
        cout << "closest data points : " << endl;
        return DataPoints.begin()->second;
    }
    map<double, double>::iterator it;

    it = DataPoints.find(x);
    if (it != DataPoints.end())
    {
        return it->second;
    }
    else
    {
        for (it = DataPoints.begin(); it != DataPoints.end();++it)
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
    map<double, double>::iterator it = DataPoints.end();
    --it;

    cout << "Input var is outside points" << endl;
    cout << "closest data points : " << endl;
    return it->second;
}
