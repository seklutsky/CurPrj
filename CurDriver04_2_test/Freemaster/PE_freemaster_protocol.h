/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   PE_freemaster_protocol.h
*
* @brief  FreeMASTER protocol header file
*
* @version 1.0.8.0
* 
* @date Apr-11-2007
* 
*******************************************************************************/

#ifndef __FREEMASTER_PROTOCOL_H
#define __FREEMASTER_PROTOCOL_H

/*-------------------------------------
  command message - standard commands
  -------------------------------------*/
  
#define FMSTR_CMD_READMEM           0x01U
#define FMSTR_CMD_WRITEMEM          0x02U
#define FMSTR_CMD_WRITEMEMMASK      0x03U
#define FMSTR_CMD_READMEM_EX        0x04U    /* read a block of memory */
#define FMSTR_CMD_WRITEMEM_EX       0x05U    /* write a block of memory */   
#define FMSTR_CMD_WRITEMEMMASK_EX   0x06U    /* write block of memory with bit mask */   
#define FMSTR_CMD_SETUPSCOPE        0x08U
#define FMSTR_CMD_SETUPREC          0x09U
#define FMSTR_CMD_SETUPSCOPE_EX     0x0aU    /* setup the osciloscope */ 
#define FMSTR_CMD_SETUPREC_EX       0x0bU    /* setup the recorder */     
#define FMSTR_CMD_SENDAPPCMD        0x10U    /* send the application command */  
#define FMSTR_CMD_GETTSAINFO        0x11U    /* get TSA info */
#define FMSTR_CMD_GETTSAINFO_EX     0x12U    /* get TSA info 32bit */
#define FMSTR_CMD_SFIOFRAME_1       0x13U    /* deliver & execute SFIO frame (even) */
#define FMSTR_CMD_SFIOFRAME_0       0x14U    /* deliver & execute SFIO frame (odd) */
#define FMSTR_CMD_PIPE              0x15U    /* read/write pipe data */

/*-------------------------------------
  command message - Fast Commands
  -------------------------------------*/
  
/* no data part */
#define FMSTR_CMD_GETINFO           0xc0U    /* retrieve board information structure */  
#define FMSTR_CMD_STARTREC          0xc1U    /* start data recorder */   
#define FMSTR_CMD_STOPREC           0xc2U    /* stop data recorder */    
#define FMSTR_CMD_GETRECSTS         0xc3U    /* get the recorder status */   
#define FMSTR_CMD_GETRECBUFF        0xc4U
#define FMSTR_CMD_READSCOPE         0xc5U    /* read the scope data */   
#define FMSTR_CMD_GETAPPCMDSTS      0xc6U    /* get the application command status */    
#define FMSTR_CMD_GETINFOBRIEF      0xc8U    /* retrieve a subset of board information structure */  
#define FMSTR_CMD_GETRECBUFF_EX     0xc9U    /* get the recorder data */ 
#define FMSTR_CMD_SFIOGETRESP_0     0xcaU    /* retry to get last SFIO response (even) */
#define FMSTR_CMD_SFIOGETRESP_1     0xcbU    /* retry to get last SFIO response (odd) */

/* 2 bytes data part */
#define FMSTR_CMD_READVAR8          0xD0U
#define FMSTR_CMD_READVAR16         0xD1U
#define FMSTR_CMD_READVAR32         0xD2U
#define FMSTR_CMD_GETAPPCMDDATA     0xD3U    /* get the application command data */
#define FMSTR_CMD_GETSTRLEN         0xD4U    /* get string length (required by TSA) */

/* 4 bytes data part */
#define FMSTR_CMD_READVAR8_EX       0xe0U    /* read byte variable */    
#define FMSTR_CMD_READVAR16_EX      0xe1U    /* read word variable */    
#define FMSTR_CMD_READVAR32_EX      0xe2U    /* read dword variable */   
#define FMSTR_CMD_WRITEVAR8         0xe3U    /* write byte variable */   
#define FMSTR_CMD_WRITEVAR16        0xe4U    /* write word variable */   
#define FMSTR_CMD_WRITEVAR8MASK     0xe5U    /* write specified bits in byte variable  */    
#define FMSTR_CMD_GETSTRLEN_EX      0xe6U    /* get string length (required by TSA) */

/* 6 bytes data part */
#define FMSTR_CMD_WRITEVAR32        0xf0U    /* write dword variable */  
#define FMSTR_CMD_WRITEVAR16MASK    0xf1U    /* write specified bits in word variable */ 

/*-------------------------------------
  response message - status byte
  -------------------------------------*/

/* flags in response codes */
#define FMSTR_STSF_ERROR            0x80U    /* FLAG: error answer (no response data) */  
#define FMSTR_STSF_VARLEN           0x40U    /* FLAG: variable-length answer (length byte) */  
#define FMSTR_STSF_EVENT            0x20U    /* FLAG: reserved */  
  
/* confirmation codes */
#define FMSTR_STS_OK                0x00U    /* operation finished successfuly */    
#define FMSTR_STS_RECRUN            0x01U    /* data recorder is running */  
#define FMSTR_STS_RECDONE           0x02U    /* data recorder is stopped */  

/* error codes */
#define FMSTR_STC_INVCMD            0x81U    /* unknown command code */  
#define FMSTR_STC_CMDCSERR          0x82U    /* command checksum error */    
#define FMSTR_STC_CMDTOOLONG        0x83U    /* comand is too long */    
#define FMSTR_STC_RSPBUFFOVF        0x84U    /* the response would not fit into transmit buffer */   
#define FMSTR_STC_INVBUFF           0x85U    /* invalid buffer length or operation */    
#define FMSTR_STC_INVSIZE           0x86U    /* invalid size specified */    
#define FMSTR_STC_SERVBUSY          0x87U    /* service is busy */   
#define FMSTR_STC_NOTINIT           0x88U    /* service is not initialised */    
#define FMSTR_STC_EACCESS           0x89U    /* access is denied */  
#define FMSTR_STC_SFIOERR           0x8AU    /* Error in SFIO frame */  
#define FMSTR_STC_SFIOUNMATCH       0x8BU    /* Even/odd mismatch in SFIO transaction */  
#define FMSTR_STC_PIPEERR           0x8CU    /* Pipe error */  
#define FMSTR_STC_FASTRECERR        0x8DU    /* Feature not implemented in Fast Recorder */  

/******************************************************************************
* Protocol constants 
*******************************************************************************/

#define FMSTR_SOB                   0x2bU    /* '+' - start of message*/
#define FMSTR_FASTCMD               0xc0U    /* code of fast cmd 0xc0> */
#define FMSTR_FASTCMD_DATALEN_MASK  0x30U    /* mask of data length part of fast command */
#define FMSTR_FASTCMD_DATALEN_SHIFT 3
#define FMSTR_DESCR_SIZE            25U      /* length board desription string */

/* Board configuration flags  */
#define FMSTR_CFGFLAG_BIGENDIAN       0x01U      /*/< used when CPU is big endian */

/* TSA-global flags  */
#define FMSTR_TSA_INFO_VERSION_MASK   0x000fU    /*/< TSA version  */
#define FMSTR_TSA_INFO_32BIT          0x0100U    /*/< TSA address format (16/32 bit) */
#define FMSTR_TSA_INFO_HV2BA          0x0200U    /*/< TSA HawkV2 byte-addressing mode */

#endif /* __FREEMASTER_PROTOCOL_H */


