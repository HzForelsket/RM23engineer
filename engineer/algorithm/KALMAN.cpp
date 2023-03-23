#include "KALMAN.h"

KALMAN::KALMAN(double T_Q, double T_R)
{
	X_last = (double)0.0;
	P_last = 0.f;
	Q = T_Q;
	R = T_R;
	A = 1.f;
	B = 0.f;
	H = 1.f;
	X_mid = X_last;
}

double KALMAN::Filter(double dat)

{
	X_mid = A * X_last;                   //百度对应公式(1)    x(k|k-1) = A*X(k-1|k-1)+B*U(k)+W(K)
	P_mid = A * P_last + Q;               //百度对应公式(2)    p(k|k-1) = A*p(k-1|k-1)*A'+Q
	kg = P_mid / (P_mid + R);           //百度对应公式(4)    kg(k) = p(k|k-1)*H'/(H*p(k|k-1)*H'+R)
	X_now = X_mid + kg * (dat - X_mid);   //百度对应公式(3)    x(k|k) = X(k|k-1)+kg(k)*(Z(k)-H*X(k|k-1))
	P_now = (1.f - kg) * P_mid;             //百度对应公式(5)    p(k|k) = (I-kg(k)*H)*P(k|k-1)
	P_last = P_now;                     //状态更新
	X_last = X_now;
	return X_now;						//输出预测结果x(k|k)
}
