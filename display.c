//Display.c


#include "config.h"
#include "main.h"


extern uint16 HTAB,VTAB;
extern uint8  EndMode,MyID;
extern uint16	shi,fen,miao;
extern IN_ROT 	in_rot;



void showPG000(void);		//起始页
void showPG001(void);		//语言选择
void showPG00(void);		//等待

void showPGRun1(void);	//专项测试
void showPassWord(void);
void showSet0(void);
void showRun0(void);
void showMyID(void);
void showDynamo(void);
void showCalib00(void);
void showCalib01(void);
void showCalib05(void);
void showScale(void);
void showPID0(void);
void showPID(void);

void showPower(void);
void showPerfomance1(char p);
void showPerfomance2(void);
void showDynaCalib(void);
void showPG_SetTestA1(char p);
void showPG_SetTestA2(void);
void showPG_SetTestA3(void);
void showConstant1(uint16 a);
void showConstant3(void);
void showConstant2(void);
void showPG_Manual(void);
void showPG_Manual0(void);
void ManualSetingDisplay(void);

void showBreak1(void);
void showBreak2(void);

/*===================================================*/
void showPG000(void)	//起始页
{
	clear_Lcd();
	HTAB=0x07;VTAB=0x0c;
	putString("电机专项试验系统");
	HTAB=0x07;VTAB=0x1c;
	putString(  "Motor Test System");
	HTAB=0x05;VTAB=0x2c;
	putString(  "安规机电设备有限公司");
	HTAB=0x05;VTAB=0x3c;
	putString(  "Angui Mechanical and");
	HTAB=0x05;VTAB=0x4c;
	putString(  "Electrical Equipment");
	HTAB=0x06;VTAB=0x60;
	putString(  "Version DGWD.1807");

	VTAB=0x70;
	HTAB=0x00;verString(  "中  国");
	HTAB=0x18;verString(  "上  海");
	
}
/*===================================================*/
void showPG00(void)		//等待
{
	clear_Lcd();
	HTAB=0x00;VTAB=0x00;
	putString(  "电机专项试验系统");
	putHLine(0x10);	
	{	HTAB=0x06;VTAB=0x12;putString(  "电压");
			HTAB=0x14;putString(  "V");
			HTAB=0x06;VTAB=0x24;putString(  "电流");
			HTAB=0x14;putString(  "A");
			HTAB=0x06;VTAB=0x36;putString(  "功率");
			HTAB=0x14;putString(  "W");	
			VTAB=0x48;
			HTAB=0x06;putString(  "转速");
			HTAB=0x14;putString(  "RPM  ");	
			VTAB=0x5a;
			HTAB=0x06;putString(  "转矩");
			HTAB=0x14;
			putString(  "Nm ");			
			
	}	


	VTAB=0x70;
	HTAB=0x00;
	putString(  "F1");verString(  "测试");	
	HTAB=0x08;
	putString(  "F2");verString(  "设定");		
	HTAB=0x18;
	putString(  "F4");verString(  "校准");	
				
}
/*===================================================*/
void showPassWord(void)
{
		clear_Lcd();
		HTAB=0;VTAB=0;
		putString( "请输入密码");
		
		putHLine(0x10);		

		VTAB=0x30;HTAB=0x0D;
		verEng('*');
		putString( "***");
		
		VTAB=0x70;HTAB=0x10;putString("F3");
		verString("返回");
		HTAB=0x18;putString("F4");
		verString("确认");		
}

/*=================================================*/
void showCalib00(void)
{		
	clear_Lcd();	
	{
		HTAB=0x00;VTAB=0x00;
		putString( "系统校准");
		putHLine(0x10);
		
		HTAB=0x08;VTAB=0x14;
		putString( "[1] 转矩表校准");
		//putString( "[1] 电流表校准");	
		HTAB=0X09;verEng('1');
		//HTAB=0x08;VTAB=0x26;
		//putString( "[2] 电压表校准");	
		//HTAB=0x08;VTAB=0x38;
		//putString( "[3] 转矩表校准");	
		
				
	}
	VTAB=0x70;
	//HTAB=0x00;putString( "F1");verString( "移动");
	HTAB=0x10;putString( "F3");verString( "返回");
	HTAB=0x18;putString( "F4");verString( "确认");	
}

/*==============================================*/
void showCalib01(void)
{
		clear_Lcd();
		
		HTAB=0x00;VTAB=0x00;
		putString( "转矩表校准");
		putHLine(0x10);	
		HTAB=0x08;VTAB=0x20;
		putString( "[1] 零位校准");	
		HTAB=0X09;verEng('1');
		HTAB=0x08;VTAB=0x38;
		putString( "[2] 刻度调整");	
			
		VTAB=0x70;
		HTAB=0x00;putString( "F1");verString( "移动");		
		HTAB=0x10;putString( "F3");verString( "返回");
		HTAB=0x18;putString( "F4");verString( "确认");
}


/*=========================================*/
void showScale(void)
{		clear_Lcd();
		
		{			
			HTAB=0x00;VTAB=0x00;
			putString( "转矩表刻度调整");
			putHLine(0x10);	
			
			HTAB=0x04;VTAB=0x28;
			putString( "当  前  值");	
			HTAB=0x04;VTAB=0x48;
			putString( "输入准确值");	
			HTAB=0x18;VTAB=0x28;
			putString(  "V");
			HTAB=0x18;VTAB=0x48;
			putString(  "V");		
		
				
		}
		VTAB=0x70;		
		HTAB=0x10;putString( "F3");verString( "返回");
		HTAB=0x18;putString( "F4");verString( "确认");
		
}

/*=====================================*/
void showSet0(void)
{
	clear_Lcd();
	{
		HTAB=0x00;VTAB=0x00;
		putString(  "参数设置");
		putHLine(0x10);
	
		HTAB=0x06;VTAB=0x18;
		putString(  "[1]  PID 参数调整");		
		HTAB=0x07;verEng('1');		
		HTAB=0x06;VTAB=0x2c;
		putString(  "[2]  测功机标定");
		HTAB=0x06;VTAB=0x40;
		putString(  "[3]  电源调整");	
		
	}
	VTAB=0x70;
	HTAB=0x00;putString(  "F1");verString(  "移动");
	HTAB=0x10;putString(  "F3");verString(  "返回");
	HTAB=0x18;putString(  "F4");verString(  "确认");	
}

/*======================================*/
void showRun0(void)
{
	clear_Lcd();
	{
		HTAB=0x00;VTAB=0x00;
		putString(  "试验选择");
		putHLine(0x10);	
		HTAB=0x06;VTAB=0x14;
		putString(  "[1] 出厂试验");
		HTAB=0x07;verEng('1');
		HTAB=0x06;VTAB=0x26;
		//putString(  "[2] 热保护试验");
		putString(  "[2] 恒值试验");	
		HTAB=0x06;VTAB=0x38;		
		putString(  "[3] 手动测试");
		HTAB=0x06;VTAB=0x4a;		
		putString(  "[4] 特性测试");		
		
	}
	VTAB=0x70;
	HTAB=0x00;putString(  "F1");verString(  "移动");
	HTAB=0x10;putString(  "F3");verString(  "返回");
	HTAB=0x18;putString(  "F4");verString(  "确认");	
}


/*============================================*/

void showPID(void)
{
		clear_Lcd();
		
		{
			HTAB=0x00;VTAB=0x00;
			putString( "PID 参数调整");
			putHLine(0x10);
			HTAB=0x01;VTAB=0x12;
			putString( "P:");	
			HTAB=0x01;VTAB=0x24;
			putString( "I:");
			HTAB=0x01;VTAB=0x36;
			putString( "D:");
			HTAB=0x0c;VTAB=0x12;
			verString( "恒");
			HTAB=0x0c;VTAB=0x24;
			putString( "设定值");
			HTAB=0x0c;VTAB=0x48;
			putString( "即时值");			
			
		
		}
		VTAB=0x70;	
		HTAB=0x00;putString( "F1");verString( "移动");
		HTAB=0x08;putString( "F2");verString( "选择");
		HTAB=0x10;putString( "F3");verString( "返回");
		HTAB=0x18;putString( "F4");verString( "确认");
}


/****************************************************/
void showPGRun1(void)	//专项测试
{
	clear_Lcd();
		putHLine(0x10);
		putHLine(0x23);
		putHLine(0x35);
		putHLine(0x47);
		putHLine(0x59);
		putHLine(0x6b);
		
		HTAB=0x00;VTAB=0x00;
		putString(  "电机出厂试验:");		
	
		VTAB=0x12;
		HTAB=0x00;putString(  "电压");
		HTAB=0x0d;putString(  "V");//HTAB=0x15;putString(  "V");
		//HTAB=0x1d;putString(  "V");
		VTAB=0x24;
		HTAB=0x00;putString(  "电流");
		HTAB=0x0d;putString(  "A");//HTAB=0x15;putString(  "A");
		//HTAB=0x1d;putString(  "A");	
		VTAB=0x36;
		HTAB=0x00;putString(  "功率");
		HTAB=0x0d;putString(  "W");
		
		VTAB=0x48;
		HTAB=0x00;putString(  "转速");
		HTAB=0x0d;putString(  "RPM");
		HTAB=0x12;putString(  "状态     T 1");		
		
		VTAB=0x5a;
		HTAB=0x00;putString(  "转矩");
		HTAB=0x0d;putString(  "Nm ");
		HTAB=0x12;putString(  "定时");
		
		VTAB=0x70;
		HTAB=0x00;putString(  "F1");verString(  "开始");
		HTAB=0x09;putString(  "F3");verString(  "返回");

	
}

/*============================================*/
void showDynamo(void)
{		clear_Lcd();
		
		{
			VTAB=0x00;HTAB=0x00;
			putString( "电机选择");
			putHLine(0x10);
				
			
			
			VTAB=0x30;
			

			
		}
		VTAB=0x70;
		HTAB=0x08;putString( "F2");verString( "选择");
		HTAB=0x10;putString( "F3");verString( "返回");
		HTAB=0x18;putString( "F4");verString( "确认");		
}

/*============================================*/
void showDynaCalib(void)
{

		clear_Lcd();
		
		{			
			HTAB=0x00;VTAB=0x00;
			putString( "测功机标定");
			putHLine(0x10);
				
			HTAB=0x06;VTAB=0x24;
			putString( "转矩");	
			HTAB=0x14;//putString(  "mNm");
				putString(  "Nm ");
			HTAB=0x06;VTAB=0x40;
			putString( "负载率");
			HTAB=0x14;putEng('%');
			
			VTAB=0x70;HTAB=0x0a;
			verString( "运行");		
			HTAB=0x12;
			verString( "返回");		
		}	
		VTAB=0x70;
		HTAB=0x00;putString("<-");verString("(-)");
		HTAB=0x19;putString("->");verString("(+)");
		
		VTAB=0x70;
		HTAB=0x08;putString( "F2");
		HTAB=0x10;putString( "F3");
		
}

/*=====================================*/
void showConstant1(uint16 a)
{
		clear_Lcd();
		HTAB=0x00;VTAB=0x00;
			putString(  "电机恒值试验:");		
			putHLine(0x10);		
			if(a==1)
		   {
				VTAB=0x12;HTAB=0x08;
				putString(  "控制方式--");				
				
				VTAB=0x24;HTAB=0x13;
				putString(  "PID参数:");
				VTAB=0x36;HTAB=0x13;
				putString(  "P");
				VTAB=0x48;
				HTAB=0x00;putString(  "试验时间");
				HTAB=0x13;putString(  "I");
				VTAB=0x5a;
				HTAB=0x0a;putString(  "Sec");
				HTAB=0x13;putString(  "D");
			}
		    else if(a==2)
		    {
		    	VTAB=0x24;HTAB=0x00;
				putString(  "起动时间");				
				
				VTAB=0x36;HTAB=0x00;
				putString(  "试验电压");
				VTAB=0x48;HTAB=0x00;
				putString(  "起动电压");
		    }
				VTAB=0x70;
				HTAB=0x00;
				putString("F1");
				verString("移动");
				
				HTAB=0x10;
				putString("F3");
				verString("返回");
				HTAB=0x17;
				putString("F4");
				verString("测试");
		//}
		
}	
/*=====================================*/
void showConstant3(void)
{
		clear_Lcd();
		HTAB=0x00;VTAB=0x00;	
		{
			putString(  "电机恒值试验:");		
			putHLine(0x10);		
			
				VTAB=0x24;HTAB=0x00;
				putString(  "启动电压");				
				
				VTAB=0x36;HTAB=0x00;
				putString(  "启动时间");
				VTAB=0x48;HTAB=0x00;
				putString(  "试验电压");
				VTAB=0x70;
				HTAB=0x00;
				putString("F1");
				verString("移动");
				
				HTAB=0x10;
				putString("F3");
				verString("返回");
				HTAB=0x18;
				putString("F4");
				verString("测试");
		}
}	

/*===================================================*/
void showConstant2(void)
{
	clear_Lcd();
	
	HTAB=0x00;VTAB=0x00;
	putString(  "电机恒值试验");
	putHLine(0x10);

	VTAB=0x12;
	HTAB=0x00;putString(  "电压");
	HTAB=0x0d;putString(  "V");
	VTAB=0x24;
	HTAB=0x00;putString(  "电流");
	HTAB=0x0d;putString(  "A");	
	
	VTAB=0x36;
	HTAB=0x00;putString(  "P_in");
	HTAB=0x0d;putEng(  'W');
	HTAB=0x11;putString(  "Pout");
	HTAB=0x1d;putEng(  'W');	
	VTAB=0x48;
	HTAB=0x00;putString(  "转速");
	HTAB=0x0d;putString(  "RPM");
	HTAB=0x11;putString(  "效率");
	HTAB=0x1d;putEng(  '%');	
	VTAB=0x5a;
	HTAB=0x00;putString(  "转矩");
	HTAB=0x0d;
	putString(  "Nm ");
	
		
	
	VTAB=0x70;
	HTAB=0x00;putString(  "F1");verString(  "暂停");
	HTAB=0x08;putString(  "F2");verString(  "制动");
}
/*============================================*/
void showPG_Manual(void)
{
		clear_Lcd();
		HTAB=0x00;VTAB=0x00;	
		{   
			putString(  "电机手动测试:");		
			putHLine(0x10);
			
			VTAB=0x12;
			HTAB=0x00;putString(  "电压");
			HTAB=0x0d;putString(  "V");
			VTAB=0x24;
			HTAB=0x00;putString(  "电流");
			HTAB=0x0d;putString(  "A");
			
			HTAB=0x00;VTAB=0x36;putString(  "功率");
			HTAB=0x0d;putString(  "W");
			HTAB=0x00;VTAB=0x48;putString(  "转速");
			HTAB=0x0d;putString(  "RPM");
			HTAB=0x00;VTAB=0x5a;putString(  "转矩");
			HTAB=0x0d;putString(  "Nm  ");		
			HTAB=0x12;VTAB=0x36;putString(  "负载");
			HTAB=0x1d;;putEng( '%');			
			
			VTAB=0x70;
			HTAB=0x0a;verString( "开始");	
			HTAB=0x12;verString( "返回");
		}

		VTAB=0x4c;
		HTAB=0x19;putString("<-");verString("(-)");
		VTAB=0x5e;
		HTAB=0x19;putString("->");verString("(+)");				
		VTAB=0x70;
		HTAB=0x00;putString( "F1");verString("(--)");
		HTAB=0x08;putString( "F2");
		HTAB=0x10;putString( "F3");
		HTAB=0x18;putString( "F4");verString("(++)");
}
/*============================================*/
void showPG_Manual0(void)
{
	clear_Lcd();
	HTAB=0x00;VTAB=0x00;
	putString(	"手动试验设定"); 	
	putHLine(0x10);
	HTAB=0x08;VTAB=0x14;
	putString(	"[1]起动电压设定"); 
	HTAB=0x09;verEng('1');
	HTAB=0x08;VTAB=0x26;
	putString(	"[2]电机手动测试");
	VTAB=0x70;
	HTAB=0x00;putString( "F1");verString( "移动");
	HTAB=0x10;putString( "F3");verString( "返回");
	HTAB=0x18;putString( "F4");verString( "确认");	

}
void ManualSetingDisplay(void)
{
	   clear_Lcd();
	   HTAB=0x00;VTAB=0x00;putString("起动设定");
	   putHLine(0x10);
	   HTAB=0x00;VTAB=0x24;putString("起动时间");
	   HTAB=0x00;VTAB=0x36;putString("试验电压");
	   HTAB=0x00;VTAB=0x48;putString("起动电压");
	   

	   VTAB=0x70;
	   HTAB=0x00;putString( "F1");verString( "移动");
	   HTAB=0x10;putString( "F3");verString( "返回");
	   HTAB=0x18;putString( "F4");verString( "保存");

}




/*=====================================*/
/*void showPerfomance1(char p)
{
		clear_Lcd();

	HTAB=0x00;VTAB=0x00;	
	putString( "特性试验设定(Page ");
  putEng(p+0x30);putEng(')');	
	putHLine(0x10);				
	VTAB=0x12;HTAB=0x08;
	putString(  "控制方式--");	
	VTAB=0x70;
	HTAB=0x00;putString("F1");verString("移动");
	HTAB=0x10;putString("F3");verString("返回");	
	HTAB=0x18;putString("F4");verString("测试");	
	
}*/
/*=========================================*/
void showPerfomance1(char p)
{
	clear_Lcd();
		HTAB=0x00;VTAB=0x00;
		putString( "特性试验设定(Page ");
		putEng(p+0x30);putEng(')');			
		putHLine(0x10);

		HTAB=0x04;VTAB=0x12;
		putString( "    恒定");
		
				
		VTAB=0x70;
		HTAB=0x00;putString(  "F1");verString(  "换页");				
		HTAB=0x10;putString(  "F3");verString(  "返回");	
		HTAB=0x18;putString(  "F4");verString(  "测试");			
}

/*============================================*/

void showPerfomance2(void)
{
	clear_Lcd();putHLine(0x10);

		
	HTAB=0x00;VTAB=0x00;	
	putString(  "电机特性试验:");
	
	VTAB=0x12;
	HTAB=0x00;putString(  "电压");
	HTAB=0x0d;putString(  "V");
	VTAB=0x24;
	HTAB=0x00;putString(  "电流");
	HTAB=0x0d;putString(  "A");
		
	
	VTAB=0x36;
	HTAB=0x00;putString(  "功率");
	HTAB=0x0d;putString(  "W");
	HTAB=0x11;putString(  "状态");
	VTAB=0x48;
	HTAB=0x00;putString(  "转速");
	HTAB=0x0d;putString(  "RPM");
	HTAB=0x11;putString(  "定时");

	
	VTAB=0x5a;
	HTAB=0x00;putString(  "转矩");
	HTAB=0x0d;
	putString(  "Nm ");
	
		
	VTAB=0x70;
	HTAB=0x00;putString("F1");verString("开始");	
	//HTAB=0x08;verString(" 等待中");
}

/*============================================*/
void showPower(void)
{

		clear_Lcd();
		
		{			
			HTAB=0x00;VTAB=0x00;
			putString( "电源设定");
			putHLine(0x10);				
			HTAB=0x08;VTAB=0x20;
			putString( "电源状态");
			
			VTAB=0x40;
			HTAB=0x14;putEng('V');
			
		}	
		VTAB=0x70;
		HTAB=0x08;putString( "F2");verString( "选择");
		HTAB=0x10;putString( "F3");verString( "返回");	
}
/*===================================================*/
void showPG_RBH1(void)		
{
	clear_Lcd();
	{
		HTAB=0x00;VTAB=0x00;
		putString(  "热保护器试验");
		putHLine(0x10);

		
		VTAB=0x14;
		HTAB=0x04;putString( "最大动作时间");
		HTAB=0x17;putString("秒");
		VTAB=0x28;
		HTAB=0x04;putString( "最大恢复时间");
		HTAB=0x17;putString("秒");
		VTAB=0x3c;
		HTAB=0x06;putString( "负载率");
		HTAB=0x17;putEng('%');
		VTAB=0x50;
		HTAB=0x06;putString( "高低速");
		
		
		VTAB=0x70;
		HTAB=0x10;
		putString(  "F3");		
		verString(  "返回");
		HTAB=0x18;
		putString(  "F4");		
		verString("测试");
		
	}			
}
/*===================================================*/
void showPG_RBH2(void)		//等待
{
	clear_Lcd();
	{
		HTAB=0x00;VTAB=0x00;
		putString(  "热保护器试验");
		putHLine(0x10);
		HTAB=0x06;VTAB=0x12;putString(  "电压");
		HTAB=0x14;putString(  "V");
		HTAB=0x06;VTAB=0x24;putString(  "电流");
		HTAB=0x14;putString(  "A");
		HTAB=0x06;VTAB=0x36;putString(  "功率");
		HTAB=0x14;putString(  "W");
		HTAB=0x06;VTAB=0x48;putString(  "阶段");
		HTAB=0x11;putString(  "T0");
		HTAB=0x06;VTAB=0x5a;putString(  "计时");
		HTAB=0x14;
		putString(  "Sec");		
		
		VTAB=0x70;
		HTAB=0x00;
		putString(  "F1");		
		verString(  "暂停");
		
	}			
}


