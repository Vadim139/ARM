/* Wiznet W5500 Library
 * Copyright (c) 2013, WIZnet Co., LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include "Ethernet\W5500\w5500.h"



////////////////////////////////////////////////////

uint8_t  WIZCHIP_READ(uint32_t AddrSel)
{
   uint8_t ret;

   WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();

   AddrSel |= (_W5500_SPI_READ_);


   WIZCHIP.IF.SPI._write_byte((AddrSel & 0x00FF0000) >> 16);
   WIZCHIP.IF.SPI._write_byte((AddrSel & 0x0000FF00) >>  8);
   WIZCHIP.IF.SPI._write_byte((AddrSel & 0x000000FF) >>  0);
   ret = WIZCHIP.IF.SPI._read_byte();

////   ret = TM_SPI_Send(SPI1,AddrSel);
//   TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x00FF0000) >> 16);
//   TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x0000FF00) >>  8);
//   TM_SPI_Send_only(ETH_SPI,(AddrSel & 0x000000FF) >>  0);
////   ret = SPI_I2S_ReceiveData(ETH_SPI);
//   ret = TM_SPI_Send(SPI1,0xFF);


   WIZCHIP.CS._deselect();
   WIZCHIP_CRITICAL_EXIT();
   return ret;
}

void     WIZCHIP_WRITE(uint32_t AddrSel, uint8_t wb )
{
    WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();

   AddrSel |= (_W5500_SPI_WRITE_);

   WIZCHIP.IF.SPI._write_byte((AddrSel & 0x00FF0000) >> 16);
   WIZCHIP.IF.SPI._write_byte((AddrSel & 0x0000FF00) >>  8);
   WIZCHIP.IF.SPI._write_byte((AddrSel & 0x000000FF) >>  0);
   WIZCHIP.IF.SPI._write_byte(wb);

//   TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x00FF0000) >> 16);
//   TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x0000FF00) >>  8);
//   TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x000000FF) >>  0);
//   TM_SPI_Send_only(ETH_SPI, wb);

   WIZCHIP.CS._deselect();
   WIZCHIP_CRITICAL_EXIT();
}
         
void     WIZCHIP_READ_BUF (uint32_t AddrSel, uint8_t* pBuf, uint16_t len)
{
   uint16_t i = 0;
   
   WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();

    AddrSel |= (_W5500_SPI_READ_);
    WIZCHIP.IF.SPI._write_byte((AddrSel & 0x00FF0000) >> 16);
    WIZCHIP.IF.SPI._write_byte((AddrSel & 0x0000FF00) >>  8);
    WIZCHIP.IF.SPI._write_byte((AddrSel & 0x000000FF) >>  0);
//    TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x00FF0000) >> 16);
//    TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x0000FF00) >>  8);
//    TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x000000FF) >>  0);

	for(i = 0; i < len; i++)
//		pBuf[i] = SPI_I2S_ReceiveData(ETH_SPI);
//		pBuf[i] = TM_SPI_Send(SPI1,AddrSel);
        	pBuf[i] = WIZCHIP.IF.SPI._read_byte();
  
   WIZCHIP.CS._deselect();
   WIZCHIP_CRITICAL_EXIT();
}

void     WIZCHIP_WRITE_BUF(uint32_t AddrSel, uint8_t* pBuf, uint16_t len)
{
   uint16_t i = 0;
   
   WIZCHIP_CRITICAL_ENTER();
   WIZCHIP.CS._select();

      AddrSel |= (_W5500_SPI_WRITE_ );
      WIZCHIP.IF.SPI._write_byte((AddrSel & 0x00FF0000) >> 16);
      WIZCHIP.IF.SPI._write_byte((AddrSel & 0x0000FF00) >>  8);
      WIZCHIP.IF.SPI._write_byte((AddrSel & 0x000000FF) >>  0);

//      TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x00FF0000) >> 16);
//      TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x0000FF00) >>  8);
//      TM_SPI_Send_only(ETH_SPI, (AddrSel & 0x000000FF) >>  0);

	  for(i = 0; i < len; i++)
//		  TM_SPI_Send_only(ETH_SPI, pBuf[i]);
        	 WIZCHIP.IF.SPI._write_byte(pBuf[i]);

   WIZCHIP.CS._deselect();
   WIZCHIP_CRITICAL_EXIT();
}


uint16_t getSn_TX_FSR(uint8_t sn)
{
   uint16_t val=0,val1=0;
   
   do
   {
      val1 = WIZCHIP_READ(Sn_TX_FSR(sn));
      val1 = (val1 << 8) + WIZCHIP_READ(WIZCHIP_OFFSET_INC(Sn_TX_FSR(sn),1));
      if (val1 != 0)
      {
        val = WIZCHIP_READ(Sn_TX_FSR(sn));
        val = (val << 8) + WIZCHIP_READ(WIZCHIP_OFFSET_INC(Sn_TX_FSR(sn),1));
      }
   }while (val != val1);
   return val;
}


uint16_t getSn_RX_RSR(uint8_t sn)
{
   uint16_t val=0,val1=0;
   
   do
   {
      val1 = WIZCHIP_READ(Sn_RX_RSR(sn));
      val1 = (val1 << 8) + WIZCHIP_READ(WIZCHIP_OFFSET_INC(Sn_RX_RSR(sn),1));
      if (val1 != 0)
      {
        val = WIZCHIP_READ(Sn_RX_RSR(sn));
        val = (val << 8) + WIZCHIP_READ(WIZCHIP_OFFSET_INC(Sn_RX_RSR(sn),1));
      }
   }while (val != val1);
   return val;
}

void wiz_send_data(uint8_t sn, uint8_t *wizdata, uint16_t len)
{
   uint16_t ptr = 0;
   uint32_t addrsel = 0;
   
   if(len == 0)  return;
   ptr = getSn_TX_WR(sn);
   
   addrsel = (ptr << 8) + (WIZCHIP_TXBUF_BLOCK(sn) << 3);
   WIZCHIP_WRITE_BUF(addrsel,wizdata, len);
   
   ptr += len;
   setSn_TX_WR(sn,ptr);
}

void wiz_recv_data(uint8_t sn, uint8_t *wizdata, uint16_t len)
{
   uint16_t ptr = 0;
   uint32_t addrsel = 0;
   
   if(len == 0) return;
   ptr = getSn_RX_RD(sn);
   addrsel = (ptr << 8) + (WIZCHIP_RXBUF_BLOCK(sn) << 3);
   
   WIZCHIP_READ_BUF(addrsel, wizdata, len);
   ptr += len;
   
   setSn_RX_RD(sn,ptr);
}


void wiz_recv_ignore(uint8_t sn, uint16_t len)
{
   uint16_t ptr = 0;
   
   ptr = getSn_RX_RD(sn);
   ptr += len;
   setSn_RX_RD(sn,ptr);
}
