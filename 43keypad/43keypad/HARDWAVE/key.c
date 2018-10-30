#include "key.h"
#include "delay.h"

void KEY_Init(void) //��ʼ���������Ҫʹ�õ�GPIO�ڡ�
{

 	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //����PB9��PB11Ϊ�������
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       //����PB12��PB15Ϊ�������롣
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    //��Ϊ���涨������Ϊ���ʱ���Ѿ�������GPIOA��ʱ���ˣ�
	//���Դ˴�������Ҫ����RCC_APB2PeriphClockCmd()����ʱ���ˡ�
    GPIO_Init(GPIOB,&GPIO_InitStructure);		
}

int KEY_Scan(void) //ʵ�־�����̡�����ֵΪ�������ļ�ֵ���˼�ֵ���û��Լ����塣
{
	u8 KeyVal;	 //keyValΪ��󷵻صļ�ֵ��
	PBout(9)=PBout(10)=PBout(11)=1;//����PB9��PB11ȫ������ߡ�
	
	if((PBin(12)==0) && (PBin(13)==0) && (PBin(14)==0) && (PBin(15)==0))  //���PB12��PB15ȫΪ0����û�м����¡���ʱ������ֵΪ-1.
	{
		return -1;
	}
	else
	{	
	    delay_ms(5);    //��ʱ5msȥ������
	    if((PBin(12)==0) && (PBin(13)==0) && (PBin(14)==0) && (PBin(15)==0))//�����ʱ5ms��PB12��PB15��ȫΪ0���򣬸ղ����ŵĵ�λ�仯�Ƕ���������.
	    return -1;
	}

	PBout(9)=1;PBout(10)=0;PBout(11)=0;//��PB9��PB11��������Ƶ�100
	if(PBin(12)){       //��PB12��PB15��ֵ�����жϣ��������ͬ�ļ�ֵ��
		KeyVal=11;
	}else if(PBin(13)){
		KeyVal=9;
	}else if(PBin(14)){
		KeyVal=6;	
	}else if(PBin(15)){
		KeyVal=3;
	}
		
	PBout(9)=0;PBout(10)=1;PBout(11)=0;//��PB9��PB11��������Ƶ�010
	if(PBin(12)){       //��PB12��PB15��ֵ�����жϣ��������ͬ�ļ�ֵ��
		KeyVal=0;
	}else if(PBin(13)){
		KeyVal=8;
	}else if(PBin(14)){
		KeyVal=5;	
	}else if(PBin(15)){
		KeyVal=2;
	}
		
	PBout(9)=0;PBout(10)=0;PBout(11)=1;//��PB9��PB11��������Ƶ�001
	if(PBin(12)){       //��PB12��PB15��ֵ�����жϣ��������ͬ�ļ�ֵ��
		KeyVal=10;
	}else if(PBin(13)){
		KeyVal=7;
	}else if(PBin(14)){
		KeyVal=4;	
	}else if(PBin(15)){
		KeyVal=1;
	}
								  
	return KeyVal;		
}	

