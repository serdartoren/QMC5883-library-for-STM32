# QMC5883-library-for-STM32

## Example usage
```ruby

#include"QMC5883.h"

QMC_t module;
float Compas_Value;

int main(void)
{
  QMC_init(&module, &hi2c?, 200);
  while (1)
  {
	if(QMC_read(&module)==0)
	{
		HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin, GPIO_PIN_SET);
		Compas_Value=module.heading;
	}
	else
	{
		HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin, GPIO_PIN_RESET);
	}
	HAL_Delay(50);
  }
}
```

| Command | Description |
| --- | --- |
| uint8_t QMC_init(QMC_t *qmc,I2C_HandleTypeDef *i2c,uint8_t Output_Data_Rate) | It's configs to module for continuous mode |
| uint8_t QMC_read(QMC_t *qmc) | It's writes readings to QMC_t type structure |
| float   QMC_readHeading(QMC_t *qmc) | it's sımular with QMC_read() just gives heading angle as the return |
| uint8_t QMC_Standby(QMC_t *qmc) | It's puts the module in standby mode. When you want use again you can use QMC_init(). |
| uint8_t QMC_Reset(QMC_t *qmc) | It's do software reset to module |

## Return values meaning 
All uint8_t return values have similar meaning.
If the function is successful, it returns 0. Else ,it returns 1.

