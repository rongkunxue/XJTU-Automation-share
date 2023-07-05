;/*****************************************************************************/
;/* W90P710.S: Startup file for Winbond W90P710 device series                 */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */ 
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2007 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


;/*
; *  The W90P710.S code is executed after CPU Reset. This file may be 
; *  translated with the following SET symbols. In uVision these SET 
; *  symbols are entered under Options - ASM - Define.
; *
; *  EBI_NOINIT: when set the startup code does not initialize External Bus 
; *              Interface (EBI)
; */


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled


;----------------------- Memory Definitions ------------------------------------

; Internal Memory Base Addresses
IRAM_BASE       EQU     0xFFE00000

; External Memory Base Addresses
EROM_BASE       EQU     0x00000000


;----------------------- Stack and Heap Definitions ----------------------------

;// <h> Stack Configuration (Stack Sizes in Bytes)
;//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:8>
;//   <o1> Supervisor Mode     <0x0-0xFFFFFFFF:8>
;//   <o2> Abort Mode          <0x0-0xFFFFFFFF:8>
;//   <o3> Fast Interrupt Mode <0x0-0xFFFFFFFF:8>
;//   <o4> Interrupt Mode      <0x0-0xFFFFFFFF:8>
;//   <o5> User/System Mode    <0x0-0xFFFFFFFF:8>
;// </h>

UND_Stack_Size  EQU     0x00000000
SVC_Stack_Size  EQU     0x00000008
ABT_Stack_Size  EQU     0x00000000
FIQ_Stack_Size  EQU     0x00000000
IRQ_Stack_Size  EQU     0x00000080
USR_Stack_Size  EQU     0x00000400

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF>
;// </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


;----------------------- System Manager Control (SMC) Definitions --------------

; System Manager Control (SMC) User Interface
SMC_BASE        EQU     0xFFF00000      ; SMC                     Base Address
PDID_OFS        EQU     0x00            ; Product Identifier Reg  Address Offset
ARBCON_OFS      EQU     0x04            ; Arbitration Control Reg Address Offset
PLLCON0_OFS     EQU     0x08            ; PLL Control Register 0  Address Offset
CLKSEL_OFS      EQU     0x0C            ; Clock Select Register   Address Offset
PLLCON1_OFS     EQU     0x10            ; PLL Control Register 1  Address Offset
I2SCKCON_OFS    EQU     0x14            ; Audio IIS Clock Ctrl R  Address Offset
IRQWAKECON_OFS  EQU     0x20            ; IRQ Wakeup Control Reg  Address Offset
IRQWAKEFLAG_OFS EQU     0x24            ; IRQ Wakeup Flag Reg     Address Offset
PMCON_OFS       EQU     0x28            ; Power Management Ctrl R Address Offset
USBTXRCON_OFS   EQU     0x30            ; USB Transciever Control Address Offset

; Constants
ECLKS_MSK       EQU     (0x1 << 4)      ; PLLCON ECLKS bit mask
CLKS_MSK        EQU     (0x7 << 1)      ; PLLCON CLKS field mask

;// <e> Clock Configuration
CLOCK_SETUP     EQU     0

;//   <h> PLL Control Register 0 (PLLCON0)
;//     <i> Fout = (Fin * NF) / (NR * NO)
;//     <i> Fout - Output clock of Output Divider
;//     <i> Fin  - External clock into the Input Divider
;//     <i> NF   - Feedback divider value (NF = FBDV + 2)
;//     <i> NO   - Output divider value (NO = OTDV)
;//     <i> NR   - Input divider value (NR = INDV + 2)
;//     <o0.16>     PWDEN: Power down mode enable
;//     <o0.7..15>  NF (= FBDV + 2): PLL VCO output clock feedback divider 
;//                     <2-513><#-2>
;//     <o0.5..6>   NO (= OTDV): PLL output clock divider
;//                     <0=> Divided by 1
;//                     <1=> Divided by 2
;//                     <2=> Divided by 2
;//                     <3=> Divided by 4
;//     <o0.0..4>   NR (= INDIV + 2): PLL input clock divider <2-33><#-2>
;//   </h>
PLLCON0_Val     EQU     0x00002F01

;//   <h> Clock Select Register (CLKSEL)
;//     <o0.28>     PS2: PS2 controller clock enable
;//     <o0.27>     KPI: Keypad controller clock enable
;//     <o0.26>     SCH1: Smart Card Host controller 1 clock enable
;//     <o0.25>     SCH0: Smart Card Host controller 0 clock enable
;//     <o0.24>     USI: USI controller clock enable
;//     <o0.23>     UART3: UART3 controller clock enable
;//     <o0.22>     UART2: UART2 controller clock enable
;//     <o0.21>     UART1: UART1 controller clock enable
;//     <o0.20>     I2C1: I2C1 controller clock enable
;//     <o0.19>     I2C0: I2C0 controller clock enable
;//     <o0.18>     RTC: RTC unit clock enable
;//     <o0.17>     PWM: PWM controller clock enable
;//     <o0.16>     AC97: Audio controller clock enable
;//     <o0.15>     USBCKS: USB host/device 48MHz clock source select
;//       <i> If USB clock 48MHz input from external GPIO0 pin is selected 
;//       <i> pin direction must be set to input.
;//                     <0=> USB clock 48MHz input from internal PLL
;//                     <1=> USB clock 48MHz input from external GPIO0 pin
;//     <o0.14>     USBD: USB device clock enable
;//     <o0.13>     GDMA: GDMA controller clock enable
;//     <o0.12>     SD: SD host controller clock enable
;//     <o0.11>     LCD: LCD controller clock enable
;//     <o0.10>     EMC: EMC controller clock enable
;//     <o0.8>      WDT: WDT clock enable
;//     <o0.7>      USBH: USB host clock enable
;//     <o0.6>      TIMER: Timer clock enable
;//     <o0.5>      UART0: UART0 controller clock enable
;//     <o0.4>      ECLKS: External clock select
;//                     <0=> External clock from EXTAL pin used as system clock
;//                     <1=> PLL output clock is used as system clock
;//     <o0.1..3>   CLKS: PLL output clock select
;//       <i> These values are based on PLL output (FOUT) of 480 MHz.
;//                     <0=> 58.594 kHz
;//                     <1=> 24 MHz
;//                     <2=> 48 MHz
;//                     <3=> 60 MHz
;//                     <4=> 80 MHz
;//   </h>
CLKSEL_Val      EQU     0x1FFF7FF8

;//   <h> PLL Control Register 1 (PLLCON1)
;//     <i> Fout = (Fin * NF) / (NR * NO)
;//     <i> Fout - Output clock of Output Divider
;//     <i> Fin  - External clock into the Input Divider
;//     <i> NF   - Feedback divider value (NF = FBDV1 + 2)
;//     <i> NO   - Output divider value (NO = OTDV1)
;//     <i> NR   - Input divider value (NR = INDV1 + 2)
;//     <o0.16>     PWDEN: PLL1 Power down mode enable
;//     <o0.7..15>  NF (= FBDV1 + 2): PLL1 VCO output clock feedback divider 
;//                     <2-513><#-2>
;//     <o0.5..6>   NO (= OTDV1): PLL1 output clock divider
;//                     <0=> Divided by 1
;//                     <1=> Divided by 2
;//                     <2=> Divided by 2
;//                     <3=> Divided by 4
;//     <o0.0..4>   NR (= INDIV1 + 2): PLL1 input clock divider <2-33><#-2>
;//   </h>
PLLCON1_Val     EQU     0x00010000

;// </e> End of Clock Configuration


;----------------------- External Bus Interface (EBI) Definitions --------------

; External Bus Interface (EBI) User Interface
EBI_BASE        EQU     0xFFF01000      ; EBI Base Address
EBICON_OFS      EQU     0x00            ; EBI Controller Register Address Offset
ROMCON_OFS      EQU     0x04            ; ROM/Flash Controller R  Address Offset
SDCCONF0_OFS    EQU     0x08            ; SDRAM Bank 0 Config Reg Address Offset
SDCCONF1_OFS    EQU     0x0C            ; SDRAM Bank 1 Config Reg Address Offset
SDTIME0_OFS     EQU     0x10            ; SDRAM Bank 0 Timing Ctl Address Offset
SDTIME1_OFS     EQU     0x14            ; SDRAM Bank 1 Timing Ctl Address Offset
EXT0CON_OFS     EQU     0x18            ; External I/O 0 Control  Address Offset
EXT1CON_OFS     EQU     0x1C            ; External I/O 1 Control  Address Offset
EXT2CON_OFS     EQU     0x20            ; External I/O 2 Control  Address Offset
EXT3CON_OFS     EQU     0x24            ; External I/O 3 Control  Address Offset
CKSKEW_OFS      EQU     0xF00           ; Clock Skew Control Reg  Address Offset

; Constants
MRSET_MSK       EQU     (0x1 << 15)     ; SDCONF0 MRSET bit mask
SWPON_MSK       EQU     (0x1 <<  8)     ; CKSKEW SWPON bit mask

;// <e> External Bus Interface Configuration (EBI)
EBI_SETUP       EQU     1

;//   <h> EBI Control Register (EBICON)
;//     <o0.27>     EXBE3: External I/O bank 3 byte enable
;//                     <0=> nWBE3 pin is by wr strobe signal
;//                     <1=> nWBE3 pin is by en signal, nWE is wr strobe signal
;//     <o0.26>     EXBE2: External I/O bank 2 byte enable
;//                     <0=> nWBE2 pin is by wr strobe signal
;//                     <1=> nWBE2 pin is by en signal, nWE is wr strobe signal
;//     <o0.25>     EXBE1: External I/O bank 1 byte enable
;//                     <0=> nWBE1 pin is by wr strobe signal
;//                     <1=> nWBE1 pin is by en signal, nWE is wr strobe signal
;//     <o0.24>     EXBE0: External I/O bank 0 byte enable
;//                     <0=> nWBE0 pin is by wr strobe signal
;//                     <1=> nWBE0 pin is by en signal, nWE is wr strobe signal
;//     <o0.18>     REFEN: SDRAM refresh cycle for SDRAM bank 0 and bank 1 enable
;//     <o0.17>     REFMOD: Refresh mode of SDRAM for SDRAM bank
;//                     <0=> Auto refresh mode
;//                     <1=> Self refresh mode
;//     <o0.16>     CLKEN: SDRAM clock enable
;//     <o0.3..15>  REFRAT: Refresh count value for SDRAM <0-8191>
;//       <i> Refresh period = REFRAT / fMCLK
;//     <o0.1..2>   WAITVT: Valid time of nWAIT signal <1-4><#-1>
;//       <i> nWAIT signal is recognized at the "nth" MCLK positive edge after 
;//       <i> the nOE or nWBE active cycle.
;//   </h>
EBICON_Val      EQU     0x080530C0

;//   <h> ROM/Flash Control Register (ROMCON)
;//     <o0.19..31> BASADDR: Base address pointer of ROM/Flash bank 
;//                     <0x0-0x7FFC0000:0x40000><#/0x40000>
;//     <o0.16..18> SIZE: The size of ROM/Flash memory
;//                     <0=> 256 kB   <1=> 512 kB   <2=> 1 MB     <3=> 2 MB
;//                     <4=> 4 MB     <5=> 8 MB     <6=> 16 MB
;//     <o0.8..11>  tPA: Page mode access cycle time
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//                     <4=> 5 MCLK   <5=> 6 MCLK   <6=> 7 MCLK   <7=> 8 MCLK
;//                     <8=> 10 MCLK  <9=> 12 MCLK  <10=> 14 MCLK <11=> 16 MCLK
;//                     <12=> 18 MCLK <13=> 20 MCLK <14=> 22 MCLK <15=> 24 MCLK
;//     <o0.4..7>   tACC: Access cycle time
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//                     <4=> 5 MCLK   <5=> 6 MCLK   <6=> 7 MCLK   <7=> 8 MCLK
;//                     <8=> 10 MCLK  <9=> 12 MCLK  <10=> 14 MCLK <11=> 16 MCLK
;//                     <12=> 18 MCLK <13=> 20 MCLK <14=> 22 MCLK <15=> 24 MCLK
;//     <o0.2..3>   BTSIZE: Boot Rom/Flash data bus width
;//                     <0=> 8-bit
;//                     <1=> 16-bit
;//                     <2=> 32-bit
;//     <o0.0..1>   PGMODE: Page mode configuration
;//                     <0=> Normal ROM
;//                     <1=> 4 word page
;//                     <2=> 8 word page
;//                     <3=> 16 word page
;//   </h>
ROMCON_Val      EQU     0x00040080

;//   <h> SDRAM Bank 0 Configuration Register (SDCONF0)
;//     <o0.19..31> BASADDR: Base address pointer of SDRAM bank 0 
;//                     <0x0-0x7FFC0000:0x40000><#/0x40000>
;//     <o0.13>     AUTOPR: SDRAM bank 0 autoprecharge enable
;//     <o0.11..12> LATENCY: The CAS latency of SDRAM bank 0
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK
;//     <o0.7>      COMPBK: Number of component bank in SDRAM bank 0
;//                     <0=> 2 banks
;//                     <1=> 4 banks
;//     <o0.5..6>   DBWD: Data bus width for SDRAM bank 0
;//                     <0=> Bank disable
;//                     <1=> 8-bit
;//                     <2=> 16-bit
;//                     <3=> 32-bit
;//     <o0.3..4>   COLUMN: Number of column address bits in SDRAM bank 0
;//                     <0=> 8
;//                     <1=> 9
;//                     <2=> 10
;//     <o0.0..2>   SIZE: Size of SDRAM bank 0
;//                     <0=> Bank disable <1=> 2 MB     <2=> 4 MB     <3=> 8 MB
;//                     <4=> 16 MB        <5=> 32 MB    <6=> 64 MB
;//   </h>
SDCONF0_Val     EQU     0xFE0090E4

;//   <h> SDRAM Bank 0 Timing Control Register (SDTIME0)
;//     <o0.8..10>  tRCD: RAS to CAS delay for SDRAM bank 0
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//                     <4=> 5 MCLK   <5=> 6 MCLK   <6=> 7 MCLK   <7=> 8 MCLK
;//     <o0.6..7>   tRDL: Last data in to precharge command for SDRAM bank 0
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//     <o0.3..5>   tRP: Row precharge time for SDRAM bank 0
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//                     <4=> 5 MCLK   <5=> 6 MCLK   <6=> 7 MCLK   <7=> 8 MCLK
;//     <o0.0..2>   tRAS: Row active time for SDRAM bank 0
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//                     <4=> 5 MCLK   <5=> 6 MCLK   <6=> 7 MCLK   <7=> 8 MCLK
;//   </h>
SDTIME0_Val     EQU     0x0000014B

;//   <h> SDRAM Bank 1 Configuration Register (SDCONF1)
;//     <o0.19..31> BASADDR: Base address pointer of SDRAM bank 1 
;//                     <0x0-0x7FFC0000:0x40000><#/0x40000>
;//     <o0.13>     AUTOPR: SDRAM bank 1 autoprecharge enable
;//     <o0.11..12> LATENCY: The CAS latency of SDRAM bank 1
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK
;//     <o0.7>      COMPBK: Number of component bank in SDRAM bank 1
;//                     <0=> 2 banks
;//                     <1=> 4 banks
;//     <o0.5..6>   DBWD: Data bus width for SDRAM bank 1
;//                     <0=> Bank disable
;//                     <1=> 8-bit
;//                     <2=> 16-bit
;//                     <3=> 32-bit
;//     <o0.3..4>   COLUMN: Number of column address bits in SDRAM bank 1
;//                     <0=> 8
;//                     <1=> 9
;//                     <2=> 10
;//     <o0.0..2>   SIZE: Size of SDRAM bank 1
;//                     <0=> Bank disable <1=> 2 MB     <2=> 4 MB     <3=> 8 MB
;//                     <4=> 16 MB        <5=> 32 MB    <6=> 64 MB
;//   </h>
SDCONF1_Val     EQU     0x00000000

;//   <h> SDRAM Bank 1 Timing Control Register (SDTIME1)
;//     <o0.8..10>  tRCD: RAS to CAS delay for SDRAM bank 1
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//                     <4=> 5 MCLK   <5=> 6 MCLK   <6=> 7 MCLK   <7=> 8 MCLK
;//     <o0.6..7>   tRDL: Last data in to precharge command for SDRAM bank 1
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//     <o0.3..5>   tRP: Row precharge time for SDRAM bank 1
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//                     <4=> 5 MCLK   <5=> 6 MCLK   <6=> 7 MCLK   <7=> 8 MCLK
;//     <o0.0..2>   tRAS: Row active time for SDRAM bank 1
;//                     <0=> 1 MCLK   <1=> 2 MCLK   <2=> 3 MCLK   <3=> 4 MCLK
;//                     <4=> 5 MCLK   <5=> 6 MCLK   <6=> 7 MCLK   <7=> 8 MCLK
;//   </h>
SDTIME1_Val     EQU     0x00000000

;//   <h> External I/O Bank 0 Control Register (EXT0CON)
;//     <o0.19..31> BASADDR: Base address pointer of externl I/O bank 0 
;//                     <0x0-0x7FFC0000:0x40000><#/0x40000>
;//     <o0.16..18> SIZE: Size of external I/O bank 0
;//                     <0=> 256 kB   <1=> 512 kB   <2=> 1 MB     <3=> 2 MB
;//                     <4=> 4 MB     <5=> 8 MB     <6=> 16 MB
;//     <o0.15>     ADRS: Address bus alignment for external I/O bank 0
;//     <o0.11..14> tACC: Access cycles of external I/O bank 0
;//                     <0=> Reserved <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//                     <8=> 9 MCLK   <9=> 11 MCLK  <10=> 13 MCLK <11=> 15 MCLK
;//                     <12=> 17 MCLK <13=> 19 MCLK <14=> 21 MCLK <15=> 23 MCLK
;//     <o0.8..10>  tCOH: Chip selection hold time of external I/O bank 0
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.5..7>   tACS: Address setup before nECS of external I/O bank 0
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.2..4>   tCOS: Chip select setup time of external I/O bank 0
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.0..1>   DBWD: Programmable data bus width for external I/O bank 0
;//                     <0=> Disable bus
;//                     <1=> 8-bit
;//                     <2=> 16-bit
;//                     <3=> 32-bit
;//   </h>
EXT0CON_Val     EQU     0xF0078001

;//   <h> External I/O Bank 1 Control Register (EXT1CON)
;//     <o0.19..31> BASADDR: Base address pointer of externl I/O bank 1 
;//                     <0x0-0x7FFC0000:0x40000><#/0x40000>
;//     <o0.16..18> SIZE: Size of external I/O bank 1
;//                     <0=> 256 kB   <1=> 512 kB   <2=> 1 MB     <3=> 2 MB
;//                     <4=> 4 MB     <5=> 8 MB     <6=> 16 MB
;//     <o0.15>     ADRS: Address bus alignment for external I/O bank 1
;//     <o0.11..14> tACC: Access cycles of external I/O bank 1
;//                     <0=> Reserved <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//                     <8=> 9 MCLK   <9=> 11 MCLK  <10=> 13 MCLK <11=> 15 MCLK
;//                     <12=> 17 MCLK <13=> 19 MCLK <14=> 21 MCLK <15=> 23 MCLK
;//     <o0.8..10>  tCOH: Chip selection hold time of external I/O bank 1
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.5..7>   tACS: Address setup before nECS of external I/O bank 1
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.2..4>   tCOS: Chip select setup time of external I/O bank 1
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.0..1>   DBWD: Programmable data bus width for external I/O bank 1
;//                     <0=> Disable bus
;//                     <1=> 8-bit
;//                     <2=> 16-bit
;//                     <3=> 32-bit
;//   </h>
EXT1CON_Val     EQU     0x00000000

;//   <h> External I/O Bank 2 Control Register (EXT2CON)
;//     <o0.19..31> BASADDR: Base address pointer of externl I/O bank 2 
;//                     <0x0-0x7FFC0000:0x40000><#/0x40000>
;//     <o0.16..18> SIZE: Size of external I/O bank 2
;//                     <0=> 256 kB   <1=> 512 kB   <2=> 1 MB     <3=> 2 MB
;//                     <4=> 4 MB     <5=> 8 MB     <6=> 16 MB
;//     <o0.15>     ADRS: Address bus alignment for external I/O bank 2
;//     <o0.11..14> tACC: Access cycles of external I/O bank 2
;//                     <0=> Reserved <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//                     <8=> 9 MCLK   <9=> 11 MCLK  <10=> 13 MCLK <11=> 15 MCLK
;//                     <12=> 17 MCLK <13=> 19 MCLK <14=> 21 MCLK <15=> 23 MCLK
;//     <o0.8..10>  tCOH: Chip selection hold time of external I/O bank 2
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.5..7>   tACS: Address setup before nECS of external I/O bank 2
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.2..4>   tCOS: Chip select setup time of external I/O bank 2
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.0..1>   DBWD: Programmable data bus width for external I/O bank 2
;//                     <0=> Disable bus
;//                     <1=> 8-bit
;//                     <2=> 16-bit
;//                     <3=> 32-bit
;//   </h>
EXT2CON_Val     EQU     0x00000000

;//   <h> External I/O Bank 3 Control Register (EXT3CON)
;//     <o0.19..31> BASADDR: Base address pointer of externl I/O bank 3 
;//                     <0x0-0x7FFC0000:0x40000><#/0x40000>
;//     <o0.16..18> SIZE: Size of external I/O bank 3
;//                     <0=> 256 kB   <1=> 512 kB   <2=> 1 MB     <3=> 2 MB
;//                     <4=> 4 MB     <5=> 8 MB     <6=> 16 MB
;//     <o0.15>     ADRS: Address bus alignment for external I/O bank 3
;//     <o0.11..14> tACC: Access cycles of external I/O bank 3
;//                     <0=> Reserved <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//                     <8=> 9 MCLK   <9=> 11 MCLK  <10=> 13 MCLK <11=> 15 MCLK
;//                     <12=> 17 MCLK <13=> 19 MCLK <14=> 21 MCLK <15=> 23 MCLK
;//     <o0.8..10>  tCOH: Chip selection hold time of external I/O bank 3
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.5..7>   tACS: Address setup before nECS of external I/O bank 3
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.2..4>   tCOS: Chip select setup time of external I/O bank 3
;//                     <0=> 0 MCLK   <1=> 1 MCLK   <2=> 2 MCLK   <3=> 3 MCLK
;//                     <4=> 4 MCLK   <5=> 5 MCLK   <6=> 6 MCLK   <7=> 7 MCLK
;//     <o0.0..1>   DBWD: Programmable data bus width for external I/O bank 3
;//                     <0=> Disable bus
;//                     <1=> 8-bit
;//                     <2=> 16-bit
;//                     <3=> 32-bit
;//   </h>
EXT3CON_Val     EQU     0x00000000

;//   <h> Clock Skew Control Register (CKSKEW)
;//     <o0.16..31> Latch DLH_CLK clock tree by HCLK positive edge <0x0-0xFFFF>
;//       <i> SDRAM MCLK is generated by inserting a delay (XOR2) chain on the 
;//       <i> HCLK positive or negative edge to adjust for MCLK skew. So 
;//       <i> software can read these bits and explore the MCLK and HCLK 
;//       <i> relationship, [31:24] is used for the positive edge and [23:16]
;//       <i> is used for the negative edge.
;//     <o0.4..7>   DLH_CLK_SKEW: Data latch clock skew adjustment
;//       <i> P-x means Data lached Clock shift "x" gates delays by refering to 
;//       <i> the MCLKO positive edge, N-x means Data latched Clock shift "x" 
;//       <i> gates delays by referring to the MCLKO negative edge.
;//                     <0=> P-0      <1=> P-1      <2=> P-2      <3=> P-3
;//                     <4=> P-4      <5=> P-5      <6=> P-6      <7=> P-7
;//                     <8=> N-0      <9=> N-1      <10=> N-2     <11=> N-3
;//                     <12=> N-4     <13=> N-5     <14=> N-6     <15=> N-7
;//     <o0.0..3>   MCLK_O_D: MCLK output delay adjustment
;//       <i> P-x means MCLKO shift "x" gates delays by refering to HCLK 
;//       <i> positive edge, N-x means MCLKO shift "x" gates delays by 
;//       <i> referring to the HCLK negative edge. MCLKO is the output
;//       <i> pin of MCLKO which is an internal signal on chip.
;//   </h>
CKSKEW_Val      EQU     0x00FF0039

;// </e> End of External Bus Interface Configuration (EBI)


;----------------------- Cache Controller Definitions --------------------------

; Cache Controller User Interface
CAH_BASE        EQU     0xFFF02000      ; Cache Controller Base Address
CAHCNF_OFS      EQU     0x00            ; Cache Configuration Reg Address Offset
CAHCON_OFS      EQU     0x04            ; Cache Control Register  Address Offset
CAHADR_OFS      EQU     0x08            ; Cache Address Register  Address Offset
CTEST0_OFS      EQU     0x0C            ; Cache Test Register 0   Address Offset
CTEST1_OFS      EQU     0x10            ; Cache Test Register 1   Address Offset

; Constants
WRBEN_MSK       EQU     (0x1 << 2)      ; CAHCNF WRBEN bit mask
DCAEN_MSK       EQU     (0x1 << 1)      ; CAHCNF DCAEN bit mask
ICAEN_MSK       EQU     (0x1 << 0)      ; CAHCNF ICAEN bit mask
DRWB_MSK        EQU     (0x1 << 7)      ; CAHCON DRWB bit mask
ULKS_MSK        EQU     (0x1 << 6)      ; CAHCON ULKS bit mask
ULKA_MSK        EQU     (0x1 << 5)      ; CAHCON ULKA bit mask
LDLK_MSK        EQU     (0x1 << 4)      ; CAHCON LDLK bit mask
FLHS_MSK        EQU     (0x1 << 3)      ; CAHCON FLHS bit mask
FLHA_MSK        EQU     (0x1 << 2)      ; CAHCON FLHA bit mask
DCAH_MSK        EQU     (0x1 << 1)      ; CAHCON DCAH bit mask
ICAH_MSK        EQU     (0x1 << 0)      ; CAHCON ICAH bit mask

;// <e> Cache Configuration
;//   <h> Cache Configuration Register (CAHCNF)
;//     <o1.2> Write buffer enable
;//     <o1.1> Data cache enable
;//     <o1.0> Instruction cache enable
;//   </h>
;// </e>
CACHE_SETUP     EQU     0
CAHCNF_Val      EQU     0x00000000


;----------------------- CODE --------------------------------------------------

                PRESERVE8
                

; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM

                IF      :DEF:__RTX
                IMPORT  IRQ_Handler_RTX
                ENDIF

; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

Vectors         LDR     PC,Reset_Addr         
                LDR     PC,Undef_Addr
                LDR     PC,SWI_Addr
                LDR     PC,PAbt_Addr
                LDR     PC,DAbt_Addr
                NOP
                LDR     PC,IRQ_Addr     
                LDR     PC,FIQ_Addr

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0                         ; Reserved Address
                IF      :DEF:__RTX
IRQ_Addr        DCD     IRQ_Handler_RTX
                ELSE
IRQ_Addr        DCD     IRQ_Handler
                ENDIF
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
SWI_Handler     PROC
                EXPORT  SWI_Handler               [WEAK]
                B       .
                ENDP
PAbt_Handler    B       PAbt_Handler
DAbt_Handler    B       DAbt_Handler
IRQ_Handler     PROC
                EXPORT  IRQ_Handler               [WEAK]
                B       .
                ENDP
FIQ_Handler     PROC
                EXPORT  FIQ_Handler               [WEAK]
                B       .
                ENDP


; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler   


; Clock Setup ------------------------------------------------------------------

                IF      CLOCK_SETUP != 0
                LDR     R0, =SMC_BASE

                LDR     R1, =PLLCON0_Val
                STR     R1, [R0, #PLLCON0_OFS]
                LDR     R1, =PLLCON1_Val
                STR     R1, [R0, #PLLCON1_OFS]

                IF      ((CLKSEL_Val:AND:CLKS_MSK) = 0)
                LDR     R1, [R0, #CLKSEL_OFS]
                AND     R1, R1, #(~ECLKS)
                STR     R1, [R0, #CLKSEL_OFS]
                ENDIF

                LDR     R1, =CLKSEL_Val
                STR     R1, [R0, #CLKSEL_OFS]
                ENDIF   ; of IF      CLOCK_SETUP != 0


; External Bus Interface Setup -------------------------------------------------

                IF      (EBI_SETUP != 0):LAND:(:LNOT::DEF:EBI_NOINIT)
                LDR     R0, =EBI_BASE

                LDR     R1, =CKSKEW_Val
                STR     R1, [R0, #CKSKEW_OFS]
                LDR     R8, =(EBI_BASE+EBICON_OFS)    ; Remap
                LDR     R1, =EBICON_Val
                LDR     R2, =ROMCON_Val
                LDR     R3, =SDCONF0_Val
                LDR     R4, =SDCONF1_Val
                LDR     R5, =SDTIME0_Val
                LDR     R6, =SDTIME1_Val
                LDR     R9, =((ROMCON_Val>>1):AND:0x7FFC0000)+4
                ADD     R9, R9, PC
                STMIA   R8!, {R1-R6}                  ; Remap end
                BX      R9                            ; Jump to remapped code
                LDR     R1, =EXT0CON_Val
                STR     R1, [R0, #EXT0CON_OFS]
                LDR     R1, =EXT1CON_Val
                STR     R1, [R0, #EXT1CON_OFS]
                LDR     R1, =EXT2CON_Val
                STR     R1, [R0, #EXT2CON_OFS]
                LDR     R1, =EXT3CON_Val
                STR     R1, [R0, #EXT3CON_OFS]
                ENDIF   ; of IF      (EBI_SETUP != 0):LAND:(:LNOT::DEF:EBI_NOINIT)


; Cache Setup ------------------------------------------------------------------

                IF      CACHE_SETUP != 0
                LDR     R0, =CAH_BASE

                ; If Data cache enabled
                IF      (CAHCNF_Val:AND:DCAEN_MSK) != 0
                MOV     R1, #(FLHA_MSK:OR:DCAH_MSK)
                STR     R1, [R0, #CAHCON_OFS]
                ENDIF
                ; If Instruction cache enabled
                IF      (CAHCNF_Val:AND:ICAEN_MSK) != 0
                MOV     R1, #(FLHA_MSK:OR:ICAH_MSK)
                STR     R1, [R0, #CAHCON_OFS]
                ENDIF

                LDR     R1, =CAHCNF_Val
                STR     R1, [R0, #CAHCNF_OFS]
                ENDIF   ; of IF      CACHE_SETUP != 0


; Setup Stack for each mode ----------------------------------------------------

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_USR
                IF      :DEF:__MICROLIB

                EXPORT __initial_sp

                ELSE

                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

                ENDIF


; Enter the C code

                IMPORT  __main
                LDR     R0, =__main
                BX      R0

                IF      :DEF:__MICROLIB

                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE
; User Initial Stack & Heap
                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDIF


                END
