#include <xc.h> 

#include "umogi2.h"
#include "system.h"

#include "encoder.h"

#include "app_device_cdc_basic.h"

#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt (void)
{
    // timer1: 1 hz.
    LEDB=!LEDB;
    IFS0bits.T1IF=0;
}

MAIN_RETURN main(void)
{
    
    CLKDIVbits.CPDIV=0; // 32 mhz
    while (!OSCCONbits.LOCK) Nop(); // megvártuk az indulást
    __builtin_write_OSCCONL(OSCCON | (1<<1)); // soscen =1 
    // pps
    // clk: rp15, out
    RPOR7bits.RP15R=8; // sck1 out 
    // spi miso/sdi RP30, in
    RPINR20bits.SDI1R=30; 
    // spi mosi/sd0: rp16, out
    RPOR8bits.RP16R=7; // sdo7 out 
    __builtin_write_OSCCONL(OSCCON | (1<<6));//!

	// spi tris
    TRISFbits.TRISF0=0;
    
    __builtin_write_OSCCONL(OSCCON | (1<<6)); // most már iolock=1. 
    // 1 sec: timer1 
    PR1=0x8000; // 32768, 1 sec: 32.768 khz
    IPC0bits.T1IP=4; // 4-es prioritás
    IFS0bits.T1IF=0; // töröld
    IEC0bits.T1IE=1; // engedélyezd az it-t
    T1CON=0x8003;  // start, külsõ
 // led tris
    TRISGbits.TRISG6=0;
    TRISGbits.TRISG7=0;
    TRISGbits.TRISG8=0;
    TRISGbits.TRISG9=0;
    TRISDbits.TRISD15=0;
    TRISFbits.TRISF4=0;
    TRISFbits.TRISF5=0;
    
    lcd_init();
    lcd_cgram();
    sprintf(lcd,"uMogi2-USB ready");
    lcd_update();
    
    // pps spi
    
    CS2=1;
    SPI1CON1=0x013e; // 4 MHz
    SPI1STAT=0x8000; // spi on.

    
    // set mode
    write_encoder(REG_MDR0, MDR0_B1B0_CLOCK_DIR | MDR0_B3B2_RANGE_LIMIT | MDR0_B5B4_NO_INDEX | MDR0_B6_ASYNC_INDEX | MDR0_B7_FILTER_CLOCK_F1 );
    write_encoder(REG_MDR1 ,MDR1_B1B0_COUNT_8_BITS | MDR1_B2_ENABLE_COUNTING);
    //write_encoder(REG_DTR,0xff);
    CS2 = 0; //select encoder
    WriteSPI1(OP_WRITE | REG_DTR); 
    WriteSPI1(0xff); // write data
    WriteSPI1(0xff); // write data
    CS2 = 1;
    
    sprintf(lcd,"SPI ready");
    lcd_update();
    lcd_cls();
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);

    USBDeviceInit();
    USBDeviceAttach();
    
    
    BYTE counter_result;
    unsigned int cntr_result;
    
    counter_result = read_encoder(REG_STR);
    //counter_result =read_counter();
    sprintf(lcd,"counter %i",counter_result);
    lcd_update();
    while(1)
    {
        SYSTEM_Tasks();
        Nop();
        //counter_result = read_counter();//read_encoder(REG_MDR1);
        lcd_cls();
        //counter_result = read_encoder(REG_CNTR);
        CS2 = 0; //select encoder
        WriteSPI1(OP_LOAD | REG_OTR); 
        CS2 = 1;
        cntr_result = read_cntr(REG_OTR);
        //sprintf(lcd,"counter= %i",counter_result);
        sprintf(lcd,"counter= %x",cntr_result);
        lcd_update();
        __delay_ms(100);
       //Application specific tasks
        APP_DeviceCDCBasicDemoTasks();
    }//end while
}//end main
