/*
 * QMC5883.c
 *
 *  Created on: 11 May 2021
 *      Author: Serdar
 */
#include"QMC5883.h"
#include "math.h"

//###############################################################################################################
uint8_t QMC_init(QMC_t *qmc,I2C_HandleTypeDef *i2c,uint8_t Output_Data_Rate)
{
	uint8_t array[2];
	qmc->i2c=i2c;
	qmc->Control_Register=0x11;
	array[0]=1;
	array[1]=qmc->Control_Register;

	if(Output_Data_Rate==200)qmc->Control_Register|=0b00001100;
	else if(Output_Data_Rate==100)qmc->Control_Register|=0b00001000;
	else if(Output_Data_Rate==50)qmc->Control_Register|=0b00000100;
	else if(Output_Data_Rate==10)qmc->Control_Register|=0b00000000;
	else qmc->Control_Register|=0b00001100;

	if(HAL_I2C_Mem_Write(qmc->i2c, 0x1A, 0x0B, 1, &array[0], 1, 100)!=HAL_OK)return 1;
	if(HAL_I2C_Mem_Write(qmc->i2c, 0x1A, 0x09, 1, &array[1], 1, 100)!=HAL_OK)return 1;

	return 0;
}

uint8_t QMC_read(QMC_t *qmc)
{
	  qmc->datas[0]=0;
	  HAL_I2C_Mem_Read(qmc->i2c, 0x1A, 0x06, 1, qmc->datas, 1, 100);

	  if((qmc->datas[0]&0x01)==1)
	  {
		  HAL_I2C_Mem_Read(qmc->i2c, 0x1A, 0x00, 1, qmc->datas, 6, 100);
		  qmc->Xaxis= (qmc->datas[1]<<8) | qmc->datas[0];
		  qmc->Yaxis= (qmc->datas[3]<<8) | qmc->datas[2];
		  qmc->Zaxis= (qmc->datas[5]<<8) | qmc->datas[4];

		  qmc->compas=atan2f(qmc->Yaxis,qmc->Xaxis)*180.00/M_PI;

		  if(qmc->compas>0)
		  {
			  qmc->heading= qmc->compas;
		  }
		  else
		  {
			  qmc->heading=360+qmc->compas;
		  }
	  }
	  else
	  {
		  return 1;
	  }
return 0;
}

float QMC_readHeading(QMC_t *qmc)
{
	QMC_read(qmc);
	return qmc->heading;
}

uint8_t QMC_Standby(QMC_t *qmc)
{
	uint8_t array[1]={0};
	if(HAL_I2C_Mem_Write(qmc->i2c, 0x1A, 0x09, 1, &array[0], 1, 100)!=HAL_OK)return 1;
	return 0;
}
uint8_t QMC_Reset(QMC_t *qmc)
{
	uint8_t array[1]={0x80};
	if(HAL_I2C_Mem_Write(qmc->i2c, 0x1A, 0x0A, 1, &array[0], 1, 100)!=HAL_OK)return 1;
	return 0;
}
