#include "encoder.h"

//* Custom -----------------------------------------------------------------------------------
void Init_encoder(void)
{
	Nop();

}
void write_encoder(BYTE write_register, BYTE data)
{
    CS2 = 0; //select encoder
    WriteSPI1(OP_WRITE | write_register); 
    //? MOVF     SSPBUFF,W //Dummy read to clear BF Flag
    WriteSPI1(data); // write data
    //while (read_encoder(REG_STR)  & 0x01) Nop(); // írás folyamatának vége (WIP) 
    CS2 = 1;
}
BYTE read_encoder(BYTE read_register)
{
    BYTE i;
    CS2 = 0; //select encoder
    WriteSPI1(OP_READ | read_register);
    //? MOVWF     SSPBUFF //Dummy byte to generate clock and recive data
    i = WriteSPI1(0);
    CS2 = 1;
    return i;
}
unsigned int read_cntr(BYTE read_register)//,BYTE*t, int darab)
{
    BYTE tmp;
    unsigned int i;
    CS2 = 0; //select encoder
    WriteSPI1(OP_READ | read_register);
    tmp = WriteSPI1(0);
    i=tmp<<8;
    tmp = WriteSPI1(0);
    i = i|(tmp);
    CS2 = 1;
    return i;
}
BYTE read_counter(void)
{   
    BYTE i;
    CS2 = 0;
    WriteSPI1(OP_LOAD | REG_OTR); // load CNTR TO OTR
    CS2 = 1;
    CS2 = 0;
    i = WriteSPI1(OP_READ | REG_OTR); // read OTR
    CS2 = 1;
    return i;
}

int WriteSPI2(int i) 
{   
    SPI2BUF = i; // buffer írása küldésre 
    while(!SPI2STATbits.SPIRBF) Nop(); // várakozás az átvitel befejezéséig 
    return SPI2BUF;    // beérkezõ adat kiolvasása 
}
