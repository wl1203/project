

#include "main.h"
#include <math.h>


#define BEEP_BIT      0x00008000
float	error,result;

extern PID pid0;
extern uint16 M_point,Gs;
extern float PxTemp,Fc,pFt,xFs,xFt;
extern float pFs,Po,Fp;
extern volatile uint32 CtrlByte;
extern volatile uint16	DelayCount;


extern U32 Export;
extern void  SSP0_Isr(void);
extern void  SSP1_Isr(void);



/********************************************************************************************************/

void pinInit (void)
{	PCONP = PCGPIO_Enable;	

    /*
     * 引脚连接配置P0.00 -- P0.15
     */
    PINSEL0  = (P0_15_FNUC << 30)|
               (P0_11_FNUC << 22)|(P0_10_FNUC << 20)|(P0_9_FNUC << 18) |(P0_8_FNUC << 16) |
               (P0_7_FNUC << 14) |(P0_6_FNUC << 12) | (P0_5_FNUC << 10)|(P0_4_FNUC << 8)  |
               (P0_3_FNUC << 6)  |(P0_2_FNUC << 4)  |(P0_1_FNUC << 2)  |(P0_0_FNUC << 0);

    /*
     * 引脚连接配置P0.16 -- P0.30
     */
    PINSEL1  = (P0_30_FNUC << 28)|(P0_29_FNUC << 26)|(P0_28_FNUC << 24)|(P0_27_FNUC << 22)|
               (P0_26_FNUC << 20)|(P0_25_FNUC <<18) |(P0_24_FNUC <<16) |(P0_23_FNUC <<14) |
               (P0_22_FNUC <<12) |(P0_21_FNUC << 10)|(P0_20_FNUC << 8) |(P0_19_FNUC << 6) |
               (P0_18_FNUC << 4) |(P0_17_FNUC << 2) |(P0_16_FNUC << 0);
    
    /*
     * 引脚连接配置P1.0 -- P1.15
     */
    PINSEL2  = (P1_15_FNUC << 30)|(P1_14_FNUC << 28)|(P1_10_FNUC << 20)|(P1_9_FNUC << 18)|
               (P1_8_FNUC  << 16)|(P1_4_FNUC << 8)  |(P1_1_FNUC << 2)  |(P1_0_FNUC << 0);

    /*
     * 引脚连接配置P1.16 -- P1.31
     */
    PINSEL3  = (P1_31_FNUC << 30)|(P1_30_FNUC << 28)|(P1_29_FNUC << 26)|(P1_28_FNUC << 24)| 
               (P1_27_FNUC << 22)|(P1_26_FNUC << 20)|(P1_25_FNUC << 18)|(P1_24_FNUC << 16)|
               (P1_23_FNUC << 14)|(P1_22_FNUC << 12)|(P1_21_FNUC << 10)|(P1_20_FNUC << 8) |
               (P1_19_FNUC << 6) |(P1_18_FNUC << 4) |(P1_17_FNUC << 2) |(P1_16_FNUC << 0);

    /*
     * 引脚连接配置P2.0 -- P2.13
     */       
    PINSEL4  = (P2_13_FNUC << 26)|(P2_12_FNUC << 24)|(P2_11_FNUC << 22)|(P2_10_FNUC << 20)|
               (P2_9_FNUC << 18) |(P2_8_FNUC  << 16)|(P2_7_FNUC << 14) |(P2_6_FNUC << 12) | 
               (P2_5_FNUC << 10) |(P2_4_FNUC << 8)  |(P2_3_FNUC << 6)  |(P2_2_FNUC << 4)  |
               (P2_1_FNUC << 2)  |(P2_0_FNUC << 0);
    
    /*
     * 引脚连接配置P3.25 -- P3.26
     */
    PINSEL7  = (P3_26_FNUC << 20)|(P3_25_FNUC << 18);

    /*
     * 引脚连接配置P4.28 -- P4.29
     */
    PINSEL9  = (P4_29_FNUC <<26) | (P4_28_FNUC <<24);

    PINSEL10 = P10_3_FNUC;                                              /*  禁止ETM接口功能             */
#if 1

    /*
     * 引脚内部上下拉电阻配置
     */
    PINMODE0 = (P0_15_MODE << 30)|(P0_14_MODE << 28)|(P0_13_MODE << 26)|(P0_12_MODE << 24)|
               (P0_11_MODE << 22)|(P0_10_MODE << 20)|(P0_9_MODE << 18) |(P0_8_MODE << 16) |
               (P0_7_MODE << 14) |(P0_6_MODE << 12) |(P0_5_MODE << 10) |(P0_4_MODE << 8)  |
               (P0_3_MODE << 6)  |(P0_2_MODE << 4)  |(P0_1_MODE << 2)  |(P0_0_MODE << 0);
    
    PINMODE1 = (P0_30_MODE << 28)|(P0_29_MODE << 26)|(P0_28_MODE << 24)|(P0_27_MODE << 22)|
               (P0_26_MODE << 20)|(P0_25_MODE << 18)|(P0_24_MODE << 16)|(P0_23_MODE << 14)|
               (P0_22_MODE << 12)|(P0_21_MODE <<10) |(P0_20_MODE << 8) |(P0_19_MODE << 6) |
               (P0_18_MODE << 4) |(P0_17_MODE << 2) |(P0_16_MODE << 0);
            
    PINMODE2 = (P1_15_MODE << 30)|(P1_14_MODE << 28)|(P1_13_MODE << 26)|(P1_12_MODE << 24)|
               (P1_11_MODE << 22)|(P1_10_MODE << 20)|(P1_9_MODE << 18) |(P1_8_MODE << 16) |
               (P1_7_MODE << 14) |(P1_6_MODE << 12) |(P1_5_MODE << 10) |(P1_4_MODE << 8)  |
               (P1_3_MODE << 6)  |(P1_2_MODE << 4)  |(P1_1_MODE << 2)  |(P1_0_MODE << 0);
     
    PINMODE3 = (P1_31_MODE << 30)|(P1_30_MODE << 28)|(P1_29_MODE << 26)|(P1_28_MODE << 24)|
               (P1_27_MODE << 22)|(P1_26_MODE << 20)|(P1_25_MODE << 18)|(P1_24_MODE << 16)|
               (P1_23_MODE << 14)|(P1_22_MODE << 12)|(P1_21_MODE << 10)|(P1_20_MODE << 8) |
               (P1_19_MODE << 6) |(P1_18_MODE << 4) |(P1_17_MODE << 2)|(P1_16_MODE << 0);

    PINMODE4 = (P2_15_MODE << 30)|(P2_14_MODE << 28)|(P2_13_MODE << 26)|(P2_12_MODE << 24)|
               (P2_11_MODE << 22)|(P2_10_MODE << 20)|(P2_9_MODE << 18) |(P2_8_MODE << 16) | 
               (P2_7_MODE << 14) |(P2_6_MODE << 12) |(P2_5_MODE << 10) |(P2_4_MODE << 8)  |
               (P2_3_MODE << 6)  |(P2_2_MODE << 4)  |(P2_1_MODE << 2)  |(P2_0_MODE << 0);

    PINMODE7 = (P3_26_MODE << 20)|(P3_25_MODE << 18);
    
    PINMODE9 = (P4_29_MODE << 26)|(P4_28_MODE << 24);
#endif

    FIO0MASK =0x00;                                                     /*  不屏蔽引脚高速功能         */
    FIO1MASK =0x00;
    FIO2MASK =0x00;
    FIO3MASK =0x00;
    FIO4MASK =0x00;

	FIO0DIR = 0x00400000;					  /* VOLT_CS */
	FIO0SET = 0xffffffff;

	FIO1DIR = 0x36480000;					  /* LCD WR/RD/CD/RST/CS/CTRL */
	FIO1SET = 0xffffffff;

	FIO2DIR = 0x00000178;					 /* KKEYIN3/KEYIN2/KEYIN1/VOLT_RST/TORQ_CS*/
	FIO2SET = 0xffffffff;

	
}


/*********************************************************************************************************/
void timer0Init (void)
{	
    PCONP =       PCONP | PCTIM0_Enable;			
    T0TCR  = 0x02;
    T0IR   = 1;
    T0CTCR = 0;
    T0TC   = 0;
    T0PR   = 0;
    T0MR0  = FPCLK/200;                  /* 5mS    中断1次                  */
    T0MCR  = 0x03;                       /* 匹配后产生中断               */
    
    zyIsrSet(NVIC_TIMER0, (unsigned long)Timer0Isr, PRIO_THREE);          /* 设置中断并使能               */	
    T0TCR  = 0x01;                                                      /* 启动定时器                   */
  

//////////////////////////////////////////////////////////////////////////////

	PCONP =       PCONP | PCTIM2_Enable;	
   	T2TCR  = 0x02;	//RESET
	//T2IR   = 1;
	T2CTCR = 0;	
	T2PR   = 143999;		/* 24Mhz/144000=166.67Hz	,T=6ms     */
	T2MCR  = 0x00;           /* Disable 匹配后产生中断               */    
	
    	T2TC   = 0;
    	T2TCR  = 0x00;                                                      /* 暂不启动定时器                   */	

		
}

/********************************************************************************************************/
void uartInit (void)
{
    INT16U ulFdiv;
#define UART_BPS	9600

    PCONP = PCONP | PCUART0_Enable;
    
    U0LCR  = 0x83;                                                      /*  允许设置波特率              */
    ulFdiv = (FPCLK / 16) / 9600;                                   /*  设置波特率                  */
    U0DLM  = ulFdiv / 256;
    U0DLL  = ulFdiv % 256; 
    U0LCR  = 0x03;                                                      /*  锁定波特率                  */
    U0FCR  = 0x01;                                                      /*  使能FIFO，设置8个字节触发点 */	
	
    U0IER  = 0x01;                                                      /*  使能接收中断                */
    zyIsrSet(NVIC_UART0,(unsigned long)Uart0Isr,PRIO_ONE);
	
	PCONP = PCONP | PCUART1_Enable;
			
				U1LCR  = 0x83;														/*	允许设置波特率			   */
			ulFdiv = (FPCLK / 16) / UART_BPS;									/*	设置波特率 				 */
			U1DLM  = ulFdiv / 256;
			U1DLL  = ulFdiv % 256; 
			U1LCR  = 0x03;														/*	锁定波特率 				 */
			U1FCR  = 0x01;														/*	使能FIFO，设置8个字节触发点 */
			U1RS485CTRL 	=0x10;
			//U1RS485CTRL		=0x30;
			U1RS485DLY		=0x00;
			
			U1IER  = 0x01;														/*	使能接收中断				  */
			zyIsrSet(NVIC_UART1,(unsigned long)Uart1Isr,PRIO_TWO);	
	
			PCONP = PCONP | PCUART3_Enable;
			   
			   U3LCR  = 0x83;													   /*  允许设置波特率			  */
			   ulFdiv = (FPCLK / 16) / 9600;								   /*  设置波特率					*/
			   U3DLM  = ulFdiv / 256;
			   U3DLL  = ulFdiv % 256; 
			   U3LCR  = 0x03;													   /*  锁定波特率					*/
			   U3FCR  = 0x01;													   /*  使能FIFO，设置8个字节触发点 */   
			
			   U3IER  |= 0x02;													   /*  使能接收中断  */
	


}


/****************************************************************************/
void  SpiInit(void)
{ 	

	PCONP = PCONP | PCSSP0_Enable;
	
	SSP0CR0 = 0x0187;		//SCR=1,CPHA=0,CPOL=1,FRF=00=SPI,DSS=7=8Bit
	SSP0CR1 = 0x02;			//SOD=0,MS=0=Master,SSE=1=EnableSSP,LBM=0
	SSP0CPSR = 0x24;		//24MHz/48 = 500KHz

	SSP0IMSC = 0x00;	
	SSP0ICR = 0x03;

	zyIsrSet(NVIC_SSP0, (unsigned long)SSP0_Isr, PRIO_TWO);	

	PCONP = PCONP | PCSSP1_Enable;
	SSP1CR0 = 0x0187;		//SCR=1,CPHA=0,CPOL=1,FRF=00=SPI,DSS=7=8Bit
	SSP1CR1 = 0x02;			//SOD=0,MS=0=Master,SSE=1=EnableSSP,LBM=0
	SSP1CPSR = 0x24;		//24MHz/48 = 500KHz

	SSP1IMSC = 0x00;	
	SSP1ICR = 0x03;

	zyIsrSet(NVIC_SSP1, (unsigned long)SSP1_Isr, PRIO_TWO);    
	

}

/************************************************************/
void Init_QEI(void)
{	PCONP = PCONP |PCQEI_Enable;
	
						
	QEICON   = 0x0f;	      /*复位*/
	QEICONF = 0x04;          /*配置*/
	
	QEILOAD =  2400000;	    //24000000/2400000=10Hz, T=1/10 Sec    (100ms)
							//1/10 Sec 读得的脉冲数=(n/60)*60*2*(1/10)=0.2n
	
	QEIMAXPSOS = 0xffffffff;
						
		QEICLR	= 0xffffffff;					
		QEIIEC=0xffffffff;
		//QEIIES=0x40;					
		QEICON   = 0x0f;	/*复位*/	
		QEICLR	= 0xffffffff;	


}



/*------------------------------------------------------------------------*/
void pid_tune(float P,float I,float D,uint16 DB,uint16 Type)
{	
	pid0.runtype=DB;
			
	switch(DB)
	{	case 0:
		{	/*switch(M_point)
			{	case 0:
				{	pid0.pgain = P;
					pid0.igain  = I/25;
					pid0.dgain = D/25;
					pid0.deadband = 0.1;
					break;				}
				case 1: case 2:
				{	pid0.pgain = P*10;
					pid0.igain  = I/2.5;
					pid0.dgain = D/2.5;
					pid0.deadband = 0.01;
					break;				}
				case 3: case 4:
				{	pid0.pgain = P*100;
					pid0.igain  = I*4;
					pid0.dgain = D*4;
					pid0.deadband = 0.001;
					break;				}
			}*/

			pid0.pgain = P*2;
			pid0.igain  = I/12.5;
			pid0.dgain = D/12.5;
			pid0.deadband = 0.01;			
			break;				
		}
	
		case 1:
		{	pid0.pgain = P/10.0;
			pid0.igain  = I/50.0;
			pid0.dgain = D/50.0;
			pid0.deadband = 0.01;
			break;
		}
		case 3: 
		{	pid0.pgain = P/1000.0;
			pid0.igain  = I/5000.0;
			pid0.dgain = D/5000.0;
			pid0.deadband = 0.5;				
			break;
		}
		case 4: 
		{	pid0.pgain = P/200.0;
			pid0.igain  = I/1000.0;
			pid0.dgain = D/1000.0;
			pid0.deadband = 0.5;	
			break;
		}  		
		default:
		{	pid0.pgain = 0.0;
			pid0.igain  = 0.0;
			pid0.dgain = 0.0;
			pid0.deadband = 1000;	

		}
	}	
	if(Type==0)
	{	pid0.integral=0.0;
    		pid0.last_error=0;
	}
}

/*-----------------------------------------------------------------------*/	
void pid_calc(void)          //PID计算部分
{	//float nFt;

	if(pid0.runtype==0)
	{	//nFt = PxTemp/100.0;
		//pid0.ProcessPoint = (nFt<0)?-nFt:nFt;
		pid0.ProcessPoint = PxTemp*0.2;          //(5v*10)*2/10=10Nm
		
	}
	else if(pid0.runtype==1)
			pid0.ProcessPoint = Fc;
	else if(pid0.runtype==3)
			pid0.ProcessPoint = Fp;	
	else if(pid0.runtype==4)
			pid0.ProcessPoint = Po;	
    	else 
	{	Out_PWM(0);
		return;
	}
    error = pid0.SetPoint-pid0.ProcessPoint;   	
   
    Out_PWM(pid_Proccesse(error));
    
}
/*********************************************************************************************************
    End Of File
*********************************************************************************************************/

