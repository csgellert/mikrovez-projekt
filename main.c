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
    
    Init_encoder(); // Starting encoder

    SYSTEM_Initialize(SYSTEM_STATE_USB_START);

    USBDeviceInit();
    USBDeviceAttach();
    
    while(1)
    {
        SYSTEM_Tasks();
        Nop();
       //Application specific tasks
        APP_DeviceCDCBasicDemoTasks();
    }//end while
}//end main
