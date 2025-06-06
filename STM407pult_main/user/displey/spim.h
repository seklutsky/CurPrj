
#ifndef _SPIM_H
#define _SPIM_H

#include "types.h"


// ��������� ������������� spi (SPI1 ��� SPI2) � ������ master
void spim_init(SPI_TypeDef* SPIx, uint8_t WordLen);
// ��������� ���������� ������ 16-������ ����
void SPI_send16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 8-������ ����
void SPI_send8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 16-������ ����
void SPI_recv16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 8-������ ����
void SPI_recv8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len);

#endif
