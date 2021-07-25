#pragma once
#include <vector>
#include <map>
#include <cmath>
#include <iostream>

using namespace std;

class CubicSpline
{
    public:
    CubicSpline() {}
    ~CubicSpline() {}
    

    //base
    void add(double x, double y);
    double value(double x);

    // derived
    void UpdateSpline();

    private:
    map<double, double> mCoordinates;
    vector<double> ma;
    vector<double> mb;
    vector<double> md;
    vector<double> mc;
    vector<vector<double> > mOutputMatrix;
};