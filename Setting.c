#include  "config.h"
#include "Main.h"






extern void Calib_I_Zero(void);
extern void Calib_V_Zero(void);
extern void Calib_M_Zero(void);
unsigned char PassWord2(void);
void showCalibDynamo(void);


extern volatile uint32 KeyValue;
extern uint16	HTAB,VTAB,STAB,BTAB;
extern uint16	Gs,M_point;
extern uint8	MyID;
extern volatile uint16	FlagDisp;
extern volatile uint16 	FlagMs100,FlagMs2;
extern volatile uint16  In_Test;
extern float Xtemp;
extern uint32 MTemp;

extern float Fv,Fc,Fp,Vtemp,pFt,pFs,Po,pFt2;
extern volatile float Ft,Fu;
extern float	KI,KV,KM,KM2;//,KM_0;
extern U32	para[8],V32;
extern char sbuff[32];
extern uint16 Second05,Second1;


extern uint8	No[9];
extern U_PID 	PidPara,PidParaS,PidPara1,PidPara2;			//7 Bytes
extern float Xtemp;
extern uint32 MTemp;
extern uint16 LoadType2,LastStep2,voltdir,voltdir1,StartTime,LastStep1;
extern float   TestVolt1,StartVolt1,TestVolt2,StartVolt2;;

extern STEP 	Step[16];
extern STEP2  Step2[22];

extern IN_ROT 	in_rot;
extern uint8	EndMode,AlarmMode;
extern float 	EndTime,AlarmValue;
extern uint32	ulEndTime;


extern uint8	s_buff[240];
extern U32	Wbuf5460M,Rbuf5460M;
extern U32 	RresultV[6],RresultM[6];
extern char   UR0_R_Buff[256],UR0_T_Buff[256];
extern uint16 Uart0_R_Count,Uart0_R_Len;
extern uint16 In_Receive,Uart0_OK,Uart0_Command;
extern uint16 Uart0_T_Count,Uart0_T_Len,In_Send,Tran_f;




uint16 In_Calib;

extern volatile uint16 Running,DelayCount;
extern volatile uint16 Uart1_OK,Uart1_Command;
extern volatile uint32 nowClock;

extern float Speed0;
extern PID pid0;
extern volatile int32 Fd,PidMax;

extern float Mx[200],M2Temp, MxTemp,PxTemp,Px[20],Mx2[200];

extern float PerFor[7],Cons[7];

extern uint8 CRC;
extern volatile uint16 FlagPid;
extern uint16 RunMode;
/*****************************************************/
void calibrate(void)
{	Bell();
		if(PassWord())
		{
			showPG00();
			while (KeyValue!=0xff)
			{ Read_Key(); }
			return;		
		}
	
	/*==================*/
	showCalib00();STAB=0;			
	while (KeyValue!=0xff)
		{ Read_Key(); }
	BTAB=0;
	while(1)
	{
		Read_Key(); 
		/*if(KeyValue==F1) 
		{
			Bell();
			if(STAB==0)
			{	STAB=1;
				HTAB=0x09;VTAB=0x14;putEng(0x31);				
				HTAB=0x09;VTAB=0x26;verEng(0x32);
			}
			else if(STAB==1)
			{	STAB=2;
				HTAB=0x09;VTAB=0x26;putEng(0x32);
				HTAB=0x09;VTAB=0x38;verEng(0x33);						 
			}	
			else// if(STAB==2)
			{	STAB=0;
				HTAB=0x09;VTAB=0x38;putEng(0x33);
				HTAB=0x09;VTAB=0x14;verEng(0x31);						 
			}	
			BTAB=0;
			while (KeyValue!=0xff)
				{ Read_Key(); }			
		}
		else*/ if(KeyValue==F3) 
		{
			Bell();				
			showPG00();
			while (KeyValue!=0xff)
			{ Read_Key(); }
			return;		
		}
		else if(KeyValue==F4) 
		{
			Bell();
			/*switch (STAB)
			{	case 0: 
				{	calib01();break;}
				case 1: 
				{	calib02();break;}	
				case 2:
				{	*/calib03();//break;
			//}
			//}			
		}

		if(FlagMs2)
			Read_ResultM();
	
		if(FlagMs100)
		{	FlagMs100=0;
			Read_ResultV();			
		}

		if(FlagDisp)
		{	FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;
			}			
		}
	
	}		
}

/***************************************************/
void calib01(void)
{
	
	/*showCalib01();STAB=0;	
	HTAB=0x00;VTAB=0x00;
	putString( "电流表校准");
	while (KeyValue!=0xff)
		{ Read_Key(); }
	In_Calib=0;
	
	
	while(1)
	{
		Read_Key(); 
		if(KeyValue==F1) 
		{	Bell();
			STAB=(STAB>=1)?0:STAB+1;
			switch (STAB)
			{
				case 0:
				{HTAB=0x09;VTAB=0x38;putEng('2');
				 HTAB=0x09;VTAB=0x20;verEng('1');
				 break;}
				case 1:
				{HTAB=0x09;VTAB=0x20;putEng('1');
				 HTAB=0x09;VTAB=0x38;verEng('2');
				 break;}					
			}	
			while (KeyValue!=0xff)
			{ Read_Key(); }			
		}
		else if(KeyValue==F2)
		{
			if(In_Calib)
			{
				Bell();
				if(ISendStr(0xa0,0x10,para[0].b8,8)==1)	
				{	VTAB=0x00;HTAB=0x16;
					putString( "保存成功");	
				}
				else
				{	VTAB=0x00;HTAB=0x16;
					putString( "保存错误");	
				}				
				Delay(200);
				VTAB=0x00;HTAB=0x16;putString( "        ");
				VTAB=0x20;HTAB=0x1a;putString( "  ");
				VTAB=0x70;HTAB=0x08;putString( "      ");
				In_Calib=0;
				while (KeyValue!=0xff)
					{ Read_Key(); }	
			}
		}
		else if(KeyValue==F3) 
		{
			Bell();
			showCalib00();STAB=0;
			while (KeyValue!=0xff)
			{ Read_Key(); }
			return;		
		}
		else if(KeyValue==F4) 
		{
			Bell();
			switch(STAB)
			{
				case 0:					
				{	 Calib_I_Zero();						
					 VTAB=0x20;HTAB=0x1a;putEng('O');putEng('K');
					 VTAB=0x70;HTAB=0x08;putString("F2");verString("保存");
					 In_Calib=1;
					 while (KeyValue!=0xff)
		         					{ Read_Key(); }
					 break;
				}
				case 1:
				{	 CalibCurrent();break;	}
				
			}			
		}		
		
	
		if(FlagMs2)
		{	Read_ResultM();	}
		
		if(FlagMs100)
		{	FlagMs100=0;
			if(--Second1==0)
				Second1=10;		
			Read_ResultV();
		}

		if(FlagDisp)
		{	FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;
			}			
		}
	}*/	
}

/*****************************************************/
void calib02(void)
{
	/*showCalib01();STAB=0;
	HTAB=0x00;VTAB=0x00;
	putString( "电压表校准");
	In_Calib=0;
	while (KeyValue!=0xff)
		{ Read_Key(); }	
	
	
	while(1)
	{
		Read_Key(); 
		if(KeyValue==F1) 
		{
			Bell();
			STAB=(STAB==0)?1:0;
			switch (STAB)
			{
				case 0:
				{HTAB=0x09;VTAB=0x38;putEng('2');
				 HTAB=0x09;VTAB=0x20;verEng('1');
				 break;}
				case 1:
				{HTAB=0x09;VTAB=0x20;putEng('1');
				 HTAB=0x09;VTAB=0x38;verEng('2');
				 break;}	
			}
			while (KeyValue!=0xff)
			{ Read_Key(); }			
		}
		else if(KeyValue==F2)
		{
			if(In_Calib)
			{
				Bell();
				if(ISendStr(0xa0,0x18,para[2].b8,8)==1)	
				{	VTAB=0x00;HTAB=0x16;
					putString( "保存成功");	
				}
				else
				{	VTAB=0x00;HTAB=0x16;
					putString( "保存错误");	
				}				
				Delay(200);
				VTAB=0x00;HTAB=0x16;putString( "        ");
				VTAB=0x20;HTAB=0x1a;putString( "  ");
				VTAB=0x70;HTAB=0x08;putString( "      ");
				In_Calib=0;
				while (KeyValue!=0xff)
					{ Read_Key(); }	
			}
		}
		else if(KeyValue==F3) 
		{
			Bell();
			showCalib00();STAB=0;
			while (KeyValue!=0xff)
			{ Read_Key(); }
			return;		
		}
		else if(KeyValue==F4) 
		{
			Bell();
			switch(STAB)
			{	case 0:					
				{	 Calib_V_Zero();						
					 VTAB=0x20;HTAB=0x1a;putEng('O');putEng('K');
					 VTAB=0x70;HTAB=0x08;putString("F2");verString("保存");
					 In_Calib=1;
					 while (KeyValue!=0xff)
		         					{ Read_Key(); }
					 break;
				}				
				case 1:
				{	 CalibVolt();break;		}
			}			
		}	
		
	
		if(FlagMs2)
		{	Read_ResultM();	}
		
		if(FlagMs100)
		{	FlagMs100=0;
			if(--Second1==0)
				Second1=10;					
			Read_ResultV();
		}	

		if(FlagDisp)
		{	FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;
			}			
		}
	}*/	
}



/***********************************************************/
void calib03(void)      //转矩表校准
{
	
	showCalib01();STAB=0;
	In_Calib=0;
	while (KeyValue!=0xff)
		{ Read_Key(); }	
	
	while(1)
	{
		Read_Key(); 
		if(KeyValue==F1) 
		{
			Bell();
			STAB=(STAB==0)?1:0;//上下移动的效果
			switch (STAB)
			{
				case 0:
				{HTAB=0x09;VTAB=0x38;putEng('2');
				 HTAB=0x09;VTAB=0x20;verEng('1');
				 break;}
				case 1:
				{HTAB=0x09;VTAB=0x20;putEng('1');
				 HTAB=0x09;VTAB=0x38;verEng('2');
				 break;}					 
			}					 			
			while (KeyValue!=0xff)//这一句非常关键
			{ Read_Key(); }			
		}
		else if(KeyValue==F2)
		{	if(In_Calib)
			{
				Bell();
				
				if(ISendStr(0xa0,0x20,para[4].b8,8)==1)		
				{
					VTAB=0x00;HTAB=0x16;
					putString( "保存成功");	
				}
				else
				{	VTAB=0x00;HTAB=0x16;
					putString( "保存错误");	
				}				
				Delay(200);
				VTAB=0x00;HTAB=0x16;putString( "        ");
				VTAB=0x20;HTAB=0x1a;putString( "  ");
				VTAB=0x70;HTAB=0x08;putString( "      ");
				In_Calib=0;
				while (KeyValue!=0xff)
					{ Read_Key(); }	
			}
		}
		else if(KeyValue==F3) 
		{
			Bell();
			showCalib00();STAB=0;
			while (KeyValue!=0xff)
			{ Read_Key(); }
			return;		
		}
		else if(KeyValue==F4) 
		{
			Bell();
			switch(STAB)
			{
				case 0:					
				{	if(In_Calib==0)
					{	VTAB=0x20;HTAB=0x1a;putEng(' ');putEng(' ');
						VTAB=0x70;HTAB=0x18;putString("      ");										 
					 	Calib_M_Zero();
						In_Calib=1;	
						 VTAB=0x20;HTAB=0x1a;putEng('O');putEng('K');
						 VTAB=0x70;HTAB=0x08;putString("F2");verString("保存");
					}					
					 while (KeyValue!=0xff)
		         					{ Read_Key(); }
					 break;
				}				
				case 1:
				{
						 CalibTorque();	
				}
			}			
		}		
		if(FlagDisp)
		{	
			DataAccess(0);		}
	
	}	
}

	
/*===========================================*/
unsigned char PassWord(void)
{
	uint16	ii;
	
	//Bell();
	showPassWord();STAB=0;BTAB=0;
	
	sbuff[0]=0x20;sbuff[1]=0x20;sbuff[2]=0x20;
	sbuff[3]=0x20;sbuff[4]=0x20;sbuff[5]=0x20;
	while (KeyValue!=0xff)
			{ Read_Key(); }
	
	while(STAB==0)
	{
		Read_Key(); 
		if(KeyValue==F3) 
		{
			Bell();				
			return 0xff; 	
		}
		else if(KeyValue==F4) 
		{
			Bell();
			if((sbuff[0]==0)&&(sbuff[1]==3)&&(sbuff[2]==0)
					&&(sbuff[3]==8))
				STAB=1;
			while (KeyValue!=0xff)
					{ Read_Key(); } 	
		}
		else if(KeyValue==GO_L)
		{
			Bell();
			sbuff[BTAB]=0x20;
			if(BTAB==0) BTAB=0;
			else --BTAB;			
			HTAB=0x0d;VTAB=0x30;
			for(ii=0;ii<4;++ii)
					putEng('*');
			HTAB=0x0d+BTAB;verEng('*');
			while (KeyValue!=0xff)
					{ Read_Key(); } 			
		}
		if(KeyValue<=9)
		{
			Bell();
			sbuff[BTAB]=KeyValue;
			if (BTAB==3) BTAB=3;
			else ++BTAB;
			HTAB=0x0d;VTAB=0x30;
			for(ii=0;ii<4;++ii)
				 putEng('*');
			HTAB=0x0d+BTAB;verEng('*');
				
			while (KeyValue!=0xff)
					{ Read_Key(); } 
		}		
		
	
		if(FlagMs2)
		{	Read_ResultM();	}
		
		
		if(FlagMs100)
		{	FlagMs100=0;
			if(--Second1==0)
				Second1=10;	
			Read_ResultV();	
		}

		if(FlagDisp)
		{	FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;
			}			
		}
	}
	
	return 0;
}


/*===========================================================*/
void CalibCurrent(void)
{	
	
	showScale();STAB=0;BTAB=0;
	HTAB=0x00;VTAB=0x00;
	putString( "电流表刻度调整");
	HTAB=0x18;VTAB=0x28;putString("A ");
	HTAB=0x18;VTAB=0x48;putString("A ");
	Vtemp=Fc;
	RunMotor(0,0);
	Second05=5;
	DataAccess(0);
	showCalib(Fc,0);				
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	while(1)
	{
		Read_Key(); 
		switch (KeyValue)
		{
	
			case F3:
			{
				Bell();
				RunMotor(0,0);
				showCalib01();STAB=0;
				HTAB=0x00;VTAB=0x00;
				putString( "电流表校准");			
				while (KeyValue!=0xff)
					{ Read_Key(); }
				return;		
			}
		 	case F4: 
			{
				Bell();
					
				if((Fc!=0)&&(Vtemp!=0))
					  KI=KI/Fc*Vtemp;
				if(KI<=1E-7)      KI=0.001;
				if(KI>=1.0) 	KI=1.0;

				V32.a32=(uint32)(1/KI);
				ISendStr(0xa0,0x30,V32.b8,4);	
					
				
				showCalib(Fc,0);			
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
		 	}	
		 	case GO_L:
			{
				Bell();
				if(BTAB==0) BTAB=3;
				else --BTAB;			
				showCalib(Fc,0);
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			case GO_R:
			{
				Bell();
				if(BTAB==3) BTAB=0;
				else ++BTAB;
				showCalib(Fc,0);
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			default:
			{
				 if(KeyValue<=9)
				{
					Bell();
					sprintf(sbuff,"%05.2f",Vtemp);
					if(BTAB<2) sbuff[BTAB]=KeyValue+0x30;
					else sbuff[BTAB+1]=KeyValue+0x30;			
					Vtemp=atof(sbuff);
					if(BTAB==3) BTAB=0;
					else ++BTAB;
					showCalib(Fc,0);	
					while (KeyValue!=0xff)
						{ Read_Key(); }	
				 }
			}
		}

		if(FlagMs2)
			Read_ResultM();
		
	
		if(FlagMs100)
		{	FlagMs100=0;
			Read_ResultV();			
		}
		if(FlagDisp)
		{	FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;				
				showCalib(Fc,0);
			}			
		}
	
		
	}
}

/*===========================================================*/
void CalibVolt(void)
{	
	
	showScale();STAB=0;BTAB=0;
	HTAB=0x00;VTAB=0x00;
	putString( "电压表刻度调整");
	HTAB=0x18;VTAB=0x28;putString("V ");
	HTAB=0x18;VTAB=0x48;putString("V ");
	Vtemp=Fv;
	RunMotor(0,0);
	Second05=5;
	DataAccess(0);
	showCalib(Fv,1);				
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	while(1)
	{
		Read_Key(); 
		switch (KeyValue)
		{
	
			case F3:
			{
				Bell();
				RunMotor(0,0);
				showCalib01();STAB=0;
				HTAB=0x00;VTAB=0x00;
				putString( "电压表校准");
				while (KeyValue!=0xff)
					{ Read_Key(); }
				return;		
			}
		 	case F4: 
			{
				Bell();				
				if((Fv!=0)&&(Vtemp!=0))
					KV=KV/Fv*Vtemp;
				if(KV<=1E-7)      KV=0.001;
				if(KV>=1.0) 	KV=1.0;
				
				V32.a32=(uint32)(1/KV);
				ISendStr(0xa0,0x34,V32.b8,4);	
				
				showCalib(Fv,1);			
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
		 	}	
		 	case GO_L:
			{
				Bell();
				if(BTAB==0) BTAB=3;
				else --BTAB;			
				showCalib(Fv,1);
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			case GO_R:
			{
				Bell();
				if(BTAB==3) BTAB=0;
				else ++BTAB;
				showCalib(Fv,1);
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			default:
			{
				 if(KeyValue<=9)
				{
					Bell();
					sprintf(sbuff,"%05.2f",Vtemp);
					if(BTAB<2) sbuff[BTAB]=KeyValue+0x30;
					else sbuff[BTAB+1]=KeyValue+0x30;			
					Vtemp=atof(sbuff);
					if(BTAB==3) BTAB=0;
					else ++BTAB;
					showCalib(Fv,1);	
					while (KeyValue!=0xff)
						{ Read_Key(); }	
				 }
			}
		}

		if(FlagMs2)
			Read_ResultM();		
	
		if(FlagMs100)
		{	FlagMs100=0;
			Read_ResultV();			
		}
		if(FlagDisp)
		{	FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;				
				showCalib(Fv,1);
			}			
		}
	}
}


/*===========================================================*/

void CalibTorque(void)
{	
	float nFt=0;
	
	showScale();STAB=0;BTAB=0;
	
	
	
	nFt=M2Temp/200;        //当前值
	nFt=(nFt<0)?-nFt:nFt;
	Vtemp=nFt;        //
	RunMotor(0,0);
	Second05=5;	
	DataAccess(0);
	showCalib(nFt,2);				
	while (KeyValue!=0xff)
		{ Read_Key(); }

	while(1)
	{
		Read_Key(); 
		switch (KeyValue)
		{
	
			case F3:
			{
				Bell();
				RunMotor(0,0);
				showCalib01();STAB=0;
				Second05=5;
				while (KeyValue!=0xff)
					{ Read_Key(); }
				return;		
			}
		 	case F4: 
			{
				Bell();
				if((nFt!=0)&&(Vtemp!=0))
					KM2=KM2/nFt*Vtemp;             
				if(KM2<=1E-7)      KM2=1E-7;
				if(KM2>=1.0) 	KM2=1.0;						
				V32.a32=(uint32)(1/KM2);	
				ISendStr(0xa0,0x38,V32.b8,4);		
				Delay(20);
				KM=KM2*2;
				V32.a32=(uint32)(1/KM);	
				ISendStr(0xa0,0x3c,V32.b8,4);				
				showCalib(nFt,2);
				Delay(20);
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
		 	}	
		 	case GO_L:
			{
				Bell();
				if(BTAB==0) BTAB=3;
				else --BTAB;			
				showCalib(nFt,2);
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			case GO_R:
			{
				Bell();
				//if(BTAB==3) BTAB=0;
				//else ++BTAB;
				BTAB=(BTAB==3)?0:BTAB+1;
				
				showCalib(nFt,2);
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			default:    //通过按键改变的值
			{
				 if(KeyValue<=9)
				{
					Bell();
					sprintf(sbuff,"%05.3f",Vtemp);
					if(BTAB<1) sbuff[BTAB]=KeyValue+0x30;//这里的判断是小数点前的位数
					else sbuff[BTAB+1]=KeyValue+0x30;			
					Vtemp=atof(sbuff);
					if(BTAB==3) BTAB=0;
					else ++BTAB;
					showCalib(nFt,2);	
					while (KeyValue!=0xff)
						{ Read_Key(); }	
				 }
			}
		}

		if(FlagMs2)
		{	
			Read_ResultM();
		}
		
		
		if(FlagPid)
		{	FlagPid=0;
			nFt=M2Temp/200;
			nFt=(nFt<0)?-nFt:nFt;
		}

		if(FlagMs100)
		{	FlagMs100=0;
			Read_ResultV();
		}
		
	
		
		if(FlagDisp)	
		{
			FlagDisp=0;	
			if(--Second05==0)
			{	Second05=5;				
				showCalib(nFt,2);
			}	
		}
	}	
}


/*================================================*/
void showCalib(float temp1,uint16 a)
{

	HTAB=0x12;VTAB=0x28;        //当前值
	if(a<2)
		sprintf(sbuff,"%05.2f",temp1);
	else
	 	sprintf(sbuff,"%5.3f",temp1);
	 putBuff(sbuff);
	 HTAB=0x12;VTAB=0x48;      //输入准确值
	 if(a<2)
	 { 	sprintf(sbuff,"%05.2f",Vtemp);
		 putBuff(sbuff);
		 if (BTAB<2)
		 	{HTAB=0x12+BTAB;verEng(sbuff[BTAB]);}
		 else 
		 	{HTAB=0x13+BTAB;verEng(sbuff[BTAB+1]);}
	 }
	 else
	 { 	sprintf(sbuff,"%05.3f",Vtemp);
		 putBuff(sbuff);
		 if (BTAB<1)
		 	{HTAB=0x12+BTAB;verEng(sbuff[BTAB]);}
		 else 
		 	{HTAB=0x13+BTAB;verEng(sbuff[BTAB+1]);}
	 }
}


/*===================================*/
void SetFirst(void)   //参数设置界面
{
	
	Bell();
	showSet0();STAB=0;		
	while (KeyValue!=0xff)
		{ Read_Key(); }
	while(1)
	{
		Read_Key(); 
		if(KeyValue==F1) 
		{
			Bell();
			STAB=(STAB>=2)?0:STAB+1;
			switch (STAB)
			{
				case 0:
				{HTAB=0x07;VTAB=0x40;putEng('3');
				 HTAB=0x07;VTAB=0x18;verEng(0x31);
				 break;}
				case 1:
				{HTAB=0x07;VTAB=0x18;putEng(0x31);
				 HTAB=0x07;VTAB=0x2c;verEng(0x32);
				 break;}				
				 case 2:
				{HTAB=0x07;VTAB=0x2c;putEng(0x32);
				 HTAB=0x07;VTAB=0x40;verEng(0x33);
				 break;}	
				
			}						
			while (KeyValue!=0xff)
			{ Read_Key(); }			
		}		
		else if(KeyValue==F3) 
		{
			Bell();	
			nowClock=0;
			showPG00();
			DispPG00();
			while (KeyValue!=0xff)
			{ Read_Key(); }
			return;		
		}
		else if(KeyValue==F4) 
		{
			Bell();
			switch (STAB)
			{	case 0: 
				{	SetPID();break;}
				case 3:
				{	SetDynamo();break;	}
				case 1:
				{	CalibDynamo();break;}
				case 2:
				{	SetPower();break;	}
			}			
		}

		
	
		if(FlagMs2)
		{	Read_ResultM();		}
		
		
		if(FlagMs100)
		{	FlagMs100=0;
			if(--Second1==0)
				Second1=10;	
			Read_ResultV();
		}

		if(FlagDisp)
		{	FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;
			}			
		}		
	}		
}
/*===================================*/
void SetPID(void)
{	
	uint8 CRC;
	uint16 nn=0;
	
	showPID();
	BTAB=0;
	STAB=0;
	
	Xtemp=0;//借用，给定值
	MTemp=0;

	PidParaS.pid.pgain=PidPara.pid.pgain;//来源paraccess获取的数据
	PidParaS.pid.igain=PidPara.pid.igain;
	PidParaS.pid.dgain=PidPara.pid.dgain;
	
	checkPID();//范围0-255
	displayPID();
	//RunMotor(1,1);	////////////////////////////////////////
	In_Test=0;
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	while(1)
	{
		Read_Key(); 
		switch (KeyValue)
		{
			case F1:
			{
				Bell();
				if(In_Test==0)
					STAB=(STAB==4)?0:STAB+1;
				else
					STAB=(STAB==4)?1:STAB+1;				
				BTAB=0;						
				checkPID();
				displayPID();				
				while (KeyValue!=0xff)
						{ Read_Key(); }			
				break;				
			}
			case F2:
			{	
				Bell();
				if(STAB==0)
				{	MTemp=(MTemp>=4)?0
						:(MTemp==1)?3:MTemp+1;
					Xtemp=0;
					displayPID();
				}
				else if(In_Test==0)
				{	checkPID();
					In_Test=1;	
					RunPID(0);
				}
				else
				{	In_Test=0;	
					PWM1MR0=1000;
					PWM1MR3=1000;
					PWM1LER=0x09;
					//IO0SET = 0x1000;
					displayPID();					
				}
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;				
			}		
			case F3:
			{	if(In_Test==0)
				{	RunMotor(0,0);
					Bell();STAB=0;BTAB=0;
					showSet0();
					//Bell();					
					while (KeyValue!=0xff)
						{ Read_Key(); }
					return;
				}
				break;
			}
			case F4:
			{
				Bell();	
				if(In_Test==0)
				{					
					checkPID();
					
					ReLoad2(0);
					ParaAccess(0);					
					
					PidPara.pid.pgain=PidParaS.pid.pgain;
					sprintf(sbuff,"%4d",PidPara.pid.pgain);					
					PidPara.pid.igain=PidParaS.pid.igain;						
					sprintf(sbuff+4,"%4d",PidPara.pid.igain);
					PidPara.pid.dgain=PidParaS.pid.dgain;
					sprintf(sbuff+8,"%4d",PidPara.pid.dgain);	
					
					for(nn=0;nn<4;nn++)
					{
						s_buff[10+nn]=sbuff[nn];
						s_buff[14+nn]=sbuff[nn+4];
						s_buff[18+nn]=sbuff[nn+8];
					}
					for(nn=0;nn<15;nn++)
					{
						if(ISendStr(0xa4,nn*16, (s_buff+nn*16),16)!=1)
							goto Lerr;
						Delay(4);
					}

					ReLoad2(1);
					ParaAccess(1);	
					PidPara1.pid.pgain=PidParaS.pid.pgain;
					sprintf(sbuff,"%4d",PidPara1.pid.pgain);					
					PidPara1.pid.igain=PidParaS.pid.igain;						
					sprintf(sbuff+4,"%4d",PidPara1.pid.igain);
					PidPara1.pid.dgain=PidParaS.pid.dgain;
					sprintf(sbuff+8,"%4d",PidPara1.pid.dgain);	
					
					for(nn=0;nn<4;nn++)
					{
						s_buff[10+nn]=sbuff[nn];
						s_buff[14+nn]=sbuff[nn+4];
						s_buff[18+nn]=sbuff[nn+8];
					}
					for(nn=0;nn<15;nn++)
					{
						if(ISendStr(0xa6,nn*16, (s_buff+nn*16),16)!=1)
							goto Lerr;
						Delay(4);
					}

					V32.f32=Cons[2]=(float)PidParaS.pid.pgain;
					ISendStr(0xa0,0x88,V32.b8,4);Delay(2);
					V32.f32=Cons[3]=(float)PidParaS.pid.igain;
					ISendStr(0xa0,0x8c,V32.b8,4);Delay(2);
					V32.f32=Cons[4]=(float)PidParaS.pid.dgain;
					ISendStr(0xa0,0x90,V32.b8,4);Delay(2);

					V32.f32=PerFor[3]=(float)PidParaS.pid.pgain;;
					ISendStr(0xa0,0xac,V32.b8,4);Delay(2);
					V32.f32=PerFor[4]=(float)PidParaS.pid.igain;
					ISendStr(0xa0,0xb0,V32.b8,4);Delay(2);
					V32.f32=PerFor[5]=(float)PidParaS.pid.dgain;
					ISendStr(0xa0,0xb4,V32.b8,4);Delay(2);


					VTAB=0x00;HTAB=0x16;
					putString( "保存成功");	
					goto L001;
					Lerr:
					VTAB=0x00;HTAB=0x16;
					putString( "保存错误");	
					L001:
					Delay(200);
					VTAB=0x00;HTAB=0x16;
					putString( "        ");					
					while (KeyValue!=0xff)
						{ Read_Key(); }
					
				}
				else
				{
					RunPID(1);
				}
				break;
			}	
			case GO_L:
			{
				Bell();
				if(STAB==4)
				{	BTAB=(BTAB==0)?3:BTAB-1;	}
				else if(STAB==0);
				else
					BTAB=(BTAB==0)?2:BTAB-1;
				displayPID();
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			case GO_R:
			{
				Bell();
				
				if(STAB==4)
				{	BTAB=(BTAB==3)?0:BTAB+1;	}
				else if(STAB==0);
				else
					BTAB=(BTAB==2)?0:BTAB+1;
				displayPID();
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			case 1:case 2:case 3:case 4:case 5:
			case 6:case 7:case 8:case 9:case 0:
			{
				
				Bell();
				{
					switch (STAB)
					{
						case 1:
						{
							sprintf(sbuff,"%03d",PidParaS.pid.pgain);
							sbuff[BTAB]=KeyValue|0x30;
							PidParaS.pid.pgain=atoi(sbuff);
							BTAB=(BTAB==2)?0:BTAB+1;
							break;}
						case 2:
						{
							sprintf(sbuff,"%03d",PidParaS.pid.igain);
							sbuff[BTAB]=KeyValue|0x30;
							PidParaS.pid.igain=atoi(sbuff);
							BTAB=(BTAB==2)?0:BTAB+1;
							break;}
						case 3:
						{
							sprintf(sbuff,"%03d",PidParaS.pid.dgain);
							sbuff[BTAB]=KeyValue|0x30;
							PidParaS.pid.dgain=atoi(sbuff);
							BTAB=(BTAB==2)?0:BTAB+1;
							break;}
						case 4:
						{
							if((MTemp==3)||(MTemp==2)||(MTemp==4))
							{
								sprintf(sbuff,"%04.0f",Xtemp);
								sbuff[BTAB]=KeyValue|0x30;								
								Xtemp=atof(sbuff);
								BTAB=(BTAB==3)?0:BTAB+1;
							}
							else if(MTemp==1)
							{	sprintf(sbuff,"%05.2f",Xtemp);
								if(BTAB<2)
									sbuff[BTAB]=KeyValue+0x30;
								else
									sbuff[BTAB+1]=KeyValue+0x30;
								Xtemp=atof(sbuff);
								BTAB=(BTAB==3)?0:BTAB+1;	
							}
							else
							{	sprintf(sbuff,"%05.2f",Xtemp);
								if(BTAB<2)
									sbuff[BTAB]=KeyValue+0x30;
								else
									sbuff[BTAB+1]=KeyValue+0x30;
										
								Xtemp=atof(sbuff);
								BTAB=(BTAB==3)?0:BTAB+1;								
							}							
							break;}
					}
					displayPID();
					while (KeyValue!=0xff)
					{ Read_Key(); }	
				}
			}
		}	
		
		if(FlagMs2)
		{	Read_ResultM();	}
		if(FlagPid)
		{	FlagPid=0;
			if((In_Test)&&(pid0.runtype==0))
			{		pid_calc();		}
		}
		

		
		
		if(FlagMs100)
		{	FlagMs100=0;
			Read_ResultV();
		}		
		if(FlagDisp)	
		{	FlagDisp=0;
			DataAccess(0);		
			if(--Second05==0)
			{	Second05=5;		
				displayPID2();
			}			
			if(In_Test)
			{	if(pid0.runtype)
					pid_calc();
			}
		}

		if(Uart0_OK)
		{
			Uart0_OK=0;
			switch (Uart0_Command)
			{				
				case 1:
				{	//U0THR = 0x91;
					U0THR = MyID|0x01;
					In_Send=0;U0IER |=0x02;
					break;
				}
				case 2:
				{
					//U0THR = 0x92;
					U0THR = MyID|0x02;
					In_Send=0;U0IER |=0x02;
					Bell();
					if(In_Test==1)
					{	
						In_Test=0;	
						PWM1MR0=1000;
						PWM1MR3=1000;
						PWM1LER=0x09;
						displayPID();					
					}
					break;
				}
				case 3:
				{	//U0THR = 0x93;
					U0THR = MyID|0x03;
					In_Send=0;U0IER |=0x02;
					break;
				}	
				case 5:
				{	s_out(0);					
					break;
				}
				case 6:
				{
					CRC=0;
				 	for(nn=0;nn<18;nn++) CRC ^= UR0_R_Buff[nn];

					if(CRC!=UR0_R_Buff[18])
					{
						//U0THR = 0x90;
						U0THR = MyID;
						In_Send=0;U0IER |=0x02;
					}
					else
					{
						//U0THR = 0x96;
						U0THR = MyID|0x06;
						In_Send=0;U0IER |=0x02;
						Bell();
						
						nn=0;
						memset(sbuff,0,sizeof(sbuff)); 
						memcpy(sbuff,&UR0_R_Buff[nn],4); nn+=4;						
						PidParaS.pid.pgain=atoi(sbuff);
						memset(sbuff,0,sizeof(sbuff)); 
						memcpy(sbuff,&UR0_R_Buff[nn],4); nn+=4;					
						PidParaS.pid.igain=atoi(sbuff);
						memset(sbuff,0,sizeof(sbuff)); 
						memcpy(sbuff,&UR0_R_Buff[nn],4); nn+=4;		    
						PidParaS.pid.dgain=atoi(sbuff);
						MTemp=UR0_R_Buff[nn++]&0x0f;
						//MTemp=0;++nn;
						memset(sbuff,0,sizeof(sbuff)); 
						memcpy(sbuff,&UR0_R_Buff[nn],5); nn+=5; 
						Xtemp=atof(sbuff);

						
						if(MTemp==5)
							MTemp=1;
						else if(MTemp==6)
							MTemp=2;
						else if(MTemp==7)
							MTemp=3;
						else if(MTemp==8)
							MTemp=4;
						else if(MTemp==0)
						{	MTemp=0;							
						}
						else
							MTemp=0;
						
						STAB=4;
						displayPID();	

						
						if(In_Test==0)
							RunPID(0);						
						else
							RunPID(1);
					}
				}
				default:
				{
					//U0THR = 0x90;
					U0THR = MyID;
					In_Send=0;U0IER |=0x02;
				}
			}
		}		
	}
}

/*===========================================*/
void displayPID(void)
{	
	{
		VTAB=0x12;HTAB=0x0c;	
		if(STAB==0)  verString( "恒");
		else			putString( "恒");
		HTAB=0x0e;
		switch (MTemp)
		{
			case 0:
			{	putString("转矩    ");break;	}
			case 1:
			{	putString("电流    ");break;	}
			case 2:
			{	putString("速度    ");break;	}
			case 3:
			{	putString("输入功率");break;	}
			case 4:
			{	putString("输出功率");break;	}
			
		}
	}

	switch (MTemp)
	{	case 0:
		{
			VTAB=0x36;HTAB=0x17;
			putString("Nm ");
			VTAB=0x5a;HTAB=0x17;
			putString("Nm ");
			break;
		}		
		case 1:
		{
			VTAB=0x36;HTAB=0x17;putString("A  ");
			VTAB=0x5a;HTAB=0x17;putString("A  ");
			break;
		}
		case 2:
		{
			VTAB=0x36;HTAB=0x17;putString("RPM");
			VTAB=0x5a;HTAB=0x17;putString("RPM");
			break;
		}
		case 3: case 4:
		{
			VTAB=0x36;HTAB=0x17;putString("W  ");
			VTAB=0x5a;HTAB=0x17;putString("W  ");
			break;
		}
	}
	
	HTAB=0x05;VTAB=0x12;
	sprintf(sbuff,"%03d",PidParaS.pid.pgain);
	putString(sbuff);
	if(STAB==1)
	{
		HTAB=0x05+BTAB;verEng(sbuff[BTAB]);
	}
	
	HTAB=0x05;VTAB=0x24;
	sprintf(sbuff,"%03d",PidParaS.pid.igain);
	putString(sbuff);
	if(STAB==2)
	{
		HTAB=0x05+BTAB;verEng(sbuff[BTAB]);
	}
	
	HTAB=0x05;VTAB=0x36;
	sprintf(sbuff,"%03d",PidParaS.pid.dgain);
	putString(sbuff);		
	if(STAB==3)
	{
		HTAB=0x05+BTAB;verEng(sbuff[BTAB]);
	}

	VTAB=0x36;HTAB=0x11;
	if((MTemp==3)||(MTemp==2)||(MTemp==4))
	{	sprintf(sbuff," %04.0f ",Xtemp);
		putString(sbuff);
		if(STAB==4)
		{
			HTAB=0x12+BTAB;verEng(sbuff[BTAB+1]);
		}
	}	
	else if(MTemp==1)
	{	sprintf(sbuff,"%05.2f ",Xtemp);
		putString(sbuff);
		if(STAB==4)
		{	if (BTAB<2)
				{HTAB=0x11+BTAB;verEng(sbuff[BTAB]);}
			else
				{HTAB=0x12+BTAB;verEng(sbuff[BTAB+1]);}
		}
	}		
	else
	{	sprintf(sbuff,"%05.2f ",Xtemp);
		putString(sbuff);
		if(STAB==4)
		{	if (BTAB<2)
				{HTAB=0x11+BTAB;verEng(sbuff[BTAB]);}
			else
				{HTAB=0x12+BTAB;verEng(sbuff[BTAB+1]);}
		}		
	}	

	if(In_Test==0)
	{
		VTAB=0x70;
		HTAB=0x00;putString("F1");
		HTAB=0x10;putString("F3");
		HTAB=0x18;putString("F4");
		
		{
			HTAB=0x02;verString("移动");
			HTAB=0x12;verString("返回");
			HTAB=0x1a;verString("确认");
			HTAB=0x0a;
			if(STAB==0)
				 verString("选择");
			else verString("运行");
		}	
	}
	else
	{
		VTAB=0x70;
		HTAB=0x18;putString("      ");
		HTAB=0x0a;
		verString("暂停");
	}	
}
/*===========================================*/
void displayPID2(void)
{
		VTAB=0x5a;HTAB=0x11;
		switch (MTemp)
		{
			case 0:
			{	sprintf(sbuff,"%5.2f",pFt);
				break;
			}	
			case 1:
			{					
				sprintf(sbuff,"%5.2f",Fc);
				break;
			}	
			case 2:
			{					
				sprintf(sbuff," %4.0f ",pFs);
				break;
			}	
			case 3:
			{		
				sprintf(sbuff," %4.0f ",Fp);
				break;
			}	
			case 4:
			{		
				sprintf(sbuff," %4.0f ",Po);
				break;
			}	
		}
		putString(sbuff);
}
/*===========================================*/
void RunPID(uint16 type)
{		
		pid0.SetPoint=Xtemp;
		pid_tune((float)PidParaS.pid.pgain,
					(float)PidParaS.pid.igain,
					(float)PidParaS.pid.dgain,(uint16)MTemp,type);
		
		In_Test=1;			
			   
			
		
		VTAB=0x70;				
		//HTAB=0x00;putString("      ");
		HTAB=0x10;putString("      ");
		//HTAB=0x18;putString("      ");
		HTAB=0x0a;
		verString("暂停");
}
/*===================================*/
void checkPID(void)
{
	PidParaS.pid.pgain=(PidParaS.pid.pgain>255)?255:PidParaS.pid.pgain;
	//PidParaS.pid.pgain=(PidParaS.pid.pgain<0)?0:PidParaS.pid.pgain;
	PidParaS.pid.igain=(PidParaS.pid.igain>255)?255:PidParaS.pid.igain;
	//PidParaS.pid.igain=(PidParaS.pid.igain<0)?0:PidParaS.pid.igain;
	PidParaS.pid.dgain=(PidParaS.pid.dgain>255)?255:PidParaS.pid.dgain;
	//PidParaS.pid.dgain=(PidParaS.pid.dgain<0)?0:PidParaS.pid.dgain;
	
}

/*===========================================*/
void SetDynamo(void)
{/*
	showDynamo();STAB=1;BTAB=0;	
	displayDynamo();		
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	while(1)
	{
		Read_Key(); 
		switch (KeyValue)
		{	case F2:
			{
				Bell();
				M_point=(M_point==0)?1:0;
				displayDynamo();
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}		 	
			case F3:
			{
				Bell();				
				showSet0();STAB=0;
				while (KeyValue!=0xff)
					{ Read_Key(); }
				return;		
			}		 
			case F4:
			{	Bell();	
				IRcvStr(0xa4, 0x08,V32.b8,4);
				V32.b8[0] = (uint8)Gs|0x30;				
				V32.b8[1] = (uint8)M_point|0x30;
				ISendStr(0xa4,0x08,V32.b8,4);
				Delay(4);

				showSet0();STAB=0;	
				while (KeyValue!=0xff)
					{ Read_Key(); }
				return;		
			}			
		}
	}*/
}
/*===========================================*/
void displayDynamo(void)
{	
	/*
		
	HTAB=0x0a;VTAB=0x30;
	switch(M_point)
	{	case 0:
		{	putString("带模块");putString("  ");
			break;		}
		default:
		{	putString("不带模块");
			break;		}	
	}	*/
}


/**********************************************/
void SetPower(void)
{
	Bell();
	showPower();BTAB=0;
	HTAB=0x0d;VTAB=0x40;
	sprintf(sbuff,"%5.1f",Fv);
	putBuff(sbuff);
	HTAB=0x14;VTAB=0x20;	
	verString("停止");	 
	while (KeyValue!=0xff)
		{ Read_Key(); }
	RunMotor(0,0);

	while(1)
	{
		Read_Key();
		if(KeyValue==F2) 
		{	Bell();
			BTAB=(BTAB>=3)?0:BTAB+1;
			if(BTAB==3) 
			{	RunMotor(0,2);RunMode=2;
				HTAB=0x14;VTAB=0x20;	
				verString("反转");putEng(' ');
				Delay(50);
				RunMotor(1,RunMode);
			}
			else if(BTAB==1) 
			{	RunMotor(0,1);RunMode=1;
				HTAB=0x14;VTAB=0x20;	
				verString("正转");putEng(' ');
				Delay(50);
				RunMotor(1,RunMode);
			}
			else
			{	RunMotor(0,RunMode);RunMode=0;
				HTAB=0x14;VTAB=0x20;	
				verString("停止");putEng(' ');
				Delay(50);
				RunMotor(0,RunMode);				
			}
			
			while (KeyValue!=0xff)
				{ Read_Key(); }
		}
		else if(KeyValue==F3) 
		{
			Bell();
			RunMotor(0,0);
			showSet0();STAB=0;
			while (KeyValue!=0xff)
				{ Read_Key(); }
			return;
	 	}
		
		if(FlagMs2)
		{	Read_ResultM();		}
		
		
		if(FlagMs100)
		{	FlagMs100=0;
			if(--Second1==0)
				Second1=10;	
			Read_ResultV();
		}

		if(FlagDisp)
		{
			FlagDisp=0;
			DataAccess(0);		
			if(--Second05==0)
			{	
				Second05=5;				
				VTAB=0x40;HTAB=0x0d;
				sprintf(sbuff,"%6.2f",Fv);
				putBuff(sbuff);	
			}
		}			 
	}
}

/*===========================================*/
unsigned char PassWord2(void)
{
	uint16	ii;
	
	Bell();
	showPassWord();STAB=0;BTAB=0;
	
	sbuff[0]=0x20;sbuff[1]=0x20;sbuff[2]=0x20;
	sbuff[3]=0x20;sbuff[4]=0x20;sbuff[5]=0x20;
	while (KeyValue!=0xff)
			{ Read_Key(); }
	
	while(STAB==0)
	{
		Read_Key(); 
		if(KeyValue==F3) 
		{
			Bell();				
			return 0xff; 	
		}
		else if(KeyValue==F4) 
		{
			Bell();
			if((sbuff[0]==1)&&(sbuff[1]==3)&&(sbuff[2]==1)
					&&(sbuff[3]==0))
				STAB=1;
			while (KeyValue!=0xff)
					{ Read_Key(); } 	
		}
		else if(KeyValue==GO_L)
		{
			Bell();
			sbuff[BTAB]=0x20;
			if(BTAB==0) BTAB=0;
			else --BTAB;			
			HTAB=0x0d;VTAB=0x30;
			for(ii=0;ii<4;++ii)
					putEng('*');
			HTAB=0x0d+BTAB;verEng('*');
			while (KeyValue!=0xff)
					{ Read_Key(); } 			
		}
		if(KeyValue<=9)
		{
			Bell();
			sbuff[BTAB]=KeyValue;
			if (BTAB==3) BTAB=3;
			else ++BTAB;
			HTAB=0x0d;VTAB=0x30;
			for(ii=0;ii<4;++ii)
				 putEng('*');
			HTAB=0x0d+BTAB;verEng('*');
				
			while (KeyValue!=0xff)
					{ Read_Key(); } 
		}
		

		if(FlagMs2)
		{	Read_ResultM();
		}
		
		
		
		if(FlagMs100)
		{	FlagMs100=0;
			Read_ResultV();
		}
		
		if(FlagDisp)
		{	DataAccess(0);
		}
	}
	
	return 0;
}



/****************************************/
void CalibDynamo(void)    //测功机标定
{	
	STAB=0;BTAB=0;In_Calib=0;
	RunMotor(0,0);
	showDynaCalib();	
	sprintf(sbuff,"%3d",BTAB);
	VTAB=0x40;HTAB=0x10;
	putBuff(sbuff);			
	sprintf(sbuff,"%6.2f",pFt2);
	HTAB=0x0d;VTAB=0x24;
	putBuff(sbuff);
	Second05 = 5;	
	
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	while(1)
	{
		Read_Key(); 
		switch (KeyValue)
		{	
			case F2:         //运行			
			{
				Bell();
				if(In_Calib)
				{
					In_Calib=0;
					{	
						PWM1MR0=1000;
						PWM1MR3=1000;
						PWM1LER=0x09;
					}
					VTAB=0x70;HTAB=0x0a;
					verString("继续");
					HTAB=0x10;putString("F3");
					verString("返回");
				}
				else
				{
					In_Calib=1;
					{	
						PWM1MR0=1000;
						PWM1MR3=1000-BTAB;
						PWM1LER=0x09;
					}
					
					VTAB=0x70;HTAB=0x0a;
					verString("暂停");
					HTAB=0x10;putString("        ");					
				}
				while (KeyValue!=0xff)
					{ Read_Key(); }	
				break;
			}		 	
			case F3:			
			{
				if(!In_Calib)
				{
					Bell();
					showSet0();STAB=0;	
					Second05=5;
					while (KeyValue!=0xff)
						{ Read_Key(); }
					return;
				}	
				break;
			}		 	
		 	case GO_L:
			{
				Bell();
				BTAB=(BTAB<=50)?0:BTAB-50;
				sprintf(sbuff,"%3d",BTAB/10);
				VTAB=0x40;HTAB=0x10;
				putBuff(sbuff);			
				if(In_Calib) 
				{	
					PWM1MR0=1000;
					PWM1MR3=1000-BTAB;
					PWM1LER=0x09;
				}				
				while (KeyValue!=0xff)
					{ Read_Key();}
				break;
			}
			case GO_R:
			{
				Bell();
				BTAB=(BTAB>=950)?1000:BTAB+50;
				sprintf(sbuff,"%3d",BTAB/10);
				VTAB=0x40;HTAB=0x10;
				putBuff(sbuff);			
				if(In_Calib) 
				{	
					PWM1MR0=1000;
					PWM1MR3=1000-BTAB;
					PWM1LER=0x09;
				}				
				while (KeyValue!=0xff)
					{ Read_Key();}
				break;
			}			
		}
		
	
		if(FlagMs2)
		{	Read_ResultM();		}
		
		
		if(FlagMs100)
		{	FlagMs100=0;
			if(--Second1==0)
				Second1=10;					
			Read_ResultV();
		}
		
		if(FlagDisp)	
		{
			FlagDisp=0;
			DataAccess(1);
			if(--Second05==0)
			{	Second05=5;
				sprintf(sbuff,"%6.2f",pFt2);
				HTAB=0x0d;VTAB=0x24;
				putBuff(sbuff);
			}
		}		
	}
}

/*********************************************************************
函数功能：获取240字节测试工艺编程参数
参数：0 表示获取10阶段工艺参数 1 表示获取20阶段测试工艺参数
************************************************************************/
void ParaAccess(uint16 a)//获取240字节测试工艺编程参数
{	uint16 nn,ii;
	char TRBuff[20];
  if(a==0)                    //出厂工艺
	{
	nn=0;
	for(ii=0;ii<8;ii++)
			No[ii]=s_buff[nn++];	//程序名称
	No[8]=0x00;
	
		Gs=(uint16)(s_buff[nn++]&0x0f);
		Gs=2;
		M_point=(uint16)(s_buff[nn++]&0x0f);	//测功机
		M_point =2;                  //M_point代表的是测功机的量程
	

	                                 //PID参数
	memset(TRBuff,0,sizeof(TRBuff)); 
	memcpy(TRBuff,&s_buff[nn],4); nn+=4; 					
	PidPara.pid.pgain=atoi(TRBuff);
	memset(TRBuff,0,sizeof(TRBuff)); 
	memcpy(TRBuff,&s_buff[nn],4); nn+=4; 				
	PidPara.pid.igain=atoi(TRBuff);
	memset(TRBuff,0,sizeof(TRBuff)); 
	memcpy(TRBuff,&s_buff[nn],4); nn+=4; 		
	PidPara.pid.dgain=atoi(TRBuff);
	
	for(ii=0;ii<10;ii++)                  //10个阶段
	{
		//nn=22+ii*18;
		Step[ii].runmode=s_buff[nn++]&0x0f;//运行状态
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],5); nn+=5; 
		Vtemp=atof(TRBuff);
		Step[ii].volt=Vtemp*10;             //电压
		Step[ii].loadtype=s_buff[nn++]&0x7f;//加载设置
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],5); nn+=5; 
		Step[ii].loadvalue=atof(TRBuff);//加载给定值
		Step[ii].endmode=s_buff[nn++]&0x0f;//阶段结束设置
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],5); nn+=5; 
		Step[ii].endvalue=atof(TRBuff);	//结束条件值				
	}//nn=202
	
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],5);nn+=5;   
		TestVolt1 = atof(TRBuff);
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],5);nn+=5;   
		StartVolt1 = atof(TRBuff);
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],3);nn+=3;   
		StartTime = atof(TRBuff);
		
	    AlarmMode=s_buff[nn++]&0x0f;
	    memset(TRBuff,0,sizeof(TRBuff)); 
	    memcpy(TRBuff,&s_buff[nn],5); nn+=5; 
	    AlarmValue=atof(TRBuff);
	/*****************************************************/

	
	//Step[10].endvalue=0;	//跳过后两个阶段
	Step[9].endvalue= 0;
	
	/*for(ii=8;ii>=5;ii--)                        //后4个阶段向后移动了一位
		{	Step[ii].volt=Step[ii-1].volt;
			Step[ii].runmode=Step[ii-1].runmode;
			Step[ii].loadtype=Step[ii-1].loadtype;
			Step[ii].loadvalue=Step[ii-1].loadvalue;
			Step[ii].endmode=Step[ii-1].endmode;
			Step[ii].endvalue=Step[ii-1].endvalue;
		}*/

	if(Step[0].endvalue==0)      //阶段1必须设置，否则后续阶段无效
		Step[1].endvalue=Step[2].endvalue=Step[3].endvalue=Step[4].endvalue=0.0;
	else
		{Step[0].endvalue=Step[0].endvalue<StartTime?StartTime+2:Step[0].endvalue;}//不足启动时间强行设定
	if(Step[5].endvalue)         //第6个阶段设定了
	{	
	     Step[5].endvalue=Step[5].endvalue<StartTime?StartTime+2:Step[5].endvalue;     //不足10s强行设定10s
	      //if(Step[0].endvalue)
			//Step[4].endvalue=2;    
	}
	else
		Step[4].endvalue=Step[6].endvalue=Step[7].endvalue=Step[8].endvalue=0.0;
	EndMode=1;
	EndTime=1;
	
	LastStep1=9;
		for(ii=9;;ii--)           //从后往前判断有多少阶段
		{	LastStep1=ii;
			if((Step[ii].endvalue!=0))
				break;
		}
   }	
 else                            //这是我添加的20阶段特性工艺
	{	nn=0;
		
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],3); nn+=3; 					
		PidPara2.pid.pgain=atoi(TRBuff);        //    4    0-3
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],3); nn+=3;    //    8		 4-7		
		PidPara2.pid.igain=atoi(TRBuff);
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],3); nn+=3;    //		12   8-11
		PidPara2.pid.dgain=atoi(TRBuff);        //atoi()函数是将字符串转换成整型数的函数
		LoadType2=(s_buff[nn]==0x35)?5          //加载方式      5 是负载率 2是转矩 
			:(s_buff[nn]==0x32)?2:0;
		nn=nn+1;
		
		voltdir=(s_buff[nn]==0x30)?1          //正反转
		      :(s_buff[nn]==0x31)?2:3;
		 nn+=1;
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],3);nn+=3;  
		TestVolt2=atof(TRBuff);;
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],3);nn+=3;   
		StartVolt2 = atof(TRBuff);
		memset(TRBuff,0,sizeof(TRBuff)); 
		memcpy(TRBuff,&s_buff[nn],2);nn+=2;   
		StartTime = atoi(TRBuff);                                 

		//nn=19+ii*11;			 
		for(ii=0;ii<20;ii++)
		{		
			Step2[ii].RunMode=s_buff[nn++]&0x0f;   //运行状态
			memset(TRBuff,0,sizeof(TRBuff)); 
			memcpy(TRBuff,&s_buff[nn],5); nn+=5; 		
			Step2[ii].LoadValue=atof(TRBuff);      //加载值
			Step2[ii].LoadMode=s_buff[nn++]&0x0f;  //加载模式
			memset(TRBuff,0,sizeof(TRBuff)); 
			memcpy(TRBuff,&s_buff[nn],4); nn+=4; 
			Step2[ii].EndValue=atof(TRBuff);	   //结束条件值				
		}//nn=239
		
		LastStep2=20;
		for(ii=0;ii<=20;ii++)
		{	LastStep2=ii;
			if((Step2[ii].EndValue==0)||(Step2[ii].RunMode==0))
				break;
		}
	}

}

	
	


