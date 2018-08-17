
#include "config.h"
 
uint8  Read_ResultV(void);
uint8 Read_ResultM(void);
void  SSP0_Isr(void);
void  SSP1_Isr(void);

extern void Delay(uint16 delayT);
extern float ReadSpeed(void);



#define SYNCHRONIZE		0xfeffffff //串口初始化
#define CLEARSTATUS		0xffffff5e
#define CURRENTGAIN		0x00ab6a44
#define VOLTAGEGAIN		0x00004048
#define SLOWER			0xa00f004a
#define TRANSSPEED		0x00

extern const U32 		Wresult[6];
extern U32 			Wbuf5460V,Rbuf5460V,Wbuf5460M,Rbuf5460M;
extern volatile uint16	Spi0Step,Spi0Byte,FlagDisp;
extern volatile uint16	Spi1Step,Spi1Byte;
extern U32			RresultV[6],RresultM[6];
extern U32			para[8],V32;
extern float Mx[200],M2Temp, MxTemp,PxTemp,Px[20],Mx2[200];
extern uint16 pT,pJ;
extern volatile uint16 O_flag,O_Count;

volatile uint32	state0,state1,spi0,spi1;
extern volatile uint16 FlagPid;
extern volatile uint16 In_Reading;

extern float KM,Ft,KM2,pFt,pFt2;
extern volatile uint16 FlagMs2;
extern uint16 Sx[12],pS,ZfZ[12],Zf;
extern uint32 SxTemp;
extern float pFs;
extern volatile uint16 Uart1_R_Count,Uart1_R_Len,Uart1_OK;

/*=====================================================================*/
uint8 Read_ResultM(void)
{	uint8	aa;

	FlagMs2=0;
	if(In_Reading==0)
	{
		while(1)
		{
			state1=SSP1SR;	
			if(state1 & 0x04)
				aa=SSP1DR;
			else		break;
		}
		FIO2CLR |= TORQ_CS;FIO2CLR |= TORQ_CS;
		
		SSP1IMSC = 0x04;
		SSP1ICR = 0x03;
		
		Spi1Step=0;Spi1Byte=1;                     //Wresult[0]=0xfeffffff    b8[3]=0xfe
		SSP1DR = Wresult[0].b8[0];SSP1DR = Wresult[0].b8[1]; //串口初始化 目的是使串口与SCLK同步
		SSP1DR = Wresult[0].b8[2];SSP1DR = Wresult[0].b8[3];	
		
		In_Reading=1;  //在读周期，当SDO引脚输出数据时，必须用SYNC0指令使SDI引脚处于选通状态
		return 0;
	}
	
	return 0xff;
}

/*=====================================================================*/
uint8 Read_ResultV(void)
{	uint8	aa;
	uint32 iSpeed;
/*****************************UART1读电压****************************/
	      Uart1_OK=0;
		  U1THR=0x55;
		  U1THR=0x00;
		  U1THR=0x10;
		  U1THR=0x65;	
		  Uart1_R_Count=0;
		  Uart1_R_Len=15;
		  FlagDisp=0;
/************************************************************/
	iSpeed =QEICAP;		
	SxTemp-=Sx[pS];
	Sx[pS]=iSpeed;
	SxTemp+=Sx[pS];               //5个之和
	
	pS=(pS>=4)?0:pS+1;		
	pFs=(float)SxTemp;
		
	while(1)
	{
		state0=SSP0SR;	
		if(state0 & 0x04)
			aa=SSP0DR;
		else		break;
	}
	FIO0CLR |= VOLT_CS;FIO0CLR |= VOLT_CS;
	
	SSP0IMSC = 0x04;
	SSP0ICR = 0x03;
	
	Spi0Step=0;Spi0Byte=1;
	SSP0DR = Wresult[0].b8[0];SSP0DR = Wresult[0].b8[1];
	SSP0DR = Wresult[0].b8[2];SSP0DR = Wresult[0].b8[3];	
	//FlagDisp=0;


	return aa;
}
 
/****************************************************************************/
void SSP0_Isr(void)
{  
	state0= SSP0SR;

	if((state0 & 0x04)&&Spi0Byte)
	{		RresultV[Spi0Step].b8[3]=SSP0DR;
			RresultV[Spi0Step].b8[2]=SSP0DR;
			RresultV[Spi0Step].b8[1]=SSP0DR;
			RresultV[Spi0Step].b8[0]=SSP0DR;
			if(Spi0Step<5)
			{
				FIO0SET  |= VOLT_CS;
				for(spi0=0;spi0<20;spi0++);
				FIO0CLR |= VOLT_CS;
				if(Spi0Step==3) Spi0Step=5;
				else	++Spi0Step;
				SSP0DR=Wresult[Spi0Step].b8[0];	
				SSP0DR=Wresult[Spi0Step].b8[1];
				SSP0DR=Wresult[Spi0Step].b8[2];
				SSP0DR=Wresult[Spi0Step].b8[3];				
			}
			else
			{
				FIO0SET  |= VOLT_CS;
				SSP0IMSC = 0x00;	//Disable Interrupt
				Spi0Step=0;
				Spi0Byte=0;
				FlagDisp=1;
				
			}
	}
	else
	{
		FIO0SET  |= VOLT_CS;
		SSP0IMSC = 0x00;	//Disable Interrupt
	}

	SSP0ICR = 0x03;
   	 // 中断处理结束
}  
/****************************************************************************/
void  SSP1_Isr(void)  
{ 	float Ft2;

	state1= SSP1SR;

	if((state1 & 0x04)&&Spi1Byte)
	{		RresultM[Spi1Step].b8[3]=SSP1DR;
			RresultM[Spi1Step].b8[2]=SSP1DR;
			RresultM[Spi1Step].b8[1]=SSP1DR;
			RresultM[Spi1Step].b8[0]=SSP1DR;
			if(Spi1Step<5)
			{
				FIO2SET  |= TORQ_CS;
				for(spi1=0;spi1<20;spi1++);
				FIO2CLR  |= TORQ_CS;
				if(Spi1Step==2) Spi1Step=4;
				else	++Spi1Step;
				SSP1DR=Wresult[Spi1Step].b8[0];	
				SSP1DR=Wresult[Spi1Step].b8[1];
				SSP1DR=Wresult[Spi1Step].b8[2];
				SSP1DR=Wresult[Spi1Step].b8[3];				
			}
			else
			{
				FIO2SET  |= TORQ_CS;
				SSP1IMSC = 0x00;	//Disable Interrupt
				Spi1Step=0;
				Spi1Byte=0;
				
				if(RresultM[4].b8[2]&0x80)       //判断最高位 正负的判断
				{	RresultM[4].b8[3]=0xff;				
					Ft = -(float)RresultM[4].a32 * KM;    //负的转矩调整成正的
					//Ft = (float)RresultM[4].a32 * KM;
				}
				else
				{	RresultM[4].b8[3]=0;				
					Ft = (float)RresultM[4].a32 * KM;
				}
				RresultM[2].b8[3]=0;	               //有效值都是正的
				Ft2 = (float)RresultM[2].a32 * KM2;

					pT=(pT>=199)?0:pT+1;
					MxTemp -= Mx[pT];
					Mx[pT]=Ft;
					MxTemp += Mx[pT];
					M2Temp -= Mx2[pT];
					Mx2[pT]=Ft2;
					M2Temp+=Mx2[pT];
						
					pJ=(pJ>=9)?0:pJ+1;
					PxTemp-=Px[pJ];
					Px[pJ]=Ft;
					PxTemp += Px[pJ];
					
				  O_Count=(O_Count)?0:1;
					if(O_Count==0) O_flag=1;    //转矩			
					
					FlagPid =1;		//在SSP1中断中会设定    		FlagPid =1;	
					In_Reading=0;
			}		
	}
	else
	{
		FIO2SET  |= TORQ_CS;
		SSP1IMSC = 0x00;	//Disable Interrupt
	}

	SSP1ICR = 0x03;   

}  




