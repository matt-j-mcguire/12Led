
#define MAX 11
int pins[] = {13,12,11,10,9,8,7,6,5,4,3,2};
int cnt; //iterations for each stage
int stage; //what the current stage is


void setup() {
  cnt=1;
  stage=0;
  for(int i=0;i<=MAX;i++){
      pinMode(pins[i],OUTPUT);
  }
  randomSeed(analogRead(1));
}

// the loop function runs over and over again forever
void loop() {
  //fill();

  switch(stage){
    case 0:
      spin();
      break;
    case 1:
      flash();
      break;
    case 2:
      drip();
      break;
    case 3:
      rnd();
      break;
    case 4:
      fill();
      break;
    case 5:
      count();
      break ;
  }
  
  if(cnt==0){
    //stage++;
    cnt=1;
    stage = random(0,6);
    //if (stage==6)stage=0;
    }
  
}

//flashes all the lights a few times
void flash(){
  static bool ison=false;
  ison = !ison;
  if(ison){
    cnt++;
    if(cnt==4)cnt=0;
  }
  

  for(int i=0;i<=MAX;i++){
    if(ison)
        digitalWrite(pins[i], HIGH);   
    else
      digitalWrite(pins[i], LOW);    
  }
  delay(50);
}

//spins the lights around
void spin(){
  static int pin=0;
  
  pin++;
  if(pin>MAX){
    pin=0;
    cnt++;
    if(cnt==10)cnt=0;
    }
  
  for(int i=0;i<=MAX;i++){
    if(i==pin)
        digitalWrite(pins[i], HIGH);   
    else
      digitalWrite(pins[i], LOW);   
  }
  delay(20);
}

//count from 0 to 4095
void count(){
  static int value=0;
  value++;

  if(value == 4096){
    value = 0;
    cnt=0;
  } 
 
  for(int i=0;i<=MAX;i++){
    if(1<<i & value)
        digitalWrite(pins[i], HIGH);   
    else
      digitalWrite(pins[i], LOW);    
  }
  delay(50);  
}

//one light at a time moving back and forth
void drip(){
  static int pin=0;
  static int addr=1;

  if (pin==0)
    addr = 1;
  else if(pin == MAX){
    addr =-1;
    cnt++;
    if(cnt==10)cnt=0;
  }
        
  pin += addr;


  for(int i=0;i<=MAX;i++){
    if(i==pin)
        digitalWrite(pins[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    else
      digitalWrite(pins[i], LOW);    // turn the LED off by making the voltage LOW
  }
  delay(50);
   
}

//count from 0 to 4095
void rnd(){
  cnt++;
  if(cnt == 30){ cnt=0;} 

  int value = random(0,4096);
 
  for(int i=0;i<=MAX;i++){
    if(1<<i & value)
        digitalWrite(pins[i], HIGH);   
    else
      digitalWrite(pins[i], LOW);    
  }
  delay(100);  
}

//fill the lights up
void fill(){
  static int value=0;
  if(value==4095){//12 bits filled
    cnt =0;
    value = 0;
  }

  bool fnd=false;
  for(int i=MAX;i>-1;i--){
    if(1<<i & value && i< MAX){
      if((1<<(i+1) & value)==0){
        fnd = true;
        //remove the old bit
        value = value ^(1<<i);
        //place it in a higher spot
        value = value | (1<<(i+1));
        i=-1;
      }
    }
  }
  if(fnd==false)value++;

  
  for(int i=0;i<=MAX;i++){
    if(1<<i & value)
        digitalWrite(pins[i], HIGH);   
    else
      digitalWrite(pins[i], LOW);    
  }
  delay(100);  
}

