NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0054   0156 =    342. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       002A  __text_start
       002A  __start
       004C  _exit
       004D  _delay
       0062  _main
       00C4  push_xgsetF000
       00C9  pop_xgsetF000
       00CE  lsl16
       00D5  __text_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
light3.o	[ light3.c ]
<library>	[ gpushy.s, lsl16.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512

