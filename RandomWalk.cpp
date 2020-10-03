#include <cstdlib>
#include <iostream>
#include <vector>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include "RandomWalk.h"


using namespace std;
using std::vector;

static boost::rand48 random_generator;

RandomWalk::RandomWalk(int size, double start, double step, int marketTilt)
: m_size(size),
  m_step(step),
  m_start(start),
  m_marketTilt(marketTilt)
{
}

RandomWalk::RandomWalk(const RandomWalk &p)
: m_size(p.m_size),
  m_step(p.m_step),
  m_start(p.m_start),
  m_marketTilt(p.m_marketTilt)
{
}

RandomWalk::~RandomWalk()
{
}

RandomWalk &RandomWalk::operator=(const RandomWalk &p)
{
    if (this != &p)
    {
        m_size = p.m_size;
        m_step = p.m_step;
        m_start = p.m_start;
        m_marketTilt = p.m_marketTilt;
    }
    return *this;
}

double RandomWalk::gaussianValue(double mean, double sigma)
{
	boost::random::normal_distribution<> distrib(mean, sigma);
	return distrib(random_generator);
}

std::vector<double> RandomWalk::getWalk()
{
    vector<double> walk;
    double prev = m_start;

    for (int i=0; i<m_size; ++i)
    {
        double stepSize = gaussianValue(0, m_step);
        int r = rand() % 2;
        double val = prev;
        if(m_marketTilt==1)
        {
            if(r==0) stepSize+=.005;
        }
        else if(m_marketTilt==-1)
        {
            if(r!=0) stepSize+=.005;
        }
        if (r == 0) val += (stepSize*val);
        else val -= (stepSize*val);
        walk.push_back(val);
        prev = val;
    }
    return walk;
}
