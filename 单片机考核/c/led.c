#include "led.h"
bit flagStart = 0;
extern unsigned int countdowntime;
unsigned char pdata LedChar[] = {
	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
	0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e
};
unsigned char xdata LedBuff[6]={0xff,0xff,0xff,0xff,0xff,0xff};

/*倒计时函数*/
void CountDown()
{
	if(flagStart)//控制倒计时开始暂停的变量
	{
		countdowntime--;
		if(countdowntime == 0)//倒计时为0时
		{
			flagStart = 0;//倒计时停止
			PWM_Set(0xff);//蜂鸣器响
		}
		ShowNum(countdowntime);//数码管显示倒计时时间
	}
}

/*数码管显示倒计时函数*/
void ShowNum(unsigned int num)
{
	LedBuff[0] = LedChar[num%10];//显示毫秒位
	LedBuff[1] = LedChar[num/10%10];//显示秒位
	LedBuff[2] = LedChar[num/100];//显示十秒位
}

/*数码管刷新函数*/
void LedScan()
{
	static unsigned char i = 0;
	P0 = 0xff;
	switch(i)
	{
		case 0: P22=1;P21=0;P20=1;i++;P0=LedBuff [0];break;//刷新毫秒位
		case 1: P22=1;P21=0;P20=0;i++;P0=LedBuff [1];break;//刷新秒位
		case 2: P22=0;P21=1;P20=1;i++;P0=LedBuff [2];break;//刷新十秒位
		case 3: P22=1;P21=0;P20=0;i=0;P0=0x7f;break;//刷新小数点
		default:break;
	}                                                               
}