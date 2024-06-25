// úžasnej kód co psal zatim petr 
// motory 5/7 6/8 PWM/směr
// D9 je tlačítko vole
// senzor vzdalenost A0 left A1 center A2 right
int mLs = 5; //motor levý směr
int mLp = 3; //motor levý výkon
int mPs = 4; //motor pravý směr
int mPp = 2; //motor pravý výkon
// Define color sensor pins
#define S0 6
#define S1 7
#define S2 8
#define S3 9
#define sensorOut 10

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

void stop(){
  Serial.println("Stop");
      digitalWrite(mLs, LOW);
      analogWrite(mLp, 0);
      digitalWrite(mPs, LOW);
      analogWrite(mPp, 0);
}

void rovne(int spozdeni) {
  Serial.println("Vpřed");
  digitalWrite(mLs, LOW);
  analogWrite(mLp, front1left);
  digitalWrite(mPs, LOW);
  analogWrite(mPp, front1right*1.07);
  delay(spozdeni);
  stop();
} 

void setup() {
  // motory
  pinMode(mLs, OUTPUT);
  pinMode(mLp, OUTPUT);
  pinMode(mPs, OUTPUT);
  pinMode(mPp, OUTPUT);
  // Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Pulse Width scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

  // sériový monitor
  Serial.begin(9600);
}

void loop() {
	// Read Red Pulse Width
	redPW = getRedPW();
	// Delay to stabilize sensor
	delay(50);

	// Read Green Pulse Width
	greenPW = getGreenPW();
	// Delay to stabilize sensor
	delay(50);

	// Read Blue Pulse Width
	bluePW = getBluePW();
	// Delay to stabilize sensor
	delay(50);

	// Print output to Serial Monitor
	Serial.print("Red PW = ");
	Serial.print(redPW);
	Serial.print(" - Green PW = ");
	Serial.print(greenPW);
	Serial.print(" - Blue PW = ");
	Serial.println(bluePW);
  if (redPW<=60 && greenPW>=110 && bluePW >=110){
    Serial.println("ČERVENÁ!");
    digitalWrite(mLs, LOW);
    analogWrite(mLp, 150);
    digitalWrite(mPs, LOW);
    analogWrite(mPp, 150);
    delay(100);
    Serial.println("otočka hotova");
    stop();
  }
  else{

    }
}
