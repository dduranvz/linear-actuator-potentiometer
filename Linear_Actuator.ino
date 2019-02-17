int PWM = 11; // assigns pin 11 to variable pwm
int DIR = 8;

/*************************************
   Variables for prcessing position
 *************************************/
int feedback = A0;
volatile int pos = 500;
volatile int val;
String str;

int actMax = 900;
int actMin = 100;//positions of actuator

int currentPosition = 0;
int destination = 0;
int difference = 0;
int precision = 2;

void setup()  // setup loop
{
  // Initialize the serial link with processing
  Serial.begin(9600);

  // Pin declarations
  pinMode(feedback, INPUT);
  pinMode(PWM, OUTPUT); 
  pinMode(DIR, OUTPUT);
}

void loop()
{
  // Read current position
  currentPosition = analogRead(feedback);
  Serial.print("Current pos: ");
  Serial.println(currentPosition);

  //Calculate how far we are away from setpoint
  difference = abs(pos - currentPosition); 

  // Define limits
  if(pos > actMax) {
    pos = actMax;
  }
  else if(pos < actMin) {
    pos = actMin;
  }

  // Run linear actuator until position is reached
  if(currentPosition > pos) {
    digitalWrite(DIR, 1);
    analogWrite(PWM, 255);
  }
  if(currentPosition < pos) {
    digitalWrite(DIR, 0);
    analogWrite(PWM, 255);
  }
  if(difference <= precision) {
    analogWrite(PWM, 0);
  }
}

// Read serial for position
void serialEvent() {
//  str = Serial.readStringUntil(':');
  pos = Serial.parseInt();
//  if(str == "pos"){
//    pos = val;
//  }
}
