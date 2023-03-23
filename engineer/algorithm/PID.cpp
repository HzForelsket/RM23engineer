#include"PID.h"
PID::PID(double Kp, double Ti, double Td, double maxINTEGRATE, double minINTEGRATE)
{
	m_P = Kp;
	m_I = Ti;
	m_D = Td;
	m_maxINTEGRATE = maxINTEGRATE;
	m_minINTEGRATE = minINTEGRATE;
}

void PID::init(double Kp, double Ti, double Td)
{
	m_P = Kp;
	m_I = Ti;
	m_D = Td;
}

void PID::Adjust(double Kp, double Ti, double Td)
{
	m_P = Kp;
	m_I = Ti;
	m_D = Td;
}
double PID::Filter(double delta)
{
	double sum = 0;
	m_filter[m_filterindex++] = delta;
	if (m_filterindex == FILTER)m_filterindex = 0;
	for (int16_t t = 0; t != FILTER; t++)
		sum += m_filter[t];
	return sum / static_cast<double>(FILTER);
}
double PID::Delta(double error)//‘ˆ¡øpid
{
	m_error[LLAST] = m_error[LAST] * 0.92f;
	m_error[LAST] = m_error[NOW] * 0.92f;
	m_error[NOW] = error * 1.08f;
	return  m_P*(m_error[NOW] - m_error[LAST]) + m_I * m_error[NOW] + m_D * (m_error[NOW] - 2 * m_error[LAST] + m_error[LLAST]);
}
double PID::Position(double error)//Œª÷√pid
{
	m_error[NOW] = error;
	m_error[INTEGRATE] += m_error[NOW];
	m_error[INTEGRATE] = std::max(std::min(m_error[INTEGRATE], m_maxINTEGRATE), m_minINTEGRATE);
	m_lderivative = m_D  * (m_error[NOW] - m_error[LAST]);
	const double result = m_error[NOW] * m_P + m_error[INTEGRATE] * m_I + m_lderivative;
	m_error[LAST] = m_error[NOW];
	return result;
}

PID::PID()
{

}
