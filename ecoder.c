#include "encoder.h"


//* Custom -----------------------------------------------------------------------------------
void Init_encoder(void)
{
	// pps spi
    // clk: rp15, out
    RPOR7bits.RP15R=8; // sck1 out 
    // spi miso/sdi RP30, in
    RPINR20bits.SDI1R=30; 
    // spi mosi/sd0: rp16, out
    RPOR8bits.RP16R=7; // sdo7 out 
    __builtin_write_OSCCONL(OSCCON | 1<<6);//!

	// spi tris
    TRISFbits.TRISF0=0;
    CS2=1;
    SPI2CON1=0x013e; // 4 MHz
    SPI2STAT=0x8000; // spi on.

    // set mode
    write_encoder(REG_MDR1 ,MDR1_B1B0_COUNT_8_BITS | MDR1_B2_ENABLE_COUNTING)
    write_encoder(REG_MDR0, MDR0_B1B0_CLOCK_DIR | MDR0_B3B2_FREE_RUNNING | MDR0_B5B4_NO_INDEX | MDR0_B6_ASYNC_INDEX | MDR0_B7_FILTER_CLOCK_F1 )

}
void write_encoder(BYTE write_register, BYTE data)
{
    CS2 = 0; //select encoder
    WriteSPI2(OP_WRITE | write_register); 
    //? MOVF     SSPBUFF,W //Dummy read to clear BF Flag
    WriteSPI2(data); // write data
    CS2 = 1;
}
BYTE read_encoder(BYTE read_register)
{
    BYTE i;
    CS2 = 0; //select encoder
    WriteSPI2(OP_READ | read_register);
    //? MOVWF     SSPBUFF //Dummy byte to generate clock and recive data
    i = WriteSPI2(0);
    CS2 = 1;
    return i;
}
BYTE read_counter(void)
{   
    byte i;
    CS2 = 0;
    WriteSPI2(OP_LOAD | REG_OTR) // load CNTR TO OTR
    CS2 = 1;
    CS2 = 0;
    WriteSPI2(OP_READ | REG_OTR) // read OTR
    CS2 = 1;
    return i;
}

int WriteSPI2(int i) 
{   
    SPI1BUF = i; // buffer írása küldésre 
    while(!SPI2STATbits.SPIRBF) Nop(); // várakozás az átvitel befejezéséig 
    return SPI2BUF;    // beérkezõ adat kiolvasása 
}
