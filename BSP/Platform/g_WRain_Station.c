/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2014; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                      Texas Instruments MSP430
*                                               on the
*                                          MSP-EXP430F5259LP
*                                          Evaluation Board
*
* Filename      : g_WRain_Station.c
* Version       : V1.00
* Programmer(s) : GLZ
*********************************************************************************************************
*/
#include  <hal_layer_api.h>
#include  <bsp.h>

#if (PRODUCT_TYPE == WRain_Station)

#define SensorNum		5 
#define CMDLength       8

AppStruct  App;
DataStruct *AppDataPointer;


uint8_t Inqure_RainGauge[Command_1Length]={0x08,0x03,0x00,0x00,0x00,0x01,0x84,0x93};       //����-XPH
uint8_t ScadaUSLV[Command_1Length]  = {0x02,0x03,0x00,0x00,0x00,0x01,0x84,0x39};	   //������Һλ

uint32_t SensorCahe = 0;
uint32_t sSensorCahe = 0;


/*******************************************************************************
* ������	: AnalyzeComand
* ����	    	: ����������ָ��
* �������  	: ��
* ���ز���  	: ��
*******************************************************************************/
static void AnalyzeComand(uint8_t *data,uint8_t Len)
{
	if(Len != 0)
	{
		hal_Delay_ms(50);

		CalcuResult = Crc16(data,Len-2);
		CRC_Result[0] = (unsigned char)((CalcuResult & 0xFF00) >> 8);
		CRC_Result[1] = (unsigned char)(CalcuResult & 0xFF);
		if((data[Len-2] == CRC_Result[0]) && (data[Len-1] == CRC_Result[1]))   //�ж����ݽ����Ƿ�����쳣
		{
			if(data[1]==0x03)
			{
				switch(data[0])
				{
					// case 0x01:		//Ͷ��ʽҺλ������
						// SensorCahe = (uint32_t)data[3]*256 + data[4];
						// AppDataPointer->WRainData.LVValue = SensorCahe;
						// SetBit(SensorStatus_H, 0);   //������״̬λ��0
						// Send_Buffer[9] = SensorCahe / 256;
						// Send_Buffer[10] = SensorCahe % 256;
						// break;
					case 0x02:		//������Һλ������
						SensorCahe = (uint32_t)data[3]*256 + data[4];
						SensorCahe = SensorCahe/10;  //mm��λת��Ϊcm
						AppDataPointer->WRainData.LVValue = SensorCahe;
						SetBit(SensorStatus_H, 1);   //������״̬λ��1
						Send_Buffer[7] = SensorCahe / 256;
						Send_Buffer[8] = SensorCahe % 256;
						break;
					// case 0x03:		//��Ӧʽ����ˮ��Һλ
						// SensorCahe = (uint32_t)data[3]*256 + data[4];
						// AppDataPointer->WRainData.LVValue = SensorCahe;
						// SetBit(SensorStatus_H, 0);   //������״̬λ��0
						// Send_Buffer[9] = SensorCahe / 256;
						// Send_Buffer[10] = SensorCahe % 256;
						// break;
					case 0x08:	    //����
						SensorCahe = (uint32_t)data[3]*256 + data[4];
						ssSensorCahe = ssSensorCahe + SensorCahe;  //�ۼ�
						AppDataPointer->WRainData.RainGauge = (float)ssSensorCahe/2/10;
						SetBit(SensorStatus_H, 0);   //������״̬λ��1
						Send_Buffer[9] = ssSensorCahe / 256;
						Send_Buffer[10] = ssSensorCahe % 256;
						break;
					default:
						break;
				}//switch(data[0]) END	
			} //(data[1]==0x03)  END
 		} //CRC  END

		SensorStatusBuff[1] = SensorStatus_L;
		SensorStatusBuff[0] = SensorStatus_H;

		AppDataPointer->TerminalInfoData.SensorStatus = (uint16_t)SensorStatus_H*256 + (uint16_t)SensorStatus_L;

		Clear_CMD_Buffer(dRxBuff,dRxNum);
		dRxNum=0;
	}
}

/*******************************************************************************
* ������		: InqureSensor
* ����	    	: �ɼ����������ݣ���������ֵ
* �������  	: ��
* ���ز���  	: ��
*******************************************************************************/
void InqureSensor(void)
{
	volatile char scadaIndex;
	for(scadaIndex=1;scadaIndex<=SensorNum;scadaIndex++)
	{
		Send_485_Enable;
		hal_Delay_ms(5);
		switch(scadaIndex)
		{
			case 1:
				OSBsp.Device.Usart3.WriteNData(Inqure_RainGauge,CMDLength);//����
				break;
			case 2:
				OSBsp.Device.Usart3.WriteNData(ScadaUSLV,CMDLength);       //������Һλ
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				break;
		}
		hal_Delay_ms(2);//�߲����ʽ�����ʱΪ1-2ms���������׶������Ͳ�����������ʱ����4800��ʱ10ms���������׶���
		Recive_485_Enable;
		hal_Delay_sec(1);
		LED_ON;
		AnalyzeComand(dRxBuff,dRxNum);
		LED_OFF;
	}
}




#endif //(PRODUCT_TYPE == Voc_Station)