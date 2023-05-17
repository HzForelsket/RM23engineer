#ifndef __PID_H__
#define __PID_H__
#define FILTER 2
#include"stdint.h"
#include <algorithm>
class PID
{
    enum { INTEGRATE = 0, LLAST = 0, LAST = 1, NOW = 2 };
private:
    double m_P{}, m_I{}, m_D{};
    double m_lderivative{};
    double m_filter[FILTER]{};
    double m_maxINTEGRATE{};
    double m_minINTEGRATE{};
    uint16_t m_filterindex{};
    double m_error[3] = {};
public:
    void Adjust(double Kp, double Ti, double Td);
    double Filter(double delta);
    double Delta(double error);
    double Position(double error);
    PID();
    PID(double Kp, double Ti, double Td, double maxINTEGRATE=0, double minINTEGRATE=0);
    void init(double Kp, double Ti, double Td);
};

#endif // !__PID_H__
