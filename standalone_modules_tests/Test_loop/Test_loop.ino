

#define LED_need_us 15000
#define strain_need_us 3000
#define light_need_us 50000

#define LED_PIN 50

uint8_t action;
uint32_t LED_last=0,strain_last=0,light_last=0,LED_reset=0;//micros() overflows once an hour

uint32_t pm,pu,ps,pd,pl,pa;
void motor(){
  //read the angle sensor
  //do calculations
  //output to motor
  pm=!pm;digitalWrite(5,pm);
  delayMicroseconds(20);
}

void USB(){
  //receive/send usb packet
  pu=!pu;digitalWrite(4,pu);
  delayMicroseconds(175);
}

void updateDisplay(){
  pd=!pd;digitalWrite(0,pd);
  delayMicroseconds(300);
}

void measureStrain(){
  strain_last = micros();
  ps=!ps;digitalWrite(2,ps);
  delayMicroseconds(20);
  
}

void updateLEDs(){
  LED_reset = 0;
  LED_last = micros();
  pl=!pl;digitalWrite(14,pl);
  delayMicroseconds(325);
}

void measureLight(){
  light_last = micros();
  pa=!pa;digitalWrite(12,pa);
  delayMicroseconds(30);
}

void readMode(){
  
}

void setup() {
  pinMode(5,OUTPUT);pinMode(4,OUTPUT);pinMode(0,OUTPUT);pinMode(2,OUTPUT);pinMode(14,OUTPUT);pinMode(12,OUTPUT);
  action = 0;
  Serial.begin(500000);
}

void loop() {
  if(action == 0 || action == 2){
    motor();
  }else if(action == 1){
    USB();
  }else if(action == 3){
    ///special
    uint32_t crtime = micros();
    

    //to not waste the 50us reset time for the LEDs, we start the reset one frame before
    uint8_t has_upd_LED=0;
    if(crtime - LED_last >= LED_need_us){
      if(LED_reset == 1){
        updateLEDs();
        has_upd_LED=1;
      }else{
        LED_reset = 1;
        GPOC = (1<<LED_PIN);
      }
    }
    //we can do something else if we haven't updated the LEDs
    if(!has_upd_LED){
      //either strain or light and then display;
      if(crtime - light_last >= light_need_us){
        measureLight();
      }else if(crtime - strain_last >= strain_need_us){
        measureStrain();
      }
        //almost every 'frame' we can update the display(if the LEDs haven't been updated)
      updateDisplay();
      
    }
  }

  action = (action+1)%4;
}
