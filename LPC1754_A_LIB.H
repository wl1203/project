/*********************************************/
extern volatile uint32 CtrlByte;
extern volatile uint16	DelayCount;
extern volatile uint32	KeyCount,KeyIn,LastKeyIn,KeyValue,B_In,LastBT,Button,FlagBT;
extern PID pid0;

extern U32	para[8],V32;

extern uint16 HTAB,VTAB;
extern uint8 Asc00[];
extern uint8 ZIKU00[];
extern uint8 chineseTab[];


/************************************************
HAL.C
*************************************************/

extern void targetInit (void);

extern uint8 IsFloat(float x);
extern void PWM_Init (uint16 Freq);	 // Freq=0 »ùÆµ12KHz
									 //Freq=1 »ùÆµ1KHz
									 //Freq=2 »ùÆµ2KHz
extern void Delay(uint16 delayT);
extern void Bell(void);
extern void Read_Key(void);
extern void pid_bumpless(void);
extern void Out_PWM(uint32 out);
extern uint32 pid_Proccesse(float error);

/********************************
I2C.C
*********************************/
extern uint8  ISendStr(uint8 sla, uint8 suba, uint8 *s, uint8 no);
extern uint8  IRcvStr(uint8 sla, uint8 suba, uint8 *s, uint8 no);
extern int32 zyIsrSet (unsigned int uiChannel, unsigned long ulFunction, unsigned int uiPrio);
extern void  I2C_Init(void);

/********************************
LCD.C
*********************************/
extern void init_Lcd(void);
extern void clear_Lcd(void); 
extern void putEng(uint8 c);
extern void verEng(uint8 c); 
extern void putHLine(uint8 line);
extern void putString(const char *cc);
extern void verString(const char *cc);
extern void putBuff(char *buf);
extern void verBuff(char *buf);
extern void putText(uint8 c);
extern void putTString(const char *cc);
extern void putBar(void);
extern void clrBar(void);
extern void nComd(uint8 c); 
extern void PLOT(uint8 x,uint8 y);
extern void LineTo(uint8 x1,uint8 y1,uint8 x2,uint8 y2);


/********************************
CS5460.C
*********************************/
extern void init_5460V(void);
extern void init_5460M(uint16 a);
extern void Calib_I_Zero(void);
extern void Calib_V_Zero(void);
extern void Calib_M_Zero(void);
extern uint8 W_R_VCP1(void);
extern uint8 W_R_VCP4(void);
extern uint8 W_R_Torque1(void);
extern uint8 W_R_Torque4(void);




