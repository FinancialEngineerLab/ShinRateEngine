#pragma once
#include <map>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Interpolator
{
    public:
    Interpolator() {}
    ~Interpolator() {}

    virtual void add(double x, double y) const = 0;
    virtual double value(double x) const = 0;

    private:
    map<double, double> mCoordinates;
};

class LinearInterpolator : public Interpolator
{
    public:
    LinearInterpolator() {}
    ~LinearInterpolator() {}
    
    virtual void add(double x, double y);
    virtual double value(double x);

    private:
};
