#include <vector>

// Simple random walk for price simulation
class RandomWalk {
public:
    RandomWalk(int size, double start, double step, int marketTilt);
    RandomWalk(const RandomWalk &p);
    ~RandomWalk();
    RandomWalk &operator=(const RandomWalk &p);

    std::vector<double> getWalk();
private:

    double gaussianValue(double mean, double sigma);

    int m_size;     // number of steps
    double m_step;  // size of each step (in percentage)
    double m_start; // starting price
    int m_marketTilt; //market leaning -1 bear, 0 nuetral, 1 bull
};

