//Display.c


#include "config.h"
#include "main.h"


extern uint16 HTAB,VTAB;
extern uint8  EndMode,MyID;
extern uint16	shi,fen,miao;
extern IN_ROT 	in_rot;



void showPG000(void);		//��ʼҳ
void showPG001(void);		//����ѡ��
void showPG00(void);		//�ȴ�

void showPGRun1(void);	//ר�����
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
void showBreak1(void);
void showBreak2(void);

/*===================================================*/
void showPG000(void)	//��ʼҳ
{
	clear_Lcd();
	HTAB=0x07;VTAB=0x0c;
	putString("���ר������ϵͳ");
	HTAB=0x07;VTAB=0x1c;
	putString(  "Motor Test System");
	HTAB=0x05;VTAB=0x2c;
	putString(  "��������豸���޹�˾");
	HTAB=0x05;VTAB=0x3c;
	putString(  "Angui Mechanical and");
	HTAB=0x05;VTAB=0x4c;
	putString(  "Electrical Equipment");
	HTAB=0x06;VTAB=0x60;
	putString(  "Version DGWD.1704");

	VTAB=0x70;
	HTAB=0x00;verString(  "��  ��");
	HTAB=0x18;verString(  "��  ��");
	
}
/*===================================================*/
void showPG00(void)		//�ȴ�
{
	clear_Lcd();
	HTAB=0x00;VTAB=0x00;
	putString(  "���ר������ϵͳ");
	putHLine(0x10);	
	{	HTAB=0x06;VTAB=0x12;putString(  "��ѹ");
			HTAB=0x14;putString(  "V");
			HTAB=0x06;VTAB=0x24;putString(  "����");
			HTAB=0x14;putString(  "A");
			HTAB=0x06;VTAB=0x36;putString(  "����");
			HTAB=0x14;putString(  "W");	
			VTAB=0x48;
			HTAB=0x06;putString(  "ת��");
			HTAB=0x14;putString(  "RPM  ");	
			VTAB=0x5a;
			HTAB=0x06;putString(  "ת��");
			HTAB=0x14;
			putString(  "Nm ");			
			
	}	


	VTAB=0x70;
	HTAB=0x00;
	putString(  "F1");verString(  "����");	
	HTAB=0x08;
	putString(  "F2");verString(  "�趨");		
	HTAB=0x18;
	putString(  "F4");verString(  "У׼");	
				
}
/*===================================================*/
void showPassWord(void)
{
		clear_Lcd();
		HTAB=0;VTAB=0;
		putString( "����������");
		
		putHLine(0x10);		

		VTAB=0x30;HTAB=0x0D;
		verEng('*');
		putString( "***");
		
		VTAB=0x70;HTAB=0x10;putString("F3");
		verString("����");
		HTAB=0x18;putString("F4");
		verString("ȷ��");		
}

/*=================================================*/
void showCalib00(void)
{		
	clear_Lcd();	
	{
		HTAB=0x00;VTAB=0x00;
		putString( "ϵͳУ׼");
		putHLine(0x10);
		
		HTAB=0x08;VTAB=0x14;
		putString( "[1] ת�ر�У׼");
		//putString( "[1] ������У׼");	
		HTAB=0X09;verEng('1');
		//HTAB=0x08;VTAB=0x26;
		//putString( "[2] ��ѹ��У׼");	
		//HTAB=0x08;VTAB=0x38;
		//putString( "[3] ת�ر�У׼");	
		
				
	}
	VTAB=0x70;
	//HTAB=0x00;putString( "F1");verString( "�ƶ�");
	HTAB=0x10;putString( "F3");verString( "����");
	HTAB=0x18;putString( "F4");verString( "ȷ��");	
}

/*==============================================*/
void showCalib01(void)
{
		clear_Lcd();
		
		HTAB=0x00;VTAB=0x00;
		putString( "ת�ر�У׼");
		putHLine(0x10);	
		HTAB=0x08;VTAB=0x20;
		putString( "[1] ��λУ׼");	
		HTAB=0X09;verEng('1');
		HTAB=0x08;VTAB=0x38;
		putString( "[2] �̶ȵ���");	
			
		VTAB=0x70;
		HTAB=0x00;putString( "F1");verString( "�ƶ�");		
		HTAB=0x10;putString( "F3");verString( "����");
		HTAB=0x18;putString( "F4");verString( "ȷ��");
}


/*=========================================*/
void showScale(void)
{		clear_Lcd();
		
		{			
			HTAB=0x00;VTAB=0x00;
			putString( "ת�ر�̶ȵ���");
			putHLine(0x10);	
			
			HTAB=0x04;VTAB=0x28;
			putString( "��  ǰ  ֵ");	
			HTAB=0x04;VTAB=0x48;
			putString( "����׼ȷֵ");	
			HTAB=0x18;VTAB=0x28;
			putString(  "V");
			HTAB=0x18;VTAB=0x48;
			putString(  "V");		
		
				
		}
		VTAB=0x70;		
		HTAB=0x10;putString( "F3");verString( "����");
		HTAB=0x18;putString( "F4");verString( "ȷ��");
		
}

/*=====================================*/
void showSet0(void)
{
	clear_Lcd();
	{
		HTAB=0x00;VTAB=0x00;
		putString(  "��������");
		putHLine(0x10);
	
		HTAB=0x06;VTAB=0x18;
		putString(  "[1]  PID ��������");		
		HTAB=0x07;verEng('1');		
		HTAB=0x06;VTAB=0x2c;
		putString(  "[2]  �⹦���궨");
		HTAB=0x06;VTAB=0x40;
		putString(  "[3]  ��Դ����");	
		
	}
	VTAB=0x70;
	HTAB=0x00;putString(  "F1");verString(  "�ƶ�");
	HTAB=0x10;putString(  "F3");verString(  "����");
	HTAB=0x18;putString(  "F4");verString(  "ȷ��");	
}

/*======================================*/
void showRun0(void)
{
	clear_Lcd();
	{
		HTAB=0x00;VTAB=0x00;
		putString(  "����ѡ��");
		putHLine(0x10);	
		HTAB=0x06;VTAB=0x14;
		putString(  "[1] ��������");
		HTAB=0x07;verEng('1');
		HTAB=0x06;VTAB=0x26;
		//putString(  "[2] �ȱ�������");
		putString(  "[2] ��ֵ����");	
		HTAB=0x06;VTAB=0x38;		
		putString(  "[3] �ֶ�����");
		HTAB=0x06;VTAB=0x4a;		
		putString(  "[4] ���Բ���");		
		
	}
	VTAB=0x70;
	HTAB=0x00;putString(  "F1");verString(  "�ƶ�");
	HTAB=0x10;putString(  "F3");verString(  "����");
	HTAB=0x18;putString(  "F4");verString(  "ȷ��");	
}


/*============================================*/

void showPID(void)
{
		clear_Lcd();
		
		{
			HTAB=0x00;VTAB=0x00;
			putString( "PID ��������");
			putHLine(0x10);
			HTAB=0x01;VTAB=0x12;
			putString( "P:");	
			HTAB=0x01;VTAB=0x24;
			putString( "I:");
			HTAB=0x01;VTAB=0x36;
			putString( "D:");
			HTAB=0x0c;VTAB=0x12;
			verString( "��");
			HTAB=0x0c;VTAB=0x24;
			putString( "�趨ֵ");
			HTAB=0x0c;VTAB=0x48;
			putString( "��ʱֵ");			
			
		
		}
		VTAB=0x70;	
		HTAB=0x00;putString( "F1");verString( "�ƶ�");
		HTAB=0x08;putString( "F2");verString( "ѡ��");
		HTAB=0x10;putString( "F3");verString( "����");
		HTAB=0x18;putString( "F4");verString( "ȷ��");
}


/****************************************************/
void showPGRun1(void)	//ר�����
{
	clear_Lcd();
		putHLine(0x10);
		putHLine(0x23);
		putHLine(0x35);
		putHLine(0x47);
		putHLine(0x59);
		putHLine(0x6b);
		
		HTAB=0x00;VTAB=0x00;
		putString(  "�����������:");		
	
		VTAB=0x12;
		HTAB=0x00;putString(  "��ѹ");
		HTAB=0x0d;putString(  "V");//HTAB=0x15;putString(  "V");
		//HTAB=0x1d;putString(  "V");
		VTAB=0x24;
		HTAB=0x00;putString(  "����");
		HTAB=0x0d;putString(  "A");//HTAB=0x15;putString(  "A");
		//HTAB=0x1d;putString(  "A");	
		VTAB=0x36;
		HTAB=0x00;putString(  "����");
		HTAB=0x0d;putString(  "W");
		
		VTAB=0x48;
		HTAB=0x00;putString(  "ת��");
		HTAB=0x0d;putString(  "RPM");
		HTAB=0x12;putString(  "״̬     T 1");		
		
		VTAB=0x5a;
		HTAB=0x00;putString(  "ת��");
		HTAB=0x0d;putString(  "Nm ");
		HTAB=0x12;putString(  "��ʱ");
		
		VTAB=0x70;
		HTAB=0x00;putString(  "F1");verString(  "��ʼ");
		HTAB=0x09;putString(  "F3");verString(  "����");

	
}

/*============================================*/
void showDynamo(void)
{		clear_Lcd();
		
		{
			VTAB=0x00;HTAB=0x00;
			putString( "���ѡ��");
			putHLine(0x10);
				
			
			
			VTAB=0x30;
			

			
		}
		VTAB=0x70;
		HTAB=0x08;putString( "F2");verString( "ѡ��");
		HTAB=0x10;putString( "F3");verString( "����");
		HTAB=0x18;putString( "F4");verString( "ȷ��");		
}

/*============================================*/
void showDynaCalib(void)
{

		clear_Lcd();
		
		{			
			HTAB=0x00;VTAB=0x00;
			putString( "�⹦���궨");
			putHLine(0x10);
				
			HTAB=0x06;VTAB=0x24;
			putString( "ת��");	
			HTAB=0x14;//putString(  "mNm");
				putString(  "Nm ");
			HTAB=0x06;VTAB=0x40;
			putString( "������");
			HTAB=0x14;putEng('%');
			
			VTAB=0x70;HTAB=0x0a;
			verString( "����");		
			HTAB=0x12;
			verString( "����");		
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
		//clear_Lcd();
		HTAB=0x00;VTAB=0x00;
			putString(  "�����ֵ����:");		
			putHLine(0x10);		
			if(a==1)
		  {
				VTAB=0x12;HTAB=0x08;
				putString(  "���Ʒ�ʽ--");				
				
				VTAB=0x24;HTAB=0x13;
				putString(  "PID����:");
				VTAB=0x36;HTAB=0x13;
				putString(  "P");
				VTAB=0x48;
				HTAB=0x00;putString(  "����ʱ��");
				HTAB=0x13;putString(  "I");
				VTAB=0x5a;
				HTAB=0x0a;putString(  "Sec");
				HTAB=0x13;putString(  "D");
			}
		    else if(a==2)
		    	{
		    	VTAB=0x24;HTAB=0x00;
				putString(  "������ѹ");				
				
				VTAB=0x36;HTAB=0x00;
				putString(  "����ʱ��");
				VTAB=0x48;HTAB=0x00;
				putString(  "�����ѹ");
		    	}
				VTAB=0x70;
				HTAB=0x00;
				putString("F1");
				verString("�ƶ�");
				
				HTAB=0x10;
				putString("F3");
				verString("����");
				HTAB=0x17;
				putString("F4");
				verString("����");
		//}
		
}	
/*=====================================*/
void showConstant3(void)
{
		clear_Lcd();
		HTAB=0x00;VTAB=0x00;	
		{
			putString(  "�����ֵ����:");		
			putHLine(0x10);		
			
				VTAB=0x24;HTAB=0x00;
				putString(  "������ѹ");				
				
				VTAB=0x36;HTAB=0x00;
				putString(  "����ʱ��");
				VTAB=0x48;HTAB=0x00;
				putString(  "�����ѹ");
				VTAB=0x70;
				HTAB=0x00;
				putString("F1");
				verString("�ƶ�");
				
				HTAB=0x10;
				putString("F3");
				verString("����");
				HTAB=0x18;
				putString("F4");
				verString("����");
		}
}	

/*===================================================*/
void showConstant2(void)
{
	clear_Lcd();
	
	HTAB=0x00;VTAB=0x00;
	putString(  "�����ֵ����");
	putHLine(0x10);

	VTAB=0x12;
	HTAB=0x00;putString(  "��ѹ");
	HTAB=0x0d;putString(  "V");
	VTAB=0x24;
	HTAB=0x00;putString(  "����");
	HTAB=0x0d;putString(  "A");	
	
	VTAB=0x36;
	HTAB=0x00;putString(  "P_in");
	HTAB=0x0d;putEng(  'W');
	HTAB=0x11;putString(  "Pout");
	HTAB=0x1d;putEng(  'W');	
	VTAB=0x48;
	HTAB=0x00;putString(  "ת��");
	HTAB=0x0d;putString(  "RPM");
	HTAB=0x11;putString(  "Ч��");
	HTAB=0x1d;putEng(  '%');	
	VTAB=0x5a;
	HTAB=0x00;putString(  "ת��");
	HTAB=0x0d;
	putString(  "Nm ");
	
		
	
	VTAB=0x70;
	HTAB=0x00;putString(  "F1");verString(  "��ͣ");
	HTAB=0x08;putString(  "F2");verString(  "�ƶ�");
}
/*============================================*/
void showPG_Manual(void)
{
		clear_Lcd();
		HTAB=0x00;VTAB=0x00;	
		{
			putString(  "����ֶ�����:");		
			putHLine(0x10);

			VTAB=0x12;
			HTAB=0x00;putString(  "��ѹ");
			HTAB=0x0d;putString(  "V");
			VTAB=0x24;
			HTAB=0x00;putString(  "����");
			HTAB=0x0d;putString(  "A");
			
			HTAB=0x00;VTAB=0x36;putString(  "����");
			HTAB=0x0d;putString(  "W");
			HTAB=0x00;VTAB=0x48;putString(  "ת��");
			HTAB=0x0d;putString(  "RPM");
			HTAB=0x00;VTAB=0x5a;putString(  "ת��");
			HTAB=0x0d;putString(  "Nm  ");		
			HTAB=0x12;VTAB=0x36;putString(  "����");
			HTAB=0x1d;;putEng( '%');			
			
			VTAB=0x70;
			HTAB=0x0a;verString( "��ʼ");	
			HTAB=0x12;verString( "����");
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

/*=====================================*/
/*void showPerfomance1(char p)
{
		clear_Lcd();

	HTAB=0x00;VTAB=0x00;	
	putString( "���������趨(Page ");
  putEng(p+0x30);putEng(')');	
	putHLine(0x10);				
	VTAB=0x12;HTAB=0x08;
	putString(  "���Ʒ�ʽ--");	
	VTAB=0x70;
	HTAB=0x00;putString("F1");verString("�ƶ�");
	HTAB=0x10;putString("F3");verString("����");	
	HTAB=0x18;putString("F4");verString("����");	
	
}*/
/*=========================================*/
void showPerfomance1(char p)
{
	clear_Lcd();
		HTAB=0x00;VTAB=0x00;
		putString( "���������趨(Page ");
		putEng(p+0x30);putEng(')');			
		putHLine(0x10);

		HTAB=0x04;VTAB=0x12;
		putString( "    �㶨");
		
				
		VTAB=0x70;
		HTAB=0x00;putString(  "F1");verString(  "��ҳ");				
		HTAB=0x10;putString(  "F3");verString(  "����");	
		HTAB=0x18;putString(  "F4");verString(  "����");			
}

/*============================================*/

void showPerfomance2(void)
{
	clear_Lcd();putHLine(0x10);

		
	HTAB=0x00;VTAB=0x00;	
	putString(  "�����������:");
	
	VTAB=0x12;
	HTAB=0x00;putString(  "��ѹ");
	HTAB=0x0d;putString(  "V");
	VTAB=0x24;
	HTAB=0x00;putString(  "����");
	HTAB=0x0d;putString(  "A");
		
	
	VTAB=0x36;
	HTAB=0x00;putString(  "����");
	HTAB=0x0d;putString(  "W");
	HTAB=0x11;putString(  "״̬");
	VTAB=0x48;
	HTAB=0x00;putString(  "ת��");
	HTAB=0x0d;putString(  "RPM");
	HTAB=0x11;putString(  "��ʱ");

	
	VTAB=0x5a;
	HTAB=0x00;putString(  "ת��");
	HTAB=0x0d;
	putString(  "Nm ");
	
		
	VTAB=0x70;
	HTAB=0x00;putString("F1");verString("��ͣ");	
	HTAB=0x08;verString(" ������");
}

/*============================================*/
void showPower(void)
{

		clear_Lcd();
		
		{			
			HTAB=0x00;VTAB=0x00;
			putString( "��Դ�趨");
			putHLine(0x10);				
			HTAB=0x08;VTAB=0x20;
			putString( "��Դ״̬");
			
			VTAB=0x40;
			HTAB=0x14;putEng('V');
			
		}	
		VTAB=0x70;
		HTAB=0x08;putString( "F2");verString( "ѡ��");
		HTAB=0x10;putString( "F3");verString( "����");	
}
/*===================================================*/
void showPG_RBH1(void)		
{
	clear_Lcd();
	{
		HTAB=0x00;VTAB=0x00;
		putString(  "�ȱ���������");
		putHLine(0x10);

		
		VTAB=0x14;
		HTAB=0x04;putString( "�����ʱ��");
		HTAB=0x17;putString("��");
		VTAB=0x28;
		HTAB=0x04;putString( "���ָ�ʱ��");
		HTAB=0x17;putString("��");
		VTAB=0x3c;
		HTAB=0x06;putString( "������");
		HTAB=0x17;putEng('%');
		VTAB=0x50;
		HTAB=0x06;putString( "�ߵ���");
		
		
		VTAB=0x70;
		HTAB=0x10;
		putString(  "F3");		
		verString(  "����");
		HTAB=0x18;
		putString(  "F4");		
		verString("����");
		
	}			
}
/*===================================================*/
void showPG_RBH2(void)		//�ȴ�
{
	clear_Lcd();
	{
		HTAB=0x00;VTAB=0x00;
		putString(  "�ȱ���������");
		putHLine(0x10);
		HTAB=0x06;VTAB=0x12;putString(  "��ѹ");
		HTAB=0x14;putString(  "V");
		HTAB=0x06;VTAB=0x24;putString(  "����");
		HTAB=0x14;putString(  "A");
		HTAB=0x06;VTAB=0x36;putString(  "����");
		HTAB=0x14;putString(  "W");
		HTAB=0x06;VTAB=0x48;putString(  "�׶�");
		HTAB=0x11;putString(  "T0");
		HTAB=0x06;VTAB=0x5a;putString(  "��ʱ");
		HTAB=0x14;
		putString(  "Sec");		
		
		VTAB=0x70;
		HTAB=0x00;
		putString(  "F1");		
		verString(  "��ͣ");
		
	}			
}


