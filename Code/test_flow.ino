int IR1 = 7;
int IR2 = 8;
int IR3 = 2;
int IR4 = 4;
int outputir1, outputir2, outputir3, outputir4; 
int intersection = 0;
int r_servo = 5; 
int l_servo = 3; 
bool check;
int straight_rightservo_speed = 1450; 
int straight_leftservo_speed = 1550; 
int tilt_right_rightservo_speed = 1550;
int tilt_right_leftservo_speed = 1550;
int tilt_left_rightservo_speed = 1450;
int tilt_left_leftservo_speed = 1450; 
int reverse_rightservo_speed = 1550;
int reverse_leftservo_speed = 1450; 

int parking_spaces = 0;
// int reverse_tilt_right_rightservo_speed = 1600;
// int reverse_tilt_right_leftservo_speed = 1450;
// int reverse_tilt_left_rightservo_speed = 1550;
// int reverse_tilt_left_leftservo_speed = 1400; 

const int TxPin = 10; // Can use any pin from 2 to 12
#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);



int halt_rightservo_speed = 1500;
int halt_leftservo_speed = 1500;
int right_turn_rightservo_speed = 1600;
int right_turn_leftservo_speed = 1600;
int left_turn_rightservo_speed = 1400;
int left_turn_leftservo_speed = 1400;
bool park_space_main;
//const int trigPin = 13;
//const int echoPin = 12;
const int PING_PIN = 9;
long duration;
int distance;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 300;
const unsigned long period_straight = 800;   //the value is a number of milliseconds
//const byte ledPin = 13;    //using the built in LED
const int distance_check = 20;
int red= 11;
int green = 12; 
int blue = 13;



//int right_turn_rightservo_speed = 


#include<Servo.h> 

Servo right_servo; 
Servo left_servo; 

void setup() 
{
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  right_servo.attach(r_servo);
  left_servo.attach(l_servo);
  pinMode(TxPin, OUTPUT);
  digitalWrite(TxPin, HIGH);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  // pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  // pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  // put your setup code here, to run once:

}


void led_parking_occupancy()
{ 
  digitalWrite(red, HIGH);
  digitalWrite(green,  LOW);
  digitalWrite(blue, LOW);
  halt();
  delay(1000);
  led_off();
}

// void lcd_parking_occupancy()
// { mySerial.write(12);
//   mySerial.write(17);
  
//   mySerial.print("Occupied");

//   delay(1000);
//   mySerial.write(18);
//   mySerial.write(12);

// }

// void lcd_parking_unoccupancy()
// { mySerial.write(12);
//   mySerial.write(17);
  
//   mySerial.print("Unoccupied");

//   delay(1000);
//   mySerial.write(18);
//   mySerial.write(12);
// }

void led_parking_unoccupancy()
{ 
  digitalWrite(red, LOW);
  digitalWrite(green,  HIGH);
  digitalWrite(blue, LOW);
  halt();
  delay(1000);
  led_off();
}

void led_off()
{
  digitalWrite(red, LOW);
  digitalWrite(green,  LOW);
  digitalWrite(blue, LOW);

}
// void lcd_intersection(int intersection)
// {
//   mySerial.write(12);
//   mySerial.write(17);
//   mySerial.print("Intersection No: ");
//   mySerial.print(intersection);
//   delay(1000);
//   mySerial.write(18);
//   mySerial.write(12);
// }

void led_intersection()
{
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  halt();
  delay(300);
  led_off();
}


void lcdtest()
{
  mySerial.write(12);
  mySerial.write(17);
  mySerial.print("Intersection No: ");
  delay(200);
  Serial.println("LCD TEst");
 // mySerial.print(intersection);
  //delay(1000);
  //mySerial.write(18);
  //mySerial.write(12);
}

void lcd_occupied_spaces(int park)
{
  Serial.write(12);
  mySerial.write(17);
  mySerial.print("Total Occupied Spaces :  ");
  mySerial.print(park);
  delay(1000);
  mySerial.write(18);
  mySerial.write(12);

}

void led_occupied_spaces(int park)
{
  
  int k;
  delay(1000);
  for(k = 1; k<=park; k++)
  {
    digitalWrite(red, HIGH);
    digitalWrite(green,  LOW);
    digitalWrite(blue, HIGH);
    //halt();
    delay(500);
    led_off();
    delay(500);
  }

}

long microsecondsToCentimeters(long microseconds) 
{
  return microseconds / 29 / 2;
}

float ultrasonic()
{
  // Clears the trigPin
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // // Sets the trigPin on HIGH state for 10 micro seconds
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  // // Reads the echoPin, returns the sound wave travel time in microseconds
  // duration = pulseIn(echoPin, HIGH);
  // // Calculating the distance
  // distance = duration * 0.034 / 2;
  // // Prints the distance on the Serial Monitor
  // //Serial.print("Distance: ");
  // Serial.println(distance);

  long duration, distance;

  pinMode(PING_PIN, OUTPUT);
  digitalWrite(PING_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(PING_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(PING_PIN, LOW);

  pinMode(PING_PIN, INPUT);
  duration = pulseIn(PING_PIN, HIGH);

  distance = microsecondsToCentimeters(duration);

  // Serial.print(inches);
  // Serial.print("in, ");
  // Serial.print(cm);
  // Serial.print("cm");
  // Serial.println();

  delay(100);


  //distance = 100;
  return distance;
}
  
void straight()
{
  right_servo.writeMicroseconds(straight_rightservo_speed);
  left_servo.writeMicroseconds(straight_leftservo_speed);
  //delay(200);

}

void tilt_right()
{
  right_servo.writeMicroseconds(tilt_right_rightservo_speed);
  left_servo.writeMicroseconds(tilt_right_leftservo_speed); 
  //delay(200);
}

// void reverse_tilt_right()
// {
//   right_servo.writeMicroseconds(reverse_tilt_right_rightservo_speed);
//   left_servo.writeMicroseconds(reverse_tilt_right_leftservo_speed);
// }

// void reverse_tilt_left()
// {
//   right_servo.writeMicroseconds(reverse_tilt_left_rightservo_speed);
//   left_servo.writeMicroseconds(reverse_tilt_left_leftservo_speed);
// }

void tilt_left()
{
  right_servo.writeMicroseconds(tilt_left_rightservo_speed);
  left_servo.writeMicroseconds(tilt_left_leftservo_speed);
  //delay(200);
}

void reverse()
{
  right_servo.writeMicroseconds(reverse_rightservo_speed);
  left_servo.writeMicroseconds(reverse_leftservo_speed);
  //delay(200);
}

void halt()
{
  
  right_servo.writeMicroseconds(halt_rightservo_speed);
  left_servo.writeMicroseconds(halt_leftservo_speed);
  //delay(200);
}


void right_turn()
{
  right_servo.writeMicroseconds(right_turn_rightservo_speed);
  left_servo.writeMicroseconds(right_turn_leftservo_speed);
}


void left_turn()
{
  right_servo.writeMicroseconds(left_turn_rightservo_speed);
  left_servo.writeMicroseconds(left_turn_leftservo_speed);
}

void straight_correction()
{
  startMillis = millis();
  currentMillis = millis();

  while((currentMillis - startMillis) <= period_straight)
  { 
    currentMillis = millis();
    straight();
  }
  halt();
  delay(500);
}

void reverse_correction()
{
  startMillis = millis();
  currentMillis = millis();

  while((currentMillis - startMillis) <= period_straight)
  { 
    currentMillis = millis();
    reverse();
  }
}


void reverse_frontsensor()
{

    outputir1 = digitalRead(IR1);
    outputir2 = digitalRead(IR2);


    while(!((outputir1 == 1) && (outputir2 == 1)))
  { 
    outputir1 = digitalRead(IR1);
    outputir2 = digitalRead(IR2);
    outputir3 = digitalRead(IR3);
    outputir4 = digitalRead(IR4);
    if((outputir3 == 0) && (outputir4 ==0))
    {
      Serial.println("Straight Line");
      reverse();

    }
    else if((outputir3 == 0) && (outputir4 == 1))
    {
      Serial.println("Right Tilt");
      tilt_left();

    }
    else if((outputir3 ==1) &&(outputir4 ==0))    
    {
      Serial.println("Left Tilt");
      tilt_right();
    }
    else if((outputir3 == 1) && (outputir4 == 1))
    {
      // Serial.println("Intersection");
      // startMillis = millis();
      // currentMillis = millis();
      // Serial.println("here at halt");
      // while((currentMillis - startMillis)<=1000)
      // {
      //   currentMillis = millis();
      //   halt();
      // }
      Serial.println("Still Reverse");
      reverse();
      
      //break;
    }
    //delay(1000);
  }
  //delay(1000);

  Serial.println("Detected Intersection");

  
}

void reverse_motion()
{
  
  while(true)
  { 
    outputir3 = digitalRead(IR3);
    outputir4 = digitalRead(IR4);
    if((outputir3 == 0) && (outputir4 ==0))
    {
      Serial.println("Straight Line");
      reverse();

    }
    else if((outputir3 == 0) && (outputir4 == 1))
    {
      Serial.println("Right Tilt");
      tilt_left();

    }
    else if((outputir3 ==1) &&(outputir4 ==0))
    {
      Serial.println("Left Tilt");
      tilt_right();
    }
    else if((outputir3 == 1) && (outputir4 == 1))
    {
      Serial.println("Intersection");
      startMillis = millis();
      currentMillis = millis();
      Serial.println("here at halt");
      while((currentMillis - startMillis)<=1000)
      {
        currentMillis = millis();
        halt();
      }
      break;
      //break;
    }
    //delay(1000);
  }

}




void Right_turn_90()
{

  startMillis = millis();
  currentMillis = millis();
  Serial.println("here at 90 degree turn");

  while((currentMillis - startMillis) <= period_straight)
  { 
    currentMillis = millis();
    straight();
  }
  halt();

  //delay(5000);
  startMillis = millis();
  currentMillis = millis();

  int currentstateir2, counter, laststateir2;
  currentstateir2 = digitalRead(IR2);
  laststateir2 = currentstateir2; 
  
  

  if(currentstateir2 == 0)
  {
    counter  = 2;
  }
  else
  {
    counter = 3; 
  }
  int i=1;


  

  while(i<=counter)
  { 
    right_turn();
    currentstateir2 = digitalRead(IR2);
    if(laststateir2 != currentstateir2)
    {
      i++;
      laststateir2 = currentstateir2; 
    }
  }


  // while((currentMillis - startMillis) <= period)
  // {

  //  currentMillis = millis();
  //  right_turn();

  // }
  // //  startMillis = millis();
  // //  currentMillis = millis();

  // while(true) 
  //  { 
  //     outputir1=digitalRead(IR1);
  //     outputir2=digitalRead(IR2);
  //     right_turn();
  //     if (outputir2 == 1)
  //     {
  //       break;
  //     }
      

  //  }   

}

void Left_turn_90()
{
  
  startMillis = millis();
  currentMillis = millis();
  Serial.println("here at 90 degree turn for left");

  // while((currentMillis - startMillis) <= period_straight)
  // { 
  //   currentMillis = millis();
  //   straight();
  // }
  //halt();

  //delay(5000);
  startMillis = millis();
  currentMillis = millis();

  int currentstateir1, counter, laststateir1;
  currentstateir1 = digitalRead(IR1);
  laststateir1 = currentstateir1; 
  
  

  if(currentstateir1 == 0)
  {
    counter  = 2;
  }
  else
  {
    counter = 3; 
  }
  int i=1;


  

  while(i<=counter)
  { 
    left_turn();
    currentstateir1 = digitalRead(IR1);
    if(laststateir1 != currentstateir1)
    {
      i++;
      laststateir1 = currentstateir1; 
      Serial.println("Change detected");
      Serial.println(i);
    }
  }


}




// void right_turn()
// {
//   right_servo.writeMicroseconds(int value);
//   left_servo.writeMicroseconds(int value)
// }

//void right_tilt()
void motion()
{

  while(true)
  { 
    outputir1 = digitalRead(IR1);
    outputir2 = digitalRead(IR2);
    if((outputir1 == 0) && (outputir2 ==0))
    {
      //Serial.println("Straight Line");
      straight();

    }
    else if((outputir1 == 0) && (outputir2 == 1))
    {
      Serial.println("Right Tilt");
      tilt_right();

    }
    else if((outputir1 ==1) &&(outputir2 ==0))
    {
      Serial.println("Left Tilt");
      tilt_left();
    }
    else if((outputir1 == 1) && (outputir2 == 1))
    {
      Serial.println("Intersection");
      startMillis = millis();
      currentMillis = millis();
      Serial.println("here at halt");
      while((currentMillis - startMillis)<=1000)
      {
        currentMillis = millis();
        halt();
        //led_intersection();
      }
      //led_off();
      break;
      //break;
    }
    //delay(1000);
  }
}



bool motion_rightside()
{ int dist;
  bool parkspace;

  while(true)
  {
    outputir1 = digitalRead(IR1);
    outputir2 = digitalRead(IR2);
    dist = ultrasonic();

    if (dist<distance_check)
    {
      parkspace = false;
      Serial.println("Space is Occupied");
      led_parking_occupancy();
      parking_spaces++; 
      //delay(3000);
      break;
    }
    else if((dist>=distance_check) && (outputir1 == 0) && (outputir2 == 0))
    {
      //move forward and keep checking
      Serial.println("Moving Straight and keep looking, empty so far");
      straight();
      //delay(3000);
    }

    else if((dist>=distance_check) && (outputir1 == 0) && (outputir2 == 1))
    {
      //tilt right and keep looking
      Serial.println("Tilting right and keep looking, empty so far");
      tilt_right();
      //delay(3000);
    }

    else if((dist>=distance_check) && (outputir1 == 1) && (outputir2 == 0))
    {
      //tilt left and keep looking
      Serial.println("Tilting left and keep looking, empty so far");
      tilt_left();
      //delay(3000);
    }
    else if((dist>=distance_check) && (outputir1 == 1) && (outputir2 == 1))
    {
      //end reached and still empty
      Serial.println("End Reached and parking space is empty");
      halt();
      parkspace = true;
      //delay(3000);
      break;
    }
  }

  if (parkspace == true)
  { 
    //lcd_parking_unoccupancy();
    return true;
  }
  else 
  {
    return false;
  }
    
}


bool motion_leftside()
{
  int dist;
  bool parkspace;
  
  while(true)
  {

    outputir3 = digitalRead(IR3);
    outputir4 = digitalRead(IR4);
    dist = ultrasonic();
    if (dist<distance_check)
    {
      parkspace = false;
      Serial.println("Space is Occupied");
      parking_spaces++; 
      led_parking_occupancy();
      //delay(3000);
      break;
    }
        else if((dist>=distance_check) && (outputir3 == 0) && (outputir4 == 0))
    {
      //move forward and keep checking
      //Serial.println("Moving Straight and keep looking, empty so far");
      reverse();
      //delay(3000);
    }

    else if((dist>=distance_check) && (outputir3 == 0) && (outputir4 == 1))
    {
      //tilt right and keep looking
      Serial.println("Tilting right and keep looking, empty so far");
      tilt_left();
      //delay(3000);
    }

    else if((dist>=distance_check) && (outputir3 == 1) && (outputir4 == 0))
    {
      //tilt left and keep looking
      Serial.println("Tilting left and keep looking, empty so far");
      tilt_right();
      //delay(3000);
    }
    else if((dist>=distance_check) && (outputir3 == 1) && (outputir4 == 1))
    {
      //end reached and still empty
      Serial.println("End Reached and parking space is empty");
      halt();
      parkspace = true;
      //delay(3000);
      break;
    }
  }

  if (parkspace == true)
  {
    //lcd_parking_unoccupancy();
    return true;
  }
  else 
  {
    return false;
  }
  
}



void loop()
{// halt();
//   lcdtest();

//led_parking_unoccupancy();


  bool park_right; 
  bool park_left;
  //lcdtest();

  motion();
  intersection = intersection + 1; 
  led_intersection();
  
  //lcd_intersection(intersection);

  if(intersection == 9)
  {
    //lcd_occupied_spaces(parking_spaces);
    exit(0);
  }
  //Right_turn_90();
  // Left_turn_90();
  // halt();
  // delay(5000);

  if (intersection % 2 != 0)
  {
    Right_turn_90();
    park_right = motion_rightside();
    reverse_correction();
    reverse_frontsensor();
    if(park_right == true)
      {//reverse for some time for calling left turn
      //left turn
      straight_correction();
      Left_turn_90();
      motion();
      Right_turn_90();
      motion();
      led_parking_unoccupancy();     
      led_occupied_spaces(parking_spaces); 
      delay(1000);
      exit(0);
      //end program
      }
    //reverse_correction();
    


    park_left = motion_leftside();
    motion();
    //forward for some time
    straight_correction();
    Left_turn_90();


    //left turn
    if(park_left == true)
    {
      motion();
      straight_correction();
      //forward for some time
      Left_turn_90();
      motion();
      led_parking_unoccupancy();

      led_occupied_spaces(parking_spaces);
      delay(1000);
      // straight_correction();
      // Left_turn_90();
      // motion();
      exit(0);
      //end program
    }



    //Left_turn_90();
  
  }

  straight_correction();

  // reverse_frontsensor();
  // halt();
  // delay(3000);
}
