volatile int numLoops = 0;
volatile double wheelRadius = 0.238125; //meters, 9 3/8 in
volatile double rps;
volatile double linear_speed;
volatile int first_value;
volatile int second_value;
volatile int linear_speed_int;

volatile const int loopsOne = 335;



//define pins
volatile int sensorPin = 15;
volatile int BCDPin1A = 20;   
volatile int BCDPin1B = 23;   
volatile int BCDPin1C = 22; 
volatile int BCDPin1D = 21;   
volatile int BCDPin2A = 16;   
volatile int BCDPin2B = 19;   
volatile int BCDPin2C = 18;   
volatile int BCDPin2D = 17;      

void setup() {
  //set pin modes
  //display #1
  pinMode(BCDPin1A, OUTPUT);
  pinMode(BCDPin1B, OUTPUT);
  pinMode(BCDPin1C, OUTPUT);
  pinMode(BCDPin1D, OUTPUT);
  //display #2
  pinMode(BCDPin2A, OUTPUT);
  pinMode(BCDPin2B, OUTPUT);
  pinMode(BCDPin2C, OUTPUT);
  pinMode(BCDPin2D, OUTPUT); 
  //interrupt pin is sensorPin, interrupt code is called speed, trigger when LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(sensorPin), speed, RISING);
}

void speed() {
  // conversions
  rps = 100.0/numLoops; //numLoops is in 10 millis
  linear_speed = 2 * 3.14159 * wheelRadius * rps; //in m/s
  linear_speed = linear_speed * 0.000621371 * 3600;// in mph (speed * miles/meter * seconds/hour)
  linear_speed_int = (int) linear_speed; //cast as an int

  first_value = linear_speed_int / 10; //calculates the first digit
  second_value = linear_speed_int % 10; //calculates the second digit


   switch (first_value)
   {
    case 0: digitalWrite(BCDPin1A, LOW); digitalWrite(BCDPin1B, LOW); digitalWrite(BCDPin1C, LOW); digitalWrite(BCDPin1D, LOW); break;
    case 1: digitalWrite(BCDPin1A, HIGH); digitalWrite(BCDPin1B, LOW); digitalWrite(BCDPin1C, LOW); digitalWrite(BCDPin1D, LOW); break;
    case 2: digitalWrite(BCDPin1A, LOW); digitalWrite(BCDPin1B, HIGH); digitalWrite(BCDPin1C, LOW); digitalWrite(BCDPin1D, LOW); break;
    case 3: digitalWrite(BCDPin1A, HIGH); digitalWrite(BCDPin1B, HIGH); digitalWrite(BCDPin1C, LOW); digitalWrite(BCDPin1D, LOW); break;
    case 4: digitalWrite(BCDPin1A, LOW); digitalWrite(BCDPin1B, LOW); digitalWrite(BCDPin1C, HIGH); digitalWrite(BCDPin1D, LOW); break;
    case 5: digitalWrite(BCDPin1A, HIGH); digitalWrite(BCDPin1B, LOW); digitalWrite(BCDPin1C, HIGH); digitalWrite(BCDPin1D, LOW); break;
    case 6: digitalWrite(BCDPin1A, LOW); digitalWrite(BCDPin1B, HIGH); digitalWrite(BCDPin1C, HIGH); digitalWrite(BCDPin1D, LOW); break;
    case 7: digitalWrite(BCDPin1A, HIGH); digitalWrite(BCDPin1B, HIGH); digitalWrite(BCDPin1C, HIGH); digitalWrite(BCDPin1D, LOW); break;
    case 8: digitalWrite(BCDPin1A, LOW); digitalWrite(BCDPin1B, LOW); digitalWrite(BCDPin1C, LOW); digitalWrite(BCDPin1D, HIGH); break;
    case 9: digitalWrite(BCDPin1A, HIGH); digitalWrite(BCDPin1B, LOW); digitalWrite(BCDPin1C, LOW); digitalWrite(BCDPin1D, HIGH); break;
   }

 switch (second_value)                            
   {
    case 0: digitalWrite(BCDPin2A, LOW); digitalWrite(BCDPin2B, LOW); digitalWrite(BCDPin2C, LOW); digitalWrite(BCDPin2D, LOW); break;
    case 1: digitalWrite(BCDPin2A, HIGH); digitalWrite(BCDPin2B, LOW); digitalWrite(BCDPin2C, LOW); digitalWrite(BCDPin2D, LOW); break;
    case 2: digitalWrite(BCDPin2A, LOW); digitalWrite(BCDPin2B, HIGH); digitalWrite(BCDPin2C, LOW); digitalWrite(BCDPin2D, LOW); break;
    case 3: digitalWrite(BCDPin2A, HIGH); digitalWrite(BCDPin2B, HIGH); digitalWrite(BCDPin2C, LOW); digitalWrite(BCDPin2D, LOW); break;
    case 4: digitalWrite(BCDPin2A, LOW); digitalWrite(BCDPin2B, LOW); digitalWrite(BCDPin2C, HIGH); digitalWrite(BCDPin2D, LOW); break;
    case 5: digitalWrite(BCDPin2A, HIGH); digitalWrite(BCDPin2B, LOW); digitalWrite(BCDPin2C, HIGH); digitalWrite(BCDPin2D, LOW); break;
    case 6: digitalWrite(BCDPin2A, LOW); digitalWrite(BCDPin2B, HIGH); digitalWrite(BCDPin2C, HIGH); digitalWrite(BCDPin2D, LOW); break;
    case 7: digitalWrite(BCDPin2A, HIGH); digitalWrite(BCDPin2B, HIGH); digitalWrite(BCDPin2C, HIGH); digitalWrite(BCDPin2D, LOW); break;
    case 8: digitalWrite(BCDPin2A, LOW); digitalWrite(BCDPin2B, LOW); digitalWrite(BCDPin2C, LOW); digitalWrite(BCDPin2D, HIGH); break;
    case 9: digitalWrite(BCDPin2A, HIGH); digitalWrite(BCDPin2B, LOW); digitalWrite(BCDPin2C, LOW); digitalWrite(BCDPin2D, HIGH); break;
   }

    numLoops = 0;
}






void loop() {
  delay(10);
  numLoops ++;
  //if the number of loops surpasses that which result from 1 mph, change the speed to zero
    if(numLoops > loopsOne)
  {
    linear_speed = 0;
    digitalWrite(BCDPin1A, LOW); digitalWrite(BCDPin1B, LOW); digitalWrite(BCDPin1C, LOW); digitalWrite(BCDPin1D, LOW);
    digitalWrite(BCDPin2A, LOW); digitalWrite(BCDPin2B, LOW); digitalWrite(BCDPin2C, LOW); digitalWrite(BCDPin2D, LOW);
  }
  //monitoring the speed and time passed
  Serial.println("Linear speed is " + String(linear_speed));
  Serial.println(numLoops);
}
