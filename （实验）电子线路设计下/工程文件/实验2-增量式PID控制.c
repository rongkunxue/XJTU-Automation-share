//增量控制需要加下面算法加入main.c
并更换main.h()中的PID_control()为PID_control_zeng()
 float Kp
 float T
 float Ti
 float Td
void PID_contrl_zeng(PID* ptr,int nowpoint){
	int tmp_error;
	int tmp_common;
	tmp_error = ptr->setpoint - nowpoint;	
	tmp_common=tmp_error-ptr->lasterror;
	ptr->result=Kp*(ptr->lasterror+(T/Ti)*ptr->sumerror+Td/T*（ptr->preverror-ptr->lasterror）；
  ptr->sumerror+=tmp_error;
	ptr->preverror=ptr->lasterror;
	ptr->lasterror = tmp_error;		
}