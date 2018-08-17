#ifndef __CONFIG_H 
#define __CONFIG_H

#include    "lpc1700.h"



/*********************************************************************************************************
  ͨ�ú궨��
*********************************************************************************************************/
#define DATABUSp       0x0000C713
#define DATABUSn	 0xffff38ec

#define KEY_IN1		0x00000020
#define KEY_IN2		0x00000040
#define KEY_IN3		0x00000100

#define CTRL        (1 << 22)
#define 	VOLT_CS		0x00400000		//p0.22
#define 	TORQ_CS 		0x00000008		//p2.3
#define	VOLT_RST		0x00000010		//p2.4



#ifndef TRUE
#define TRUE        1
#endif                                                                  /*  TRUE                        */

#ifndef FALSE
#define FALSE       0
#endif                                                                  /*  FALSE                       */

#ifndef NULL
#define NULL        0ul
#endif                                                                  /*  NULL                       */

/*********************************************************************************************************
  ������������޹ص���������
*********************************************************************************************************/
typedef unsigned char  BOOLEAN;                                         /*  ��������                    */
typedef unsigned char  INT8U;                                           /*  �޷���8λ���ͱ���           */
typedef unsigned char  uint8;

typedef signed   char  INT8S;                                           /*  �з���8λ���ͱ���           */
typedef signed   char  int8;

typedef unsigned short INT16U;                                          /*  �޷���16λ���ͱ���          */
typedef unsigned short uint16;      

typedef signed   short INT16S;                                          /*  �з���16λ���ͱ���          */
typedef signed   short int16;

typedef unsigned long  INT32U;                                          /*  �޷���32λ���ͱ���          */
typedef unsigned long uint32;
	
typedef signed   long  INT32S;                                          /*  �з���32λ���ͱ���          */
typedef signed   long  int32;

typedef float          FP32;                                            /*  �����ȸ�������32λ���ȣ�    */
typedef double         FP64;                                            /*  ˫���ȸ�������64λ���ȣ�    */



typedef  union _U32{
	int32	a32;
	uint8	b8[4];
	uint16	ui16[2];	
	float		f32;
}U32;

typedef  union _U16{
	uint16	a16;
	uint8	b8[2];
}U16;

typedef struct _pidP {
	uint16	pgain;
	uint16	igain;
	uint16	dgain;
	uint16	deadband;	
}PIDP;
typedef union u_pid {
	PIDP		pid;
	unsigned char	byte[sizeof(PIDP)];
}U_PID;	

typedef struct  _pid {
	uint32	runtype;
	//float		*pv;  /*pointer to an integer that contains the process value*/
	//float		*sp;  /*pointer to an integer that contains the set point*/	
	float		ProcessPoint;
	float		SetPoint;
	float		SetPoint2;
	float		pgain;
	float		igain;
	float		dgain;
	float 	deadband;
	float		last_error;
	float		Pterm;
	float 	integral;
	float		Dterm;
}PID;
  
typedef struct _STEP2 {
	unsigned char		RunMode;
	unsigned char		LoadMode;
	float				    LoadValue;	
	float				    EndValue;
	uint16			    Reserve;
}STEP2; 

/*********************************************************************************************************
  �̼����������, ��һ������Ķ�
*********************************************************************************************************/





/*********************************************************************************************************
  ϵͳʱ������
*********************************************************************************************************/
#define FUSBCLK_EN                  1                                   /*  ʹ��USBʱ��                 */
#define FOSC                        12000000                             /*  ����Ƶ��                  */
#define FCCLK                      (FOSC  * 8)                          /*  ��ʱ��Ƶ��12*8=96Mhz   <=100Mhz          */                                                                       
												   /*  FOSC��������                */
#define FCCO                       (FCCLK * 3)                          /*  PLLƵ��96*3=288Mhz      (275Mhz~550Mhz)      */
                                                                       		   /*  ��FCCLK��ͬ���������ż���� */
#define FPCLK                      (FCCLK / 4)                          /*  ����ʱ��Ƶ��,FCCLK��1/2��1/4   = 24Mhz       */
                                                                                       /*  ����FCCLK��ͬ               */
#define PLL_NVALUE                  1                                   /*  1~256                       */
#define PLL_MVALUE                ((FCCO / FOSC) * (PLL_NVALUE) / 2)    /*  6~512   288/12*(1/2)=12                    */

#if FUSBCLK_EN == 1
#define FUSBCLK                     48000000                            /*  ����Ϊ48000000              */
#endif                                                                  /*  USE_USB                     */


#endif

/********************************************************************************************************
**                                      End Of File
********************************************************************************************************/
