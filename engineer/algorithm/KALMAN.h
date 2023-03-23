#pragma once
class KALMAN
{
public:
	double X_last; //上一时刻的最优结果  X(k-|k-1)
	double X_mid;  //当前时刻的预测结果  X(k|k-1)
	double X_now;  //当前时刻的最优结果  X(k|k)
	double P_mid;  //当前时刻预测结果的协方差  P(k|k-1)
	double P_now;  //当前时刻最优结果的协方差  P(k|k)
	double P_last; //上一时刻最优结果的协方差  P(k-1|k-1)
	double kg;     //kalman增益
	double A;      //系统参数
	double B;
	double Q;
	double R;
	double H;
	/**
	  * @name   kalmanCreate
	  * @brief  创建一个卡尔曼滤波器
	  * @param  p:  滤波器
	  *         T_Q:系统噪声协方差
	  *         T_R:测量噪声协方差
	  *
	  * @retval none
	  * @attention R固定，Q越大，代表越信任侧量值，Q无穷代表只用测量值
	  *		       	反之，Q越小代表越信任模型预测值，Q为零则是只用模型预测
	  */
	KALMAN(double T_Q, double T_R);


	double Filter(double dat);
};