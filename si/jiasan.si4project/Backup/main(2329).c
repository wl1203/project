


#include "MAIN.h"

const float Modi[13]={
	0.80,
	0.90,
	0.95,
	1.00,
	1.05,
	1.08,
	1.11,
	1.14,
	1.17,
	1.20,
	1.23,
	1.26,
	1.28};
const float Disti[13]={
	0.00,
	0.10,
	0.20,
	0.30,
	0.40,
	0.50,
	0.60,
	0.70,
	0.80,
	0.90,
	1.00,
	1.10,
	1.20};
const U32 Wresult[6]={
	0xfeffffff,0xfefefe1e,
	0xfefefe16,0xfefefe18,
	0xfefefe0e,0xffffff5e};
	
U32 		Wbuf5460V,Rbuf5460V,Wbuf5460M,Rbuf5460M,Voltb;
volatile uint16	Spi0Step,Spi0Byte,FlagDisp;
volatile uint16	Spi1Step,Spi1Byte;
U32		RresultV[6],RresultM[6];




U32		para[8],V32;

float Mx[200],M2Temp, MxTemp,PxTemp,Px[20],Mx2[200];
volatile uint16 pT,pJ;


float  Vx[202],VxTemp,ixTemp,ix[20],IxTemp,Ix[202];
volatile uint16 pV,pI;

uint16 Sx[12],pS,ZfZ[12],Zf=0;
uint32 SxTemp;

float KV,KI,KM,KM2;

float	Fv,Fc,Fp,Ft,Vtemp,pFt,pFs,pFt2;
volatile float dFs=0;

float sFv,sFc,sFp,sFt,sFs;


volatile int32  Fd=0,Fmax=0,LastFd=0,PidMax=0;
int32 pFd,pFmax;
volatile uint16 SpeedCount=0;





	

//uint8  Buff0[64];
uint16 HTAB,VTAB,STAB,BTAB;

uint8 	MyID;
uint8	No[9];
uint16	Gs,M_point;
U_PID 	PidPara,	PidParaS,PidPara1,PidPara2;
STEP 	Step[16];
STEP2  Step2[22];
uint16 LoadType2=0,LastStep2=0,voltdir=0,voltdir1=0;
uint16  TestVolt2,LoadVolt2,StartVolt2,StartTime,volt,VoltGain=0;
float TestVolt1,StartVolt1,LoadVolt1,TestVolt3,StartVolt3;
IN_ROT 	in_rot;
uint8	EndMode,AlarmMode;
float 	EndTime,AlarmValue;
uint32	ulEndTime=0;

float Xtemp;
uint32 MTemp;
volatile uint16  In_Test,Running,EnableF=0;

U32 Export;
volatile uint16	DelayCount,BellCount;
volatile uint32	KeyCount,KeyIn,LastKeyIn,KeyValue,B_In,LastBT,Button,FlagBT;
volatile uint32	PosiCount,PosiIn,LastPosiIn,Position;

volatile uint16 FlagMs2=0,FlagMs100=0,mS100=0,mS005=0,FlagS1,S1;

char   UR0_R_Buff[256],UR0_T_Buff[256];
uint16 Uart0_R_Count,Uart0_R_Len;
uint16 In_Receive,Uart0_OK,Uart0_Command;
volatile uint16 Uart0_T_Count,Uart0_T_Len,In_Send,Tran_f;
 volatile uint16 Uart1_R_Count,Uart1_R_Len;




uint8   s_buff[240];
char	  sbuff[32];
uint16 Second05;

uint8 CRC=0;



PID pid0;



uint16 End_Test;
volatile uint32 nowClock=0,cClock;
volatile uint32 Total=0,TotalRev=0;
volatile uint16 FlagRev=0;

uint16	Cycle,CycleCount;
uint16	Counter; 
uint16 Alarm,KL_Counter,ZL_Counter,LastStep,SL_Counter;
uint16	shi,fen,miao,Second1;
uint32 sCounter;
unsigned char sNowState;
uint32 Hot_In=0,Hot_Count=0,Hot_Alarm=0;

char	UR1_R[75],UR1_RBuff[75];
volatile uint16 VoltCount=0,ReadBSQ_Flag=0;


uint16 Finish1=0,Finish2=0,Finish=0;
volatile uint16 FlagInverse=0,FlagJici=0;
volatile uint16 Uart1_OK,Uart1_Command;
volatile uint32 CtrlByte=0;
volatile uint16 In_pause=0;

volatile uint16 In_Reading=0,FlagPid=0;

float PerFor[7],Cons[10];
uint32 RBH[4];
float SetS,dS;
float Po,eff;

 
float xFt=0,xFs=0;
 

union{signed short i;unsigned char c[2];}InTorque;

uint16 RunMode=0,StartCount=0;

volatile uint16 O_flag=0,O_Count=0;

/**********************************************************************************************************/
int main (void)
{	uint16 n;

	targetInit();                                                       /* ��ʼ��Ŀ��壬����ɾ��       */	
	pinInit();                                                          /* ���ų�ʼ��                   */    
	CtrlByte=0;
	timer0Init();                                                       /* ��ʱ��0��ʼ��                */
	uartInit();
	PWM_Init(0);
	I2C_Init();
	Delay(20);
	SpiInit();
	Delay(20);
	init_Lcd();
	showPG000();
	
	
	Bell();
	
	for (pT=0;pT<200;pT++)
		Mx2[pT]=Mx[pT]=0.0;	
	M2Temp=MxTemp=0.0;pT=0;
	for (pJ=0;pJ<20;pJ++)
		Px[pJ]=0.0;
	PxTemp=0;pJ=0;	
	
	for(pS=0;pS<10;pS++)
		ZfZ[pS]=Sx[pS]=0;
	pS=0;SxTemp=0;

	
	
	KeyCount=0;
	KeyValue=0xff;

	IRcvStr(0xa0,0x00,V32.b8,2);
	MyID = V32.b8[0];
	MyID=(MyID<0x90)?0x90
			:(MyID>0xc0)?0xc0:MyID&0xf0;
	MyID = 0x90;
	

	Delay(10);	

	ReLoad2(0);
	ParaAccess(0);

	
	
	
	Init_QEI();

	Delay(20);
	
	IRcvStr(0xa0,0x10,para[0].b8,16);	
	Delay(2);
	IRcvStr(0xa0,0x20,para[4].b8,16);	
	Delay(2);

	IRcvStr(0xa0,0x30,V32.b8,4);Delay(2);	
	KI = 1/(float)V32.a32;  	
	if(KI<=1E-7) KI=1E-7;if(KI>=0.01) KI=0.01;	
	Delay(4);
	
	IRcvStr(0xa0,0x34,V32.b8,4);Delay(2);	
	KV= 1/(float)V32.a32;  	
	if(KV<=1E-7) KV=1E-7;	if(KV>=0.01) KV=0.01;	
	Delay(4);
	
	IRcvStr(0xa0,0x38,V32.b8,4);Delay(2);	
	KM2= 1/(float)V32.a32;   	 	
	if(KM2<=1E-7) KM2=1E-7;	if(KM2>=0.1) KM2=0.1;
	Delay(4);
	
	IRcvStr(0xa0,0x3c,V32.b8,4);Delay(2);	
	KM= 1/(float)V32.a32;    	
	if(KM<=1E-7) KM=1E-7;	if(KM>=0.01) KM=0.01;
	Delay(4);

	



	Delay(20);
	init_5460V();
	init_5460M(1);
	
	

	Delay(20);
	
	In_pause=0;
 	
	Delay(200);
	showPG00();
	DispPG00();
	Second05=5;
	Second1=10;
	CtrlByte=0;
	RunMotor(0,0);
	RunMode=0;
	

    while (1) 
	{	
	    Read_Posi();
		Read_Key();
		switch(KeyValue)            //������������
		{
			
			case F1:
			{	RunFirst();break;	}
			case F2:
			{	SetFirst();break;	 	}	
			case F4:
			{	calibrate();break;	}
		}
		
		
	
		if(FlagMs2)
		{	Read_ResultM();
    
		}
		if(Uart1_OK)
		{Uart1_OK=0;
			DataAccess(0);
		}
		
		if(FlagMs100)
		{	FlagMs100=0;
			if(--Second1==0)
			{	Second1=10;			
			}
			   Read_ResultV();	
			 
		}

		if(FlagDisp)
		{	FlagDisp=0;

			DataAccess(0);
		
			if(--Second05==0)
			{	Second05=5;		
				DispPG00();
			}
			
		}
		if(Uart0_OK)
		{
			Uart0_OK=0;
			switch (Uart0_Command)
			{	
				case 3:
				{
					DownLoadProg(0);         //��ӦEEPRM��0xa4��ַ
					RunTest1(2);
					break;					
				}	
				case 4:
				{
					UpLoadProg(0);          //�����ϴ����ղ���
					break;
				}
				case 5:
				{	
					s_out(0);
					break;
				}				
				case 7:
				{	n=DownLoadProg2();
					if(n==8)
						ConstantTest2(1);	
					else if(n==9)
						Manual(1);
					break;
				}
				case 8:                  //0x98     ��������
        {
					DownLoadProg(1);
				    Performance2(1);
				  break;
				}	
				case 15:
				{
				  UpLoadProg(1);				
				  break;
				}					
				default:
				{
					U0THR = MyID;
					In_Send=0;U0IER |=0x02;
				}
			}
		}
		
    }
}

/*******************************************************/
void DataAccess(uint16 a)
{		
        uint16 ii;
		U32 RTemp;
		//float cFreq;
        CRC=0;
		for(ii=0;ii<15;ii++)   //15�ֽ�
			CRC+= UR1_RBuff[ii];//У��
			if(CRC==UR1_RBuff[15])
			{
				RTemp.b8[0]=UR1_RBuff[3];RTemp.b8[1]=UR1_RBuff[4];  //����ʱ��4��16����ת����һ��������
				RTemp.b8[2]=UR1_RBuff[5];RTemp.b8[3]=UR1_RBuff[6];
				Fv=RTemp.f32;Fv=(Fv<5.0)?0:Fv;//��ѹ
				RTemp.b8[0]=UR1_RBuff[7];RTemp.b8[1]=UR1_RBuff[8];
				RTemp.b8[2]=UR1_RBuff[9];RTemp.b8[3]=UR1_RBuff[10];
				Fc=RTemp.f32;                 //����
				RTemp.b8[0]=UR1_RBuff[11];RTemp.b8[1]=UR1_RBuff[12];
				RTemp.b8[2]=UR1_RBuff[13];RTemp.b8[3]=UR1_RBuff[14];
				Fp=RTemp.f32;	
				Fp=(Fp<0)?-Fp:Fp;	          //���빦��	
			}
		    else
			Fv=Fc=Fp=0.0;
		
		

		pFt= MxTemp/5;                        //��������5V��ѹ	200*5=1000    pFt =1000/5=200
		//pFt=(pFt<0)?-pFt:pFt;
		if(pFt<Modi[12])
		{
			   pFt=(pFt<Modi[0])?Disti[0]		
				:(pFt<Modi[1])?Disti[1]
				:(pFt<Modi[2])?Disti[2]
				:(pFt<Modi[3])?Disti[3]
				:(pFt<Modi[4])?Disti[4]
				:(pFt<Modi[5])?Disti[5]
				:(pFt<Modi[6])?Disti[6]
				:(pFt<Modi[7])?Disti[7]
				:(pFt<Modi[8])?Disti[8]
				:(pFt<Modi[9])?Disti[9]
				:(pFt<Modi[10])?Disti[10]
				:(pFt<Modi[11])?Disti[11]
				:Disti[12];
		}		
		pFt =  pFt*0.05;		//      200*0.05=10Nm      ����

		pFt2 = M2Temp/5;
		if(pFt2<Modi[12])
		{
			   pFt2=(pFt2<Modi[0])?Disti[0]		
				:(pFt2<Modi[1])?Disti[1]
				:(pFt2<Modi[2])?Disti[2]
				:(pFt2<Modi[3])?Disti[3]
				:(pFt2<Modi[4])?Disti[4]
				:(pFt2<Modi[5])?Disti[5]
				:(pFt2<Modi[6])?Disti[6]
				:(pFt2<Modi[7])?Disti[7]
				:(pFt2<Modi[8])?Disti[8]
				:(pFt2<Modi[9])?Disti[9]
				:(pFt2<Modi[10])?Disti[10]
				:(pFt2<Modi[11])?Disti[11]
				:Disti[12];
		}	
		pFt2 =pFt2*0.05;
		
		 
		Po=pFs*pFt/9.55;
		
		if(Fp)
			eff=Po*100/Fp;
		else eff=0;

		eff=(eff>200)?200:eff;

}



/************************************************************/
void DispPG00(void)
{	
	VTAB=0x12;
	sprintf(sbuff,"%5.2f",Fv);
	HTAB=0x0e;putBuff(sbuff);
	
	
	VTAB=0x24;
	sprintf(sbuff,"%6.2f",Fc);
	HTAB=0x0d;putBuff(sbuff);

	VTAB=0x36;
	sprintf(sbuff,"%6.1f",Fp);
	HTAB=0x0d;
	putBuff(sbuff);	
	VTAB=0x48;
	sprintf(sbuff,"%6.1f",pFs);
	HTAB=0x0d;
	putBuff(sbuff);
	VTAB=0x5a;
	sprintf(sbuff,"%6.2f",pFt2);//��Чֵת��
	HTAB=0x0d;
	putBuff(sbuff);	
	
	
				
}



/************************************************************/
void DispPG01(void)
{	
	VTAB=0x12;
	sprintf(sbuff,"%5.2f",Fv);
	HTAB=0x0e;putBuff(sbuff);
	
	
	VTAB=0x24;
	sprintf(sbuff,"%6.2f",Fc);
	HTAB=0x0d;putBuff(sbuff);

	VTAB=0x36;
	sprintf(sbuff,"%6.1f",Fp);
	HTAB=0x0d;
	putBuff(sbuff);	
	
				
}

	
/****************************************
������onoffΪ0ʱ Motor_SW = 0x52 ֹͣ
      onoffΪ1 type=1ʱ Motor_SW = 0x50 ��ת
      onoffΪ1 type=2ʱ Motor_SW = 0x51 ��ת
******************************************/
void RunMotor(uint16 onoff,uint16 type)
{	char b8[6];
	uint32 Motor_SW;               //����
	if(onoff)
	{	Motor_SW=0x50;             //����
		Running=1;                 //�趨���Ա�־ 
	  if(type==2)
		Motor_SW |= 0x01;	
	}
	else{
		Motor_SW = 0x52;               //Ĭ��ֹͣ
		Running=0;
	    volt=0;
	    }
	
	
	volt=(volt>50)?50:volt;
	
	sprintf(b8,"%04d",(uint16)(volt*100)); 
	
	U3THR=0xEB;
	U3THR=0x90;
	U3THR=  Motor_SW;
	U3THR=  (uint8)(b8[0]&0x0f);
	U3THR=  (uint8)(b8[1]&0x0f);
	U3THR=  (uint8)(b8[2]&0x0f);
	U3THR=  (uint8)(b8[3]&0x0f);
	
}


/*********************************************************************************************************/
void Timer0Isr (void)
{
    T0IR         = 0x01;					                            /* ����жϱ�־	                */  
	

	FlagMs2=1;	


	if(DelayCount)
		--DelayCount;
	
	if(KeyCount)
		--KeyCount;

	if(VoltCount)
		--VoltCount;
    if(PosiCount)
  	    --PosiCount;
	if(++mS100>=20)
	{	mS100=0;
		FlagMs100=1;
	} 
	/*if(++S1>=200)
	{	S1=0;
		FlagS1=1;
		}*/
}
/*********************************************************************************************************/
void Uart0Isr (void)
{	uint32  usta,u;
	uint8	Temp;
  
	usta = U0IIR&0x0F;
	
	if( usta == 0x04) 
	{	Temp = U0RBR;           // ��ȡFIFO�����ݣ�������жϱ�־
   		if((Temp&0xf0)== MyID)	//MyID=1
	   	{
		   	Uart0_Command=Temp&0x0f;
		   	Uart0_R_Count=0;
			In_Receive=0;			
			switch (Uart0_Command)
			{
				case 0: case 1: case 2:
				case 4: case 5: case 9:
				case 10: case 11:case 14: case 15:
		   	   	{
					Uart0_OK=1;
					break;
				    }			
				case 0x03: case 8:
		   		{ 
					Uart0_R_Count=0;
					Uart0_R_Len=240;
					In_Receive=1;
					break;
				}				
				case 0x06:
		   		{ 
					Uart0_R_Count=0;
					Uart0_R_Len=19;
					In_Receive=1;
					break;
				}
				case 7:
		   		{ 
					Uart0_R_Count=0;
					Uart0_R_Len=40;
					In_Receive=1;
					break;
				}				
				case 12:
		   		{ 
					Uart0_R_Count=0;
					Uart0_R_Len=31;
					In_Receive=1;
					break;
				}				
				case 13:
				{	U0THR = MyID|0x0d;
					U0THR = 0x32;
					U0THR = 0x32;
					U0THR = 0x00;				
					In_Send=0;U0IER |=0x02;
					break;
				}
			}
	   }
	   else if(In_Receive!=0)
	   {
	   	
	   		UR0_R_Buff[Uart0_R_Count++]=Temp;
	   		if (Uart0_R_Count >= Uart0_R_Len)
	   		{
	   			Uart0_R_Count=0;
	   			In_Receive=0;
				Uart0_OK=1;	   			
	   		}		
	    }		
	}
	else if(usta ==0x02)
	{ 
		if(In_Send != 0)           //���ͱ�־����s_out����������Ϊ1ͬʱUart0_T_Count=0
		{
			for(u=0;u<12;u++)
			{
				U0THR=UR0_T_Buff[Uart0_T_Count];
				if(++Uart0_T_Count>=Uart0_T_Len)
				{	In_Send=0;u=16;		}
			}
		}
		else
		{
			U0IER &= 0xfd;	//�ط����ж�
		}
	}  	
}
/**********************************************************/
void Uart1Isr(void)
{
	uint32  usta,u;
    uint8 Temp;
	usta = U1IIR&0x0F;
	if( usta == 0x04) //����
	{	
		  Temp =U1RBR;
   		UR1_RBuff[Uart1_R_Count] = Temp;  //��������ڲ�ͣ�Ľ�������                  
	
		switch(Uart1_R_Count) //���ݴ��ڽ������ݵĸ��� �жϽ������ݵ���ȷ��
		{
			case 0:
			{	if(Temp==0xaa)
					  Uart1_R_Count=1;
				else Uart1_R_Count=0;break;
			}
			case 1:
			{	if(Temp==0x00)
					 Uart1_R_Count=2;
			  else Uart1_R_Count=0;break;
			}
			case 2:
			{	if(Temp==0x10)
					 Uart1_R_Count=3;
				else Uart1_R_Count=0;
				break;		}
			
			default:
			{
				if(Uart1_R_Count==Uart1_R_Len)
					{	Uart1_R_Count=0;
						Uart1_OK=Uart1_R_Len;
				        FlagDisp=1;
						
					}	
					else
					{	Uart1_R_Count++;
						
					}
			}
		}
		
	}
	else
 	{ 
  		for(u=0; u<8; u++)
   		{ UR1_RBuff[u] = U1RBR;                        
   		}
  	}   
}





/*********************************************************/
char DownLoadProg(uint16 a)
{
	uint16 n,ii;
	
	CRC=0;
	for(ii=0;ii<239;ii++)
		CRC ^= UR0_R_Buff[ii];
	if(CRC!=UR0_R_Buff[239])  //У�����
	{
		//U0THR = 0x90;
		U0THR = MyID;
		In_Send=0;U0IER |=0x02;
		return 0xff;
	}
	else
	{				
		if(a==0)                              
		{	U0THR = MyID|0x03;                 //0x93 ��ʼҳ�����ع��ղ���
			In_Send=0;U0IER |=0x02;            //�������ж� �����ǿ����������ķ���ֵ
			for(ii=0;ii<239;ii++)
				s_buff[ii]=UR0_R_Buff[ii];       //UR0_R_Buff[ii]�е�����ʱ���ж��н��յ�
			ParaAccess(0);                     //�����Ѿ���ʼ�� s_buff�����л�ȡ������
			for(ii=0;ii<15;ii++)               //15*16=240
			{	n=ii*16;
				if(ISendStr(0xa4,n, (s_buff+n),16)!=1)
					goto Lerr1;
				Delay(2);
			}
		}
		else
		{	U0THR = MyID|0x08;                //MyID=0x98
			In_Send=0;U0IER |=0x02;
			for(ii=0;ii<239;ii++)
				s_buff[ii]=UR0_R_Buff[ii];
			  ParaAccess(1);                    //����Ϊ1 ��ʾ20�׶β��Թ��ձ�̲���
			for(ii=0;ii<15;ii++)
			{	n=ii*16;
				if(ISendStr(0xa6,n, (s_buff+n),16)!=1)
					goto Lerr1;
				Delay(2);
			}
		}	
		
			
		Bell();
		VTAB=0x00;HTAB=0x16;
		putString( "����ɹ�");	
		goto L002;
		Lerr1:
		Bell();
		VTAB=0x00;HTAB=0x16;
		putString( "�������");	
		L002:
		Delay(200);
		VTAB=0x00;HTAB=0x16;
		putString( "        ");
		return 0;
	}
}


/*******************************************
�������ܣ������ϴ����ղ���
��EEPROM�л�ȡ���������UART0���ͻ����У��ڴ����ж��з���
**********************************************/
void UpLoadProg(uint16 a)
{
	uint16 ii;
	
	ReLoad2(a);      //��EEPROM�л�ȡ����
	Bell();
	CRC=0;
	for(ii=0;ii<239;ii++) 
	{
		CRC ^= s_buff[ii];
		UR0_T_Buff[ii]=s_buff[ii];
	}
		UR0_T_Buff[239]=CRC;
		
		if(a==0)
			U0THR = MyID|0x04;//�����ϴ����ղ���
		else
			U0THR = MyID|0x0f;
	
		In_Send=1;U0IER |=0x02;
		Uart0_T_Count=0;
		Uart0_T_Len=240;
}


/****************************************************/
void ReLoad2(uint16 a)
{
	uint16 n;
	if(a==0)
	{	for(n=0;n<15;n++)
		{	IRcvStr(0xa4, n*16,(s_buff+n*16),16);		}  //16�ֽ�ҳд�빦��
	}
	else
	{	for(n=0;n<15;n++)
		{	IRcvStr(0xa6, n*16,(s_buff+n*16),16);		}
	}			
}

/*************************************************/
void RunFirst(void)
{
	Bell();
	showRun0();STAB=0;		
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	while(1)
	{
		Read_Key(); 
		if(KeyValue==F1) 
		{
			Bell();
			STAB=(STAB>=3)?0:STAB+1;				
			switch (STAB)
			{	case 0:
				{HTAB=0x07;VTAB=0x4a;putEng(0x34);
				 HTAB=0x07;VTAB=0x14;verEng(0x31);
				 break;}
				case 1:
				{HTAB=0x07;VTAB=0x14;putEng(0x31);
				 HTAB=0x07;VTAB=0x26;verEng(0x32);
				 break;}		
				case 2:
				{HTAB=0x07;VTAB=0x26;putEng(0x32);
				 HTAB=0x07;VTAB=0x38;verEng(0x33);
				 break;}	
         case 3:
				{HTAB=0x07;VTAB=0x38;putEng(0x33);
				 HTAB=0x07;VTAB=0x4a;verEng(0x34);
				 break;}						
				
			}						
			while (KeyValue!=0xff)
			{ Read_Key(); }			
		}		
		else if(KeyValue==F3) 
		{
			Bell();		
			showPG00();
			DispPG00();
			nowClock=0;

			while (KeyValue!=0xff)
			{ Read_Key(); }
			return;		
		}
		else if(KeyValue==F4) 
		{
			Bell();
			switch (STAB)
			{	case 0:
				{	RunTest1(0);break;}	     //��������
				case 1: 
				{	ConstantTest0();break;}	 //��ֵʵ��				
				case 2:				
				{	Manual(0);break;}        //�ֶ�����
				case 3:				
				{	Performance();break;}    //���Բ���
			}			
			End_Test=0;In_pause=0;
		}

		
	
		if(FlagMs2)
		{	Read_ResultM();		}
		
		if(FlagMs100)
		{	FlagMs100=0;
			if(--Second1==0)
			{	Second1=10;			
			}
			Read_ResultV();	
		}

		if(FlagDisp)
		{	FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;	
			}
			
		}
		
		if(Uart0_OK)
		{	Uart0_OK=0;
			switch (Uart0_Command)
			{	case 1:
				{	U0THR = MyID|0x01;
					In_Send=0;U0IER |=0x02;
					break;
				}	
				case 3:
				{	U0THR = MyID|0x03;
					In_Send=0;U0IER |=0x02;
					break;
				}	
				case 5:
				{	s_out(0);
					break;
				}
				default:
				{	U0THR = MyID|0x00;
					In_Send=0;U0IER |=0x02;
				}
			}
		}
	}		
}
 

/*======================================*/
void ConstantTest0(void)
{
	if(ConstantTest1()) return;
	ConstantTest2(0);
}
/*========================================================*/
char ConstantTest1(void)
{
	
	                                 //����Ҫ˼��һ��
	IRcvStr(0xa0, 0x80,V32.b8,4);
	Cons[0]=V32.f32;
	IRcvStr(0xa0, 0x84,V32.b8,4);
	Cons[1]=V32.f32;
	IRcvStr(0xa0, 0x88,V32.b8,4);
	Cons[2]=V32.f32;
	IRcvStr(0xa0, 0x8c,V32.b8,4);
	Cons[3]=V32.f32;
	IRcvStr(0xa0, 0x90,V32.b8,4);
	Cons[4]=V32.f32;
	IRcvStr(0xa0, 0x94,V32.b8,4);
	Cons[5]=V32.f32;
	IRcvStr(0xa0, 0x98,V32.b8,4);
	Cons[6]=V32.f32;
	IRcvStr(0xa0, 0x9c,V32.b8,4);
	Cons[7]=V32.f32;
	IRcvStr(0xa0, 0xa0,V32.b8,4);
	Cons[8]=V32.f32;
	IRcvStr(0xa0, 0xa4,V32.b8,4);
	Cons[9]=V32.f32;

	//Cons[0]=0;
	Cons[1]=(Cons[1]<0)?0:Cons[1];
	if(Cons[0]==0)
		Cons[1]=(Cons[1]>=15)?15:Cons[1];
	else if(Cons[0]==1)
		Cons[1]=(Cons[1]>=50)?50:Cons[1];
	else
		Cons[1]=(Cons[1]>=300)?300:Cons[1];
		
	Cons[3]=(Cons[3]>255)?255:Cons[3];
	Cons[4]=(Cons[4]>255)?255:Cons[4];
	Cons[2]=(Cons[2]>255)?255:Cons[2];	
	Cons[2]=(Cons[2]<0)?0:Cons[2];
	Cons[3]=(Cons[3]<0)?0:Cons[3];
	Cons[4]=(Cons[4]<0)?0:Cons[4];	
	Cons[5]=(Cons[5]<0)?0:Cons[5];	
	Cons[6]=(Cons[6]==0)?0:1;
	Cons[7]=(Cons[7]<0)?0:Cons[7];	
	Cons[8]=(Cons[8]<0)?0:Cons[8];	
	Cons[9]=(Cons[9]<0)?0:Cons[9];

	showConstant1(1);STAB=0;BTAB=0;
	showConstSet(1);
	
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	
	
	In_Test=0;End_Test=0;
	

	
	while (1)
	{
		
		Read_Key();
		switch(KeyValue)
		{
			case F1:
			{				
				Bell();
				switch(STAB)
				{	case 1:
					{	STAB=5;break;	}
					case 5:
					{	STAB=2;break;	}
					case 4:
					{	STAB=6;break;	}
					case 0: case 2: case 3:case 7:case 8:
					{	STAB+=1;break;	}	
					case 6:{STAB=7;break;}
					default:
						STAB=0;
				}
				BTAB=0;
				Cons[3]=(Cons[3]>255)?255:Cons[3];
				Cons[4]=(Cons[4]>255)?255:Cons[4];
				Cons[2]=(Cons[2]>255)?255:Cons[2];					
                if(STAB<7)
				{if(STAB==0)
				    showConstant1(1);
				 showConstSet(1);
				}
				else 
				{if(STAB==7)
				     showConstant1(2);
				   showConstSet(2);
					}
				while (KeyValue!=0xff)
					{ Read_Key(); }				
				break;
			}
			case F2:           //ѡ��
			{
				if(STAB==0)
				{
					Bell();	
					//Cons[0]=(Cons[0]==0)?1:0;
					Cons[0]=(Cons[0]==0)?1
						:(Cons[0]==1)?3
						:(Cons[0]==3)?4:0;
					Cons[1]=0;
					showConstSet(1);					
				}
				else if(STAB==6)
				{	
					Cons[6]=(Cons[6]==0)?1:0;
					showConstSet(1);	
				}
				while (KeyValue!=0xff)
						{ Read_Key(); }
				break;
			}		
			case F3:
			{					
				Bell();
				RunMotor(0,0);
				showRun0();STAB=0;
				while (KeyValue!=0xff)
				{ Read_Key(); }
				return 0xff;
			}
			case F4:    //����
			{	
				
				Bell();			
				if(Cons[0]==0)
					Cons[1]=(Cons[1]>=15)?15:Cons[1];
				else if(Cons[0]==1)
					Cons[1]=(Cons[1]>=50)?50:Cons[1];
				else
					Cons[1]=(Cons[1]>=300)?300:Cons[1];
				V32.f32=Cons[0];
				ISendStr(0xa0,0x80,V32.b8,4);Delay(2);
				V32.f32=Cons[1];
				ISendStr(0xa0,0x84,V32.b8,4);Delay(2);
				V32.f32=Cons[2];
				ISendStr(0xa0,0x88,V32.b8,4);Delay(2);
				V32.f32=Cons[3];
				ISendStr(0xa0,0x8c,V32.b8,4);Delay(2);
				V32.f32=Cons[4];
				ISendStr(0xa0,0x90,V32.b8,4);Delay(2);
				V32.f32=Cons[5];
				ISendStr(0xa0,0x94,V32.b8,4);Delay(2);
				V32.f32=Cons[6];
				ISendStr(0xa0,0x98,V32.b8,4);Delay(2);					
				V32.f32=Cons[7];
				ISendStr(0xa0,0x9c,V32.b8,4);Delay(2);     //��ַ��Ҫ�Ķ�
				V32.f32=Cons[8];
				ISendStr(0xa0,0xa0,V32.b8,4);Delay(2);
				V32.f32=Cons[9];
				ISendStr(0xa0,0xa4,V32.b8,4);Delay(2);

				showConstant2();
				
				//if(Cons[6]==0)    //����ת
	            //{	volt = Cons[9]*100;RunMotor(1,1);RunMode=1;StartCount=Cons[7];}
	            //else		
	            //{	volt = Cons[9]*100;RunMotor(1,2);RunMode=2;StartCount=Cons[7];}

				while (KeyValue!=0xff)
				{ Read_Key(); }
				return 0;        //���ص���0������ִ��
			}
			case GO_L://���ƶ�
			{
				
				Bell();	
				switch(STAB)
				{
					case 1:
					{	if((Cons[0]==4)||(Cons[0]==3))
							BTAB=(BTAB==0)?3:BTAB-1;//ʵ�ֵ�����ʾ���Ĺ���ڸ�λʮλ��λ...�ϵ��ƶ�
						else
							BTAB=(BTAB==0)?3:BTAB-1;
						break;	}
					case 5:
					{	BTAB=(BTAB==0)?4:BTAB-1;break;} //��ʾ��ʽ�Ĳ�ͬ��BTAB�Ĵ�С�������ı�
                                                  //Ҫ��ʾ��λС��
					//case 8: case 9:
						//{
						//BTAB=(BTAB==0)?3:BTAB-1;break;
						//}
					default:
						BTAB=(BTAB==0)?2:BTAB-1;	//��λ��			
				}
				//showConstSet(1);
				if(STAB<7)
				showConstSet(1);
				else 
				showConstSet(2);
				while (KeyValue!=0xff)
					{ Read_Key(); }
				break;
			}
			case GO_R:  //���ƶ�
			{
				Bell();
				switch (STAB)
				{	case 1:
					{	if((Cons[0]==4)||(Cons[0]==3))
							BTAB=(BTAB==3)?0:BTAB+1;
						else
							BTAB=(BTAB==3)?0:BTAB+1;
						break;	}	
					case 5:
					{	BTAB=(BTAB==4)?0:BTAB+1;break;		}
					//case 8: case 9:
						//{
						//BTAB=(BTAB==3)?0:BTAB+1;break;
						//}
					default:
						BTAB=(BTAB==2)?0:BTAB+1;
				}
				//showConstSet(1);
				if(STAB<7)
				showConstSet(1);
				else 
				showConstSet(2);
				while (KeyValue!=0xff)
					{ Read_Key(); }				
				break;
			}
			
			default:
			{
				 if(KeyValue<=9)
				{
					Bell();
					switch(STAB)
					{
						case 1:
						{
							if((Cons[0]==4)||(Cons[0]==3))//���Ʒ�ʽ�������������
							{
								sprintf(sbuff,"%04.0f",Cons[STAB]);
								sbuff[BTAB]=KeyValue+0x30;  //BTAB�ǿ���ÿһλ���ƶ�								
								Cons[STAB]=atof(sbuff);    //ʵ��ֵ��Cons[1]
								BTAB=(BTAB==3)?0:BTAB+1;
								break;
							}
							else if(Cons[0]==1)//���Ʒ�ʽ������
							{
								sprintf(sbuff,"%05.2f",Cons[STAB]);
								if(BTAB<2)
									sbuff[BTAB]=KeyValue+0x30;
								else
									sbuff[BTAB+1]=KeyValue+0x30;
								Cons[STAB]=atof(sbuff);
								BTAB=(BTAB==3)?0:BTAB+1;
								break;
							}
							else
							{	sprintf(sbuff,"%05.2f",Cons[STAB]);
								if(BTAB<=1)
									sbuff[BTAB]=KeyValue+0x30;
								else
									sbuff[BTAB+1]=KeyValue+0x30;
								
								Cons[STAB]=atof(sbuff);
								BTAB=(BTAB==3)?0:BTAB+1;
								break;
							}
						}				
						case 2:case 3: case 4:case 7:
						{	sprintf(sbuff,"%03.0f",Cons[STAB]);
							sbuff[BTAB]=KeyValue+0x30;
							Cons[STAB]=atof(sbuff);
							BTAB=(BTAB==2)?0:BTAB+1;
							break;
						}
						 case 5:
						 {	sprintf(sbuff,"%05.0f",Cons[STAB]);
							sbuff[BTAB]=KeyValue+0x30;
							Cons[STAB]=atof(sbuff);
							BTAB=(BTAB==4)?0:BTAB+1;
							break;
						}
						 case 8:case 9:
						 {
						 	sprintf(sbuff,"%04.1f",Cons[STAB]);
								if(BTAB<2)
									sbuff[BTAB]=KeyValue+0x30;
								else
									sbuff[BTAB+1]=KeyValue+0x30;
								Cons[STAB]=atof(sbuff);
								BTAB=(BTAB==2)?0:BTAB+1;
								break;
						 }
					}							
					//showConstSet(1);
					if(STAB<7)
				    showConstSet(1);
				    else 
				    showConstSet(2);
					while (KeyValue!=0xff)
						{ Read_Key(); }	
			 	}				
			}
		}	
		
		if(FlagMs2)
		{	Read_ResultM();	}	
		
		if(FlagMs100)
		{	FlagMs100=0;	
			Read_ResultV();
		}
		
		if(FlagDisp)	
		{	FlagDisp=0;
			DataAccess(0);
		}	

		if(Uart0_OK)
		{
			Uart0_OK=0;
			switch (Uart0_Command)
			{	case 5:
				{	s_out(0);
					break;
				}
				default:
				{	U0THR = MyID;
					In_Send=0;U0IER |=0x02;
				}
			}
		}
		
	}
}
/*======================================*/
void ConstantTest2(uint16 a)
{		uint32 TotalTime;
		
		if(a)
		{	
			Bell();
			showConstant1(1);STAB=6;BTAB=0;
			showConstSet(1);
			
		    Counter=0;
			VTAB=0x70;
			HTAB=0x00;putString("Starting...   ");		
			HTAB=0x10;putString("       ");	
			HTAB=0x17;putString("       ");
			while(Counter<30)                //������3Sʱ��        ��ֻ����ʾһ��
			{	Read_Key();
				if(FlagMs2)
				{	Read_ResultM();		}	
				
				if(FlagMs100)
				{	FlagMs100=0;	
					Read_ResultV();
				    ++Counter;
				}
			
				if(FlagDisp)	
				{
					FlagDisp=0;
					DataAccess(0);
					if(--Second05==0)
					{	Second05=5;	
					}
				}
				
				if(Uart0_OK)
				{	Uart0_OK=0;
					if (Uart0_Command==5)
						s_out(0);
					else if(Uart0_Command==11)						
					{	
						//if(!In_Test)
						//{	
						    Bell();
							U0THR = MyID|0x0b;
							In_Send=0;U0IER |=0x02;
							nowClock=0;In_pause=0;
							RunMotor(0,0);
							Delay(20);
							STAB=0;	
							if(a==0)
								showRun0();
							else
								showPG00();
							while (KeyValue!=0xff)
								{ Read_Key(); }
								return;
						}						
						else
						{	U0THR = MyID|0x00;
							In_Send=0;U0IER |=0x02;
						}
					}
			}
			showConstant1(2);STAB=6;BTAB=0;
			showConstSet(2);
			
		    Counter=0;
			VTAB=0x70;
			HTAB=0x00;putString("Starting...   ");		
			HTAB=0x10;putString("       ");	
			HTAB=0x17;putString("       ");
			while(Counter<30)                //������3Sʱ��        ��ֻ����ʾһ��
			{	Read_Key();
				if(FlagMs2)
				{	Read_ResultM();		}	
				
				if(FlagMs100)
				{	FlagMs100=0;	
					Read_ResultV();
				    ++Counter;
				}
			
				if(FlagDisp)	
				{
					FlagDisp=0;
					DataAccess(0);
					if(--Second05==0)
					{	Second05=5;	
					}
				}
				
				if(Uart0_OK)
				{	Uart0_OK=0;
					if (Uart0_Command==5)
						s_out(0);
					else if(Uart0_Command==11)						
					{	
						//if(!In_Test)
						//{	
						    Bell();
							U0THR = MyID|0x0b;
							In_Send=0;U0IER |=0x02;
							nowClock=0;In_pause=0;
							RunMotor(0,0);
							Delay(20);
							STAB=0;	
							if(a==0)
								showRun0();
							else
								showPG00();
							while (KeyValue!=0xff)
								{ Read_Key(); }
								return;
						}						
						else
						{	U0THR = MyID|0x00;
							In_Send=0;U0IER |=0x02;
						}
					}
			}
					
		}				


		Counter=0;
		showConstant2();
		DispPG11(0);
		RunMode=(Cons[6]==0)?1:2;
		volt=Cons[9];
		if(StartMotor(Cons[7],0))       //���ž���������  ����ֵΪ1����F3����
		{
			nowClock=0;STAB=0;In_pause=0;
			if(a==0)             //a�������� ConstantTest2(uint16 a)��a
				showRun0();
			else
			{   showPG00();
				DispPG00();
				}
			while (KeyValue!=0xff)
					{ Read_Key(); }
			return;                   //�������
		}
		volt=Cons[8];
		RunMotor(1, RunMode);
		VTAB=0;HTAB=0x15;
		putString("  0:00:00");
		nowClock=0;	
		TotalTime =(uint32)(Cons[5]);
		
		pid0.SetPoint=Cons[1];  //ͨ�������趨��ʱ��		
		if(Cons[0]==0)
		{	pid_tune(Cons[2],Cons[3],Cons[4],0,0);
		}
		else if(Cons[0]==1)
			pid_tune(Cons[2],Cons[3],Cons[4],1,0);
		else if(Cons[0]==3)
			pid_tune(Cons[2],Cons[3],Cons[4],3,0);
		else if(Cons[0]==4)
			pid_tune(Cons[2],Cons[3],Cons[4],4,0);
		else
		{	pid0.SetPoint=0;
			pid_tune(0,0,0,0,0);	
		}
		
		End_Test=0;
		Alarm=0;In_pause=0;
		Hot_Alarm=0;Hot_Count=0;
		In_Test=0;
		VTAB=0x70;				
		HTAB=0x00;putString("F1");verString( "��ʼ");	
		HTAB=0x08;putString("       ");	
		HTAB=0x10;putString("F3");verString( "����");
	
		while(1)
		{
			
			Read_Key();

			if((KeyValue==F1)&&(!End_Test))  //�����F1����ͣ��     !End_Test�������ڲ��Թ�����
			{
				Bell();
				if(In_Test) //�ڲ��Թ�����
				{					
					In_Test=0;In_pause=1;        //��ͣ�Ĺ���
					PWM1MR0=1000;
					PWM1MR3=1000;
					PWM1LER=0x09;
						
					RunMotor(0,0);RunMode=0;			
					
					VTAB=0x70;HTAB=0x00;putString("F1");				
					verString( "����");
					HTAB=0x08;putString("       ");	
					HTAB=0x10;putString("F3");				
					verString( "����");
				}
				else if(In_pause==0)		//����F1һ�κ�In_Test����Ϊ0�ˣ������ٰ�F1��ִ��else���
				{	
					VTAB=0x70;HTAB=0x02;
					verString( "��ͣ");
					HTAB=0x08;putString("F2");
					verString( "�ƶ�");
					HTAB=0x10;
					putString("      ");
					In_Test=1;
				}
               else
				{	VTAB=0;HTAB=0x15;
					putString("         ");
					Counter=0;
					RunMode=(Cons[6]==0)?1:2;
					volt=Cons[9];             //������ѹ
					if(StartMotor(Cons[7],0)==0)
					{	In_pause=0;
						volt=Cons[8];         //�����ѹ
						RunMotor(1, RunMode);
						sprintf(sbuff,"%3d:%02d:%02d",shi,fen,miao);			
						VTAB=0;HTAB=0x15;
						putBuff(sbuff);	
						VTAB=0x70;
						HTAB=0x00;putString("F1");verString( "��ʼ");
						HTAB=0x08;putString("       ");	
						HTAB=0x10;putString("F3");verString( "����");
					}
					else
					{	VTAB=0x70;
						HTAB=0x00;putString("F1");verString( "����");putString("    ");
						HTAB=0x08;putString("       ");	
						HTAB=0x10;putString("F3");verString( "����");
					}
				}
				while(KeyValue!=0xff)
					{ Read_Key(); }
			}
			else if((KeyValue==F2)&&In_Test) //�ڲ��Թ����У�����F2����Ӧ�����ƶ�
			{	Bell();
				In_Test=0;In_pause=0;
				RunMotor(0,0);RunMode=0;									
				PWM1MR0=1000;
				PWM1MR3=500;
				PWM1LER=0x09;
				Delay(400);
				PWM1MR0=1000;
				PWM1MR3=1000;
				PWM1LER=0x09;
				End_Test=1;				
				
				{
					VTAB=0x70;HTAB=0x00;
					verString( "��  ��");
					HTAB=0x08;putString("       ");
					HTAB=0x10;
					putString( "F3");
					verString( "����");
				}		

			}				
			else if((KeyValue==F3)&&!In_Test)
			{
				Bell();RunMotor(0,0);
				nowClock=0;STAB=0;In_pause=0;
				if(a==0)
					showRun0();
				else
				{	showPG00();
					DispPG00();	}
				while (KeyValue!=0xff)
				{ Read_Key(); }
				return;
			}

			if(FlagMs2)
			{	Read_ResultM();	}
			if(FlagPid)
			{	FlagPid=0;
				if(In_Test)
				{	if(pid0.runtype==0)
								pid_calc();
				}
			}

			if((Hot_Alarm)&&(End_Test==0))
			{	Bell();
				In_Test=0;
				RunMotor(0,0);	
				PWM1MR0=1000;
				PWM1MR3=1000;
				PWM1LER=0x09;
				End_Test=1;
			
				VTAB=0x70;HTAB=0x00;
				verString( "���ȱ���!");	
				putString("       ");
				HTAB=0x10;
				putString( "F3");
				verString( "����");
			}
			

						
			if(FlagMs100)
			{
				FlagMs100=0;		
				if(In_Test)  //ʵ����ͣ��ʱ����ͨ���� In_Test����Ϊ0 �Ӷ�ʵ����ͣ��ʱ
				{
					if(--Second1==0)
					{	Second1=10;

						++nowClock;
						shi = nowClock / 3600;
						fen= (nowClock%3600)/ 60;
						miao=nowClock-shi*3600-fen*60;

						sprintf(sbuff,"%3d:%02d:%02d",shi,fen,miao);			
						VTAB=0;HTAB=0x15;
						putBuff(sbuff);	
						if(TotalTime!=0)
						{	if(nowClock>=TotalTime)
							{	In_Test=0;
								RunMotor(0,0);									
								PWM1MR0=1000;
								PWM1MR3=500;
								PWM1LER=0x09;
								Delay(400);
								PWM1MR0=1000;
								PWM1MR3=1000;
								PWM1LER=0x09;
								Bell();
								End_Test=1;
								
								{
									VTAB=0x70;HTAB=0x00;
									verString( "��  ��");
									HTAB=0x08;putString("       ");
									HTAB=0x10;
									putString( "F3");
									verString( "����");
								}		
							}
						}
					}
				}		
				Read_ResultV();	
			}
			
			if(FlagDisp)	
			{
				FlagDisp=0;
				DataAccess(0);
				
				if(In_Test)
				{
					if(pid0.runtype)
						pid_calc();
				}			
				if(--Second05==0)
				{	Second05=5;		
					DispPG11(0);
					
				}
			}
			
			
			if(Uart0_OK)    //������ʵ��ͨ����λ�����һЩ��������ͬ������ͨ��������������ʵ�֣�һ�����ھ�Ҫ����ͨѶЭ����д��
			{
				Uart0_OK=0;
				switch (Uart0_Command)
				{				
					case 1:
					{	if((In_Test==0)&&End_Test==0)
						{	U0THR = MyID|0x01;
							In_Send=0;U0IER |=0x02;	
							Bell();
							
							 if(In_pause==0)      //û����ͣ
								{
								VTAB=0x70;HTAB=0x02;
					            verString( "��ͣ");
					            HTAB=0x08;putString("F2");
					            verString( "�ƶ�");
					            HTAB=0x10;
					            putString("      ");
					            In_Test=1;           //���Դ���ͣ������
								}
							else                     //��ͣ״̬��Ҫ��ѹ����In_pause==1
								{
								VTAB=0;HTAB=0x15;
					            putString("         ");
					            Counter=0;
					            RunMode=(Cons[6]==0)?1:2;
					            volt=Cons[9];             //������ѹ
					           if(StartMotor(Cons[7],0)==0)
					           {	In_pause=0;           //��ܹؼ��������ٴ�������Ҫ�ط�0x91����
						            volt=Cons[8];         //�����ѹ
						            RunMotor(1, RunMode);
						            sprintf(sbuff,"%3d:%02d:%02d",shi,fen,miao);			
						            VTAB=0;HTAB=0x15;
						            putBuff(sbuff);	
						            VTAB=0x70;
						            HTAB=0x00;putString("F1");verString( "��ʼ");
						            HTAB=0x08;putString("       ");	
						            HTAB=0x10;putString("F3");verString( "����");
					               }
					             else
					             {	VTAB=0x70;
						            HTAB=0x00;putString("F1");verString( "����");putString("    ");
						            HTAB=0x08;putString("       ");	
						            HTAB=0x10;putString("F3");verString( "����");
					              }
								}
						}
						else
						{	U0THR = MyID|0x00;
							In_Send=0;U0IER |=0x02;
						}				
						break;
					}	
					case 2:
					{	if(In_Test) //Ҫ����ͣ
						{	U0THR = MyID|0x02;
							In_Send=0;U0IER |=0x02;
							Bell();
							In_Test=0;In_pause=1;
							PWM1MR0=1000;
							PWM1MR3=1000;
							PWM1LER=0x09;
							RunMotor(0,0);RunMode=0;
							VTAB=0x70;HTAB=0x02;				
							verString( "����");
							HTAB=0x08;putString("       ");					
							HTAB=0x10;putString("F3");				
							verString( "����");
												
						}
						else
						{	U0THR = MyID|0x00;
							In_Send=0;U0IER |=0x02;
						}						
						break;
					}
					case 5:
					{	if(In_Test)
								s_out(1);
						else
								s_out(0);  					
						break;
					}
					case 0x0b:                   //����
					{	if(!In_Test)
						{	
						   Bell();
							U0THR = MyID|0x0b;
							In_Send=0;U0IER |=0x02;
							nowClock=0;
							In_pause=0;
							RunMotor(0,0);
							Delay(20);
							STAB=0;	
							if(a==0)
								showRun0();
							else
							{	showPG00();
								DispPG00();	}
							return;
						}
						else
						{	U0THR = MyID|0x00;
							In_Send=0;U0IER |=0x02;
						}
						break;
					}
					case 14:
					{	if(In_Test) 
						{	U0THR = MyID|0x02;
							In_Send=0;U0IER |=0x02;
							Bell();
							RunMotor(0,0);	
							In_Test=0;
							PWM1MR0=1000;
							PWM1MR3=500;
							PWM1LER=0x09;
							Delay(200);
							PWM1MR0=1000;
							PWM1MR3=1000;
							PWM1LER=0x09;
							End_Test=1;
							VTAB=0x70;HTAB=0x00;
							verString( " ��  �� ");	
							HTAB=0x08;putString("       ");
							HTAB=0x10;
							putString( "F3");
							verString( "����");
						}
						else
						{	U0THR = MyID|0x00;
							In_Send=0;U0IER |=0x02;
						}						
						break;
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
/*======================================*/
void showConstSet(uint16 a)
{	if(a==1)
	{
	VTAB=0x00;HTAB=0x1a;
	if(STAB==6)
	{	if(Cons[6]==0)
			verString("��ת");
		else
			verString("��ת");	
	}
	else
	{	if(Cons[6]==0)
			putString("��ת");
		else
			putString("��ת");	
	}

	
	VTAB=0x12;	HTAB=0x12;
	if(STAB==0)
	{	if(Cons[0]==3) {verString("���빦��");}
		else if(Cons[0]==1) 
			{verString("����");putString("    ");}
		else if(Cons[0]==4) 
			{verString("�������");}
		else {verString("ת��");putString("    ");}
	}
	else
	{
		if(Cons[0]==3) putString("���빦��");
		else if(Cons[0]==1) 
			 putString("����    ");
		else if(Cons[0]==4) 
			 putString("�������");
		else putString("ת��    ");
	}

	if((Cons[0]==3)||(Cons[0]==4))
						{	VTAB=0x24;HTAB=0x00;
							putString(  "�㶨����");
							VTAB=0x36;HTAB=0x0a;
							putString(  "W ");}	
	else if(Cons[0]==1)	{	VTAB=0x24;HTAB=0x00;
							putString(  "�㶨����");
							VTAB=0x36;HTAB=0x0a;
							putString(  "A ");}						
	else					{	VTAB=0x24;HTAB=0x00;
							putString(  "�㶨ת��");
							VTAB=0x36;HTAB=0x0a;
							putString(  "Nm");	}
	
	VTAB=0x36;HTAB=0x04;                       //��ʾ�������
	if((Cons[0]==4)||(Cons[0]==3))          //���Ʒ�ʽ������������� ��ʽ��0000
		sprintf(sbuff," %04.0f",Cons[1]);
	else if(Cons[0]==1)
		sprintf(sbuff,"%05.2f",Cons[1]);
	else
		sprintf(sbuff,"%05.2f",Cons[1]);
	putString(sbuff);	
	if(STAB==1)                  //���Ʒ�ʽ������������� ��ʽ��0000
	{	if((Cons[0]==4)||(Cons[0]==3))
		{			
			HTAB=0x05+BTAB;verEng(sbuff[BTAB+1]);			
		}
		else if(Cons[0]==1)     //���Ʒ�ʽ������ ��ʽ��00.00
		{	switch(BTAB)
			{	case 0: case 1: //���������ж���Ϊ������С����
				{	HTAB=0x04+BTAB;verEng(sbuff[BTAB]);
				 	break;	}	
				 default:
				 {	HTAB=0x05+BTAB;verEng(sbuff[BTAB+1]);
				 	break;	}
			}
		}
		else
		{	switch(BTAB)
			{	case 0: case 1:
				{	HTAB=0x04+BTAB;verEng(sbuff[BTAB]);
				 	break;	}	
				 default:
				 {	HTAB=0x05+BTAB;verEng(sbuff[BTAB+1]);
				 	break;	}
			}
			
		}
	}

	VTAB=0x36;HTAB=0x18;
	sprintf(sbuff,"%03.0f",Cons[2]);
	putString(sbuff);
	if(STAB==2) 
	{
		HTAB=0x18+BTAB;verEng(sbuff[BTAB]);
	}

	VTAB=0x48;HTAB=0x18;
	sprintf(sbuff,"%03.0f",Cons[3]);
	putString(sbuff);
	if(STAB==3) 
	{
		HTAB=0x18+BTAB;verEng(sbuff[BTAB]);
	}
	
	VTAB=0x5a;HTAB=0x18;
	sprintf(sbuff,"%03.0f",Cons[4]);
	putString(sbuff);
	if(STAB==4) 
	{
		HTAB=0x18+BTAB;verEng(sbuff[BTAB]);
	}

	VTAB=0x5a;HTAB=0x04;
	sprintf(sbuff,"%05.0f",Cons[5]);
	putString(sbuff);
	if(STAB==5) 
	{
		HTAB=0x04+BTAB;verEng(sbuff[BTAB]);
	}
	
	if((STAB==0)||(STAB==6))
	{	VTAB=0x70;HTAB=0x08;putString("F2");
	  	verString("ѡ��");
	}
	else
	{	VTAB=0x70;HTAB=0x08;
		putString("      ");	  	
	}
   }
  else if(a==2)
 {  
    VTAB=0x24;	HTAB=0x11;
	putString("Sec");
	VTAB=0x24;	HTAB=0x0a;
	sprintf(sbuff,"%03.0f",Cons[7]);
	putString(sbuff);
   if(STAB==7)    //��ѹ����ʱ��
   	{
   	 HTAB=0x0a+BTAB;verEng(sbuff[BTAB]);
   	}
    VTAB=0x36;	HTAB=0x11;
	putString("V");
    VTAB=0x36;	HTAB=0x0a;
	sprintf(sbuff,"%04.1f",Cons[8]);
	putString(sbuff);
   if(STAB==8)    //�����ѹ
   	{
   	 switch(BTAB)
			{	case 0: case 1: //���������ж���Ϊ������С����
				{	HTAB=0x0a+BTAB;verEng(sbuff[BTAB]);
				 	break;	}	
				 default:
				 {	HTAB=0x0b+BTAB;verEng(sbuff[BTAB+1]);
				 	break;	}
   	        }
   	}
      VTAB=0x48;	HTAB=0x11;
	  putString("V");
	  VTAB=0x48;	HTAB=0x0a;
	sprintf(sbuff,"%04.1f",Cons[9]);
	putString(sbuff);
   if(STAB==9)    //������ѹ
   	{
   	     switch(BTAB)
			{	case 0: case 1: //���������ж���Ϊ������С����
				{	HTAB=0x0a+BTAB;verEng(sbuff[BTAB]);
				 	break;	}	
				 default:
				 {	HTAB=0x0b+BTAB;verEng(sbuff[BTAB+1]);
				 	break;	}
   	         }
     }
	
 }
}
/********************************************************
*����������0 ��ֵ 1 �ֶ� 2 ���� 3 ����
************************************************************/
void DispPG11(uint16 a)
{	float XFx;
	VTAB=0x12;
	sprintf(sbuff,"%5.2f",Fv);
	HTAB=0x07;putBuff(sbuff);	
	
	VTAB=0x24;
	sprintf(sbuff,"%6.2f",Fc);
	HTAB=0x06;putBuff(sbuff);
	
	VTAB=0x36;
	sprintf(sbuff,"%6.1f",Fp);
	HTAB=0x06;putBuff(sbuff);
	if(a==3);
	else if(a==0)
	{	sprintf(sbuff,"%6.1f",Po);
		HTAB=0x16;putBuff(sbuff);
	}
	
	VTAB=0x48;
	//if(pFs<1000)
		//sprintf(sbuff,"%6.1f",pFs);
	//else
		sprintf(sbuff,"%6.1f",pFs);
	HTAB=0x06;putBuff(sbuff);
	if(a==0)
	{	sprintf(sbuff,"%6.2f",eff);
		HTAB=0x16;putBuff(sbuff);
	}

	if(In_Test==0)
		XFx=pFt2;
	else
		XFx=pFt;
	VTAB=0x5a;
	sprintf(sbuff,"%6.2f",XFx);
	HTAB=0x06;putBuff(sbuff);
	

	if(a==2)                            //����
	{	
		VTAB=0x48;	
		sprintf(sbuff,"%2d",Cycle);     //״̬�Ǵ�0��ʼ��
		HTAB=0x1c;putString(sbuff);
		
		VTAB=0x5a;
		sprintf(sbuff,"%5.1f",(float)Counter/10);
		HTAB=0x19;putString(sbuff);	
	
	}			
}

/******************************************************
        ��������
********************************************************/
int RunTest1(uint8 num)
{	
	//uint16 ii;

	ReLoad2(0);
	ParaAccess(0);
	
	End_Test=0;
	nowClock=0;	
	Total=0;TotalRev=0;
	Cycle=0;CycleCount=0;
	Counter=0;
	Alarm=0;KL_Counter=0;ZL_Counter=0;SL_Counter=0;
	In_Test=0;EnableF=1;		
	
	
	STAB=0;
	showPGRun1();	
	STAB=0;
	DispPG11(2);  
	RunStep(0);
	while (KeyValue!=0xff)
		{ Read_Key(); }	
	
	
	Hot_Alarm=0;Hot_Count=0;
   	In_pause=0;
	shi = nowClock / 3600;
	fen= (nowClock%3600)/ 60;
	miao=(nowClock-shi*3600-fen*60);
/*
	sprintf(sbuff,"%3d:%02d:%02d",shi,fen,miao);			
	VTAB=0x00;HTAB=0x15;
   	putString(sbuff);*/


	if(Step[0].loadtype=='2')  //����ת��
	{	pid_tune((float)PidPara.pid.pgain,
				(float)PidPara.pid.igain,
				(float)PidPara.pid.dgain,0,0);
	}
	else
	{	pid_tune(0,0,0,5,0);	
		pid0.runtype=5;
	}	
	if(Step[0].endvalue)                         //�������ǰ4�κͺ�4��
	{	Finish1=(uint16)(Step[0].endvalue*10);Cycle=CycleCount=0;	}  //����10��
	else if(Step[4].endvalue)
	{	Finish1=(uint16)(Step[4].endvalue*10);Cycle=CycleCount=5;	}
	else
	{	Finish1=10;Cycle=CycleCount=12;							}
	/*
	if(num==0)
	{}
	else
	{	VTAB=0x70;HTAB=0x00;
		putString("F1");verString( "ֹͣ");
		HTAB=0x09;
		putString("      ");	
		VTAB=0x70;HTAB=0x13;
		putString("          ");
						
		Second1=2;
		Alarm=0;
		EnableF=0;nowClock=0;In_pause=0;
		Cycle=0;
		KL_Counter=0;ZL_Counter=0;SL_Counter=0;
	   	RunStep(0);
		In_Test=1;Running=1;In_pause=0;
	}
	*/
	/*if((Position&0x01))
	{   Counter=0;
		volt = StartVolt1;
		if(StartMotor(StartTime,2))       //���ž���������  ����ֵΪ1����F3����
		{
			nowClock=0;STAB=0;In_pause=0;In_Test=0;
			if(num==0)             //a�������� ConstantTest2(uint16 a)��a
				showRun0();
			else
			{   showPG00();
				DispPG00();
				}
			while (KeyValue!=0xff)
					{ Read_Key(); }
			return 0;                   //�������
		}
		VTAB=0x00;HTAB=0x19;putString("     ");
		Counter=0;
		volt = TestVolt1;
		RunMotor(1, RunMode);

		VTAB=0x70;				
		HTAB=0x00;putString("F1");verString( "��ʼ");	
		//HTAB=0x08;putString("       ");	
		HTAB=0x09;putString("F3");verString( "����");
		}*/
	
	while(1)
	{   
	    Read_Posi();
		Read_Key();	
		if(FlagBT)                      //FlagBT   Button=0x02������  
		{	FlagBT=0;
			if((Button==0x02)&&(!End_Test)&&EnableF)
			{	if(In_Test==0)          //Ҫ����ͣ	End_Test=0 ˵����û�н�������	
				{	Bell();             //EnableF��RunTest1()֮ǰ�趨��
			       if(Position&0x01)    //���ܿ��رպϵ�������
					{
					EnableF=0;  	
					VTAB=0x70;HTAB=0x00;
					putString("F1");verString( "ֹͣ");
					HTAB=0x09;
					putString("      ");	
					VTAB=0x70;HTAB=0x13;
					putString("          ");									
					Second1=2;
					Alarm=0;
					nowClock=0;In_pause=0;
					KL_Counter=0;ZL_Counter=0;SL_Counter=0;
					Hot_Alarm=0;Hot_Count=0;
				   	RunStep(0);      
					In_Test=1;
			       	}
				}			
			}	
			else if((Button==0x01)&&In_Test)  //Button==0x01��ֹͣ��
			{
			  
				Bell();
				Running=0;End_Test=1;
				In_Test=0;
				In_Test=0;
				PWM1MR0=1000;
				PWM1MR3=1000;
				PWM1LER=0x09;
				RunMotor(0,RunMode);//�رյ��	
				RunMode=0;
				StartCount=3;	    //�رյ��ҲҪ�ӳ���
				VTAB=0x70;HTAB=0x00;
				verString("��  ֹ");		
				HTAB=0x09;putString("F3");
				verString( "�˳�");
				Delay(50);
				RunMotor(0,0);RunMode=0;
			  	
			}
			
		} 
		if((KeyValue==F1)&&(!End_Test))       //End_Test=0�ں�����ͷ����ֵ
		{                        
			Bell();
			if(In_Test!=0)                    //��һ��ִ�б�������In_Test=1���� ˵�����ڲ�����
			{	
			 
			    In_pause=0;   //In_Test!=0 ˵�����ڲ�����
				End_Test=1;
				In_Test=0;
				PWM1MR0=1000;
				PWM1MR3=1000;
				PWM1LER=0x09;			
				RunMotor(0,RunMode);    //	ͬ��
				RunMode=0;
				StartCount=5;           //����Ĺ��ܾ����ӳ�
				VTAB=0x70;HTAB=0x00;
				verString("��  ֹ");		
				HTAB=0x09;putString("F3");
				verString( "����");	
			 	
				while(KeyValue!=0xff)
						{ Read_Key(); }				
			}
			
			else if(In_Test==0) 		      //      In_Test=0�ں�����ͷ�͸�ֵ����������
			{	if(Position&0x01)
				{
				VTAB=0x70;HTAB=0x00;
				putString("F1");verString( "ֹͣ");
				HTAB=0x09;
				putString("      ");	
				VTAB=0x70;HTAB=0x13;
				putString("          ");								
				Second1=2;
				Alarm=0;
				EnableF=0;nowClock=0;In_pause=0;
				KL_Counter=0;ZL_Counter=0;SL_Counter=0;
				Hot_Alarm=0;Hot_Count=0;
			   	RunStep(0);
				In_Test=1;            //���Թ����л�    In_Test=1
				
				}
				while(KeyValue!=0xff)
						{ Read_Key(); }
				In_pause=0;
			}
			
		}
		
		else if((KeyValue==F3)&&!In_Test)         //����
		{
			Bell();
			STAB=0;	RunMotor(0,0);
			Cycle=0;CycleCount=0;
			Total=0;End_Test=0;
			if(num<2) 
			{	showRun0();
				while (KeyValue!=0xff)
					{ Read_Key(); }
				return 0;	
			}
			else 
			{	showPG00();
				DispPG00();
				while (KeyValue!=0xff)
					{ Read_Key(); }
				return 1;
			}
		}
		else if(Position==0)			//�����λ�õ�ǰ��Ҳ����Ҫ������ִ�е�˳��
			{
				In_pause=0;   //In_Test!=0 ˵�����ڲ�����
				End_Test=1;
				In_Test=0;
				Alarm = 1;    //���ÿ�·������־
				PWM1MR0=1000;
				PWM1MR3=1000;
				PWM1LER=0x09;			
				RunMotor(0,RunMode);	//	
				RunMode=0;
				
				VTAB=0x70;HTAB=0x00;
				verString("��״̬");	
				HTAB=0x09;putString("F3");
				verString( "����");
				while(KeyValue!=0xff)
				{ Read_Key(); }
			}
		
		if(FlagMs2)
		{	Read_ResultM();	}
		if(FlagPid)
		{	FlagPid=0;
			if(In_Test)
			{	if((pid0.runtype==0)&&(pid0.SetPoint2==0))
							pid_calc();
			}
		}
	/*	
		if((Hot_Alarm)&&In_Test)
		{	Bell();
			//Alarm=4;						
			{	
				In_Test=0;
				PWM1MR0=1000;
				PWM1MR3=1000;
				PWM1LER=0x09;
				RunMotor(0,0);
			}							
			
			End_Test=1;			
			VTAB=0x70;HTAB=0x00;
			verString( "���ȱ���!");	
			putString("       ");
			HTAB=0x10;
			putString( "F3");
			verString( "����");	
			

			
		}	*/
		
			
			
		if(FlagMs100)
		{	FlagMs100=0;	

			
			if(--Second1==0)
			{	Second1=10;		
				
				if(In_Test)
					++nowClock;		//��ʱ 
				cClock=nowClock;
				shi = cClock / 3600;
				fen= (cClock%3600)/ 60;
				miao=(cClock-shi*3600-fen*60);
				/*
				sprintf(sbuff,"%3d:%02d:%02d",shi,fen,miao);			
				VTAB=0x00;HTAB=0x15;
				putBuff(sbuff);
				*/				
			}
			
			if(In_Test)
			{	++Counter;                 //����     ÿ100MS����1		
				if(Counter>=Finish1)       //��������˵��һ���׶β��Խ���
					GoNext();               //�ı����Cycle	�͵���RunStep()����ִ����һ���׶�
				else
				{	VTAB=0x5a;
					sprintf(sbuff,"%5.1f",(float)Counter/10);
					HTAB=0x19;putString(sbuff);	
				}
							
			}
			Read_ResultV();
		}
		
		if(FlagDisp)	
		{
			FlagDisp=0;
			DataAccess(0);		
			
			if(--Second05==0)
			{	Second05=5;
				if(Alarm==0)
					DispPG11(2);
			}				
		}

		if(Uart0_OK)
		{
			Uart0_OK=0;
			switch (Uart0_Command)
			{				
				case 1:
				{	if(End_Test)                 //�������Ա�־
					{	
					    U0THR = MyID|0x01;
						In_Send=0;U0IER |=0x02;
						Bell();
						EnableF=1;
						Alarm=0;End_Test=0;
						KL_Counter=0;ZL_Counter=0;SL_Counter=0;
						Total=0;nowClock=0;Counter=0;
						Cycle=CycleCount;
						DispPG11(2);						
						VTAB=0x70;HTAB=0x00;
						putString("F1");verString( "ֹͣ");						
						VTAB=0x70;HTAB=0x18;
						putString("      ");							
					}
					else
					{	U0THR = MyID;
						In_Send=0;U0IER |=0x02;//ֹͣ����
					}
					break;
				}
				case 2:             //ֹͣ
				{	U0THR = MyID|0x02;
					In_Send=0;U0IER |=0x02;					
					if(In_Test) //��ʾ���ڲ�����
					{	Bell();
						In_pause=0;
						End_Test=1;EnableF=0;
						{	
							In_Test=0;
							PWM1MR0=1000;
							PWM1MR3=1000;
							PWM1LER=0x09;
						}
						RunMotor(0,RunMode);//�ر�����	
						RunMode=0;
						StartCount=5;			
						VTAB=0x70;HTAB=0x00;
						putString("       ");	
						HTAB=0x09;putString("F3");
						verString( "����");			

						
					}
					break;
				}
				case 4:
					{
					UpLoadProg(0);          //�����ϴ����ղ���
					break;
					}
				case 5:
				{	s_out(0);				
					break;
				}
				case 11:
				{	U0THR = MyID|0x0b;
					In_Send=0;U0IER |=0x02;		
					if(In_Test==0)
					{	Bell();
						STAB=0;
						Cycle=0;CycleCount=0;
						Total=0;nowClock=0;
						RunMotor(0,0);End_Test=0;
						if(num<2)
						{	showRun0();
							return 0;	}
						else
						{	showPG00();
							DispPG00();
							return 1;	}		
								
					}
					break;
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


/*===================================================*/
void RunStep(uint16 a)
{		float result;		

		if(a==0)
			Counter=0;
		Finish1=(uint16)(Step[Cycle].endvalue*10);
	
		DispPG11(2);		
		
		switch(Cycle)
		{	

            case 0:
            {	
				 Counter=0;
		         volt = StartVolt1;
				 RunMode = 2;
		         if(StartMotor(StartTime,2)==0)    //���ž���������  ����ֵΪ1����F3����
		         	{
					VTAB=0x00;HTAB=0x19;putString("     ");
					volt = TestVolt1;
		            RunMotor(1, RunMode);
					VTAB=0x70;
					HTAB=0x00;putString("F1");verString( "��ʼ");
					//HTAB=0x08;putString("		"); 
					HTAB=0x09;putString("F3");verString( "����");
		         	}
                 else
					{	VTAB=0x70;
						HTAB=0x00;putString("F1");verString( "����");putString("    ");
						//HTAB=0x08;putString("       ");	
						HTAB=0x09;putString("F3");verString( "����");
					}
		    
			    pid0.SetPoint= Step[Cycle].loadvalue;     
			    
				break;			}
		
			case 1:  case 2:  case 3:
			{	pid0.SetPoint= Step[Cycle].loadvalue;
			    RunMode = 1;	                  
				break;			}	
			case 4: 
			{	RunMotor(0,1);RunMode=0;   //���ջ��趨��5�׶ε�ʱ�� 
			    pid0.SetPoint= Step[Cycle].loadvalue;
				break;			}
			case 5: 
			{	
				 Counter=0;
		         volt = StartVolt1;
				 RunMode = 2;
		         if(StartMotor(StartTime,2)==0)    //���ž���������  ����ֵΪ1����F3����
		         	{
					VTAB=0x00;HTAB=0x19;putString("     ");
					volt = TestVolt1;
		            RunMotor(1, RunMode);
					VTAB=0x70;
					HTAB=0x00;putString("F1");verString( "��ʼ");
					//HTAB=0x08;putString("		"); 
					HTAB=0x09;putString("F3");verString( "����");
		         	}
                 else
					{	VTAB=0x70;
						HTAB=0x00;putString("F1");verString( "����");putString("    ");
						//HTAB=0x08;putString("       ");	
						HTAB=0x09;putString("F3");verString( "����");
					}
		    
			    pid0.SetPoint= Step[Cycle].loadvalue;     
			    
				break;			}
			 case 6: case 7: case 8: 
			{	pid0.SetPoint= Step[Cycle].loadvalue;
			    RunMode = 2;	
				
				break;			}
			
		}
			
		
		
		
		if(pid0.integral<0) pid0.integral=0;	
		pid0.SetPoint2=0;
		
		if(pid0.SetPoint==0)
		{	PWM1MR0=1000;
			PWM1MR3=1000;
			PWM1LER=0x09;	//PWM����ʹ�ܼĴ��� ����д��ƥ��3�Ĵ���
			pid0.last_error=0;pid0.integral=0;
			pid0.SetPoint2=1;
		}
		else if(pid0.runtype==5)//������
		{	pid0.SetPoint2=1;	
			result=pid0.SetPoint*10;
			result=(result > 1000.0) ? 1000.0 : (result < 0.0 ? 0.0 : result);
			PWM1MR0=1000;
			PWM1MR3=1000-(uint32)result;
			PWM1LER=0x09;
		}		
}
/*********************************************************/
void GoNext(void)
{	
In001:
	++Cycle;                         //���Cycle �ǻ���10��
	if(Cycle<10)
	{	if(Step[Cycle].endvalue==0)  //ĳ�׶ν���ֵΪ0�������ý׶�
			goto In001;
		RunStep(0);	}
	else                             //�������һ��       10���׶β������
	{		Total=2;
			In_Test=0;
			End_Test=1;
			Out_PWM(0);
			RunMotor(0,RunMode);	//�ر�
			RunMode=0;
			//StartCount=StartTime;
			Bell();
							
			VTAB=0x5a;
			sprintf(sbuff,"%5.1f",(float)Counter/10);
			HTAB=0x19;putString(sbuff);
			VTAB=0x70;HTAB=0x00;
			verString( "��  ��");
			HTAB=0x09;
			putString( "F3");								
			verString( "����");
			
	}
	
}

/****************************************************/
void Manual(uint16 a)                //�ֶ�����
{
	RunMotor(0,0);	
	showPG_Manual();
	DataAccess(0);	
		
	
	nowClock=0;Cycle=1;
	End_Test=0;
	DispPG11(1);	
	Second05=5;	
	In_Test=0;
	End_Test=0;
	Hot_Alarm=0;Alarm=0;
	Hot_Count=0;

	if(a==0)
	{	BTAB=0;STAB=0;	}
	else
		Bell();
	sprintf(sbuff,"%4.1f",(float)BTAB/10.0);
	VTAB=0x36;HTAB=0x18;
	putBuff(sbuff);	

	VTAB=0;HTAB=0x17;
	putEng('"');putEng('0');putEng('"');
	if(STAB==0)
		verString("��ת");
	else
		verString("��ת");
	
	while(KeyValue!=0xff)
				{ Read_Key(); }
	
	while(1)
	{
			
		Read_Key();
		if((KeyValue==F2)&&(!End_Test))     //F2�ǿ�ʼ����
		{
			Bell();
			if(In_Test) //Ҫ����ͣ
			{					
				{	
					In_Test=0;
					PWM1MR0=1000;
					PWM1MR3=1000;
					PWM1LER=0x09;
				}
				RunMotor(0,0);					
				
				VTAB=0x70;HTAB=0x0a;				
				verString( "����");
						
				HTAB=0x10;putString("F3");				
				verString( "����");
			}
			else 		//����
			{
				VTAB=0x70;HTAB=0x0a;
				verString( "��ͣ");
				HTAB=0x10;
				putString("      ");	
				if(STAB==0)
				{	volt = StartVolt3; RunMotor(1,1);RunMode =1;StartCount=StartTime;		}
				else
				{	volt = StartVolt3; RunMotor(1,2);RunMode =2;StartCount=StartTime;		}
				In_Test=1;	
				PWM1MR0=1000;
				PWM1MR3=1000-BTAB;
				PWM1LER=0x09;
			}
			while(KeyValue!=0xff)
				{ Read_Key(); }
		}
		else if((KeyValue==F3)&&!In_Test)
		{
			Bell();RunMotor(0,0);
			nowClock=0;STAB=0;
			In_pause=0;End_Test=0;
			if(a==0)
				showRun0();
			else
			{	showPG00();
				DispPG00();	}
			while (KeyValue!=0xff)
			{ Read_Key(); }
			return;
		}
		else if(KeyValue==GO_L)
		{	Bell();
			BTAB=(BTAB<=1)?0:BTAB-1;
			sprintf(sbuff,"%4.1f",(float)BTAB/10.0);
			VTAB=0x36;HTAB=0x18;putBuff(sbuff);
			if(In_Test) 
			{	PWM1MR0=1000;
				PWM1MR3=1000-BTAB;
				PWM1LER=0x09;
			}				
			while (KeyValue!=0xff)
				{ Read_Key();}
		}
		else if(KeyValue==GO_R)
		{	Bell();
			BTAB=(BTAB>=998)?999:BTAB+1;
			sprintf(sbuff,"%4.1f",(float)BTAB/10.0);
			VTAB=0x36;HTAB=0x18;putBuff(sbuff);	
			if(In_Test) 
			{	PWM1MR0=1000;
				PWM1MR3=1000-BTAB;
				PWM1LER=0x09;
			}				
			while (KeyValue!=0xff)
				{ Read_Key();}
		}	
		else if(KeyValue==F1)
		{	Bell();
			BTAB=(BTAB<=10)?0:BTAB-10;
			sprintf(sbuff,"%4.1f",(float)BTAB/10.0);
			VTAB=0x36;HTAB=0x18;putBuff(sbuff);
			if(In_Test) 
			{	PWM1MR0=1000;
				PWM1MR3=1000-BTAB;
				PWM1LER=0x09;
			}				
			while (KeyValue!=0xff)
				{ Read_Key();}
		}
		else if(KeyValue==F4)
		{	Bell();
			BTAB=(BTAB>=990)?999:BTAB+10;
			sprintf(sbuff,"%4.1f",(float)BTAB/10.0);
			VTAB=0x36;HTAB=0x18;putBuff(sbuff);	
			if(In_Test) 
			{	PWM1MR0=1000;
				PWM1MR3=1000-BTAB;
				PWM1LER=0x09;
			}				
			while (KeyValue!=0xff)
				{ Read_Key();}
		}	
		else if(KeyValue==0)
		{	if(In_Test==0)
			{	Bell();
				STAB=(STAB==0)?1:0;
				VTAB=0;HTAB=0x1a;
				if(STAB==0)
				{	verString("��ת");
					//RunMotor(1,1);		
				}
				else
				{	verString("��ת");
					//RunMotor(1,2);		
				}
			}
			while (KeyValue!=0xff)
				{ Read_Key();}
		}	


		if(FlagMs2)
		{	Read_ResultM();		}
			
		if((Hot_Alarm)&&(End_Test==0))
		{	Bell();
			In_Test=0;
			RunMotor(0,0);	
			PWM1MR0=1000;
			PWM1MR3=1000;
			PWM1LER=0x09;
			End_Test=1;
		
			VTAB=0x70;HTAB=0x00;
			//verString( "OverTemp.");	
			verString( "���ȱ���!");	
			putString("       ");
			HTAB=0x10;
			putString( "F3");
			//verString( "Quit");
			verString(  "����");
		}		
		
		if(FlagMs100)
		{
			FlagMs100=0;	
			Read_ResultV();
		}
		if(FlagS1)
		{
			FlagS1=0;
			if(StartCount)
			{ 
				--StartCount;
			   if(StartCount==0)
			    {volt = TestVolt3;
			     RunMotor(1,RunMode);
			    }	
			}
		}	
		if(FlagDisp)	
		{
			FlagDisp=0;
			DataAccess(0);
						
			if(--Second05==0)
			{	Second05=5;		
				DispPG11(1);
			}
		}
		

		if(Uart0_OK)                  //����λ��ʵ���ֶ�����
		{
			Uart0_OK=0;
			switch (Uart0_Command)
			{	case 1:                                
				{	if((In_Test==0)&&(End_Test==0))
					{	U0THR = MyID|0x01;
						In_Send=0;U0IER |=0x02;	
						Bell();
						VTAB=0x70;HTAB=0x0a;
						verString( "��ͣ");
						HTAB=0x10;
						putString("      ");	
						if(STAB==0)
				         {	volt = StartVolt3; RunMotor(1,1);RunMode =1;StartCount=StartTime;		}
  				        else
  				         {	volt = StartVolt3; RunMotor(1,2);RunMode =2;StartCount=StartTime;		}
						In_pause=0;
						In_Test=1;
						PWM1MR0=1000;
						PWM1MR3=1000-BTAB;
						PWM1LER=0x09;	
					}
					else
					{	U0THR = MyID|0x00;
						In_Send=0;U0IER |=0x02;
					}				
					break;
					}	
				case 2:
				{	if(In_Test)                  //Ҫ����ͣ
					{	U0THR = MyID|0x02;
						In_Send=0;U0IER |=0x02;
						Bell();
						In_Test=0;
						In_pause=1;
						PWM1MR0=1000;
						PWM1MR3=1000;
						PWM1LER=0x09;
						RunMotor(1,0);					
						
						VTAB=0x70;HTAB=0x0a;				
						verString( "����");
								
						HTAB=0x10;putString("F3");				
						verString( "����");
					}
					else
					{	U0THR = MyID|0x00;
						In_Send=0;U0IER |=0x02;
					}						
					break;
				}	
				case 5:
				{	if(In_Test)
							s_out(1);
					else
							s_out(0);
					break;
				}
				case 7:
				{	if(DownLoadProg2()==9)
					{	sprintf(sbuff,"%4.1f",(float)BTAB/10.0);
						VTAB=0x36;HTAB=0x18;putBuff(sbuff);	
						if(In_Test) 
						{	
							PWM1MR0=1000;
							PWM1MR3=1000-BTAB;
							PWM1LER=0x09;
						}					
					}
					break;
				}
				case 0x0b:             //�����Ѿ���ͣ���߽���
				{	if(!In_Test)
					{	Bell();
						U0THR = MyID|0x0b;
						In_Send=0;U0IER |=0x02;
						nowClock=0;
						RunMotor(0,0);
						Delay(20);
						STAB=0;	
						In_pause=0;End_Test=0;
						
						if(a==0)
							showRun0();
						else
						{	showPG00();
							DispPG00();	}
						return;
					}
					else
					{	U0THR = MyID|0x00;
						In_Send=0;U0IER |=0x02;
					}
					break;
				}	
				default:
				{	U0THR = MyID;
					In_Send=0;U0IER |=0x02;
				}
			}
		}
	}
}


/************************************************************************
�������ܣ���ȡ�������ݣ������UART0�ķ��ͻ����У�Ȼ�������ж����ϴ�����λ��
����Ĳ�����type
***************************************************************************/
void s_out(char type)     
{	uint16 ii,sCycleCount;
	uint32 sTotal;

	sFv=Fv;sFc=Fc;sFp=Fp;
	sFs=pFs;	
	sCounter=Counter;
	if(type==0)     //type���ô���Ĳ���ֻ��0 ����1 
		sFt=pFt2;
	else
		sFt=pFt;


	sNowState=(uint8)(Cycle+0x30);
	sCounter=Counter;
	sCycleCount=CycleCount;	
	sTotal=Total;
	
	if(In_Test)                     //��һ���ֽ�����������
		UR0_T_Buff[0]=0x31;         //�ڲ�����
	else if (In_pause)
		 UR0_T_Buff[0]=0x32;        //��ͣ
	else if (End_Test)
		 UR0_T_Buff[0]=0x34;        //ȫ��ʵ�����
	else if(type==6)
		 UR0_T_Buff[0]=0x36;
	else UR0_T_Buff[0]=0x30;        //�ȴ���

	sprintf(UR0_T_Buff+1,"%05.2f",sFv);	      //��ѹ	
	sprintf(UR0_T_Buff+6,"%05.2f",sFc);       //����	
	if(sFp<1000)
		sprintf(UR0_T_Buff+11,"%05.1f",sFp);  //����	
	else
		sprintf(UR0_T_Buff+11,"%05.0f",sFp);	
	sprintf(UR0_T_Buff+16,"%05.3f",sFt);      //ת��
	sprintf(UR0_T_Buff+21,"%05.1f",sFs);      //ת��
	sprintf(UR0_T_Buff+26,"00000");	          //ֱ�� Ĭ��Ϊ00000
	
	UR0_T_Buff[31]=sNowState;                 //�׶�
	UR0_T_Buff[32]=0x30|(uint8)Alarm;         //����
	if(Zf)
		UR0_T_Buff[32] |= 0x40;
	
	if(type<5)
	{	sprintf(UR0_T_Buff+33,"%05.1f",(float)sCounter/10);			
		sprintf(sbuff,"%03d%02d%02d",shi,fen,miao);
		for(ii=0;ii<7;ii++)  UR0_T_Buff[ii+38]=sbuff[ii];
	}
	else if(type==6)
	{	if(PerFor[0]==0)	UR0_T_Buff[33]=0x30;		//ת�ؿ���
		else	 if(PerFor[0]==1)	UR0_T_Buff[33]=0x31;		//������
		else UR0_T_Buff[33]=0x32;		                        //�ٶ�
		sprintf(UR0_T_Buff+34,"%04.1f",PerFor[2]);		//����		
		sprintf(UR0_T_Buff+38,"%07.3f",PerFor[1]);		//����?
	}		
	sCounter=CycleCount;
	sprintf(UR0_T_Buff+45,"%03d",sCycleCount);	
	sprintf(UR0_T_Buff+48,"%05d",sTotal);	
	
	CRC=0;
	for(ii=0;ii<53;ii++) CRC ^= UR0_T_Buff[ii];
	UR0_T_Buff[53]=CRC;	
	Uart0_T_Count=0;
	Uart0_T_Len=54;
	

	
	In_Send=1;			 
	//Etxd=0;
	U0IER |=0x02;    //�������ж�
	U0THR=MyID|0x05;//���ز�������	
	
}




/**************************************
�������ܣ����Ի��ֵ���Թ��ձ�̲�����40�ֽڣ�
**************************************************/
uint16 DownLoadProg2(void)           //��ֵ���Թ���
{
	uint16 ii,nn,mode;
	char TRBuff[20];
	
	CRC=0;
	for(ii=0;ii<39;ii++)
		CRC ^= UR0_R_Buff[ii];
	if(CRC!=UR0_R_Buff[39])
	{	U0THR = MyID|0x00;
		In_Send=0;U0IER |=0x02;
		return 0xff;
	}
	else
	{	U0THR = MyID|0x07;
		In_Send=0;U0IER |=0x02;
		for(ii=0;ii<39;ii++)
			s_buff[ii]=UR0_R_Buff[ii];

		mode = s_buff[14]; mode = mode & 0x000f;
		
		switch(mode)
		{	/*
			case 0:
			{	nn=2;
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 					
				PerFor[3]=atof(TRBuff);
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 				
				PerFor[4]=atof(TRBuff);
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 		
				PerFor[5]=atof(TRBuff);

				nn=15;
				ii = 0x0f& s_buff[nn];nn++;
				PerFor[0]=(ii==5)?2:0;
				
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],5); nn+=5; 		
				PerFor[1]=atof(TRBuff);
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 		
				PerFor[2]=atof(TRBuff);
				
				PerFor[6]=(s_buff[nn]==0x30)?0:1;

				if(PerFor[0]==0)
				{	PerFor[1]=(PerFor[1]>20)?20:PerFor[1];									
				}
				else
					PerFor[1]=(PerFor[1]>99.9)?99.9:PerFor[1];		
				
				

				V32.f32=PerFor[0];
				ISendStr(0xa0,0xa0,V32.b8,4);Delay(2);
				//if(PerFor[0]==2)
					//PerFor[1]=pFs;				
				V32.f32=PerFor[1];
				ISendStr(0xa0,0xa4,V32.b8,4);Delay(2);
				V32.f32=PerFor[2];
				ISendStr(0xa0,0xa8,V32.b8,4);Delay(2);
				V32.f32=PerFor[3];
				ISendStr(0xa0,0xac,V32.b8,4);Delay(2);
				V32.f32=PerFor[4];
				ISendStr(0xa0,0xb0,V32.b8,4);Delay(2);
				V32.f32=PerFor[5];
				ISendStr(0xa0,0xb4,V32.b8,4);Delay(2);
				V32.f32=PerFor[6];
				ISendStr(0xa0,0xb8,V32.b8,4);Delay(2);
				return 0;								
			}
			case 7:
			{	nn=16;
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],5); nn+=5; 		
				Xtemp=atof(TRBuff);
				MTemp=(uint32)(Xtemp*10);
				MTemp=(MTemp>999)?999:MTemp;
				RBH[0]=MTemp;
								
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 		
				Xtemp=atof(TRBuff);
				MTemp=(uint32)Xtemp;
				MTemp=(MTemp>99)?99:MTemp;
				RBH[1]=MTemp;				
				RBH[3]=(s_buff[nn]==0x30)?0:1;nn++;

				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],3); 		
				Xtemp=atof(TRBuff);
				MTemp=(uint32)Xtemp;
				MTemp=(MTemp>99)?99:MTemp;
				RBH[2]=MTemp;					
				
				

				V32.a32=RBH[0];
				ISendStr(0xa0,0xd0,V32.b8,4);Delay(2);
				V32.a32=RBH[1];
				ISendStr(0xa0,0xd4,V32.b8,4);Delay(2);
				V32.a32=RBH[2];
				ISendStr(0xa0,0xd8,V32.b8,4);Delay(2);
				V32.a32=RBH[3];
				ISendStr(0xa0,0xdc,V32.b8,4);Delay(2);
				return 7;								
			}	*/
			case 8:                                 //��ֵ����
			{	nn=2;
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 					
				Cons[2]=atof(TRBuff);
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 				
				Cons[3]=atof(TRBuff);
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 		
				Cons[4]=atof(TRBuff);

				nn=15;
				ii = 0x0f& s_buff[nn];nn++;
				switch(ii)
				{	case 1:	{Cons[0]=1;break;}
					case 2:	{Cons[0]=0;break;}
					case 3:	{Cons[0]=4;break;}
					default:	{Cons[0]=3;break;}
				}
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],5); nn+=5; 		
				Cons[1]=atof(TRBuff);
				if(Cons[0]==0)
					Cons[1]=(Cons[1]>=15)?15:Cons[1];
				else if(Cons[0]==1)
					Cons[1]=(Cons[1]>=50)?50:Cons[1];
				else
					Cons[1]=(Cons[1]>=300)?300:Cons[1];
				
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],4); nn+=4; 						
				Cons[5]=atof(TRBuff)*60;				
				
				Cons[6]=(s_buff[nn]==0x30)?0:1;   //����ת
				nn=nn+1;
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],3); nn+=3; 						
				Cons[7]=atof(TRBuff);          //��ѹ����ʱ��
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],5); nn+=5; 						
				Cons[8]=atof(TRBuff);      //�����ѹ
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],5); nn+=5; 						
				Cons[9]=atof(TRBuff);      //������ѹ
				//Alarm=(uint16)s_buff[28];    //��ֵ��û�б���
				if(In_Test==0)
				{
					V32.f32=Cons[0];
					ISendStr(0xa0,0x80,V32.b8,4);Delay(2);
					V32.f32=Cons[1];
					ISendStr(0xa0,0x84,V32.b8,4);Delay(2);
					V32.f32=Cons[2];
					ISendStr(0xa0,0x88,V32.b8,4);Delay(2);
					V32.f32=Cons[3];
					ISendStr(0xa0,0x8c,V32.b8,4);Delay(2);
					V32.f32=Cons[4];
					ISendStr(0xa0,0x90,V32.b8,4);Delay(2);	
					V32.f32=Cons[5];
					ISendStr(0xa0,0x94,V32.b8,4);Delay(2);	
					V32.f32=Cons[6];
					ISendStr(0xa0,0x98,V32.b8,4);Delay(2);
					V32.f32=Cons[7];
					ISendStr(0xa0,0x9c,V32.b8,4);Delay(2);
					V32.f32=Cons[8];
					ISendStr(0xa0,0xa0,V32.b8,4);Delay(2);
					V32.f32=Cons[9];
					ISendStr(0xa0,0xa4,V32.b8,4);Delay(2);
				}
				return 8;								
			}
			case 9:
			{	
				nn=16;
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],5); nn+=5; 		
				Xtemp=atof(TRBuff);
				BTAB=(uint32)(Xtemp*10);
				BTAB=(BTAB>999)?999:BTAB;     //�����ʵ�ֵ	
				nn+=4; 						
				STAB = (s_buff[nn]==0x30)?0:1;//����ת	
				nn+=1;
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],3); nn+=3; 						
				StartTime=atof(TRBuff);          //��ѹ����ʱ��
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],5); nn+=5; 						
				TestVolt3=atof(TRBuff)*100;      //�����ѹ
				memset(TRBuff,0,sizeof(TRBuff)); 
				memcpy(TRBuff,&s_buff[nn],5); nn+=5; 						
				StartVolt3=atof(TRBuff)*100;      //������ѹ
				return mode;								
			}
			default:
				return 0xff;
		}		
	}
}

/*======================================*/
void Performance(void)                     //�ɿ�����ʵ�ֵ����Բ���
{
	if(Performance1()) return;
	Performance2(0);
}
/**********************************************/

char Performance1(void)                //������������ʵ�ֵ�����ת
{
		
	Bell();
	STAB=0;BTAB=0;	
	ReLoad2(1);
	ParaAccess(1);
	showPerfomance1(1);
	showPerfoSet();	
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	while(1)
	{
		Read_Key(); 
		
		if(KeyValue==F1)   //F1ʵ�ֵ��ǻ�ҳ����
		{
			Bell();
			switch(STAB)
			{	case 0:
				{	if(LastStep2>4)
					{	STAB=1;
						showPerfomance1(2);	}
					break;
				}
				case 1:
				{	if(LastStep2>8)
					{	STAB=2;
						showPerfomance1(3);	}
					else
					{	STAB=0;
						showPerfomance1(1);	}	
					break;
				}				
				default:
				{	STAB=0;
					showPerfomance1(1);		
					break;	
				}
			}				
			showPerfoSet();
			while (KeyValue!=0xff)
			{ Read_Key(); }									
		}
				
		else if(KeyValue==F3)
		{
			Bell();
			showRun0();STAB=0;
				RunMotor(0,0);
			while (KeyValue!=0xff)
					{ Read_Key(); }
			return 0xff;
		}
		else if(KeyValue==F4)
		{
			Bell();			
			showPerfomance2();
			STAB=0;
			volt = StartVolt2;
	        RunMotor(1,RunMode);                //������Ҫ�Ķ�
	        StartCount=StartTime;
			while (KeyValue!=0xff)
			{ Read_Key(); }
			return 0;							
		}
		
		if(FlagMs2)
		{
			FlagMs2=0;
			Read_ResultM();
		}
		
	
		if(FlagMs100)
		{
			FlagMs100=0;		
			if(--Second1==0)
				Second1=10;			
			Read_ResultV();
		}
		if(FlagDisp)	
		{
			FlagDisp=0;
			DataAccess(0);
		}
		if(Uart0_OK)
		{	Uart0_OK=0;
			switch (Uart0_Command)
			{	
				case 5:
				{	s_out(0);
					break;
				}
				default:
				{	U0THR = MyID|0x00;
					In_Send=0;U0IER |=0x02;
				}
			}
		}
	}
}


/*=========================================================================================================*/
void showPerfoSet(void)
{
		VTAB=0x12;
		HTAB=0x0d;verString(">>>>");		
		HTAB=0x12;
		switch (LoadType2)
		{
			case 7:
				{ putString("ת��    ");	
				
				  /*VTAB=0x24;HTAB=0x15;putString("RPM");
				  VTAB=0x36;HTAB=0x15;putString("RPM");
				  VTAB=0x48;HTAB=0x15;putString("RPM");
				  VTAB=0x5a;HTAB=0x15;putString("RPM"); */
				  break;		}
			case 5: 
				{putString("������  ");			
					
				 /* VTAB=0x24;HTAB=0x15;putString("%  ");
				  VTAB=0x36;HTAB=0x15;putString("%  ");
				  VTAB=0x48;HTAB=0x15;putString("%  ");
				  VTAB=0x5a;HTAB=0x15;putString("%  "); */	
				  break;				}
			default:
				{	putString("ת��    ");
					
					/*VTAB=0x24;HTAB=0x15;putString("Nm ");
					VTAB=0x36;HTAB=0x15;putString("Nm ");
					VTAB=0x48;HTAB=0x15;putString("Nm ");
					VTAB=0x5a;HTAB=0x15;putString("Nm "); */ 

				}//ת��
				  
		}

		switch(STAB)
		{	case 0:
			{	VTAB=0x24;disp_line2(0);
				VTAB=0x36;disp_line2(1);
				VTAB=0x48;disp_line2(2);		
				VTAB=0x5a;disp_line2(3);
				break;	}
			case 1:
			{	VTAB=0x24;disp_line2(4);		
				VTAB=0x36;disp_line2(5);
				VTAB=0x48;disp_line2(6);		
				VTAB=0x5a;disp_line2(7);
				break;	}			
			default:
			{	VTAB=0x24;disp_line2(8);
				VTAB=0x36;disp_line2(9);
			}
		}	
}


/*========================================*/
void disp_line2(char x)
{		
	if((uint16)x<LastStep2)
	{	HTAB=0x00;
		if(x<9)
			sprintf(sbuff,"T%1d",(uint16)x+1);
		else
			sprintf(sbuff,"T%2d",(uint16)x+1);
		putBuff(sbuff);

		HTAB=0x04;
		sprintf(sbuff,"%04.1f",Step2[x].EndValue);
		putString(sbuff);
		HTAB=0X09;	putString( "��");
		

		//HTAB=0x0c;
		//if(Step2[x].LoadMode==0)
				//putString("��");
		//else		putString("��");
		
		
		HTAB=0x0f;
		if(LoadType2==5)
		{	sprintf(sbuff," %04.1f",Step2[x].LoadValue);
			 putString(sbuff);
			 HTAB=0x15;putString("%  ");
		}
		else if(LoadType2==7)
		{	 sprintf(sbuff," %04.0f",Step2[x].LoadValue);
			 putString(sbuff);
			 HTAB=0x15;putString("RPM");
		 }
		else
		{	sprintf(sbuff,"%05.2f",Step2[x].LoadValue);
			putString(sbuff);
			HTAB=0x15;putString("Nm ");
		}
		

		HTAB=0x1a;
		if(Step2[x].RunMode==2&&voltdir==1)putString("��ת");
		else if(Step2[x].RunMode==2&&voltdir==2)putString("��ת");
		else if(Step2[x].RunMode==1)putString("��ֹ");
		else putString("����");
		/*switch(Step2[x].RunMode)
		{	case 1:{putString("��ֹ");break;}	
			case 2:{putString("��ת");break;}
			case 3:{putString("��ת");break;}					
			default:{putString("����");}	
		}*/
	}
}

/********************************************
����������0         1      2
*********************************************/
void Performance2(uint16 num)  //0x98����ᴫ��num=1���Ǵ���λ��ʵ�����Բ���
{	
	Alarm=0;	KL_Counter=0;ZL_Counter=0;
	Running=0;In_pause=0;
	In_Test=0;End_Test=0;       ////////////////////////////
	EnableF=0;STAB=0;
	In_pause=0;
	nowClock=0;	Total=0;
	Cycle=0;CycleCount=0;
   	cClock=nowClock=0;
	shi =fen=miao=0;
	if(num)	                      //����λ��ֱ��ʵ�����Բ��Եĵ�ѹ����
	{	
	    Bell();
		showPerfomance1(1);
		showPerfoSet();
		VTAB=0x70;
		HTAB=0x00;putString("Staring...");
		HTAB=0x10;putString("      ");
		HTAB=0x17;putString("       ");
	    Counter=0;	
		while(Counter<30)                        //3sʱ����ʾһ��
		{	
		    Read_Key();
			if(KeyValue==F3)    //��������
			{	Bell();
				Out_PWM(0);
				RunMotor(0,0);
				STAB=0;
				if(num==0)
					showRun0();//����ѡ�����
				else
					showPG00();
				while (KeyValue!=0xff)
				{ Read_Key(); }
				return;
			}			
			
			if(FlagMs2)
			{
				FlagMs2=0;
				Read_ResultM();	
			}	
			if(FlagMs100)
			{
				FlagMs100=0;
				Read_ResultV();
				++Counter;
			}
		
			if(FlagDisp)
			{	FlagDisp=0;
				DataAccess(0);
				if(--Second05==0)
				{	Second05=5;		
					//DispPG11(3);
				}
			}	
			if(Uart0_OK)
			{	Uart0_OK=0;
				if (Uart0_Command==5)
					s_out(0);
				else if(Uart0_Command==11)   //����						
				{	
					    Bell();
						U0THR = MyID|0x0b;
						In_Send=0;U0IER |=0x02;
						nowClock=0;In_pause=0;
						RunMotor(0,0);
						Delay(20);
						STAB=0;	
						if(num==0)
							showRun0();
						else
							showPG00();
						while (KeyValue!=0xff)
							{ Read_Key(); }
							return;
				}
				else
					{	U0THR = MyID|0x00;
						In_Send=0;U0IER |=0x02;
					}
				
			}				
		}
		if(LastStep2>4)
		{   
		    Counter=0;
			showPerfomance1(2);
		    showPerfoSet();
			while(Counter<30)
			{	
		    Read_Key();
			if(KeyValue==F3)    //��������
			{	Bell();
				Out_PWM(0);
				RunMotor(0,0);
				STAB=0;
				if(num==0)
					showRun0();//����ѡ�����
				else
					showPG00();
				while (KeyValue!=0xff)
				{ Read_Key(); }
				return;
			}			
			
			if(FlagMs2)
			{
				FlagMs2=0;
				Read_ResultM();	
			}	
			if(FlagMs100)
			{
				FlagMs100=0;
				Read_ResultV();
				++Counter;
			}
		
			if(FlagDisp)
			{	FlagDisp=0;
				DataAccess(0);
				if(--Second05==0)
				{	Second05=5;		
					//DispPG11(3);
				}
			}	
			if(Uart0_OK)
			{	Uart0_OK=0;
				if (Uart0_Command==5)
					s_out(0);
				else if(Uart0_Command==11)   //����						
				{	
					    Bell();
						U0THR = MyID|0x0b;
						In_Send=0;U0IER |=0x02;
						nowClock=0;In_pause=0;
						RunMotor(0,0);
						Delay(20);
						STAB=0;	
						if(num==0)
							showRun0();
						else
							showPG00();
						while (KeyValue!=0xff)
							{ Read_Key(); }
							return;
				}
				else
					{	U0THR = MyID|0x00;
						In_Send=0;U0IER |=0x02;
					}
				
			   }				
		   }
	   }
		if(LastStep2>8)
		{   
		    Counter=0;
			showPerfomance1(3);
		    showPerfoSet();
			while(Counter<30)
			{	
		    Read_Key();
			if(KeyValue==F3)    //��������
			{	Bell();
				Out_PWM(0);
				RunMotor(0,0);
				STAB=0;
				if(num==0)
					showRun0();//����ѡ�����
				else
					showPG00();
				while (KeyValue!=0xff)
				{ Read_Key(); }
				return;
			}			
			
			if(FlagMs2)
			{
				FlagMs2=0;
				Read_ResultM();	
			}	
			if(FlagMs100)
			{
				FlagMs100=0;
				Read_ResultV();
				++Counter;
			}
		
			if(FlagDisp)
			{	FlagDisp=0;
				DataAccess(0);
				if(--Second05==0)
				{	Second05=5;		
					//DispPG11(3);
				}
			}	
			if(Uart0_OK)
			{	Uart0_OK=0;
				if (Uart0_Command==5)
					s_out(0);
				else if(Uart0_Command==11)   //����						
				{	
					    Bell();
						U0THR = MyID|0x0b;
						In_Send=0;U0IER |=0x02;
						nowClock=0;In_pause=0;
						RunMotor(0,0);
						Delay(20);
						STAB=0;	
						if(num==0)
							showRun0();
						else
							showPG00();
						while (KeyValue!=0xff)
							{ Read_Key(); }
							return;
				}
				else
					{	U0THR = MyID|0x00;
						In_Send=0;U0IER |=0x02;
					}
				
			   }				
		   }
	   }
		
}	
	    Counter=0;
	    showPerfomance2();			 
		DispPG11(3);
		PerforStep(0);        //RunMode�ᱻ��ֵ
		volt=StartVolt2/10;
		if(StartMotor(StartTime,3))  //��ѹ����
		{
			nowClock=0;STAB=0;In_pause=0;
			if(num==0)             //a�������� ConstantTest2(uint16 a)��a
				showRun0();
			else
			{   showPG00();
				DispPG00();
				}
			while (KeyValue!=0xff)
					{ Read_Key(); }
			return;                   //�������
		}
		
		VTAB=0x00;HTAB=0x19;putString("     ");
		Counter=0;
        volt = TestVolt2/10;
		RunMotor(1,RunMode);          //���Ե�ѹ
		VTAB=0x70;				
		HTAB=0x00;putString("F1");verString( "��ʼ");	
		HTAB=0x08;putString("       ");	
		
	while (KeyValue!=0xff)
		{ Read_Key(); }
	
	pid0.SetPoint=Step2[Cycle].LoadValue;        //ÿ���׶εļ���ֵ��ֵ��SetPoint

	if(LoadType2==0)
	{	pid_tune((float)PidPara2.pid.pgain,
					(float)PidPara2.pid.igain,
					(float)PidPara2.pid.dgain,0,0);
	}
	else
	{	
		pid_tune(0.0,0.0,0.0,5,0);				
	}
	pid_bumpless();		
	Hot_Alarm=0;Hot_Count=0;
	
	while(1)
	{
		Read_Key();		
		if((KeyValue==F1)&&(!End_Test))//��F1��������û�н������Ե������
		{
			Bell();
			if(In_Test)          // In_Test�ǵ���1��  ��ʾ�ڲ��Թ�����
			{
				In_Test=0;Running=0;In_pause=1;//��ͣ
				End_Test=1;				
				Out_PWM(0);				
				RunMotor(0,0);				
				VTAB=0x70;HTAB=0x00;
				verString( "��  ֹ");				
				HTAB=0x09;putEng('F');putEng('3');				
				verString( "����");

				while(KeyValue!=0xff)//||(Button==0x01))
						{ Read_Key(); }				
			}
			else 		//���� In_Test�ǵ���0�������
			{
				EnableF=0;
				VTAB=0x70;HTAB=0x00;
				putString("F1");verString( "��ֹ");//��ʾ����һ�ΰ�F1����ֹ����
				HTAB=0x08;
				putString("       ");				

				VTAB=0x70;HTAB=0x13;								
				Second1=2;
				Alarm=0;
				KL_Counter=0;ZL_Counter=0;
				CycleCount=0;
			   	PerforStep(1);
				In_Test=1;Running=1;In_pause=0;
				while(KeyValue!=0xff)//||(Button==0x01))
						{ Read_Key(); }				
			}			
		}		
		else if((KeyValue==F3)&&!In_Test)
		{
			Bell();
			STAB=0;Running=0;	
			In_pause=0;End_Test=0;
			Out_PWM(0);			
			RunMotor(0,0);
			if(num==0) 
				showRun0();
			else 
				showPG00();	
			
			while (KeyValue!=0xff)
					{ Read_Key(); }
				return ;
		}

		if(FlagMs2)
		{
			FlagMs2=0;
			Read_ResultM();		
		}

		if(FlagMs100)
		{
			FlagMs100=0;	
			if(In_Test)
			{
				if(--Second1==0)
				{	Second1=10;
					if(Running)
						++nowClock;
					cClock=nowClock;
					shi = cClock / 3600;
					fen= (cClock%3600)/ 60;
					miao=(cClock-shi*3600-fen*60);
					//sprintf(sbuff,"%3d:",shi);
					//sprintf(sbuff+4,"%02d:",fen);
					//sprintf(sbuff+7,"%02d",miao);
					//VTAB=0x00;HTAB=0x15;
					//for(ii=0;ii<9;ii++)
						//putEng(*(sbuff+ii));
					//putBuff(sbuff);	
					
				}			
				
				if(++Counter>=Finish)      //Counter��ÿ100MS��һ��  Finishÿһ�׶εļ���ʱ��
				{	if(++Cycle<LastStep2)  //һ���׶ν���      Cycle���б仯��  
					{	          ///////////////////	
					    pid0.SetPoint = Step2[Cycle].LoadValue;
						PerforStep(1);
					}
					else
					{
						RunMotor(0,0);
						In_Test=0;
						Out_PWM(0);
						End_Test=1;In_Test=0;
						nowClock=0;
						Bell();
						VTAB=0x70;HTAB=0x08;
						HTAB=0x00;
						{verString(" �� ��");putEng(' ');}					
						HTAB=0x08;
						putString( "F3");
						verString( "����");				
					}	
				}				
			}			
			
			Read_ResultV();
		}
		if(FlagDisp)	
		{
			FlagDisp=0;
			DataAccess(0);
			if(--Second05==0)
			{	Second05=5;
				if(Alarm==0)
				{
					DispPG11(3);
				}	
				
			}				
			sprintf(sbuff,"%5.1f",(float)Counter/10);
			VTAB=0x48;HTAB=0x19;
			putString(sbuff);			
			
		}

		if(O_flag)
		{	O_flag=0;
			if(In_Test)
			{	if(pid0.runtype==0)
						pid_calc();
			}
		}

		/*if((Hot_Alarm)&&(End_Test==0))
		{	Bell();
			In_Test=0;Running=0;
			RunMotor(0,0);	
			Out_PWM(0);
			End_Test=1;
		
			VTAB=0x70;HTAB=0x00;
			verString("���ȱ���!");	
			putString("       ");
			HTAB=0x10;
			putString( "F3");
			verString( "����");
		}*/
			
		
		if(Uart0_OK)
		{
			Uart0_OK=0;
			switch (Uart0_Command)
			{	case 1:                        //����λ������0x91����
				{	U0THR = MyID|0x01;
					In_Send=0;U0IER |=0x02;
					if((In_Test==0)&&(End_Test==0))
					{	Bell();
						EnableF=0;
						VTAB=0x70;
						HTAB=0x00;putString(  "F1");
						verString(  "��ֹ");
						HTAB=0x08;
						putString("       ");    /////////////////////////
						//RunMotor(1,RunMode);     //����Ӧ��Ҳ����Ҫ������
						//Delay(200);
						VTAB=0x70;HTAB=0x13;								
						Second1=2;
						Alarm=0;
						KL_Counter=0;ZL_Counter=0;
						CycleCount=0;
					   	PerforStep(1);
						In_Test=1;Running=1;In_pause=0;
					}			
					break;
				}
				case 2:
				{	U0THR = MyID|0x02;
					In_Send=0;U0IER |=0x02;					
					if(In_Test) //Ҫ����ͣ
					{	Bell();
						In_Test=0;Running=0;In_pause=1;	
						End_Test=1;
						Out_PWM(0);			
						RunMotor(0,0);
						
						VTAB=0x70;HTAB=0x00;
						verString( "��  ֹ");				
						HTAB=0x09;putEng('F');putEng('3');				
						verString( "����");
					}
					break;
				}
				case 15:
				{
					UpLoadProg(1);          //�����ϴ����ղ���
					break;
				}
				case 5:
					{	if(In_Test)
								s_out(1);
						else
								s_out(0);					
						break;
					}
				case 11:
				{	U0THR = MyID|0x0b;
					In_Send=0;U0IER |=0x02;		
					if(In_Test==0)
					{	Bell();
						STAB=0;Running=0;
						In_pause=0;End_Test=0;
						Out_PWM(0);			
						RunMotor(0,0);
						if(num==0) 		showRun0();
						else 		showPG00();			
						nowClock=0;Total=0;
						return ;
					}
					break;
				}
				default:
				{	U0THR = MyID|0x00;
					In_Send=0;U0IER |=0x02;
				}
			}
		}
	
	}
}
/*===================================================*/
void PerforStep(uint16 a)
{	
    float result;
	VTAB=0x36;HTAB=0x1c;
	sprintf(sbuff,"%d",(Cycle));         //��ʾ�׶�
	putBuff(sbuff);	

	Counter=0;
	sprintf(sbuff,"%5.1f",(float)Counter/10.0);
	VTAB=0x48;HTAB=0x19;putString(sbuff);	
	Finish=(uint16)(Step2[Cycle].EndValue*10);
	  //pid0.SetPoint = Step2[Cycle].LoadValue;
	//pid0.SetPoint =SetS;                              ///////////        
	if(voltdir==1)
	   RunMode = 1;	     //RunMode = 1  ��ת             
	else
	   RunMode=2;        //��ת
	    
	if(a)
	{
		if(pid0.runtype==5)
		{	pid0.SetPoint2=1;	
			result=pid0.SetPoint*10;
			result=(result > 1000.0) ? 1000.0 : (result < 0.0 ? 0.0 : result);
			PWM1MR0=1000;
			PWM1MR3=1000-(uint32)result;
			PWM1LER=0x09;
		}
	}
}
/*******************************************************************/
char StartMotor(float sTime,uint16 a)
{		uint16 Start=0;

			VTAB=0x70;
			HTAB=0x00;putString("����...      ");
			

			RunMotor(1,RunMode);
			StartCount=(uint16)sTime*10;          //
	
			while(Start==0)
			{	Read_Key();
				if(KeyValue==F3)
				{	Bell();
					RunMotor(0,0);RunMode=0;
					STAB=0;					
					while (KeyValue!=0xff)
					{ Read_Key(); }
					return 1;
				}
				
				if(FlagMs2)
				{	Read_ResultM();		}	
				
				if(FlagMs100)
				{	FlagMs100=0;	
					Read_ResultV();
					++Counter;                    //0.1S
					VTAB=0x00;HTAB=0x19;
					sprintf(sbuff,"%5.1f",(float)Counter/10);
					VTAB=0x00;HTAB=0x19;putBuff(sbuff);
					if(Counter>=StartCount)
						Start=1;
				}
			
				if(FlagDisp)	
				{
					FlagDisp=0;
					DataAccess(0);
					if(--Second05==0)
					{	Second05=5;	
						if(a==0)									
							DispPG11(0);  //��ֵ
						else if(a==3)
							DispPG11(3);  //����
						//else if(a==2)
						//	DispPG11(2);  //����          //�������Counter��ʾ
						else if(a==1)     //�ֶ�
							DispPG11(1);
					}
				}
				
				if(Uart0_OK)
				{	Uart0_OK=0;
					if (Uart0_Command==5)
						s_out(0);
					else if(Uart0_Command==11)						
					{	Bell();
						U0THR = MyID|0x0b;
						In_Send=0;U0IER |=0x02;
						//nowClock=0;
						//In_pause=1;
						RunMotor(0,0);RunMode=0;
						STAB=0;							
						while (KeyValue!=0xff)
							{ Read_Key(); }
							return 1;
					}
					
					else
					{	U0THR = MyID|0x00;
						In_Send=0;U0IER |=0x02;
					}
				}				
			}	
			VTAB=0x70;
			HTAB=0x00;putString("              ");
			return 0;
}





