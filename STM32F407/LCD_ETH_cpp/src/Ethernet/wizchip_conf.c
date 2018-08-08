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

#include "Ethernet\wizchip_conf.h"
/**
 * @brief Default function to enable interrupt.
 * @note This function help not to access wrong address. If you do not describe this function or register any functions,
 * null function is called.
 */
void 	  wizchip_cris_enter(void)           {};
/**
 * @brief Default function to disable interrupt.
 * @note This function help not to access wrong address. If you do not describe this function or register any functions,
 * null function is called.
 */
void 	  wizchip_cris_exit(void)          {};
/**
 * @brief Default function to select chip.
 * @note This function help not to access wrong address. If you do not describe this function or register any functions,
 * null function is called.
 */
void 	wizchip_cs_select(void)            {};
/**
 * @brief Default function to deselect chip.
 * @note This function help not to access wrong address. If you do not describe this function or register any functions,
 * null function is called.
 */
void 	wizchip_cs_deselect(void)          {};
/**
 * @brief Default function to read in SPI interface.
 * @note This function help not to access wrong address. If you do not describe this function or register any functions,
 * null function is called.
 */
uint8_t wizchip_spi_readbyte(void)        {return 0;};
/**
 * @brief Default function to write in SPI interface.
 * @note This function help not to access wrong address. If you do not describe this function or register any functions,
 * null function is called.
 */
void 	wizchip_spi_writebyte(uint8_t wb) {};

/**
 * @\ref _WIZCHIP instance
 */
_WIZCHIP  WIZCHIP =
      {
      .CRIS._enter         = wizchip_cris_enter,
      .CRIS._exit          = wizchip_cris_exit,
      .CS._select          = wizchip_cs_select,
      .CS._deselect        = wizchip_cs_deselect,
      .IF.SPI._read_byte   = wizchip_spi_readbyte,
      .IF.SPI._write_byte  = wizchip_spi_writebyte
      };

static uint8_t    _DNS_[4];      // DNS server ip address
static dhcp_mode  _DHCP_;        // DHCP mode

void reg_wizchip_cris_cbfunc(void(*cris_en)(void), void(*cris_ex)(void))
{
   if(!cris_en || !cris_ex)
   {
      WIZCHIP.CRIS._enter = wizchip_cris_enter;
      WIZCHIP.CRIS._exit  = wizchip_cris_exit;
   }
   else
   {
      WIZCHIP.CRIS._enter = cris_en;
      WIZCHIP.CRIS._exit  = cris_ex;
   }
}

void reg_wizchip_cs_cbfunc(void(*cs_sel)(void), void(*cs_desel)(void))
{
   if(!cs_sel || !cs_desel)
   {
      WIZCHIP.CS._select   = wizchip_cs_select;
      WIZCHIP.CS._deselect = wizchip_cs_deselect;
   }
   else
   {
      WIZCHIP.CS._select   = cs_sel;
      WIZCHIP.CS._deselect = cs_desel;
   }
}


void reg_wizchip_spi_cbfunc(uint8_t (*spi_rb)(void), void (*spi_wb)(uint8_t wb))
{
  
   if(!spi_rb || !spi_wb)
   {
      WIZCHIP.IF.SPI._read_byte   = wizchip_spi_readbyte;
      WIZCHIP.IF.SPI._write_byte  = wizchip_spi_writebyte;
   }
   else
   {
      WIZCHIP.IF.SPI._read_byte   = spi_rb;
      WIZCHIP.IF.SPI._write_byte  = spi_wb;
   }
}

int8_t ctlwizchip(ctlwizchip_type cwtype, void* arg)
{
   uint8_t tmp = 0;
   uint8_t* ptmp[2] = {0,0};
   
   switch(cwtype)
   {
      case CW_RESET_WIZCHIP:
         wizchip_sw_reset();
         break;
      case CW_INIT_WIZCHIP:
         if(arg != 0) 
         {
            ptmp[0] = (uint8_t*)arg;
            ptmp[1] = ptmp[0] + _WIZCHIP_SOCK_NUM_;
         }
         return wizchip_init(ptmp[0], ptmp[1]);
      case CW_CLR_INTERRUPT:
         wizchip_clrinterrupt(*((intr_kind*)arg));
         break;
      case CW_GET_INTERRUPT:
        *((intr_kind*)arg) = wizchip_getinterrupt();
         break;
      case CW_SET_INTRMASK:
         wizchip_setinterruptmask(*((intr_kind*)arg));
         break;         
      case CW_GET_INTRMASK:
         *((intr_kind*)arg) = wizchip_getinterruptmask();
         break;
      case CW_SET_INTRTIME:
         setINTLEVEL(*(uint16_t*)arg);
         break;
      case CW_GET_INTRTIME:
         *(uint16_t*)arg = getINTLEVEL();
         break;
      case CW_RESET_PHY:
         wizphy_reset();
         break;
      case CW_SET_PHYCONF:
         wizphy_setphyconf((wiz_PhyConf*)arg);
         break;
      case CW_GET_PHYCONF:
         wizphy_getphyconf((wiz_PhyConf*)arg);
         break;
      case CW_GET_PHYSTATUS:
         break;
      case CW_SET_PHYPOWMODE:
         return wizphy_setphypmode(*(uint8_t*)arg);
      case CW_GET_PHYPOWMODE:
         tmp = wizphy_getphypmode();
         if((int8_t)tmp == -1) return -1;
         *(uint8_t*)arg = tmp;
         break;
      case CW_GET_PHYLINK:
         tmp = wizphy_getphylink();
         if((int8_t)tmp == -1) return -1;
         *(uint8_t*)arg = tmp;
         break;
      default:
         return -1;
   }
   return 0;
}


int8_t ctlnetwork(ctlnetwork_type cntype, void* arg)
{
   
   switch(cntype)
   {
      case CN_SET_NETINFO:
         wizchip_setnetinfo((wiz_NetInfo*)arg);
         break;
      case CN_GET_NETINFO:
         wizchip_getnetinfo((wiz_NetInfo*)arg);
         break;
      case CN_SET_NETMODE:
         return wizchip_setnetmode(*(netmode_type*)arg);
      case CN_GET_NETMODE:
         *(netmode_type*)arg = wizchip_getnetmode();
         break;
      case CN_SET_TIMEOUT:
         wizchip_settimeout((wiz_NetTimeout*)arg);
         break;
      case CN_GET_TIMEOUT:
         wizchip_gettimeout((wiz_NetTimeout*)arg);
         break;
      default:
         return -1;
   }
   return 0;
}

void wizchip_sw_reset(void)
{
   uint8_t gw[4], sn[4], sip[4];
   uint8_t mac[6];

   getSHAR(mac);
   getGAR(gw);  getSUBR(sn);  getSIPR(sip);
   setMR(MR_RST);
   getMR(); // for delay
   setSHAR(mac);
   setGAR(gw);
   setSUBR(sn);
   setSIPR(sip);
}

int8_t wizchip_init(uint8_t* txsize, uint8_t* rxsize)
{
   int8_t i;
   int8_t tmp = 0;
   
   wizchip_sw_reset();
   if(txsize)
   {
      tmp = 0;
      for(i = 0 ; i < _WIZCHIP_SOCK_NUM_; i++)
         tmp += txsize[i];
      if(tmp > 16) return -1;
      for(i = 0 ; i < _WIZCHIP_SOCK_NUM_; i++)
         setSn_TXBUF_SIZE(i, txsize[i]);
   }
   if(rxsize)
   {
      tmp = 0;
      for(i = 0 ; i < _WIZCHIP_SOCK_NUM_; i++)
         tmp += rxsize[i];
      if(tmp > 16) return -1;
      for(i = 0 ; i < _WIZCHIP_SOCK_NUM_; i++)
         setSn_RXBUF_SIZE(i, rxsize[i]);
   }
   return 0;
}

void wizchip_clrinterrupt(intr_kind intr)
{
   uint8_t ir  = (uint8_t)intr;
   uint8_t sir = (uint8_t)((uint16_t)intr >> 8);
   
   setIR(ir);
   setSIR(sir);
}

intr_kind wizchip_getinterrupt(void)
{
   uint8_t ir  = 0;
   uint8_t sir = 0;
   uint16_t ret = 0;
   
   ir  = getIR();
   sir = getSIR();

  ret = sir;
  ret = (ret << 8) + ir;
  return (intr_kind)ret;
}

void wizchip_setinterruptmask(intr_kind intr)
{
   uint8_t imr  = (uint8_t)intr;
   uint8_t simr = (uint8_t)((uint16_t)intr >> 8);

   setIMR(imr);
   setSIMR(simr);
}

intr_kind wizchip_getinterruptmask(void)
{
   uint8_t imr  = 0;
   uint8_t simr = 0;
   uint16_t ret = 0;

   imr  = getIMR();
   simr = getSIMR();

  ret = simr;
  ret = (ret << 8) + imr;
  return (intr_kind)ret;
}

int8_t wizphy_getphylink(void)
{
   int8_t tmp;

   if(getPHYCFGR() & PHYCFGR_LNK_ON)
      tmp = PHY_LINK_ON;
   else
      tmp = PHY_LINK_OFF;
   return tmp;
}


int8_t wizphy_getphypmode(void)
{
   int8_t tmp = 0;
   
    if(getPHYCFGR() & PHYCFGR_OPMDC_PDOWN)
       tmp = PHY_POWER_DOWN;
    else 
       tmp = PHY_POWER_NORM;
	
   return tmp;
}

void wizphy_reset(void)
{
   uint8_t tmp = getPHYCFGR();
   
   tmp &= PHYCFGR_RST;
   setPHYCFGR(tmp);
   tmp = getPHYCFGR(); 
   tmp |= ~PHYCFGR_RST;
   setPHYCFGR(tmp);
}

void wizphy_setphyconf(wiz_PhyConf* phyconf)
{
   uint8_t tmp = 0;
   
   if(phyconf->by == PHY_CONFBY_SW)
      tmp |= PHYCFGR_OPMD;
   else
      tmp &= ~PHYCFGR_OPMD;
   if(phyconf->mode == PHY_MODE_AUTONEGO)
      tmp |= PHYCFGR_OPMDC_ALLA;
   else
   {
      if(phyconf->duplex == PHY_DUPLEX_FULL)
      {
         if(phyconf->speed == PHY_SPEED_100)
            tmp |= PHYCFGR_OPMDC_100F;
         else
            tmp |= PHYCFGR_OPMDC_10F;
      }   
      else
      {
         if(phyconf->speed == PHY_SPEED_100)
            tmp |= PHYCFGR_OPMDC_100H;
         else
            tmp |= PHYCFGR_OPMDC_10H;
      }
   }
   setPHYCFGR(tmp);
   wizphy_reset();
}

void wizphy_getphyconf(wiz_PhyConf* phyconf)
{
   uint8_t tmp = 0;
   
   tmp = getPHYCFGR();
   phyconf->by   = (tmp & PHYCFGR_OPMD) ? PHY_CONFBY_SW : PHY_CONFBY_HW;
   switch(tmp & PHYCFGR_OPMDC_ALLA)
   {
      case PHYCFGR_OPMDC_ALLA:
      case PHYCFGR_OPMDC_100FA: 
         phyconf->mode = PHY_MODE_AUTONEGO;
         break;
      default:
         phyconf->mode = PHY_MODE_MANUAL;
         break;
   }
   switch(tmp & PHYCFGR_OPMDC_ALLA)
   {
      case PHYCFGR_OPMDC_100FA:
      case PHYCFGR_OPMDC_100F:
      case PHYCFGR_OPMDC_100H:
         phyconf->speed = PHY_SPEED_100;
         break;
      default:
         phyconf->speed = PHY_SPEED_10;
         break;
   }
   switch(tmp & PHYCFGR_OPMDC_ALLA)
   {
      case PHYCFGR_OPMDC_100FA:
      case PHYCFGR_OPMDC_100F:
      case PHYCFGR_OPMDC_10F:
         phyconf->duplex = PHY_DUPLEX_FULL;
         break;
      default:
         phyconf->duplex = PHY_DUPLEX_HALF;
         break;
   }
}

void wizphy_getphystat(wiz_PhyConf* phyconf)
{
   uint8_t tmp = getPHYCFGR();
   
   phyconf->duplex = (tmp & PHYCFGR_DPX_FULL) ? PHY_DUPLEX_FULL : PHY_DUPLEX_HALF;
   phyconf->speed  = (tmp & PHYCFGR_SPD_100) ? PHY_SPEED_100 : PHY_SPEED_10;
}

int8_t wizphy_setphypmode(uint8_t pmode)
{
   uint8_t tmp = 0;
   
   tmp = getPHYCFGR();
   if((tmp & PHYCFGR_OPMD)== 0) return -1;
   tmp &= ~PHYCFGR_OPMDC_ALLA;         
   if( pmode == PHY_POWER_DOWN)
      tmp |= PHYCFGR_OPMDC_PDOWN;
   else
      tmp |= PHYCFGR_OPMDC_ALLA;
   setPHYCFGR(tmp);
   wizphy_reset();
   tmp = getPHYCFGR();
   if( pmode == PHY_POWER_DOWN)
   {
      if(tmp & PHYCFGR_OPMDC_PDOWN) return 0;
   }
   else
   {
      if(tmp & PHYCFGR_OPMDC_ALLA) return 0;
   }
   return -1;
}


void wizchip_setnetinfo(wiz_NetInfo* pnetinfo)
{
   setSHAR(pnetinfo->mac);
   setGAR(pnetinfo->gw);
   setSUBR(pnetinfo->sn);
   setSIPR(pnetinfo->ip);
   _DNS_[0] = pnetinfo->dns[0];
   _DNS_[1] = pnetinfo->dns[1];
   _DNS_[2] = pnetinfo->dns[2];
   _DNS_[3] = pnetinfo->dns[3];
   _DHCP_   = pnetinfo->dhcp;
}

void wizchip_getnetinfo(wiz_NetInfo* pnetinfo)
{
   getSHAR(pnetinfo->mac);
   getGAR(pnetinfo->gw);
   getSUBR(pnetinfo->sn);
   getSIPR(pnetinfo->ip);
   pnetinfo->dns[0]= _DNS_[0];
   pnetinfo->dns[1]= _DNS_[1];
   pnetinfo->dns[2]= _DNS_[2];
   pnetinfo->dns[3]= _DNS_[3];
   pnetinfo->dhcp  = _DHCP_;
}

int8_t wizchip_setnetmode(netmode_type netmode)
{
   uint8_t tmp = 0;
   
   if(netmode & ~(NM_WAKEONLAN | NM_PPPOE | NM_PINGBLOCK | NM_FORCEARP)) return -1;
   
   tmp = getMR();
   tmp |= (uint8_t)netmode;
   setMR(tmp);
   return 0;
}

netmode_type wizchip_getnetmode(void)
{
   return (netmode_type) getMR();
}

void wizchip_settimeout(wiz_NetTimeout* nettime)
{
   setRCR(nettime->retry_cnt);
   setRTR(nettime->time_100us);
}

void wizchip_gettimeout(wiz_NetTimeout* nettime)
{
   nettime->retry_cnt = getRCR();
   nettime->time_100us = getRTR();
}
