#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"//4x4矩阵按键外部中断
#include "oled.h"
#include "random_generate.h"//生成随机数
#include "beep.h" //蜂鸣器驱动
#include "timer.h"



 int main(void)
 {		
	extern int KeyValue;
	extern int randomValue;
	extern int score;
	int i;  //循环变量
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口波特率115200
 	LED_Init();		  		 //初始化与LED连接的硬件接口
	OLED_Init();			   //初始化OLED  
	OLED_Clear();  
	EXTIX_Init();		 	   //外部中断初始�
	Adc_Init();          //adc初始化
	BEEP_Init();         	//初始化蜂鸣器端口
	 
	TIM3_Int_Init(29999,71999);//1Khz的计数频率，计数到29999为30s


	KeyValue=17;
	led_output();//输出led随机显示

	while(1)
	{

		OLED_ShowCHinese(0,0,0);//比
		OLED_ShowCHinese(16,0,0);//比
		OLED_ShowCHinese(32,0,1);//谁
		OLED_ShowCHinese(48,0,2);//的 
		OLED_ShowCHinese(64,0,3);//反
		OLED_ShowCHinese(80,0,4);//应
		OLED_ShowCHinese(96,0,5);//快
		OLED_ShowCHinese(112,0,6);//�
		
    if((KeyValue-1) == randomValue)
		{
		//蜂鸣器响
			for(i=0;i<20;i++)
			{
			BEEP = 0;
			delay_us(200);
			BEEP = 1;
			delay_us(200);			
			}
			BEEP_LED = 0;
			delay_ms(50);
			BEEP_LED = 1;
			score++;
			led_output();		
		}	
		delay_ms(50);

		
		OLED_ShowString(0,2,"score:",7);
		OLED_ShowNum(50,2,score,8,8);
		OLED_ShowString(0,4,"time:   30s",10);
		OLED_ShowString(0,6,"KEY: ",5);
		OLED_ShowNum(50,6,(KeyValue-1),8,8);
	
	}
 }

