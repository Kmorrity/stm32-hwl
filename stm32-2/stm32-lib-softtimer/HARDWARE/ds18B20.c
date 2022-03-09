#include "ds18b20.h"
#include "delay.h"

#include "stm32f10x_gpio.h"

#define EnableINT()
#define DisableINT()
#define DS_PORT GPIOB
#define DS_DQIO GPIO_Pin_14
#define DS_RCC_PORT RCC_APB2Periph_GPIOB
#define DS_PRECISION 0x7f //�������üĴ��� 1f=9λ; 3f=10λ; 5f=11λ; 7f=12λ;
#define DS_AlarmTH 0x64
#define DS_AlarmTL 0x8a
#define DS_CONVERT_TICK 1000
#define ResetDQ() GPIO_ResetBits(DS_PORT, DS_DQIO)
#define SetDQ() GPIO_SetBits(DS_PORT, DS_DQIO)
#define GetDQ() GPIO_ReadInputDataBit(DS_PORT, DS_DQIO)

#define SkipROM 0xCC         //����ROM
#define SearchROM 0xF0       //����ROM
#define ReadROM 0x33         //��ROM
#define MatchROM 0x55        //ƥ��ROM
#define AlarmROM 0xEC        //�澯ROM
#define StartConvert 0x44    //��ʼ�¶�ת�������¶�ת���ڼ����������0��ת�����������1
#define ReadScratchpad 0xBE  //���ݴ�����9���ֽ�
#define WriteScratchpad 0x4E //д�ݴ������¶ȸ澯TH��TL
#define CopyScratchpad 0x48  //���ݴ������¶ȸ澯���Ƶ�EEPROM���ڸ����ڼ����������0������������1
#define RecallEEPROM 0xB8    //��EEPROM���¶ȸ澯���Ƶ��ݴ����У������ڼ����0��������ɺ����1
#define ReadPower 0xB4       //����Դ�Ĺ��緽ʽ��0Ϊ������Դ���磻1Ϊ�ⲿ��Դ����

static unsigned char TempX_TAB[16] = {0x00, 0x01, 0x01, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x06, 0x06, 0x07, 0x08, 0x08, 0x09, 0x09};

// void delay_us(u32 Nus)
// {
//
//   SysTick->LOAD = Nus * 9;
//                         //ʱ�����
//   SysTick->CTRL |= 0x01;
//                               //��ʼ����
//   while (!(SysTick->CTRL & (1 << 16)));
//        //�ȴ�ʱ�䵽��
//   SysTick->CTRL = 0X00000000;
//                     //�رռ�����
//   SysTick->VAL = 0X00000000;
//                       //��ռ�����
// }
//
unsigned char ResetDS18B20(void)
{
    unsigned char resport;
    unsigned int ii = 0 ;
    SetDQ();
    delay_us(50);

    ResetDQ();
    delay_us(500);
    //500us ����ʱ���ʱ�䷶Χ���Դ�480��960΢�룩
    SetDQ();
    delay_us(40);
    //40us
    //resport = GetDQ();
    while (GetDQ() && ii++<500000 )
        ;
    delay_us(500);
    //500us
    SetDQ();
    return resport;
}
void DS18B20WriteByte(unsigned char Dat)
{
    unsigned char i;
    for (i = 8; i > 0; i--)

    {
        ResetDQ();
        //��15u���������������ϣ�DS18B20��15-60u����
        delay_us(5);
        //5us
        if (Dat & 0x01)
            SetDQ();
        else
            ResetDQ();
        delay_us(65);
        //65us
        SetDQ();
        delay_us(2);
        //������λ��Ӧ����1us
        Dat >>= 1;
    }
}

unsigned char DS18B20ReadByte(void)
{
    unsigned char i, Dat;
    SetDQ();
    delay_us(5);
    for (i = 8; i > 0; i--)

    {
        Dat >>= 1;
        ResetDQ();
        //�Ӷ�ʱ��ʼ�������ź��߱�����15u�ڣ��Ҳ�������������15u�����
        delay_us(5);
        //5us
        SetDQ();
        delay_us(5);
        //5us
        if (GetDQ())
            Dat |= 0x80;
        else
            Dat &= 0x7f;

        delay_us(65);
        //65us
        SetDQ();
    }
    return Dat;
}

void ReadRom(unsigned char *Read_Addr)
{
    unsigned char i;
    DS18B20WriteByte(ReadROM);

    for (i = 8; i > 0; i--)

    {
        *Read_Addr = DS18B20ReadByte();
        Read_Addr++;
    }
}

void DS18B20Init(unsigned char Precision, unsigned char AlarmTH, unsigned char AlarmTL)
{
    unsigned int ii = 0 ;
    DisableINT();
    ResetDS18B20();
    DS18B20WriteByte(SkipROM);

    DS18B20WriteByte(WriteScratchpad);
    DS18B20WriteByte(AlarmTL);
    DS18B20WriteByte(AlarmTH);
    DS18B20WriteByte(Precision);
    ResetDS18B20();
    DS18B20WriteByte(SkipROM);

    DS18B20WriteByte(CopyScratchpad);
    EnableINT();
    while (!GetDQ() && ii++<500000)
        ;
    //�ȴ��������  ///////////
}

void DS18B20StartConvert(void)
{
    DisableINT();
    ResetDS18B20();
    DS18B20WriteByte(SkipROM);

    DS18B20WriteByte(StartConvert);

    EnableINT();
}

void DS18B20_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(DS_RCC_PORT, ENABLE);
    GPIO_InitStructure.GPIO_Pin = DS_DQIO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    //��©���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //2Mʱ���ٶ�
    GPIO_Init(DS_PORT, &GPIO_InitStructure);
}

void ds18b20_start(void)
{
    DS18B20_Configuration();
    DS18B20Init(DS_PRECISION, DS_AlarmTH, DS_AlarmTL);
    DS18B20StartConvert();
}

unsigned short ds18b20_read(void)
{
    unsigned char TemperatureL, TemperatureH;
    unsigned int Temperature;
    DisableINT();
    ResetDS18B20();
    DS18B20WriteByte(SkipROM);

    DS18B20WriteByte(ReadScratchpad);
    TemperatureL = DS18B20ReadByte();
    TemperatureH = DS18B20ReadByte();

    ResetDS18B20();
    EnableINT();
    if (TemperatureH & 0x80)

    {
        TemperatureH = (~TemperatureH) | 0x08;
        TemperatureL = ~TemperatureL + 1;
        if (TemperatureL == 0)
            TemperatureH += 1;
    }
    TemperatureH = (TemperatureH << 4) + ((TemperatureL & 0xf0) >> 4);
    TemperatureL = TempX_TAB[TemperatureL & 0x0f];
    //bit0-bit7ΪС��λ��bit8-bit14Ϊ����λ��bit15Ϊ����λ
    Temperature = TemperatureH;
    Temperature = (Temperature << 8) | TemperatureL;

    DS18B20StartConvert();
    // return Temperature;

    return  TemperatureH ;
}

// #include "ds18b20.h"
// #include "delay.h"

// //��λDS18B20
// void DS18B20_Rst(void)
// {
// 	DS18B20_IO_OUT(); //SET PA0 OUTPUT
//     DS18B20_DQ_OUT=0; //����DQ
//     delay_us(750);    //����750us
//     DS18B20_DQ_OUT=1; //DQ=1
// 	delay_us(15);     //15US
// }
// //�ȴ�DS18B20�Ļ�Ӧ
// //����1:δ��⵽DS18B20�Ĵ���
// //����0:����
// u8 DS18B20_Check(void)
// {
// 	u8 retry=0;
// 	DS18B20_IO_IN();//SET PA0 INPUT
//     while (DS18B20_DQ_IN&&retry<200)
// 	{
// 		retry++;
// 		delay_us(1);
// 	};
// 	if(retry>=200)return 1;
// 	else retry=0;
//     while (!DS18B20_DQ_IN&&retry<240)
// 	{
// 		retry++;
// 		delay_us(1);
// 	};
// 	if(retry>=240)return 1;
// 	return 0;
// }
// //��DS18B20��ȡһ��λ
// //����ֵ��1/0
// u8 DS18B20_Read_Bit(void) 			 // read one bit
// {
//     u8 data;
// 	DS18B20_IO_OUT();//SET PA0 OUTPUT
//     DS18B20_DQ_OUT=0;
// 	delay_us(2);
//     DS18B20_DQ_OUT=1;
// 	DS18B20_IO_IN();//SET PA0 INPUT
// 	delay_us(12);
// 	if(DS18B20_DQ_IN)data=1;
//     else data=0;
//     delay_us(50);
//     return data;
// }
// //��DS18B20��ȡһ���ֽ�
// //����ֵ������������
// u8 DS18B20_Read_Byte(void)    // read one byte
// {
//     u8 i,j,dat;
//     dat=0;
// 	for (i=1;i<=8;i++)
// 	{
//         j=DS18B20_Read_Bit();
//         dat=(j<<7)|(dat>>1);
//     }
//     return dat;
// }
// //дһ���ֽڵ�DS18B20
// //dat��Ҫд����ֽ�
// void DS18B20_Write_Byte(u8 dat)
//  {
//     u8 j;
//     u8 testb;
// 	DS18B20_IO_OUT();//SET PA0 OUTPUT;
//     for (j=1;j<=8;j++)
// 	{
//         testb=dat&0x01;
//         dat=dat>>1;
//         if (testb)
//         {
//             DS18B20_DQ_OUT=0;// Write 1
//             delay_us(2);
//             DS18B20_DQ_OUT=1;
//             delay_us(60);
//         }
//         else
//         {
//             DS18B20_DQ_OUT=0;// Write 0
//             delay_us(60);
//             DS18B20_DQ_OUT=1;
//             delay_us(2);
//         }
//     }
// }
// //��ʼ�¶�ת��
// void DS18B20_Start(void)// ds1820 start convert
// {
//     DS18B20_Rst();
// 	DS18B20_Check();
//     DS18B20_Write_Byte(0xcc);// skip rom
//     DS18B20_Write_Byte(0x44);// convert
// }
// //��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
// //����1:������
// //����0:����
// u8 DS18B20_Init(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO
// 	//RCC->APB2ENR|=1<<2;    //ʹ��PORTA��ʱ��
// 	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	 //ʹ��PORTA��ʱ��

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  //SPI CS
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�����������
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
// 	/* Deselect the PA0 Select high */
// 	GPIO_SetBits(GPIOA,GPIO_Pin_0);
// 	DS18B20_Rst();
// 	return DS18B20_Check();
// }
// //��ds18b20�õ��¶�ֵ
// //���ȣ�0.1C
// //����ֵ���¶�ֵ ��-550~1250��
// short DS18B20_Get_Temp(void)
// {
//     u8 temp;
//     u8 TL,TH;
// 	short tem;
//     DS18B20_Start ();                    // ds1820 start convert
//     DS18B20_Rst();
//     DS18B20_Check();
//     DS18B20_Write_Byte(0xcc);// skip rom
//     DS18B20_Write_Byte(0xbe);// convert
//     TL=DS18B20_Read_Byte(); // LSB
//     TH=DS18B20_Read_Byte(); // MSB

//     if(TH>7)
//     {
//         TH=~TH;
//         TL=~TL;
//         temp=0;//�¶�Ϊ��
//     }else temp=1;//�¶�Ϊ��
//     tem=TH; //��ø߰�λ
//     tem<<=8;
//     tem+=TL;//��õװ�λ
//     tem=(float)tem*0.625;//ת��
// 	if(temp)return tem; //�����¶�ֵ
// 	else return -tem;
// }
