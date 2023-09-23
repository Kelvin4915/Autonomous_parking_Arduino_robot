//pins and declaring variables and constants
int IR1 = 7; //Front IR
int IR2 = 8; //Front IR 
int IR3 = 2; //Back IR
int IR4 = 4; //Back IR
int outputir1, outputir2, outputir3, outputir4; //Variables for keeping track of the output of the IR's 
int intersection = 0; //Keeping track of the number of encountered intersections
int r_servo = 5; //Pin for Right Servo  
int l_servo = 3; //Pin for Left Servo
bool check;

// Declaring different use case servo speeds
int straight_rightservo_speed = 1450; 
int straight_leftservo_speed = 1550; 
int tilt_right_rightservo_speed = 1550;
int tilt_right_leftservo_speed = 1550;
int tilt_left_rightservo_speed = 1450;
int tilt_left_leftservo_speed = 1450; 
int reverse_rightservo_speed = 1550;
int reverse_leftservo_speed = 1450; 
int parking_spaces = 0;
int halt_rightservo_speed = 1500;
int halt_leftservo_speed = 1500;
int right_turn_rightservo_speed = 1600;
int right_turn_leftservo_speed = 1600;
int left_turn_rightservo_speed = 1400;
int left_turn_leftservo_speed = 1400;


bool park_space_main;
const int PING_PIN = 9; // pin for ultrasonic 
long duration; // variable for ultrasonic wave duration return time
int distance; // variable for distance measurement 
unsigned long startMillis;  //keeping track of time using millis();
unsigned long currentMillis; //keeping track of time using millis();
const unsigned long period = 300; 
const unsigned long period_straight = 800;   //straight correction
const int distance_check = 20; // value for obstacle thereshold 
int red= 11; //pin for red colour in led
int green = 12; //pin for green colour in led
int blue = 13; //pin for blue color in led
const unsigned long bonus = 2800; // variable for bonus case 
const unsigned long bonus_left = 1700; 


#include<Servo.h> 
Servo right_servo; 
Servo left_servo; 


//setup for all hardware (except ultrasonic)
void setup() 
{
  pinMode(IR1, INPUT); 
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  right_servo.attach(r_servo);
  left_servo.attach(l_servo);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT); 
  Serial.begin(9600);
}


//function for indicating an occupied space
void led_parking_occupancy()
{ 
  digitalWrite(red, HIGH);
  digitalWrite(green,  LOW);
  digitalWrite(blue, LOW);
  halt();
  delay(1000);
  led_off();
}

//function for BONUS TWO WHEELER INDICATION
void led_bonus()
{
  digitalWrite(red, HIGH);
  digitalWrite(green,  HIGH);
  digitalWrite(blue, HIGH);
  halt();
  delay(1000);
  led_off();

}

//function for indicating an unnocupied space
void led_parking_unoccupancy()
{ 
  digitalWrite(red, LOW);
  digitalWrite(green,  HIGH);
  digitalWrite(blue, LOW);
  halt();
  delay(1000);
  led_off();
}

//function for turning of LEDs
void led_off()
{
  digitalWrite(red, LOW);
  digitalWrite(green,  LOW);
  digitalWrite(blue, LOW);

}

//function for indicating intersection
void led_intersection()
{
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
  halt();
  delay(300);
  led_off();
}

//function for indicating encountered occupied parking spaces along the way
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

//function for converting microseconds to centimeters 
long microsecondsToCentimeters(long microseconds) 
{
  return microseconds / 29 / 2;
}

//function for returning distance fro the ultrasonic
float ultrasonic()
{

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
  delay(100);
  return distance;
}

//function for heading straight 
void straight()
{
  right_servo.writeMicroseconds(straight_rightservo_speed);
  left_servo.writeMicroseconds(straight_leftservo_speed);
  //delay(200);

}
//function for tilting right
void tilt_right()
{
  right_servo.writeMicroseconds(tilt_right_rightservo_speed);
  left_servo.writeMicroseconds(tilt_right_leftservo_speed); 
  //delay(200);
}

//function for tilting left
void tilt_left()
{
  right_servo.writeMicroseconds(tilt_left_rightservo_speed);
  left_servo.writeMicroseconds(tilt_left_leftservo_speed);
  //delay(200);
}

//function for going reverse
void reverse()
{
  right_servo.writeMicroseconds(reverse_rightservo_speed);
  left_servo.writeMicroseconds(reverse_leftservo_speed);
  //delay(200);
}

//function for halting
void halt()
{
  
  right_servo.writeMicroseconds(halt_rightservo_speed);
  left_servo.writeMicroseconds(halt_leftservo_speed);
  //delay(200);
}

//function for right turn
void right_turn()
{
  right_servo.writeMicroseconds(right_turn_rightservo_speed);
  left_servo.writeMicroseconds(right_turn_leftservo_speed);
}

//function for left turn
void left_turn()
{
  right_servo.writeMicroseconds(left_turn_rightservo_speed);
  left_servo.writeMicroseconds(left_turn_leftservo_speed);
}
//function for going straight for some time
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

//function for going reverse for some time
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

//function for going reverse using back IRs until the front IRs detect black
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
      Serial.println("Intersection");

      reverse();
      
      //break;
    }
    //delay(1000);
  }
  //delay(1000);

  Serial.println("Detected Intersection");

  
}

//function for reverse using the IRs at the back 
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
      while((currentMillis - startMillis)<=100)
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



//function for turning right
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

  


}


//function for turning left
void Left_turn_90()
{
  
  startMillis = millis();
  currentMillis = millis();
  Serial.println("here at 90 degree turn for left");

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


//function for simple line following 
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
      while((currentMillis - startMillis)<=100)
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

//function for BONUS case to detect TWO Wheeler beyond the designated parking availability
void bonus_rightside()
{
  int dist;
  Serial.println("Here at bonus case");

  while(true)
  {
    outputir1 = digitalRead(IR1);
    outputir2 = digitalRead(IR2);
    //currentMillis = millis();
    dist = ultrasonic();

    if (dist<distance_check)
    {

      halt();
      Serial.println("Bonus occupied space");
      led_bonus();
      break;
    }
    else if((dist>=distance_check) && (outputir1 == 0) && (outputir2 == 0))
    {

      straight();
      Serial.println("Bonus Straight");

    }

    else if((dist>=distance_check) && (outputir1 == 0) && (outputir2 == 1))
    {

      tilt_right();
  
    }

    else if((dist>=distance_check) && (outputir1 == 1) && (outputir2 == 0))
    {
      tilt_left();

    }
    else if((dist>=distance_check) && (outputir1 == 1) && (outputir2 == 1))
    {
      Serial.println("Bonus empty");
      halt();
      break;
    }
  }

}

//function for checking the parking occupancy in the right lane
bool motion_rightside()
{ int dist;
  bool parkspace= true;
  startMillis = millis();
  currentMillis = millis();


  while(currentMillis - startMillis < bonus)
  {
    outputir1 = digitalRead(IR1);
    outputir2 = digitalRead(IR2);
    currentMillis = millis();
    dist = ultrasonic();

    if (dist<distance_check )
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

  }



  if (parkspace == true)
  { 
    bonus_rightside();
    //return true;

  }

  return parkspace; 
}

//Function for BONUS Case to detect an object beyond the designated parking availability
void bonus_leftside()
{
  int dist;
  //bool parkspace;
    while(true)
  {

    outputir3 = digitalRead(IR3);
    outputir4 = digitalRead(IR4);
    //currentMillis = millis();
    dist = ultrasonic();
    if (dist<distance_check)
    {
      //parkspace = false;
      Serial.println("Space is Occupied");
      //parking_spaces++; 
      led_bonus();
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
      //halt();
      //parkspace = true;
      //delay(3000);
      break;
    }
  }
}

//function for checking the parking occupancy in the left lane
bool motion_leftside()
{
  int dist;
  bool parkspace= true;
  startMillis = millis();
  currentMillis = millis();

  
  while(currentMillis - startMillis <  bonus_left)
  {

    outputir3 = digitalRead(IR3);
    outputir4 = digitalRead(IR4);
    currentMillis = millis();
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

  }
  

  if (parkspace == true)
  {  
    bonus_leftside();

  }

  return parkspace;

  
}



void loop()
{


  bool park_right; // variable for checking parking occupancy in the right side 
  bool park_left; // variable for checking parking occupancy in the left side
  //lcdtest();

  motion(); //forward
  intersection = intersection + 1; //intersection update
  led_intersection();
  

  if(intersection == 9) //condition for stopping at the 9th intersection
  {
    led_occupied_spaces(parking_spaces); 
    exit(0);
  }

  if (intersection % 2 != 0) //condition for checking only in odd intersections
  {
    Right_turn_90();
    park_right = motion_rightside(); //get a boolean value 

    reverse_correction(); 
    reverse_frontsensor(); //go reverse until hitting center lane
    if(park_right == true) //if the parking is available in the right side, then code for parking and exit
      {//reverse for some time for calling left turn
      //left turn
      straight_correction();
      Left_turn_90();
      motion();
      //led_intersection();
      Right_turn_90();
      motion();
      led_parking_unoccupancy();     
      led_occupied_spaces(parking_spaces); 
      delay(1000);
      exit(0);
      //end program
      }
    //reverse_correction();
    


    park_left = motion_leftside(); //get a boolean value
    motion(); //forward motion until hitting center lane

    straight_correction();
    Left_turn_90(); 


    //left turn
    if(park_left == true)//if the parking is available in the right side, then code for parking and exit
    {
      motion();
      straight_correction();
      //forward for some time
      Left_turn_90();
      motion();
      //led_intersection();
      led_parking_unoccupancy();

      led_occupied_spaces(parking_spaces);
      delay(1000);

      exit(0);

    }


  
  }

  straight_correction();

}
