#include "DistributionData.h"
#include "GnuPlotter.h"
#include "RandomWalk.h"
#include "boost/date_time/gregorian/gregorian.hpp"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace  {
    template <class T>
    void printData(const string &label, const T &data)
    {
        cout << " " << label << ":  ";
        for (auto i : data)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

void printUsage(){
            cout << "Input was not correct the accepted input formats are:" << endl;
            cout << "<Distribution Type> <number of points to generate> <parameters> <output file name>" << endl;
            cout << "Distribution Types, parameters" << endl;
            cout << "Gaussian-G, <mean> <sigma>" << endl;
            cout << "Example Gaussian with 100 points generated with mean of 5 and sigma of 2, output file name example" << endl;
            cout << "G 100 5 2 example" << endl;
            cout << "Exponential-E, <rate>" << endl;
            cout << "Example Exponential with 10 points rate equal to 4, output file name example2" << endl;
            cout << "E 10 4 example2" << endl;
            cout << "ChiSquared-C, <degrees of freedom>"  << endl;
            cout << "Example ChiSquared with 50 points generated with 3 degrees of freedom, output file name example3" << endl;
            cout << "C 50 3 example3" << endl;
            cout << "LogNormal-L, <mean> <sigma>" << endl;
            cout << "Example LogNormal with 300 points generated with mean of 10 and sigma of 9, output file name example4" << endl;
            cout << "L 300 10 9 example4" << endl;
            cout << "Random Walk normal dist-R, <start price>, <average step size in percent out off 100>" << endl;
            cout << "<market tilt ie -1(bear), 0(neutral), 1(bear)>" << endl;
            cout << "Example random walk with 200 points start price of $40 average step size of 2% in neutral market, output file name example" << endl;
            cout << "R 200 40 2 0 example" << endl;
            cout << "Enter 'Q' to quit" << endl;
}

using namespace boost::gregorian;

std::vector<string> generateDateVector(int count)
{
    vector<string> outputVector;
    day_iterator day_itr(date(day_clock::local_day()));
    for (int i=0; i<count; ++i)
    {
        outputVector.push_back(to_iso_extended_string(*day_itr));
        ++day_itr;
    }
    return outputVector;
}

int main()
{
    std::string inputString, outputFileCsv, outputFileGP;
    char firstInput;
    int numPoints=0, mean=0, sigma=0, rate=0, degOfFreedom=0, marketTilt=0;
    double startPrice=0, avgStep=0;
    bool quit = false, generateData = false;
    vector<string> xdata;
    vector<double> ydata;
    DistributionData dData;

    while(1)
    {
        if(cin >> firstInput)
        {
            switch(firstInput){
            case 'G':
                cin >> numPoints >> mean >> sigma;
                getline(cin, inputString);
                ydata = dData.gaussianData(numPoints, mean, sigma);
                outputFileCsv = inputString + ".csv";
                generateData=true;
                break;
            case 'E':
                cin >> numPoints >> rate;
                getline(cin, inputString);
                ydata = dData.exponentialData(numPoints, rate);
                generateData=true;
                break;
            case 'C':
                cin >> numPoints >> degOfFreedom;
                getline(cin, inputString);
                ydata = dData.chiSquaredData(numPoints, degOfFreedom);
                generateData=true;
                break;
            case 'L':
                cin >> numPoints >> mean >> sigma;
                getline(cin, inputString);
                ydata = dData.logNormalData(numPoints, mean, sigma);
                generateData=true;
                break;
            case 'R':
                {
                    cin >> numPoints >> startPrice >> avgStep >> marketTilt;
                    getline(cin, inputString);
                    RandomWalk rWalk(numPoints, startPrice, ((avgStep)/100), marketTilt);
                    ydata = rWalk.getWalk();
                    generateData=true;
                }
                break;
            case 'Q':
                quit=true;
                break;
            default:
                printUsage();
            }
            if(quit)
            {
                break;
            }
            else
            {
                if(generateData)
                {
                    GnuPlotter plotter(inputString + ".csv");
                    plotter.setHeaders("Date", "Price");
                    xdata = generateDateVector(numPoints);
                    plotter.setData(xdata, ydata);
                    plotter.csvWrite();
                    plotter.generateCmds(inputString + ".gp");
                    generateData = false;
                }
            }
        }
        else
        {
            printUsage();
        }
    }

    return 0;
}
