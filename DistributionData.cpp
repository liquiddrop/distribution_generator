#include "DistributionData.h"

#include <iostream>

#include <boost/math/distributions.hpp>

using boost::math::quantile;

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

static boost::rand48 random_generator;

using std::cout;
using std::endl;
using std::string;


DistributionData::DistributionData()
{
}

DistributionData::~DistributionData()
{
}

std::vector<double> DistributionData::gaussianData(int nPoints, double mean, double sigma)
{
	std::vector<double> data;

	boost::random::normal_distribution<> distrib(mean, sigma);

	for (int i=0; i<nPoints; ++i)
	{
		double val = distrib(random_generator);
		data.push_back(val);
	}

	return data;
}

std::vector<double> DistributionData::exponentialData(int nPoints, double rate)
{
    std::vector<double> data;

	boost::random::exponential_distribution<> distrib(rate);

	for (int i=0; i<nPoints; ++i)
	{
		double val = distrib(random_generator);
		data.push_back(val);
	}

	return data;
}

std::vector<double> DistributionData::logNormalData(int nPoints, double mean, double sigma)
{
    std::vector<double> data;

	boost::random::lognormal_distribution<> distrib(mean, sigma);

	for (int i=0; i<nPoints; ++i)
	{
		double val = distrib(random_generator);
		data.push_back(val);
	}

	return data;
}


std::vector<double> DistributionData::chiSquaredData(int nPoints, int degreesOfFreedom)
{
	std::vector<double> data;

	boost::random::chi_squared_distribution<> distrib(degreesOfFreedom);

	for (int i=0; i<nPoints; ++i)
	{
		double val = distrib(random_generator);
		data.push_back(val);
	}

	return data;
}

double DistributionData::gaussianQuantile(double x, double mean, double sigma)
{
	boost::math::normal_distribution<> dist(mean, sigma);

	return quantile(dist, x);
}


double DistributionData::chiSquaredQuantile(double x, int degreesOfFreedom)
{
	boost::math::chi_squared_distribution<> dist(degreesOfFreedom);

	return quantile(dist, x);
}

double DistributionData::exponentialQuantile(double x, double rate)
{
    boost::math::exponential_distribution<> dist(rate);

	return quantile(dist, x);
}

double DistributionData::logNormalQuantile(double x, double mean, double sigma)
{
    boost::math::lognormal_distribution<> dist(mean, sigma);

	return quantile(dist, x);
}
