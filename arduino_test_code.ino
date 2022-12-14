int a = 0;
void setup()
{
  Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps
}

void loop()
{
    char receiveVal;                  // Defined receive data
   
    if(Serial.available() > 0)       //Receive serial data
    {        
        receiveVal = Serial.read();  //Save the serial data received 
        
       if(receiveVal == '?')           
       {      
           Serial.println("uMogi-2"); //send data to the serial monitor
       }
       else if(receiveVal == 'e')          
       {                
           a = analogRead(A0);//Read the voltage photoresistance
           Serial.println(a);//send data to the serial monitor
       }
       else if(receiveVal != 0)          
       {              
           Serial.println("?");//send data to the serial monitor
       }  
    }
  delay(50);                          //delay 50ms
}
