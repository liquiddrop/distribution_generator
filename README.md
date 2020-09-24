# distribution_generator
c++ code to generate various distribution data sets to run models agains

The code takes in inputs for various distributions and generates a set of data
then outputs it to csv and gnu plot commands. This is using the boost math and
random libs to generate the data.

Distribution Types, parameters
Gaussian-G, <mean> <sigma>
Exponential-E, <rate>
ChiSquared-C, <degrees of freedom>
LogNormal-L, <mean> <sigma>
Example Gaussian with 100 point generated with mean of 5 and sigma of 2, output file name example
G 100 5 2 example
Enter 'Q' to quit

A lot of this code is taken or addapted from the book "Practical C++ Financial Programming" 
by Carlos Oliveira, Apress, 2015. For more information, visit http://coliveira.net
