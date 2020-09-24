
#include "GnuPlotter.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

using std::ofstream;
using std::vector;
using std::cout;
using std::endl;

GnuPlotter::GnuPlotter(const std::string &fileName)
: m_fileName(fileName),
  m_isDate(false)
{
}

GnuPlotter::GnuPlotter(const GnuPlotter &p)
: m_fileName(p.m_fileName),
  m_xheader(p.m_xheader),
  m_yheader(p.m_yheader),
  m_xdata(p.m_xdata),
  m_ydata(p.m_ydata),
  m_isDate(p.m_isDate)
{
}

GnuPlotter::~GnuPlotter()
{
}

GnuPlotter &GnuPlotter::operator=(const GnuPlotter &p)
{
	if (&p != this)
	{
		m_fileName = p.m_fileName;
		m_xheader = p.m_xheader;
		m_yheader = p.m_yheader;
		m_xdata = p.m_xdata;
		m_ydata = p.m_ydata;
		m_isDate = p.m_isDate;
	}
    return *this;
}

void GnuPlotter::setData(const std::vector<std::string> &xdata, const std::vector<double> &ydata)
{
	m_xdata = xdata;
	m_ydata = ydata;
	m_isDate = true; // assume that x-axis is a date
}

void GnuPlotter::setData(const std::vector<double> &xdata, const std::vector<double> &ydata)
{
	for (unsigned i = 0; i < xdata.size(); ++i)
	{
		std::stringstream ss;
		ss << xdata[i];
		m_xdata.push_back(ss.str());
	}
	m_ydata = ydata;
	m_isDate = false; // x-axis cannot be a date.
}

void GnuPlotter::setHeaders(const std::string &xheader, const std::string &yheader)
{
	m_xheader = xheader;
	m_yheader = yheader;
}

void GnuPlotter::generateCmds(const std::string &cmdFileName)
{
	ofstream file;

	file.open(cmdFileName.c_str());
	if (file.fail())
	{
		cout << "failed to open file " << m_fileName << endl;
		return;
	}

	if (m_isDate)
	{
		file << "set xdata time"  << endl;
		file << "set timefmt \"%Y-%m-%d\" "  << endl;
	}
	file << "set datafile separator \",\" "  << endl;
	file << "plot '" << m_fileName <<  "'  u 1:2  title columnhead w lines " << endl;
}

void GnuPlotter::csvWrite()
{
	ofstream file;

	file.open(m_fileName.c_str());
	if (file.fail())
	{
		cout << "failed to open file " << m_fileName << endl;
		return;
	}

	if (m_xdata.size() != m_ydata.size())
	{
		cout << "data has incorrect size " << endl;
		return;
	}

	file << m_xheader << "," << m_yheader << endl;

	for (unsigned i = 0; i < m_xdata.size(); ++i)
	{
		file << m_xdata[i] << "," << m_ydata[i] << endl;
	}
}
