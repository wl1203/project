#ifndef __HAL_H
#define __HAL_H







/*********************************************************************************************************
** 引脚内部上下拉电阻配置
*********************************************************************************************************/
#define PIN_PULL_UP           (uint32)0x00                                      /* 引脚内部上拉                 */
#define PIN_REPEATER         (uint32)0x01                                      /* 引脚内部上拉                 */
#define PIN_NO_PULL           (uint32)0x02                                      /* 引脚既不上拉，也不下拉       */
#define PIN_PULL_DOWN      (uint32)0x03                                      /* 引脚内部下拉                 */

 /*  P0    */
#define P0_0_FNUC             P0_0_GPIO				//CAN RD1
#define P0_1_FNUC             P0_1_GPIO				//CAN TD1
#define P0_2_FNUC             P0_2_TXD0					//TDX0
#define P0_3_FNUC             P0_3_RXD0					//RXD0
#define P0_4_FNUC             P0_4_GPIO				//175X-NO
#define P0_5_FNUC             P0_5_GPIO				//175X-NO
#define P0_6_FNUC             P0_6_GPIO				//SSP1  SSEL1
#define P0_7_FNUC             P0_7_SSCK1		//SSP1  SSCK1      
#define P0_8_FNUC             P0_8_SMISO1	//SSP1  MISO1		
#define P0_9_FNUC             P0_9_SMOSI1	//SSP1  MOSI1
#define P0_10_FNUC            P0_10_SDA2					//I2C2  SDA2    
#define P0_11_FNUC            P0_11_SCL2					//I2C2  SCL2  
#define P0_15_FNUC            P0_15_SCK0					//SSP0  SSCK0                    
#define P0_16_FNUC            P0_16_SSEL0					//SSP0  SSEL0                                                    
#define P0_17_FNUC            P0_17_MISO0				      //SSP0  MISO0	                                              
#define P0_18_FNUC            P0_18_MOSI0				      //SSP0  MOSI0      
#define P0_19_FNUC            P0_19_GPIO				//175X-NO
#define P0_20_FNUC            P0_20_GPIO				//175X-NO 
#define P0_21_FNUC            P0_21_GPIO				//175X-NO     
#define P0_22_FNUC            P0_22_GPIO					//SSP0--CS 
#define P0_23_FNUC            P0_23_GPIO				//175X-NO
#define P0_24_FNUC            P0_24_GPIO				//175X-NO                                  
#define P0_25_FNUC            P0_25_GPIO				//ANALOG 0
#define P0_26_FNUC            P0_26_GPIO				//ANALOG 1
#define P0_27_FNUC            P0_27_GPIO				//175X-NO      
#define P0_28_FNUC            P0_28_GPIO				//175X-NO   
#define P0_29_FNUC            P0_29_GPIO				//USB_D+ 
#define P0_30_FNUC            P0_30_GPIO				//USB_D-

#define P0_0_MODE             PIN_PULL_UP                   //CAN RD1               
#define P0_1_MODE             PIN_PULL_UP                   //CAN TD1               
#define P0_2_MODE             PIN_NO_PULL                   	//TDX0            
#define P0_3_MODE             PIN_NO_PULL                   	//RXD0            
#define P0_4_MODE             PIN_PULL_UP                   //175X-NO               
#define P0_5_MODE             PIN_PULL_UP                   //175X-NO               
#define P0_6_MODE             PIN_PULL_UP                   	//SSP1  SSEL1     
#define P0_7_MODE             PIN_NO_PULL			//SSP1  SSCK1          
#define P0_8_MODE             PIN_NO_PULL                   	//SSP1  MISO1	     
#define P0_9_MODE             PIN_NO_PULL			//SSP1  MOSI1          
#define P0_10_MODE            PIN_PULL_UP                //I2C2  SDA2           
#define P0_11_MODE            PIN_PULL_UP                //I2C2  SCL2      
#define P0_12_MODE            PIN_PULL_UP                //175X-NO 
#define P0_13_MODE            PIN_PULL_UP                    //175X-NO 
#define P0_14_MODE            PIN_PULL_UP			     //175X-NO 
#define P0_15_MODE            PIN_PULL_UP			     //SSP0  SSCK0      	
#define P0_16_MODE            PIN_PULL_UP				//SSP0  SSEL0     
#define P0_17_MODE            PIN_NO_PULL				//SSP0  MISO0	
#define P0_18_MODE            PIN_PULL_UP				//SSP0  MOSI0     
#define P0_19_MODE            PIN_PULL_UP    			 //175X-NO      
#define P0_20_MODE            PIN_PULL_UP    			 //175X-NO                             
#define P0_21_MODE            PIN_PULL_UP    			 //175X-NO                             
#define P0_22_MODE            PIN_PULL_UP			//SSP0--CS                           
#define P0_23_MODE            PIN_PULL_UP                    //175X-NO    
#define P0_24_MODE            PIN_PULL_UP                    //175X-NO 
#define P0_25_MODE            PIN_PULL_UP                    //ANALOG 0
#define P0_26_MODE            PIN_PULL_UP                    //ANALOG 1
#define P0_27_MODE            PIN_PULL_UP                    //175X-NO 
#define P0_28_MODE            PIN_PULL_UP                    //175X-NO 
#define P0_29_MODE            PIN_PULL_UP                    //USB_D+  
#define P0_30_MODE            PIN_PULL_UP                    //USB_D-  
#define P0_31_MODE            PIN_PULL_UP                    //175X-NO

/*  P1   */
#define P1_0_FNUC             P1_0_GPIO 					//DATA BUS.0                                     
#define P1_1_FNUC             P1_1_GPIO
#define P1_4_FNUC             P1_4_GPIO
#define P1_8_FNUC             P1_8_GPIO
#define P1_9_FNUC             P1_9_GPIO
#define P1_10_FNUC            P1_10_GPIO
#define P1_14_FNUC            P1_14_GPIO                
#define P1_15_FNUC            P1_15_GPIO					//DATA BUS.7
#define P1_16_FNUC            P1_16_GPIO				//175X-NO
#define P1_17_FNUC            P1_17_GPIO				//175X-NO
#define P1_18_FNUC            P1_18_GPIO				//USB_LED
#define P1_19_FNUC            P1_19_GPIO                   		//LCD RESET
#define P1_20_FNUC            P1_20_GPIO		//QEI-PHA
#define P1_21_FNUC            P1_21_GPIO				//175X-NO          
#define P1_22_FNUC            P1_22_GPIO					//CTRL                       
#define P1_23_FNUC            P1_23_MCFB1		//QEI-PHB
#define P1_24_FNUC            P1_24_GPIO				//QEI-INDEX
#define P1_25_FNUC            P1_25_GPIO					//READ
#define P1_26_FNUC            P1_26_GPIO    				//WRITE
#define P1_27_FNUC            P1_27_GPIO				//175X-NO  
#define P1_28_FNUC            P1_28_GPIO					//COMMAND/DATA
#define P1_29_FNUC            P1_29_GPIO					//LCD SELECT
#define P1_30_FNUC            P1_30_GPIO				//USB VBUS
#define P1_31_FNUC            P1_31_GPIO				//ANALOG 2

#define P1_0_MODE             PIN_NO_PULL			    //DATA BUS.0      
#define P1_1_MODE             PIN_NO_PULL                         //DATA BUS.1                   
#define P1_2_MODE             PIN_PULL_UP                   //175X-NO                                           
#define P1_3_MODE             PIN_PULL_UP                   //175X-NO                                           
#define P1_4_MODE             PIN_NO_PULL                         //DATA BUS.2                   
#define P1_5_MODE             PIN_PULL_UP                   //175X-NO                                           
#define P1_6_MODE             PIN_PULL_UP                   //175X-NO                                           
#define P1_7_MODE             PIN_PULL_UP                   //175X-NO	    
#define P1_8_MODE             PIN_NO_PULL                   	//DATA BUS.3          
#define P1_9_MODE             PIN_NO_PULL                        	//DATA BUS.4
#define P1_10_MODE            PIN_NO_PULL                     	//DATA BUS.5
#define P1_11_MODE            PIN_PULL_UP                   //175X-NO    
#define P1_12_MODE            PIN_PULL_UP                   //175X-NO    
#define P1_13_MODE            PIN_PULL_UP                   //175X-NO	  
#define P1_14_MODE            PIN_NO_PULL                  		//DATA BUS.6
#define P1_15_MODE            PIN_NO_PULL					//DATA BUS.7
#define P1_16_MODE            PIN_PULL_UP                    //175X-NO            	
#define P1_17_MODE            PIN_PULL_UP                    //175X-NO        	
#define P1_18_MODE            PIN_PULL_UP                    //USB_LED    	 	
#define P1_19_MODE            PIN_NO_PULL                    	//LCD RESET          
#define P1_20_MODE            PIN_NO_PULL                    	//QEI-PHA     
#define P1_21_MODE            PIN_PULL_UP                    //175X-NO          
#define P1_22_MODE            PIN_NO_PULL				 	//CTRL        																				       
#define P1_23_MODE            PIN_NO_PULL                    	//QEI-PHB     																				       
#define P1_24_MODE            PIN_NO_PULL				//QEI-INDEX   																			
#define P1_25_MODE            PIN_NO_PULL                    	//READ        																			
#define P1_26_MODE            PIN_NO_PULL                    	//WRITE       																			
#define P1_27_MODE            PIN_PULL_UP     			 //175X-NO
#define P1_28_MODE            PIN_NO_PULL     				//COMMAND/DATA 
#define P1_29_MODE            PIN_NO_PULL				//LCD SELECT   			
#define P1_30_MODE            PIN_PULL_UP     			//USB VBUS
#define P1_31_MODE            PIN_PULL_UP     			//ANALOG 2    

/*  P2    */
#define P2_0_FNUC             P2_0_TXD1				//TXD1
#define P2_1_FNUC             P2_1_RXD1				//RXD1
#define P2_2_FNUC             P2_2_PWM13					//PWM OUT
#define P2_3_FNUC             P2_3_GPIO					//SSP1 SELECT
#define P2_4_FNUC             P2_4_GPIO					//SPI0 RESET
#define P2_5_FNUC             P2_5_GPIO					//KEYIN1
#define P2_6_FNUC             P2_6_GPIO					//KEYIN2
#define P2_7_FNUC             P2_7_RTS1				//UART1 485 ENABLE
#define P2_8_FNUC             P2_8_GPIO					//KEYIN3
#define P2_9_FNUC             P2_9_GPIO				//USB CONNECT
#define P2_10_FNUC            P2_10_GPIO   			//ISP
#define P2_11_FNUC            P2_11_GPIO   			//175X-NO
#define P2_12_FNUC            P2_12_GPIO				//175X-NO
#define P2_13_FNUC            P2_13_GPIO    			//175X-NO

#define P2_0_MODE             PIN_NO_PULL			//TXD1              
#define P2_1_MODE             PIN_NO_PULL			//RXD1              
#define P2_2_MODE             PIN_NO_PULL                   //PWM OUT           
#define P2_3_MODE             PIN_NO_PULL                   //SSP1 SELECT       
#define P2_4_MODE             PIN_NO_PULL                   //SPI0 RESET        
#define P2_5_MODE             PIN_NO_PULL				//KEYIN1            
#define P2_6_MODE             PIN_NO_PULL				//KEYIN2            
#define P2_7_MODE             PIN_NO_PULL				//UART1 485 ENABLE  
#define P2_8_MODE             PIN_NO_PULL				//KEYIN3            
#define P2_9_MODE             PIN_PULL_UP
#define P2_10_MODE            PIN_NO_PULL               //添加 KEYIN4
#define P2_11_MODE            PIN_PULL_UP
#define P2_12_MODE            PIN_PULL_UP
#define P2_13_MODE            PIN_PULL_UP
#define P2_14_MODE            PIN_PULL_UP
#define P2_15_MODE            PIN_PULL_UP

/*  P3   */
#define P3_25_FNUC            P3_25_GPIO				//175X-NO                            
#define P3_26_FNUC            P3_26_GPIO				//175X-NO

#define P3_25_MODE            PIN_PULL_UP
#define P3_26_MODE            PIN_PULL_UP

 /*  P4   */
#define P4_28_FNUC            P4_28_TXD3		//TXD3     
#define P4_29_FNUC            P4_29_RXD3	//RXD3
 

#define P4_28_MODE            PIN_NO_PULL
#define P4_29_MODE            PIN_NO_PULL



		



/*******************************************************************************************************/
#define UART0TXFIFO	   0x4000C000	                                    /* 串口FIFO寄存器地址           */




extern uint8  ISendStr(uint8 sla, uint8 suba, uint8 *s, uint8 no);
extern uint8  IRcvStr(uint8 sla, uint8 suba, uint8 *s, uint8 no);
extern uint8 I2C_ReadNByte (uint8 sla, uint8 suba_type, uint32 suba, uint8 *s, uint32 num);
extern uint8 I2C_WriteNByte(uint8 sla, uint8 suba_type, uint32 suba, uint8 *s, uint32 num);
extern void  IRQ_I2C(void);					
extern void  I2C_Init(void);     


extern INT32S zyIsrSet (unsigned int uiChannel, unsigned long ulFunction, unsigned int uiPrio);

extern void Bell(void);
extern void Delay(uint16 delayT);
extern void Read_Key(void);
void Read_Posi(void);





extern void pid_tune(float P,float I,float D,uint16 DB,uint16 Type);
extern void pid_bumpless(void);
extern void pid_calc(void);

#endif                                                                  /*  __TARGET_CFG_H              */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

