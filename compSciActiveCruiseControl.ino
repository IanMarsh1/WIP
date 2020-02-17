/*
This is my AP comp sci project and the goal is to set up an arduino to run 4 motors and set up adaptive cruise control
We use a Ultrasonic Motion sensor to calculate distance
Used H Bridge to make the car move
*/

//define logic control output pin
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;

//define channel enable output pins
int ENA = 5;
int ENB = 11;

// defines pins numbers for sensor
const int trigPin = A5;
const int echoPin = A4;
int flag = 0;
int flag2 = 0;
int dprev = 0;
int speed1 = 255;
int speed2 = 255;

// defines variables for sensor
long duration;
int distance;
int dChange = 0;
int flagCheckF = 0;
int flagCheckB = 0;

//put your setup code
////////////////////////////////////////////////////////////////////////
void setup() {
 Serial.begin(9600); //Open the serial port and set the baud rate to 9600

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}


////////////////////////////////////////////////////////////////////////
void _disCheckF(){
//imput of distance

  int d = distance;
////////////////////////////////////////////////////////////////////////

  if (flag == 0){
    dprev = d;
    flag = 1;
  }
  
////////////////////////////////////////////////////////////////////////
  if(distance <= 15){
    _mStop();
    dprev = d;
  }
  if((dprev - 3) <= d && (dprev + 3) >= d){
    //keep speed
    //_mStop();
    Serial.println("no change");
    dprev = d;
    delay(50);
  }
  //stop
  else if(((dprev - 6) <= d && (dprev + 6) >= d) && !((dprev - 3) <= d && (dprev + 3) >= d)){
    _mStop();
    //dprev=d;
  }
////////////////////////////////////////////////////////////////////////
  //Forward
  else if(d > dprev){
    dChange = d - dprev;
    
    if(dChange < 10){
      speed1 = 75;
      Serial.println("slow");
    }
    else if(dChange >= 10){
      speed1 = 100;
      Serial.println("fast");
    }
    _mForward();
    Serial.println("Forward");
    delay(50);
    dprev = d;
    //flagCheckF==1;
  }
  
////////////////////////////////////////////////////////////////////////
  //Back
  else if(d < dprev){
    dChange = dprev - d;
    
    if(dChange < 10){
      speed2 = 75;
      Serial.println("slow");
    }
    else if(dChange >= 10){
      speed2 = 100;
      Serial.println("fast");
    }
    _mBack();
    Serial.println("back");
    delay(50);
    dprev = d;
    //flagCheckB==1;
  }
}



////////////////////////////////////////////////////////////////////////
void _disCheckB(){
  int d=distance;
  
    if(d > 75){
      //no beep
    }
    else if(d <= 75 && d > 20){//2.5-2
      //beep
    }
    else if(d <= 20 && d > 15){//2-1.5
      //beep beep
    }
    else if(d <= 15 && d > 7.5){
      //beep beep beep
    }
    else if(d <= 7.5){
      //beep beep beep beep
    }
}



////////////////////////////////////////////////////////////////////////
void _mForward(){ 
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed1);
  digitalWrite(in1, HIGH);//digital output
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //Serial.println("Forward");
  }


  
/*define back function*/
////////////////////////////////////////////////////////////////////////
void _mBack(){
  analogWrite(ENA, speed2);
  analogWrite(ENB, speed2);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //Serial.println("Back");
}



/*define left function*/
////////////////////////////////////////////////////////////////////////
void _mleft(){
  
  digitalWrite(ENA, speed1);
  digitalWrite(ENB, speed1);
  digitalWrite(in1, speed1);
  digitalWrite(in2, LOW);
  digitalWrite(in3, speed1);
  digitalWrite(in4, LOW); 
  Serial.println("Left");
}



/*define right function*/
////////////////////////////////////////////////////////////////////////
void _mright(){
  
  digitalWrite(ENA, speed1);
  digitalWrite(ENB, speed1);
  digitalWrite(in1, LOW);
  digitalWrite(in2, speed1);
  digitalWrite(in3, LOW);
  digitalWrite(in4, speed1);
  Serial.println("Right");
}
void _mStop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
} 
////////////////////////////////////////////////////////////////////////
void _echo(){
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance = duration * 0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}


//loop
////////////////////////////////////////////////////////////////////////
void loop() {
delay(200);
_echo();
_disCheckF();
////////////////////////////////////////////////////////////////////////
}
