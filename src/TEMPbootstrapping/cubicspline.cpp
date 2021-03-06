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
    int Counter = 0;
    ma.resize(n+1);
    mb.resize(n);
    md.resize(n);
    vector<double> mu;
    mu.resize(n);
    vector<double>h;
    h.resize(n);

    for(map<double, double>::iterator it = mCoordinates.begin(); it != mCoordinates.end();)
    {
        ma[Counter] = it->second;
        double xlow = it->first;
        ++it;
        if(it != mCoordinates.end())
        {
            double xhigh = it->first;
            h[Counter] = xhigh -xlow;
        }
        ++Counter;
    }
    vector<double> beta;
    beta.resize(n-1); // beta from k =1, k=n-1
    // all vectros 1 extra added
    
    for(int i = 0; i<=n-2;++i)
    {
        beta[i] = 3 * (ma[i+2]-ma[i+1]) / h[i+1] -3*(ma[i+1]-ma[i])/h[i];
    }
    mc.resize(n+1);
    vector<double> l;
    l.resize(n+1);
    vector<double> z;
    z.resize(n+1);
    l[0]=1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    int Counter2 = 1;
    for(map<double, double>::iterator it = mCoordinates.begin();it != mCoordinates.end();)
    {
        double xmin2 = it->first;
        ++it; ++it;
        if(it!=mCoordinates.end())
        {
            double xplus2 = it->first;
            --it;
            l[Counter2] = 2*(xplus2-xmin2) - h[Counter2 -1]*mu[Counter2 - 1];
        }
        ++Counter2;
    }
    
    for(int i=1;i<n-1;++i)
    {
        mu[i] = h[i]/l[i];
        z[i] = (beta[i-1]-h[i-1] * z[i-1])/ l[i];
        // beta m starts 1
    }
    l[n] = 1.0;
    z[n] = 0.0;
    mc[n] = 0.0;

    for(int i = n-2; i>=0;--i)
    {
        mc[i] = z[i] - mu[i] * mc[i+1];
        mb[i] = (ma[i+1]-ma[i]) / h[i] - h[i] * (mc[i+1]+2*mc[i])/3.0;
        md[i] = (mc[i+1] - mc[i]) / 3.0 * h[i];
    }

    // initializing, row = one spline polynomial
    mOutputMatrix.resize(n, vector<double>(4,0));
    
    for(int i=0; i < n - 1; ++i)
    {
        mOutputMatrix[i] = { ma[i], mb[i], mc[i], md[i] };
    }

}

double CubicSpline::value(double x)
{
    UpdateSpline();
    int TermNum = 0;
    map<double,double>::iterator it = mCoordinates.begin();
    if (x<it->first)
    {
        exit(EXIT_FAILURE);
    }
    for(;it!=mCoordinates.end();)
    {
        ++it;
        if(x==it->first)
        {
            return it->second;
        }
        else if (x<it->first)
        {
            --it;
            return ma[TermNum] + mb[TermNum] * (x-it->first)+
            mc[TermNum] * std::pow(x-it->first,2) + md[TermNum] * std::pow(x-it->first, 2);
        }
        ++TermNum;
    }
    exit(EXIT_FAILURE);
}