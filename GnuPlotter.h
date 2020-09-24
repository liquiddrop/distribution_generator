#include <vector>
#include <string>

class GnuPlotter {
public:
    GnuPlotter(const std::string &fileName);
    GnuPlotter(const GnuPlotter &p);
    ~GnuPlotter();
    GnuPlotter &operator=(const GnuPlotter &p);
    void generateCmds(const std::string &cmdFileName);
    void setHeaders(const std::string &xheader, const std::string &yheader);
    void setData(const std::vector<double> &xdata, const std::vector<double> &ydata);
    void setData(const std::vector<std::string> &xdata, const std::vector<double> &ydata);
    void csvWrite();
private:
    std::string m_fileName;
    std::string m_xheader;
    std::string m_yheader;
    std::vector<std::string> m_xdata;
    std::vector<double> m_ydata;
    bool m_isDate;
};
