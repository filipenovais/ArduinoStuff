
int photocellPin = 0;
int photocellReading;     
int LED = 11;
int sol = 12;
int buzzer = 9;

void setup(void) {
  pinMode(sol, OUTPUT);
  digitalWrite(sol, LOW);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);     
  
  if(photocellReading < 100 ){
    digitalWrite(LED, HIGH);
    delay(1500);
    digitalWrite(LED, LOW);
    tone(buzzer, 500);
    delay(500);
    digitalWrite(LED, HIGH);
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(250);
    digitalWrite(LED, LOW);
    tone(buzzer, 500);
    delay(250);
    digitalWrite(LED, HIGH);
    tone(buzzer, 1000);
    delay(100);
    digitalWrite(LED, LOW);
    tone(buzzer, 500);
    delay(100);
    digitalWrite(LED, HIGH);
    tone(buzzer, 1000);
    delay(50);
    digitalWrite(LED, LOW);
    tone(buzzer, 1000);
    delay(50);
    digitalWrite(sol, HIGH);
    tone(buzzer, 1500);
    delay(100);
    digitalWrite(sol, LOW);
    delay(200);
    noTone(buzzer);     
        
    delay(1000);
  }else{
    digitalWrite(LED, LOW);
    digitalWrite(sol, LOW);
    noTone(buzzer);
  }
 
  delay(100);
}
