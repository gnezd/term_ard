void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  while(!Serial) {
    ;
  }
}

unsigned long cycle_length = 5000; // Cycle delay in ms

void loop() {
  String command;
  String response;
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    Serial.println("Received cmd");
  }
  // Command read
  // Perform pin IO
  // Write output
  if (command.length() > 0){
    response.concat(response)
  } else {
  }
  delay(cycle_length);
}
