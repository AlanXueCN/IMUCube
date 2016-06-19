/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_adc.h"
#include "modules\module_serial.h"

#include "imuCube_bsp.h"
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_CKOCK_Config( void )
{
  nrf_drv_clock_init();
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_GPIO_Config( void )
{
  nrf_gpio_cfg(KEY, NRF_GPIO_PIN_DIR_INPUT,
                    NRF_GPIO_PIN_INPUT_CONNECT,
                    NRF_GPIO_PIN_PULLDOWN,
                    NRF_GPIO_PIN_S0S1,
                    NRF_GPIO_PIN_NOSENSE);
  nrf_gpio_cfg(BUZ, NRF_GPIO_PIN_DIR_OUTPUT,
                    NRF_GPIO_PIN_INPUT_DISCONNECT,
                    NRF_GPIO_PIN_NOPULL,
                    NRF_GPIO_PIN_S0S1,
                    NRF_GPIO_PIN_NOSENSE);
  nrf_gpio_cfg(MOT, NRF_GPIO_PIN_DIR_OUTPUT,
                    NRF_GPIO_PIN_INPUT_DISCONNECT,
                    NRF_GPIO_PIN_NOPULL,
                    NRF_GPIO_PIN_S0S1,
                    NRF_GPIO_PIN_NOSENSE);

  BUZ_Reset();
  MOT_Reset();
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_ADC_Config( void )
{
  ADC_Config();
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_UART_Config( void )
{
  Serial_Config();
  printf("\fHello World!!\r\n");
}
/*====================================================================================================*/
/*====================================================================================================*/
