#include "gps.h"
#include "string.h"

#define false 0
#define true 1

//定义数组长度
#define GPS_Buffer_Length 80
#define UTCTime_Length 11
#define latitude_Length 15
#define N_S_Length 2
#define longitude_Length 15
#define E_W_Length 2

typedef struct SaveData
{
    char GPS_Buffer[GPS_Buffer_Length];
    char isGetData;                   //是否获取到GPS数据
    char isParseData;                 //是否解析完成
    char UTCTime[UTCTime_Length];     //UTC时间
    char latitude[latitude_Length];   //纬度
    char N_S[N_S_Length];             //N/S
    char longitude[longitude_Length]; //经度
    char E_W[E_W_Length];             //E/W
    char isUsefull;                   //定位信息是否有效
} _SaveData;

#define gpsRxBufferLength 76

char gpsRxBuffer[gpsRxBufferLength];
unsigned char RX_Count;
_SaveData Save_Data;

static void errorLog(int i)
{
    //i
}

static void parseGpsBuffer(void (*callback)(char *x, char *y))
{
    char *subString;
    char *subStringNext;
    char i = 0;

    for (i = 0; i <= 6; i++)
    {
        if (i == 0)
        {
            if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == 0)
                errorLog(1); //解析错误
        }
        else
        {
            subString++;
            if ((subStringNext = strstr(subString, ",")) != 0)
            {
                char usefullBuffer[2];
                switch (i)
                {
                case 1:
                    memcpy(Save_Data.UTCTime, subString, subStringNext - subString);
                    break; //获取UTC时间
                case 2:
                    memcpy(usefullBuffer, subString, subStringNext - subString);
                    break; //获取UTC时间
                case 3:
                    memcpy(Save_Data.latitude, subString, subStringNext - subString);
                    break; //获取纬度信息
                case 4:
                    memcpy(Save_Data.N_S, subString, subStringNext - subString);
                    break; //获取N/S
                case 5:
                    memcpy(Save_Data.longitude, subString, subStringNext - subString);
                    break; //获取经度信息
                case 6:
                    memcpy(Save_Data.E_W, subString, subStringNext - subString);
                    break; //获取E/W
                default:
                    break;
                }

                subString = subStringNext;
                Save_Data.isParseData = true;
                if (usefullBuffer[0] == 'A')
                {
                    Save_Data.isUsefull = true;
                }
                else if (usefullBuffer[0] == 'V')
                    Save_Data.isUsefull = false;
            }
            else
            {
                errorLog(2); //解析错误
            }
        }
    }

    if (Save_Data.isUsefull == true)
    {
        Save_Data.isUsefull = false;
        callback(Save_Data.longitude, Save_Data.latitude);

        memset(Save_Data.latitude, 0, latitude_Length);
        memset(Save_Data.longitude, 0, longitude_Length);
    }
}

void GPS_parse(unsigned char *input_buff, unsigned int input_len, void (*callback)(char *x, char *y))
{

    int index;
    char temp;
    for (index = 0; index < input_len; index++)
    {
        temp = (char)input_buff[index];

        if (temp == '$')
        {
            RX_Count = 0;
        }

        if (RX_Count <= 5)
        {
            gpsRxBuffer[RX_Count++] = temp;
        }
        else if (gpsRxBuffer[0] == '$' & gpsRxBuffer[4] == 'M' && gpsRxBuffer[5] == 'C') //确定是否收到"GPRMC/GNRMC"这一帧数据
        {
            gpsRxBuffer[RX_Count++] = temp;
            if (temp == '\n')
            {
                memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);  //清空
                memcpy(Save_Data.GPS_Buffer, gpsRxBuffer, RX_Count); //保存数据
                Save_Data.isGetData = true;
                RX_Count = 0;
                memset(gpsRxBuffer, 0, gpsRxBufferLength); //清空

                parseGpsBuffer(callback);
            }

            if (RX_Count >= 75)
            {
                RX_Count = 75;
                gpsRxBuffer[RX_Count] = '\0'; //添加结束符
            }
        }
    }
}
