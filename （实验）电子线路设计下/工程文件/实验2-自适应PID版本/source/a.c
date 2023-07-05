#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NB -3
#define NM -2
#define NS -1
#define ZO 0
#define PS 1
#define PM 2
#define PB 3

void FuzzyPID();	//初始化PID参数
float FuzzyPIDcontroller(float e_max, float e_min, float ec_max, float ec_min, float kp_max, float kp_min, float error, float error_c, float ki_max, float ki_min,float kd_max, float kd_min,float error_pre, float error_ppre);  //模糊PID控制实现函数
float Quantization(float maximum, float minimum, float x);	//误差 error 和误差变化 error_c 映射到论域中的函数
void Get_grad_membership(float error, float error_c);	////计算输入e与de/dt隶属度
void GetSumGrad();// 获取输出增量 △kp、△ki、△kd 的总隶属度
void GetOUT();  // 计算输出增量 △kp、△ki、△kd 对应论域值
float Inverse_quantization(float maximum, float minimum, float qvalues);  //去模糊化


const int  num_area = 8; //划分区域个数
float e_membership_values[7] = {-3,-2,-1,0,1,2,3}; //输入e的隶属值
float ec_membership_values[7] = { -3,-2,-1,0,1,2,3 };//输入de/dt的隶属值
float kp_menbership_values[7] = { -3,-2,-1,0,1,2,3 };//输出增量kp的隶属值
float ki_menbership_values[7] = { -3,-2,-1,0,1,2,3 }; //输出增量ki的隶属值
float kd_menbership_values[7] = { -3,-2,-1,0,1,2,3 };  //输出增量kd的隶属值

float kp;                       //PID参数kp
float ki;                       //PID参数ki
float kd;                       //PID参数kd
float qdetail_kp;               //增量kp对应论域中的值
float qdetail_ki;               //增量ki对应论域中的值
float qdetail_kd;               //增量kd对应论域中的值
float detail_kp;                //输出增量kp
float detail_ki;                //输出增量ki
float detail_kd;                //输出增量kd
float qerror;                    //输入e对应论域中的值
float qerror_c;                  //输入de/dt对应论域中的值             
float e_gradmembership[2];      //输入e的隶属度
float ec_gradmembership[2];     //输入de/dt的隶属度
int e_grad_index[2];            //输入e隶属度在规则表的索引
int ec_grad_index[2];           //输入de/dt隶属度在规则表的索引
float KpgradSums[7] = { 0,0,0,0,0,0,0 };   //输出增量kp总的隶属度
float KigradSums[7] = { 0,0,0,0,0,0,0 };   //输出增量ki总的隶属度
float KdgradSums[7] = { 0,0,0,0,0,0,0 };   //输出增量kd总的隶属度

float e_max = 150;      //误差最大值
float e_min = -150;    //误差最小值
float ec_max = 300;     //误差变化最大值
float ec_min = -300;    //误差变化最小值
float kp_max = 50;       //比例系数 kp 上限值
float kp_min = -50;    //比例系数 kp 下限值
float ki_max = 0.1;     //积分系数 ki 上限值
float ki_min = -0.1;    //积分系数 ki 下限值
float kd_max = 0.01;    //微分系数 kd 上限值
float kd_min = -0.01;   //微分系数 kd 下限值
float error;        //误差值
float error_c;      //误差变化值
float error_pre = 0;    //上一次误差值
float error_ppre = 0;   //上上次误差值


int  Kp_rule_list[7][7] = { {PB,PB,PM,PM,PS,ZO,ZO},        //kp规则表
			       {PB,PB,PM,PS,PS,ZO,NS},
			       {PM,PM,PM,PS,ZO,NS,NS},
			       {PM,PM,PS,ZO,NS,NM,NM},
			       {PS,PS,ZO,NS,NS,NM,NM},
			       {PS,ZO,NS,NM,NM,NM,NB},
			       {ZO,ZO,NM,NM,NM,NB,NB} };

int  Ki_rule_list[7][7] = { {NB,NB,NM,NM,NS,ZO,ZO},     //ki规则表
			      {NB,NB,NM,NS,NS,ZO,ZO},
			      {NB,NM,NS,NS,ZO,PS,PS},
			      {NM,NM,NS,ZO,PS,PM,PM},
			      {NM,NS,ZO,PS,PS,PM,PB},
			      {ZO,ZO,PS,PS,PM,PB,PB},
			      {ZO,ZO,PS,PM,PM,PB,PB} };

	int  Kd_rule_list[7][7] = { {PS,NS,NB,NB,NB,NM,PS},     //kd规则表
			       {PS,NS,NB,NM,NM,NS,ZO},
			       {ZO,NS,NM,NM,NS,NS,ZO},
			       {ZO,NS,NS,NS,NS,NS,ZO},
			       {ZO,ZO,ZO,ZO,ZO,ZO,ZO},
		                       {PB,NS,PS,PS,PS,PS,PB},
		                       {PB,PM,PM,PM,PS,PS,PB} };

void FuzzyPID()  //参数初始化
{
	kp = 0;
	ki = 0;
	kd = 0;
	qdetail_kp = 0;
	qdetail_ki = 0;
	qdetail_kd = 0;
}

//模糊PID控制实现函数
float FuzzyPIDcontroller(float e_max, float e_min, float ec_max, float ec_min, float kp_max, float kp_min, float error, float error_c,float ki_max,float ki_min,float kd_max,float kd_min,float error_pre,float error_ppre)
{
	float output;
	qerror = Quantization(e_max, e_min, error);	   //将 误差 error 映射到论域中
	qerror_c = Quantization(ec_max, ec_min, error_c);	  //将误差变化 error_c 映射到论域中
	Get_grad_membership(qerror, qerror_c);	//计算误差 error 和误差变化 error_c 的隶属度
	GetSumGrad();	//计算输出增量 △kp、△ki、△kd 的总隶属度
	GetOUT();		// 计算输出增量 △kp、△ki、△kd 对应论域值
	detail_kp = Inverse_quantization(kp_max, kp_min, qdetail_kp);    //去模糊化得到增量 △kp
	detail_ki = Inverse_quantization(ki_max, ki_min, qdetail_ki);    //去模糊化得到增量 △ki
	detail_kd = Inverse_quantization(kd_max, kd_min, qdetail_kd);    //去模糊化得到增量 △kd
	qdetail_kd = 0;
	qdetail_ki = 0;
	qdetail_kp = 0;
	kp = kp + detail_kp;    //得到最终的 kp 值
	ki = ki + detail_ki;    //得到最终的 ki 值
	kd = kd + detail_kd;    //得到最终的 kd 值
	if (kp < 0){
		kp = 0;}
	if (ki < 0){
		ki = 0;}
	if (kd < 0){
		kd = 0;}
	detail_kp = 0;
  detail_ki = 0;
  detail_kd = 0;
  output = kp*(error - error_pre) + ki * error + kd * (error - 2 * error_pre + error_ppre);   //计算最终的输出
	return output;
}

 
///区间映射函数
float Quantization(float maximum,float minimum,float x)
{
	float qvalues= 6.0 *(x-minimum)/(maximum - minimum)-3;
	return qvalues;
}
 
//输入e与de/dt隶属度计算函数
void Get_grad_membership(float error,float error_c)   
{
	int i;
	if (error > e_membership_values[0] && error < e_membership_values[6])
	{
		for ( i = 0; i < num_area - 2; i++)
		{
			if (error >= e_membership_values[i] && error <= e_membership_values[i + 1])
			{
				e_gradmembership[0] = -(error - e_membership_values[i + 1]) / (e_membership_values[i + 1] - e_membership_values[i]);
				e_gradmembership[1] = 1+(error - e_membership_values[i + 1]) / (e_membership_values[i + 1] - e_membership_values[i]);
				e_grad_index[0] = i;
				e_grad_index[1] = i + 1;
				break;
			}
		}
	}
	else
	{
		if (error <= e_membership_values[0])
		{
			e_gradmembership[0] = 1;
			e_gradmembership[1] = 0;
			e_grad_index[0] = 0;
			e_grad_index[1] = -1;
		}
		else if (error >= e_membership_values[6])
		{
			e_gradmembership[0] = 1;
			e_gradmembership[1] = 0;
			e_grad_index[0] = 6;
			e_grad_index[1] = -1;
		}
	}
 
	if (error_c > ec_membership_values[0] && error_c < ec_membership_values[6])
	{
		for ( i = 0; i < num_area - 2; i++)
		{
			if (error_c >= ec_membership_values[i] && error_c <= ec_membership_values[i + 1])
			{
				ec_gradmembership[0] = -(error_c - ec_membership_values[i + 1]) / (ec_membership_values[i + 1] - ec_membership_values[i]);
				ec_gradmembership[1] = 1 + (error_c - ec_membership_values[i + 1]) / (ec_membership_values[i + 1] - ec_membership_values[i]);
				ec_grad_index[0] = i;
				ec_grad_index[1] = i + 1;
				break;
			}
		}
	}
	else
	{
		if (error_c <= ec_membership_values[0])
		{
			ec_gradmembership[0] = 1;
			ec_gradmembership[1] = 0;
			ec_grad_index[0] = 0;
			ec_grad_index[1] = -1;
		}
		else if (error_c >= ec_membership_values[6])
		{
			ec_gradmembership[0] = 1;
			ec_gradmembership[1] = 0;
			ec_grad_index[0] = 6;
			ec_grad_index[1] = -1;
		}
	}
 
}
 
// 获取输出增量kp,ki,kd的总隶属度
void GetSumGrad()
{
	int i;
	int j;

    // 初始化 Kp、Ki、Kd 总的隶属度值为 0
								
	for ( i = 0; i <= num_area - 1; i++)
	{
		KpgradSums[i] = 0;
		KigradSums[i] = 0;
        		KdgradSums[i] = 0;
	}

    	for ( i = 0; i < 2; i++)
   	 {
        		if (e_grad_index[i] == -1)
        		{
            			continue;
       		}
        		for ( j = 0; j < 2; j++)
       		{
            			if (ec_grad_index[j] != -1)
            			{
                			int indexKp = Kp_rule_list[e_grad_index[i]][ec_grad_index[j]] + 3;
               				int indexKi = Ki_rule_list[e_grad_index[i]][ec_grad_index[j]] + 3;
                			int indexKd = Kd_rule_list[e_grad_index[i]][ec_grad_index[j]] + 3;
                			KpgradSums[indexKp]= KpgradSums[indexKp] + (e_gradmembership[i] * ec_gradmembership[j]);
               				KigradSums[indexKi] = KigradSums[indexKi] + (e_gradmembership[i] * ec_gradmembership[j]);
                			KdgradSums[indexKd] = KdgradSums[indexKd] + (e_gradmembership[i] * ec_gradmembership[j]);
            			}
            			else
            			{
                			continue;
            			}
        		}
 	 }
}
 
// 计算输出增量kp,kd,ki对应论域值
void GetOUT()
{
	int i;
	for ( i = 0; i < num_area - 1; i++)
	{
		qdetail_kp += kp_menbership_values[i] * KpgradSums[i];
		qdetail_ki += ki_menbership_values[i] * KigradSums[i];
		qdetail_kd += kd_menbership_values[i] * KdgradSums[i];
	}
}
 
//反区间映射函数
float Inverse_quantization(float maximum, float minimum, float qvalues)
{
	float x = (maximum - minimum) *(qvalues + 3)/6 + minimum;
	return x;
}