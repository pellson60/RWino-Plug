/*
 RWino Plug Lab PCB App - AC Voltage dimmer with Zero cross detection withe SPARK Core
 
 Author: Per Johansson, Bläckbild 
 License: Released under the Creative Commons Attribution Share-Alike 3.0 License. 
 http://creativecommons.org/licenses/by-sa/3.0
 Target:  Spark Core
 
 Attach the Zero cross pin of the module to Spark Core External Interrupt pin
 In this example pin D1 is used to Zero cross detector pin
 */

int AC_LOAD = 0;    // Output to Opto Triac pin
int Z_C = D1;       // Zero Cross pin D1
volatile int i= 128;  // Dimming level (0-128)  0 = ON, 128 = OFF

void setup()
{
  pinMode(AC_LOAD, OUTPUT);	      // Set the AC Load as output
  pinMode(Z_C, INPUT);          // Set as input for Zero Cross interupt     
   
  attachInterrupt(1, zero_cross_int, RISING);  // Choose the zero cross interrupt for pin D1
}

void zero_cross_int()  // Interupt rutin to be fired at the zero crossing to dim AC Voltage
{
  // Dim time calculation
  // 50Hz-> 10ms (1/2 Cycle) → (10000us - 10us) / 128 = 78 (Approx)
  // 60Hz-> 8.33ms (1/2 Cycle) → (8333us - 8.33us) / 128 = 65 (Approx)
  int dimtime = (78*i);      
  delayMicroseconds(dimtime);    // Off cycle
  digitalWrite(AC_LOAD, HIGH);   // triac firing
  delayMicroseconds(10);         // triac On propogation delay
  digitalWrite(AC_LOAD, LOW);    // triac Off
}

void loop()
{

  for (i = 0; i <= 128; i++)    // Dim time 0=ON 128=OFF
  {
    delay(40);
  }
}

