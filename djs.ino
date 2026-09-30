// TB6612FNG Motor Driver Pins
#define PWMA 25
#define AIN1 26
#define AIN2 27
#define PWMB 14
#define BIN1 12
#define BIN2 13
#define STBY 33

// IR Sensor Pins
#define R_S 34
#define L_S 35

// PWM Config
#define MOTOR_A_CH 0
#define MOTOR_B_CH 1
#define PWM_FREQ 5000
#define PWM_RES 8

#define BASE_SPEED 170
#define TURN_SPEED 160

void setupMotors() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  ledcSetup(MOTOR_A_CH, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWMA, MOTOR_A_CH);
  ledcSetup(MOTOR_B_CH, PWM_FREQ, PWM_RES);
  ledcAttachPin(PWMB, MOTOR_B_CH);
}

void forward() {
  digitalWrite(AIN1, LOW);   // flipped
  digitalWrite(AIN2, HIGH);
  ledcWrite(MOTOR_A_CH, BASE_SPEED);

  digitalWrite(BIN1, LOW);   // flipped
  digitalWrite(BIN2, HIGH);
  ledcWrite(MOTOR_B_CH, BASE_SPEED);
}

void turnRight() {
  digitalWrite(AIN1, LOW);   // flipped
  digitalWrite(AIN2, HIGH);
  ledcWrite(MOTOR_A_CH, TURN_SPEED);

  digitalWrite(BIN1, HIGH);  // flipped
  digitalWrite(BIN2, LOW);
  ledcWrite(MOTOR_B_CH, TURN_SPEED);
}

void turnLeft() {
  digitalWrite(AIN1, HIGH);  // flipped
  digitalWrite(AIN2, LOW);
  ledcWrite(MOTOR_A_CH, TURN_SPEED);

  digitalWrite(BIN1, LOW);   // flipped
  digitalWrite(BIN2, HIGH);
  ledcWrite(MOTOR_B_CH, TURN_SPEED);
}

void stopMotors() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  ledcWrite(MOTOR_A_CH, 0);
  ledcWrite(MOTOR_B_CH, 0);
}

void setup() {
  Serial.begin(115200);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  
  ledcSetup(MOTOR_A_CH, 5000, 8);
  ledcAttachPin(PWMA, MOTOR_A_CH);
  ledcSetup(MOTOR_B_CH, 5000, 8);
  ledcAttachPin(PWMB, MOTOR_B_CH);

  Serial.println("Both motors forward");
  
  // Motor A - FLIPPED to fix left motor
  digitalWrite(AIN1, HIGH);  // changed from LOW
  digitalWrite(AIN2, LOW);   // changed from HIGH
  ledcWrite(MOTOR_A_CH, 200);
  
  // Motor B - stays same, already correct
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  ledcWrite(MOTOR_B_CH, 200);
}

void loop() {
  int rightSensor = digitalRead(R_S);
  int leftSensor  = digitalRead(L_S);

  Serial.print("L: "); Serial.print(leftSensor);
  Serial.print(" | R: "); Serial.println(rightSensor);

  // Swapped all conditions
  if (leftSensor == 0 && rightSensor == 0) {
    forward();
    Serial.println("forward going");
  } else if (leftSensor == 1 && rightSensor == 0) {
    turnLeft();
    Serial.println("left going");
  } else if (leftSensor == 0 && rightSensor == 1) {
    turnRight();
    Serial.println("right going");
  } else if (leftSensor == 1 && rightSensor == 1) {
    stopMotors();
    Serial.println("stopping");
  }

  delay(50);
}