#include "led.h"
bit flagStart = 0;
extern unsigned int countdowntime;
unsigned char pdata LedChar[] = {
	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
	0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e
};
unsigned char xdata LedBuff[6]={0xff,0xff,0xff,0xff,0xff,0xff};

/*����ʱ����*/
void CountDown()
{
	if(flagStart)//���Ƶ���ʱ��ʼ��ͣ�ı���
	{
		countdowntime--;
		if(countdowntime == 0)//����ʱΪ0ʱ
		{
			flagStart = 0;//����ʱֹͣ
			PWM_Set(0xff);//��������
		}
		ShowNum(countdowntime);//�������ʾ����ʱʱ��
	}
}

/*�������ʾ����ʱ����*/
void ShowNum(unsigned int num)
{
	LedBuff[0] = LedChar[num%10];//��ʾ����λ
	LedBuff[1] = LedChar[num/10%10];//��ʾ��λ
	LedBuff[2] = LedChar[num/100];//��ʾʮ��λ
}

/*�����ˢ�º���*/
void LedScan()
{
	static unsigned char i = 0;
	P0 = 0xff;
	switch(i)
	{
		case 0: P22=1;P21=0;P20=1;i++;P0=LedBuff [0];break;//ˢ�º���λ
		case 1: P22=1;P21=0;P20=0;i++;P0=LedBuff [1];break;//ˢ����λ
		case 2: P22=0;P21=1;P20=1;i++;P0=LedBuff [2];break;//ˢ��ʮ��λ
		case 3: P22=1;P21=0;P20=0;i=0;P0=0x7f;break;//ˢ��С����
		default:break;
	}                                                               
}