//pid控制函数
void PIDOperation (void)   
{ 
	/*uint32 Temp[3];                                       
	uint32 PostSum;                                    
	uint32 NegSum; 
	Temp[0] = 0; 
	Temp[1] = 0; 
	Temp[2] = 0; 
	PostSum = 0; 
	NegSum  = 0; 
	PID.KP_Uint8 = kp;
	PID.KI_Uint8 = ki;
	PID.KD_Uint8 = kd;
	PID.RK_Uint16 = rk;*/
	PID.KP_Uint8 = kp;
 	PID.KI_Uint8 = ki;
  PID.KD_Uint8 = kd;
  PID.RK_Uint16 = rk;
	PostSum = 0; 
  NegSum  = 0;
	Temp_pid[0] = 0; 
  Temp_pid[1] = 0; 
  Temp_pid[2] = 0; 
	if( PID.RK_Uint16 > PID.CK_Uint16 )                   
	{ 
	 if( PID.RK_Uint16 - PID.CK_Uint16 >10 )            
	 { 
		PID.Uk_Uint16 = 100;   
	 }                     
	 else 
	{ 
	Temp_pid[0] = PID.RK_Uint16 - PID.CK_Uint16;        
	PID.EkFlag_Uint8[1]=0;                         
	PID.Ek_Uint32[2] = PID.Ek_Uint32[1]; 
	PID.Ek_Uint32[1] = PID.Ek_Uint32[0]; 
	PID.Ek_Uint32[0] = Temp_pid[0]; 
	/****************************************/ 
	if( PID.Ek_Uint32[0] >PID.Ek_Uint32[1] )                           
	{ 
	Temp_pid[0]=PID.Ek_Uint32[0] - PID.Ek_Uint32[1];           
	PID.EkFlag_Uint8[0]=0;                                       
	} 
	else 
	{ 
	Temp_pid[0]=PID.Ek_Uint32[0] - PID.Ek_Uint32[1];        
	 PID.EkFlag_Uint8[0]=1;                                                
	}
	/****************************************/ 
	Temp_pid[2]=PID.Ek_Uint32[1]*2 ;                                             
	if( (PID.Ek_Uint32[0]+ PID.Ek_Uint32[2])>Temp_pid[2] )            
	{ 
	Temp_pid[2]=(PID.Ek_Uint32[0]+ PID.Ek_Uint32[2])-Temp_pid[2];     
	PID.EkFlag_Uint8[2]=0;                                           
	} 
	else 
	{ 
	Temp_pid[2]=Temp_pid[2]-(PID.Ek_Uint32[0]+ PID.Ek_Uint32[2]);  
	PID.EkFlag_Uint8[2]=1;                                      
	}  
	/****************************************/        
	Temp_pid[0] = (uint32)PID.KP_Uint8 * Temp_pid[0];                        
	Temp_pid[1] = (uint32)PID.KI_Uint8 * PID.Ek_Uint32[0];             
	Temp_pid[2] = (uint32)PID.KD_Uint8 * Temp_pid[2];                      
	/**********KP*[E(k)-E(k-1)]**********/ 
	if(PID.EkFlag_Uint8[0]==0) 
	PostSum += Temp_pid[0];                                   
	else                                               
	NegSum += Temp_pid[0];                                    
	/********* KI*E(k)****************/  
	if(PID.EkFlag_Uint8[1]==0)       
	PostSum += Temp_pid[1];                                
	else 
	;                                                 
	/****KD*[E(k-2)+E(k)-2E(k-1)]****/                            
	if(PID.EkFlag_Uint8[2]==0) 
	PostSum += Temp_pid[2];                               
	else 
	NegSum += Temp_pid[2];                             
	/***************U(K)***************/                              
	PostSum += (uint32)PID.Uk_Uint16;     
	 
	if(PostSum > NegSum )                         
	{ 
			Temp_pid[0] = PostSum - NegSum; 
		if( Temp_pid[0] < 100 )                         
			PID.Uk_Uint16 = Temp_pid[0]; 
		else 
			PID.Uk_Uint16 = 100;                    
	} 
	else                                    
		PID.Uk_Uint16 = 0; 
	} 
	} 
	else  
	{ 
		PID.Uk_Uint16 = 0;  
	}  
} 