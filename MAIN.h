#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "config.h"
#include "HAL.h"
#include "Lpc1754_a_lib.h"


#define F1	0x0c                         
#define F2	0x0d                         
#define F3	0x0e                         
#define F4	0x0f
#define GO_L	0x0a 
#define GO_R	0x0b     
#define Zero	0x00



typedef struct _STEP {
	unsigned char		runmode;
	unsigned int		volt;
	unsigned char		loadtype;
	float				loadvalue;	
	unsigned char		endmode;	
	float				endvalue;
}STEP;




typedef struct _IN_ROT {
	unsigned char		onoff;
	unsigned char		start;
	unsigned char		end;
	int				times;	
	unsigned char		idlemode;	
	float				endvalue;
}IN_ROT;


void DataAccess(uint16 a);
void DispPG00(void);
void DispPG01(void);
void RunFirst(void);
void RunMotor(uint16 onoff,uint16 type);
char StartMotor(float sTime,uint16 a);

void Torque_Access(void);


void ConstantTest0(void);
char ConstantTest1(void);
void ConstantTest2(uint16 a);
void DispPG11(uint16 a);
void showConstSet(uint16 a);

void Performance(void);
char Performance1(void);
void Performance2(uint16 a);
void disp_line2(char x);
void showPerfoSet(void);
void ShowPerforData(char Type);
void s_out(char type);
char DownLoadProg(uint16 a);
void UpLoadProg(uint16 a);
void ReLoad2(uint16 a);
void GoNext(void);
void GoNext2(void);
void RunStep(uint16 a);
void RunStep2(uint16 a);
int   RunTest1(uint8 num);
int  RunTest2(uint8 num);
void PerforStep(uint16 a);

void DispTestData(uint16 a);
void Manual(uint16 a);
void Manual0(void);
void ManualSeting(void);
void showManualSeting(void);





void Performance3(void);
char Performance31(void);
void Performance32(void);
void showPerfoSet3(void);
void AsynchAutoRun(void);
void NormalFirst(void);
uint16 DownLoadProg2(void);

uint8 Read_ResultM(void);
void RBH_Test0(void);
char RBH_Test1(void);
void RBH_Test2(uint16 a);
void showRBHSet(void);





extern void showPG000(void);		//起始页
extern void showPG001(void);		//语言选择
extern void showPG00(void);		//等待
extern void showCalib02(void);
extern void showPGRun1(void);	//专项测试
extern void showPassWord(void);
extern void showSet0(void);
extern void showAdj0(void);
extern void showRun0(void);
extern void showMyID(void);
extern void showDynamo(void);
extern void showCalib00(void);
extern void showCalib01(void);
extern void showScale(void);
extern void showPID0(void);
extern void showPID(void);

extern void showPower(void);
extern void showPerfomance1(char p);
extern void showPerfomance2(void);
extern void showDynaCalib(void);
extern void showPG_SetTestA1(char p);
extern void showPG_SetTestA2(void);
extern void showPG_SetTestA3(void);
extern void showConstant1(uint16 a);
extern void showConstant3(void);

extern void showConstant2(void);
extern void showPG_Manual(void);
extern void showPG_Manual0(void);
extern void ManualSetingDisplay(void);

extern void showPG_RBH1(void);
extern void showPG_RBH2(void);


extern unsigned char PassWord(void);
extern void	calibrate(void);
extern void calib01(void);
extern void calib02(void);
extern void calib03(void);
extern void showCalib(float temp1,uint16 a);
extern void CalibCurrent(void);
extern void CalibVolt(void);
extern void CalibTorque(void);
extern void calibZero(void);

extern void SetDynamo(void);
extern void displayDynamo(void);
extern void AdjFirst(void);
extern void SetFirst(void);
extern void SetTestA(void);
extern void SetPID0(void);
extern void SetPID(void);
extern void displayPID(void);
extern void displayPID2(void);
extern void RunPID(uint16 type);
extern void checkPID(void);
extern void CalibDynamo(void);
extern void disp_line(char x);
extern void disp_Curser(char point,char position);
extern void ParaAccess(uint16 a);
extern void Read_Result(void);
extern void SetMyId(void);
extern void SetPower(void);
extern void showPara_SetTestA(void);



                                    
/*  HAL.c  */
extern void pinInit(void);
extern void pconpInit(void);
extern void timer0Init (void);
extern void Timer0Isr (void);
extern void uartInit(void);
extern void Uart0Isr (void);
extern void Uart1Isr (void);
//extern void Uart3Isr (void);
extern void uart0DmaInit(void);
extern void uart0DmaSend(INT32U ulNum);
extern void  SpiInit(void);
extern uint8 IsFloat(float x);
extern void Init_QEI(void);
extern void QEI_Isr (void);
extern void Timer1Isr (void);
extern void Read_Posi(void);

/*Cs5460.c */

extern  uint8 Read_ResultV(void);

//extern  void Read_Resultv(void);



#endif


