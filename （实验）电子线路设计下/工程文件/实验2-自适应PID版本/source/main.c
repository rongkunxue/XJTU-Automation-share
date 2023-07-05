
// 字符编码使用 UTF-8
#include "ADC.h"
#include "DAC.h"
#include "Delay.h"
#include "SYS_Init.h"
#include "Timer.h"
#include "led.h"
#include "lcd.h" 
// #include "Handle_Menu.h"
#include "c8051f020.h"
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
// Timers value
unsigned int  timer0_value;
unsigned int  timer1_value;
unsigned int  timer2_value;
unsigned int  timer3_value;
unsigned int  timer4_value;

// ADC & DAC variables
unsigned char channel;   // ADC 通道转换
unsigned int  vref;      // VREF
unsigned int  vtarget;   // VTARGET
unsigned int  vadc;      // ADC 取值
unsigned int  vadc_dec;  // ADC 取值
unsigned int  vdac;      // DAC 输出
unsigned int  vdac_dec;  // DAC 输出





//用户初始化代码
uchar code str0[]="PIDCONTROL";
uchar code str1[]="accruate";
uchar code str2[]="Press 1 to start";
uchar code str3[]="Press 3 to back";

typedef struct{
	int setpoint;	
	long sumerror;			
	float P;			
	float I;			
	float D;	
	int lasterror;	
	int preverror;
	int result;
}PID;

PID tmp_pid={0,0,0,0,0,0,0,0};
const unsigned char code blank[1024] = { /* 0X00,0X01,0X80,0X00,0X40,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

volatile int wave[128]={0};

unsigned int KEY_FLAG;


//用户初始化代码
void PID_init(PID* ptr)
{
	ptr->setpoint = 3000;
	ptr->sumerror = 0; 
	ptr->lasterror = 0;
	ptr->preverror = 0;	
	ptr->P = 1;                
	ptr->I = 0.025;                
	ptr->D = 0.004;   
	ptr->result = 0;                                      			
}


void PID_contrl(PID* ptr,int nowpoint){
	int tmp_error;
	int tmp_common;
	tmp_error = ptr->setpoint - nowpoint;	
	ptr->sumerror+=tmp_error;
	tmp_common=tmp_error-ptr->lasterror;
	ptr->result=FuzzyPIDcontroller(2000, -2000,500, -500, 50, -50, tmp_error, tmp_common, 0.1,-0.1,0.01, -0.01,ptr->lasterror, ptr->preverror);
	ptr->preverror=ptr->lasterror;
	ptr->lasterror = tmp_error;		
}

void PID_display(){
			WriteStr(0, 0, str0);
			WriteStr(1, 0, str1);
			WriteStr(2, 0, str2);
			WriteStr(3, 0, str3);
}

//User end

void Timer1_Init_Main(void) {
    Enable_Timer1;       // 设定 IE 标志位 1，允许 Timer1 溢出中断请求
    Timer1_Set_Method1;  // 设置定时器 1 为方式 1 定时器功能
}

void Timer1_ISR(void) interrupt 3 {
    timer1_value++;

    TH1 = 0x00; // Reinit Timer0 High register
    TL1 = 0x00;
}

void Device_Init(void) {
    SYS_Init();  // SYS 初始化
		LcdInit();
		LedInit();
    Timer1_Init_Main();
    Timer3_Init_ADC0(SYSCLK / SAMPLERATE);  // TIMER3 初始化 

    INT_Init();  // INT 中断初始化

    ADC0_Init();     // ADC0 初始化
    ADC0_Enable(1);  // 使能 ADC0
    DAC0_Init();     // DAC 初始化

    Timer1_Start;  // 设定 TCON 中断标志位 6，定时器 1 开启

    timer1_value = 0;
    timer3_value = 0;

    channel  = 1;
    vref     = 5244;
    vtarget  = 2800;
    vadc     = 0x0000;
    vadc_dec = 0;
    vdac     = 0x0000;
    vdac_dec = 0;
}

void Do(void) {
    if ((timer1_value & 0x0007) == 0x0001) {     
        if (channel == 1) 	 {
            // 从 ADC0 AIN1 取得 10 位 16 进制数 vadc
            vadc = ADC_ValueReturn(channel);
            // 将 vadc 转化为 10 进制数进行计算
            vadc_dec = (unsigned long int)vadc * (unsigned long int)vref / 4096;
						PID_contrl(&tmp_pid,vadc_dec);
						vdac_dec=vadc_dec+tmp_pid.result;
						// 将 10 进制数 vdac_dec 转化为 16 进制数
            vdac = (unsigned long int)vdac_dec * 4096 / (unsigned long int)vref;
            // 从 ADC0 输出 10 位 16 进制数 vdac
            DAC0_Output(vdac);
					//调节目标霍尔电压值
					if(KEY_FLAG==1){
						tmp_pid.setpoint-=100;
						KEY_FLAG=0;}
					else{
						if(KEY_FLAG==2){
						tmp_pid.setpoint+=100;
						KEY_FLAG=0;}
          }
      }
		}
	}
int main(void) {
    int i=0,j=0;
		Device_Init();
	  PID_init(&tmp_pid);
    while (1) {
		my_LedDispNum(vadc_dec,tmp_pid.setpoint,vdac_dec);
		PID_display();
		if(KEY_FLAG==1){
		LcdClear();
		ImageShow(blank);
		KEY_FLAG=0;
		while(KEY_FLAG!=3){
			my_LedDispNum(vadc_dec,tmp_pid.setpoint,vdac_dec);
			Do();
			i+=1;
			if(i%5==0){
				wave[j]=vadc_dec;
				LcdShowPoint(j);
				i=0;
				j+=1;
				if(j==128){
					ImageShow(blank);
					j=0;
					}
				}
			}
			vdac=0;
			DAC0_Output(vdac);
			KEY_FLAG=0;
			LcdInit();
      }
    }
}

void INT1_ISR(void) interrupt 2
{
	Delay_ms(20);
	switch(P5){
		case 0xfb:
      KEY_FLAG=1;
			break;		
		case 0xfd:
			KEY_FLAG=2;
			break;
		case 0xfe:
			KEY_FLAG=3;
			break;
	}
}

