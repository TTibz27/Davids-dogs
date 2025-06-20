;*
;* Gameboy Hardware definitions
;*
;* Based on Jones' hardware.inc
;* And based on Carsten Sorensen's ideas.
;*
;* Rev 1.1 - 15-Jul-97 : Added define check
;* Rev 1.2 - 18-Jul-97 : Added revision check macro
;* Rev 1.3 - 19-Jul-97 : Modified for RGBASM V1.05
;* Rev 1.4 - 27-Jul-97 : Modified for new subroutine prefixes
;* Rev 1.5 - 15-Aug-97 : Added _HRAM, PAD, CART defines
;*                     :  and Nintendo Logo
;* Rev 1.6 - 30-Nov-97 : Added rDIV, rTIMA, rTMA, & rTAC
;* Rev 1.7 - 31-Jan-98 : Added _SCRN0, _SCRN1
;* Rev 1.8 - 15-Feb-98 : Added rSB, rSC
;* Rev 1.9 - 16-Feb-98 : Converted I/O registers to $FFXX format
;* Rev 2.0 -           : Added GBC registers
;* Rev 2.1 -           : Added MBC5 & cart RAM enable/disable defines
;* Rev 2.2 -           : Fixed NR42,NR43, & NR44 equates
;* Rev 2.3 -           : Fixed incorrect _HRAM equate
;* Rev 2.4 - 27-Apr-13 : Added some cart defines (AntonioND)
;* Rev 2.5 - 03-May-15 : Fixed format (AntonioND)
;* Rev 2.6 - 09-Apr-16 : Added GBC OAM and cart defines (AntonioND)
;* Rev 2.7 - 19-Jan-19 : Added rPCMXX (ISSOtm)
;* Rev 2.8 - 03-Feb-19 : Added audio registers flags (Álvaro Cuesta)

; If all of these are already defined, don't do it again.

    IF !DEF(HARDWARE_INC)
; HARDWARE_INC SET 1

MACRO rev_Check_hardware_inc
;NOTE: REVISION NUMBER CHANGES MUST BE ADDED
;TO SECOND PARAMETER IN FOLLOWING LINE.
    IF  \1 > 2.8 ;PUT REVISION NUMBER HERE
        WARN    "Version \1 or later of 'hardware.inc' is required."
    ENDC
ENDM

; STUFF PULLED IN 
DEF rRP_ENABLE_READ_MASK EQU %11000000
DEF rBGPI                EQU $ff68 ; CGB Mode Only - Background Palette Index
DEF rBGPI_AUTO_INCREMENT EQU 7     ; increment rBGPI after write to rBGPD
DEF rBGPD                EQU $ff69 ; CGB Mode Only - Background Palette Data
DEF rOBPI                EQU $ff6a ; CGB Mode Only - Sprite Palette Index
DEF rOBPI_AUTO_INCREMENT EQU 7     ; increment rOBPI after write to rOBPD
DEF rOBPD                EQU $ff6b ; CGB Mode Only - Sprite Palette Data
DEF rOPRI                EQU $ff6c ; CGB Mode Only - Object Priority Mode
;;; OLD INCLUDES
def _HW          EQU $FF00

def _VRAM        EQU $8000 ; $8000->$9FFF
def _SCRN0       EQU $9800 ; $9800->$9BFF
def _SCRN1       EQU $9C00 ; $9C00->$9FFF
def _SRAM        EQU $A000 ; $A000->$BFFF
def _RAM         EQU $C000 ; $C000->$DFFF
def _OAMRAM      EQU $FE00 ; $FE00->$FE9F
def _AUD3WAVERAM EQU $FF30 ; $FF30->$FF3F
def _HRAM        EQU $FF80 ; $FF80->$FFFE

; *** MBC5 Equates ***

def rRAMG        EQU $0000 ; $0000->$1fff
def rROMB0       EQU $2000 ; $2000->$2fff
def rROMB1       EQU $3000 ; $3000->$3fff - If more than 256 ROM banks are present.
def rRAMB        EQU $4000 ; $4000->$5fff - Bit 3 enables rumble (if present)


; --
; -- OAM flags
; --

def OAMF_PRI        EQU %10000000 ; Priority
def OAMF_YFLIP      EQU %01000000 ; Y flip
def OAMF_XFLIP      EQU %00100000 ; X flip
def OAMF_PAL0       EQU %00000000 ; Palette number; 0,1 (DMG)
def OAMF_PAL1       EQU %00010000 ; Palette number; 0,1 (DMG)
def OAMF_BANK0      EQU %00000000 ; Bank number; 0,1 (GBC)
def OAMF_BANK1      EQU %00001000 ; Bank number; 0,1 (GBC)

def OAMF_PALMASK    EQU %00000111 ; Palette (GBC)

def OAMB_PRI        EQU 7 ; Priority 
def OAMB_YFLIP      EQU 6 ; Y flip 
def OAMB_XFLIP      EQU 5 ; X flip 
def OAMB_PAL1       EQU 4 ; Palette number; 0,1 (DMG) 
def OAMB_BANK1      EQU 3 ; Bank number; 0,1 (GBC) 


;***************************************************************************
;*
;* Custom registers
;*
;***************************************************************************

; --
; -- P1 ($FF00)
; -- Register for reading joy pad info.    (R/W)
; --
def rP1 EQU $FF00

def P1F_5 EQU %00100000 ; P15 out port
def P1F_4 EQU %00010000 ; P14 out port
def P1F_3 EQU %00001000 ; P13 in port
def P1F_2 EQU %00000100 ; P12 in port
def P1F_1 EQU %00000010 ; P11 in port
def P1F_0 EQU %00000001 ; P10 in port

; --
; -- SB ($FF01)
; -- Serial Transfer Data (R/W)
; --
def rSB EQU $FF01

; --
; -- SC ($FF02)
; -- Serial I/O Control (R/W)
; --
def rSC EQU $FF02

; --
; -- DIV ($FF04)
; -- Divider register (R/W)
; --
def rDIV EQU $FF04


; --
; -- TIMA ($FF05)
; -- Timer counter (R/W)
; --
def rTIMA EQU $FF05


; --
; -- TMA ($FF06)
; -- Timer modulo (R/W)
; --
def rTMA EQU $FF06


; --
; -- TAC ($FF07)
; -- Timer control (R/W)
; --
def rTAC EQU $FF07

def TACFSTART  EQU %00000100
def TACF_STOP   EQU %00000000
def TACF_4KHZ   EQU %00000000
def TACF_16KHZ  EQU %00000011
def TACF_65KHZ  EQU %00000010
def TACF_262KHZ EQU %00000001

; --
; -- IF ($FF0F)
; -- Interrupt Flag (R/W)
; --
def rIF EQU $FF0F

; --
; -- LCDC ($FF40)
; -- LCD Control (R/W)
; --
def rLCDC EQU $FF40

def LCDCF_OFF     EQU %00000000 ; LCD Control Operation
def LCDCF_ON      EQU %10000000 ; LCD Control Operation
def LCDCF_WIN9800 EQU %00000000 ; Window Tile Map Display Select
def LCDCF_WIN9C00 EQU %01000000 ; Window Tile Map Display Select
def LCDCF_WINOFF  EQU %00000000 ; Window Display
def LCDCF_WINON   EQU %00100000 ; Window Display
def LCDCF_BG8800  EQU %00000000 ; BG & Window Tile Data Select
def LCDCF_BG8000  EQU %00010000 ; BG & Window Tile Data Select
def LCDCF_BG9800  EQU %00000000 ; BG Tile Map Display Select
def LCDCF_BG9C00  EQU %00001000 ; BG Tile Map Display Select
def LCDCF_OBJ8    EQU %00000000 ; OBJ Construction
def LCDCF_OBJ16   EQU %00000100 ; OBJ Construction
def LCDCF_OBJOFF  EQU %00000000 ; OBJ Display
def LCDCF_OBJON   EQU %00000010 ; OBJ Display
def LCDCF_BGOFF   EQU %00000000 ; BG Display
def LCDCF_BGON    EQU %00000001 ; BG Display
; "Window Character Data Select" follows BG


; --
; -- STAT ($FF41)
; -- LCDC Status   (R/W)
; --
def rSTAT EQU $FF41

def STATF_LYC     EQU  %01000000 ; LYCEQULY Coincidence (Selectable)
def STATF_MODE10  EQU  %00100000 ; Mode 10
def STATF_MODE01  EQU  %00010000 ; Mode 01 (V-Blank)
def STATF_MODE00  EQU  %00001000 ; Mode 00 (H-Blank)
def STATF_LYCF    EQU  %00000100 ; Coincidence Flag
def STATF_HB      EQU  %00000000 ; H-Blank
def STATF_VB      EQU  %00000001 ; V-Blank
def STATF_OAM     EQU  %00000010 ; OAM-RAM is used by system
def STATF_LCD     EQU  %00000011 ; Both OAM and VRAM used by system
def STATF_BUSY    EQU  %00000010 ; When set, VRAM access is unsafe


; --
; -- SCY ($FF42)
; -- Scroll Y (R/W)
; --
def rSCY EQU $FF42


; --
; -- SCY ($FF43)
; -- Scroll X (R/W)
; --
def rSCX EQU $FF43


; --
; -- LY ($FF44)
; -- LCDC Y-Coordinate (R)
; --
; -- Values range from 0->153. 144->153 is the VBlank period.
; --
def rLY EQU $FF44


; --
; -- LYC ($FF45)
; -- LY Compare (R/W)
; --
; -- When LYEQUEQULYC, STATF_LYCF will be set in STAT
; --
def rLYC EQU $FF45


; --
; -- DMA ($FF46)
; -- DMA Transfer and Start Address (W)
; --
def rDMA EQU $FF46


; --
; -- BGP ($FF47)
; -- BG Palette Data (W)
; --
; -- Bit 7-6 - Intensity for %11
; -- Bit 5-4 - Intensity for %10
; -- Bit 3-2 - Intensity for %01
; -- Bit 1-0 - Intensity for %00
; --
def rBGP EQU $FF47


; --
; -- OBP0 ($FF48)
; -- Object Palette 0 Data (W)
; --
; -- See BGP for info
; --
def rOBP0 EQU $FF48


; --
; -- OBP1 ($FF49)
; -- Object Palette 1 Data (W)
; --
; -- See BGP for info
; --
def rOBP1 EQU $FF49


; --
; -- WY ($FF4A)
; -- Window Y Position (R/W)
; --
; -- 0 <EQU WY <EQU 143
; --
def rWY EQU $FF4A


; --
; -- WX ($FF4B)
; -- Window X Position (R/W)
; --
; -- 7 <EQU WX <EQU 166
; --
def rWX EQU $FF4B


; --
; -- KEY 1 ($FF4D)
; -- Select CPU Speed (R/W)
; --
def rKEY1 EQU $FF4D


; --
; -- VBK ($FF4F)
; -- Select Video RAM Bank (R/W)
; --
def rVBK EQU $FF4F


; --
; -- HDMA1 ($FF51)
; -- Horizontal Blanking, General Purpose DMA (W)
; --
def rHDMA1 EQU $FF51


; --
; -- HDMA2 ($FF52)
; -- Horizontal Blanking, General Purpose DMA (W)
; --
def rHDMA2 EQU $FF52


; --
; -- HDMA3 ($FF53)
; -- Horizontal Blanking, General Purpose DMA (W)
; --
def rHDMA3 EQU $FF53


; --
; -- HDMA4 ($FF54)
; -- Horizontal Blanking, General Purpose DMA (W)
; --
def rHDMA4 EQU $FF54


; --
; -- HDMA5 ($FF55)
; -- Horizontal Blanking, General Purpose DMA (R/W)
; --
def rHDMA5 EQU $FF55


; --
; -- RP ($FF56)
; -- Infrared Communications Port (R/W)
; --
def rRP EQU $FF56


; --
; -- BCPS ($FF68)
; -- Background Color Palette Specification (R/W)
; --
def rBCPS EQU $FF68


; --
; -- BCPD ($FF69)
; -- Background Color Palette Data (R/W)
; --
def rBCPD EQU $FF69


; --
; -- BCPS ($FF6A)
; -- Object Color Palette Specification (R/W)
; --
def rOCPS EQU $FF6A


; --
; -- BCPD ($FF6B)
; -- Object Color Palette Data (R/W)
; --
def rOCPD EQU $FF6B


; --
; -- SVBK ($FF4F)
; -- Select Main RAM Bank (R/W)
; --
def rSVBK EQU $FF70


; --
; -- IE ($FFFF)
; -- Interrupt Enable (R/W)
; --
def rIE EQU $FFFF


def IEF_HILO   EQU %00010000 ; Transition from High to Low of Pin number P10-P13
def IEF_SERIAL EQU %00001000 ; Serial I/O transfer end
def IEF_TIMER  EQU %00000100 ; Timer Overflow
def IEF_LCDC   EQU %00000010 ; LCDC (see STAT)
def IEF_VBLANK EQU %00000001 ; V-Blank




;***************************************************************************
;*
;* Sound control registers
;*
;***************************************************************************

; --
; -- AUDVOL/NR50 ($FF24)
; -- Channel control / ON-OFF / Volume (R/W)
; --
; -- Bit 7   - Vin->SO2 ON/OFF (Vin??)
; -- Bit 6-4 - SO2 output level (volume) (# 0-7)
; -- Bit 3   - Vin->SO1 ON/OFF (Vin??)
; -- Bit 2-0 - SO1 output level (volume) (# 0-7)
; --
def rNR50 EQU $FF24
def rAUDVOL EQU rNR50

def AUDVOL_VIN_LEFT  EQU %10000000 ; SO2
def AUDVOL_VIN_RIGHT EQU %00001000 ; SO1


; --
; -- AUDTERM/NR51 ($FF25)
; -- Selection of Sound output terminal (R/W)
; --
; -- Bit 7   - Output sound 4 to SO2 terminal
; -- Bit 6   - Output sound 3 to SO2 terminal
; -- Bit 5   - Output sound 2 to SO2 terminal
; -- Bit 4   - Output sound 1 to SO2 terminal
; -- Bit 3   - Output sound 4 to SO1 terminal
; -- Bit 2   - Output sound 3 to SO1 terminal
; -- Bit 1   - Output sound 2 to SO1 terminal
; -- Bit 0   - Output sound 0 to SO1 terminal
; --
def rNR51 EQU $FF25
def rAUDTERM EQU rNR51

; SO2
def AUDTERM_4_LEFT  EQU %10000000
def AUDTERM_3_LEFT  EQU %01000000
def AUDTERM_2_LEFT  EQU %00100000
def AUDTERM_1_LEFT  EQU %00010000
; SO1
def AUDTERM_4_RIGHT EQU %00001000
def AUDTERM_3_RIGHT EQU %00000100
def AUDTERM_2_RIGHT EQU %00000010
def AUDTERM_1_RIGHT EQU %00000001


; --
; -- AUDENA/NR52 ($FF26)
; -- Sound on/off (R/W)
; --
; -- Bit 7   - All sound on/off (sets all audio regs to 0!)
; -- Bit 3   - Sound 4 ON flag (doesn't work!)
; -- Bit 2   - Sound 3 ON flag (doesn't work!)
; -- Bit 1   - Sound 2 ON flag (doesn't work!)
; -- Bit 0   - Sound 1 ON flag (doesn't work!)
; --
def rNR52 EQU $FF26
def rAUDENA EQU rNR52

def AUDENA_ON    EQU %10000000
def AUDENA_OFF   EQU %00000000  ; sets all audio regs to 0!


;***************************************************************************
;*
;* SoundChannel #1 registers
;*
;***************************************************************************

; --
; -- AUD1SWEEP/NR10 ($FF10)
; -- Sweep register (R/W)
; --
; -- Bit 6-4 - Sweep Time
; -- Bit 3   - Sweep Increase/Decrease
; --           0: Addition    (frequency increases???)
; --           1: Subtraction (frequency increases???)
; -- Bit 2-0 - Number of sweep shift (# 0-7)
; -- Sweep Time: (n*7.8ms)
; --
def rNR10 EQU $FF10
def rAUD1SWEEP EQU rNR10

def AUD1SWEEP_UP   EQU %00000000
def AUD1SWEEP_DOWN EQU %00001000


; --
; -- AUD1LEN/NR11 ($FF11)
; -- Sound length/Wave pattern duty (R/W)
; --
; -- Bit 7-6 - Wave Pattern Duty (00:12.5% 01:25% 10:50% 11:75%)
; -- Bit 5-0 - Sound length data (# 0-63)
; --
def rNR11 EQU $FF11
def rAUD1LEN EQU rNR11


; --
; -- AUD1ENV/NR12 ($FF12)
; -- Envelope (R/W)
; --
; -- Bit 7-4 - Initial value of envelope
; -- Bit 3   - Envelope UP/DOWN
; --           0: Decrease
; --           1: Range of increase
; -- Bit 2-0 - Number of envelope sweep (# 0-7)
; --
def rNR12 EQU $FF12
def rAUD1ENV EQU rNR12


; --
; -- AUD1LOW/NR13 ($FF13)
; -- Frequency lo (W)
; --
def rNR13 EQU $FF13
def rAUD1LOW EQU rNR13


; --
; -- AUD1HIGH/NR14 ($FF14)
; -- Frequency hi (W)
; --
; -- Bit 7   - Initial (when set, sound restarts)
; -- Bit 6   - Counter/consecutive selection
; -- Bit 2-0 - Frequency's higher 3 bits
; --
def rNR14 EQU $FF14
def rAUD1HIGH EQU rNR14


;***************************************************************************
;*
;* SoundChannel #2 registers
;*
;***************************************************************************

; --
; -- AUD2LEN/NR21 ($FF16)
; -- Sound Length; Wave Pattern Duty (R/W)
; --
; -- see AUD1LEN for info
; --
def rNR21 EQU $FF16
def rAUD2LEN EQU rNR21


; --
; -- AUD2ENV/NR22 ($FF17)
; -- Envelope (R/W)
; --
; -- see AUD1ENV for info
; --
def rNR22 EQU $FF17
def rAUD2ENV EQU rNR22


; --
; -- AUD2LOW/NR23 ($FF18)
; -- Frequency lo (W)
; --
def rNR23 EQU $FF18
def rAUD2LOW EQU rNR23


; --
; -- AUD2HIGH/NR24 ($FF19)
; -- Frequency hi (W)
; --
; -- see AUD1HIGH for info
; --
def rNR24 EQU $FF19
def rAUD2HIGH EQU rNR24


;***************************************************************************
;*
;* SoundChannel #3 registers
;*
;***************************************************************************

; --
; -- AUD3ENA/NR30 ($FF1A)
; -- Sound on/off (R/W)
; --
; -- Bit 7   - Sound ON/OFF (1EQUON,0EQUOFF)
; --
def rNR30 EQU $FF1A
def rAUD3ENA EQU rNR30


; --
; -- AUD3LEN/NR31 ($FF1B)
; -- Sound length (R/W)
; --
; -- Bit 7-0 - Sound length
; --
def rNR31 EQU $FF1B
def rAUD3LEN EQU rNR31


; --
; -- AUD3LEVEL/NR32 ($FF1C)
; -- Select output level
; --
; -- Bit 6-5 - Select output level
; --           00: 0/1 (mute)
; --           01: 1/1
; --           10: 1/2
; --           11: 1/4
; --
def rNR32 EQU $FF1C
def rAUD3LEVEL EQU rNR32


; --
; -- AUD3LOW/NR33 ($FF1D)
; -- Frequency lo (W)
; --
; -- see AUD1LOW for info
; --
def rNR33 EQU $FF1D
def rAUD3LOW EQU rNR33


; --
; -- AUD3HIGH/NR34 ($FF1E)
; -- Frequency hi (W)
; --
; -- see AUD1HIGH for info
; --
def rNR34 EQU $FF1E
def rAUD3HIGH EQU rNR34


; --
; -- AUD4LEN/NR41 ($FF20)
; -- Sound length (R/W)
; --
; -- Bit 5-0 - Sound length data (# 0-63)
; --
def rNR41 EQU $FF20
def rAUD4LEN EQU rNR41


; --
; -- AUD4ENV/NR42 ($FF21)
; -- Envelope (R/W)
; --
; -- see AUD1ENV for info
; --
def rNR42 EQU $FF21
def rAUD4ENV EQU rNR42


; --
; -- AUD4POLY/NR43 ($FF22)
; -- Polynomial counter (R/W)
; --
; -- Bit 7-4 - Selection of the shift clock frequency of the (scf)
; --           polynomial counter (0000-1101)
; --           freqEQUdrf*1/2^scf (not sure)
; -- Bit 3 -   Selection of the polynomial counter's step
; --           0: 15 steps
; --           1: 7 steps
; -- Bit 2-0 - Selection of the dividing ratio of frequencies (drf)
; --           000: f/4   001: f/8   010: f/16  011: f/24
; --           100: f/32  101: f/40  110: f/48  111: f/56  (fEQU4.194304 Mhz)
; --
def rNR43 EQU $FF22
def rAUD4POLY EQU rNR43


; --
; -- AUD4GO/NR44 ($FF23)
; -- (has wrong name and value (ff30) in Dr.Pan's doc!)
; --
; -- Bit 7 -   Inital
; -- Bit 6 -   Counter/consecutive selection
; --
def rNR44 EQU $FF23
def rAUD4GO EQU rNR44 ; silly name!


; --
; -- PCM12 ($FF76)
; -- Sound channel 1&2 PCM amplitude (R)
; --
; -- Bit 7-4 - Copy of sound channel 2's PCM amplitude
; -- Bit 3-0 - Copy of sound channel 1's PCM amplitude
; --
def rPCM12 EQU $FF76


; --
; -- PCM34 ($FF77)
; -- Sound channel 3&4 PCM amplitude (R)
; --
; -- Bit 7-4 - Copy of sound channel 4's PCM amplitude
; -- Bit 3-0 - Copy of sound channel 3's PCM amplitude
; --
def rPCM34 EQU $FF77


;***************************************************************************
;*
;* Flags common to multiple sound channels
;*
;***************************************************************************

; --
; -- Square wave duty cycle
; --
; -- Can be used with AUD1LEN and AUD2LEN
; -- See AUD1LEN for more info
; --
def AUDLEN_DUTY_12_5    EQU %00000000 ; 12.5%
def AUDLEN_DUTY_25      EQU %01000000 ; 25%
def AUDLEN_DUTY_50      EQU %10000000 ; 50%
def AUDLEN_DUTY_75      EQU %11000000 ; 75%


; --
; -- Audio envelope flags
; --
; -- Can be used with AUD1ENV, AUD2ENV, AUD4ENV
; -- See AUD1ENV for more info
; --
def AUDENV_UP           EQU %00001000
def AUDENV_DOWN         EQU %00000000


; --
; -- Audio trigger flags
; --
; -- Can be used with AUD1HIGH, AUD2HIGH, AUD3HIGH
; -- See AUD1HIGH for more info
; --

def AUDHIGH_RESTART     EQU %10000000
def AUDHIGH_LENGTH_ON   EQU %01000000
def AUDHIGH_LENGTH_OFF  EQU %00000000


;***************************************************************************
;*
;* Cart related
;*
;***************************************************************************

def CART_COMPATIBLE_DMG     EQU $00
def CART_COMPATIBLE_DMG_GBC EQU $80
def CART_COMPATIBLE_GBC     EQU $C0

def CART_ROM                     EQU $00
def CART_ROM_MBC1                EQU $01
def CART_ROM_MBC1_RAM            EQU $02
def CART_ROM_MBC1_RAM_BAT        EQU $03
def CART_ROM_MBC2                EQU $05
def CART_ROM_MBC2_BAT            EQU $06
def CART_ROM_RAM                 EQU $08
def CART_ROM_RAM_BAT             EQU $09
def CART_ROM_MBC3_BAT_RTC        EQU $0F
def CART_ROM_MBC3_RAM_BAT_RTC    EQU $10
def CART_ROM_MBC3                EQU $11
def CART_ROM_MBC3_RAM            EQU $12
def CART_ROM_MBC3_RAM_BAT        EQU $13
def CART_ROM_MBC5                EQU $19
def CART_ROM_MBC5_BAT            EQU $1A
def CART_ROM_MBC5_RAM_BAT        EQU $1B
def CART_ROM_MBC5_RUMBLE         EQU $1C
def CART_ROM_MBC5_RAM_RUMBLE     EQU $1D
def CART_ROM_MBC5_RAM_BAT_RUMBLE EQU $1E
def CART_ROM_MBC7_RAM_BAT_GYRO   EQU $22
def CART_ROM_POCKET_CAMERA       EQU $FC

def CART_ROM_256K EQU 0 ; 2 banks
def CART_ROM_512K EQU 1 ; 4 banks
def CART_ROM_1M   EQU 2 ; 8 banks
def CART_ROM_2M   EQU 3 ; 16 banks
def CART_ROM_4M   EQU 4 ; 32 banks
def CART_ROM_8M   EQU 5 ; 64 banks
def CART_ROM_16M  EQU 6 ; 128 banks
def CART_ROM_32M  EQU 7 ; 256 banks
def CART_ROM_64M  EQU 8 ; 512 banks

def CART_RAM_NONE EQU 0
def CART_RAM_16K  EQU 1 ; 1 incomplete bank
def CART_RAM_64K  EQU 2 ; 1 bank
def CART_RAM_256K EQU 3 ; 4 banks
def CART_RAM_1M   EQU 4 ; 16 banks

def CART_RAM_ENABLE  EQU $0A
def CART_RAM_DISABLE EQU $00

;***************************************************************************
;*
;* Keypad related
;*
;***************************************************************************

def PADF_DOWN   EQU $80
def PADF_UP     EQU $40
def PADF_LEFT   EQU $20
def PADF_RIGHT  EQU $10
def PADF_START  EQU $08
def PADF_SELECT EQU $04
def PADF_B      EQU $02
def PADF_A      EQU $01

def PADB_DOWN   EQU $7
def PADB_UP     EQU $6
def PADB_LEFT   EQU $5
def PADB_RIGHT  EQU $4
def PADB_START  EQU $3
def PADB_SELECT EQU $2
def PADB_B      EQU $1
def PADB_A      EQU $0

;***************************************************************************
;*
;* Screen related
;*
;***************************************************************************

def SCRN_X    EQU 160 ; Width of screen in pixels
def SCRN_Y    EQU 144 ; Height of screen in pixels
def SCRN_X_B  EQU 20  ; Width of screen in bytes
def SCRN_Y_B  EQU 18  ; Height of screen in bytes

def SCRN_VX   EQU 256 ; Virtual width of screen in pixels
def SCRN_VY   EQU 256 ; Virtual height of screen in pixels
def SCRN_VX_B EQU 32  ; Virtual width of screen in bytes
def SCRN_VY_B EQU 32  ; Virtual height of screen in bytes

;*
;* Nintendo scrolling logo
;* (Code won't work on a real GameBoy)
;* (if next lines are altered.)
MACRO NINTENDO_LOGO
    DB  $CE,$ED,$66,$66,$CC,$0D,$00,$0B,$03,$73,$00,$83,$00,$0C,$00,$0D
    DB  $00,$08,$11,$1F,$88,$89,$00,$0E,$DC,$CC,$6E,$E6,$DD,$DD,$D9,$99
    DB  $BB,$BB,$67,$63,$6E,$0E,$EC,$CC,$DD,$DC,$99,$9F,$BB,$B9,$33,$3E
ENDM

    ENDC ;HARDWARE_INC
