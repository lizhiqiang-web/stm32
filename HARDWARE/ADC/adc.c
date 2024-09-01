#include "adc.h"

void adc_gm_pc_init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);//PC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//GM
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	
	
	GPIO_InitStruct.GPIO_Mode=  GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,  &GPIO_InitStruct);//PC
	
	
	GPIO_InitStruct.GPIO_Mode=  GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,  &GPIO_InitStruct);//GM
	
	
	ADC_StructInit(&ADC_InitStruct);
	ADC_Init(ADC1,&ADC_InitStruct);
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = DISABLE;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	//ADC_InitStruct.ADC_NbrOfConversion =
	 ADC_CommonStructInit(&ADC_CommonInitStruct);
	 ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4;
	 ADC_CommonInit(&ADC_CommonInitStruct);
	 ADC_Cmd(ADC1,ENABLE);
}
uint16_t get_pc_adc_value(void)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_480Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==0);
	return ADC_GetConversionValue(ADC1);

}

uint16_t get_gm_adc_value(void)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==0);
	return ADC_GetConversionValue(ADC1);

}
