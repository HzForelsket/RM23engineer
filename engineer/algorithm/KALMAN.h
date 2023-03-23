#pragma once
class KALMAN
{
public:
	double X_last; //��һʱ�̵����Ž��  X(k-|k-1)
	double X_mid;  //��ǰʱ�̵�Ԥ����  X(k|k-1)
	double X_now;  //��ǰʱ�̵����Ž��  X(k|k)
	double P_mid;  //��ǰʱ��Ԥ������Э����  P(k|k-1)
	double P_now;  //��ǰʱ�����Ž����Э����  P(k|k)
	double P_last; //��һʱ�����Ž����Э����  P(k-1|k-1)
	double kg;     //kalman����
	double A;      //ϵͳ����
	double B;
	double Q;
	double R;
	double H;
	/**
	  * @name   kalmanCreate
	  * @brief  ����һ���������˲���
	  * @param  p:  �˲���
	  *         T_Q:ϵͳ����Э����
	  *         T_R:��������Э����
	  *
	  * @retval none
	  * @attention R�̶���QԽ�󣬴���Խ���β���ֵ��Q�������ֻ�ò���ֵ
	  *		       	��֮��QԽС����Խ����ģ��Ԥ��ֵ��QΪ������ֻ��ģ��Ԥ��
	  */
	KALMAN(double T_Q, double T_R);


	double Filter(double dat);
};