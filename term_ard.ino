void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  while(!Serial) {
    ;
  }
}

void loop() {
  int pin_to_read;
  int read_temp = 0;
  String command;
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
  /* debug dump
    Serial.println("Received");
    Serial.println(command.length());
    Serial.println(command);
  */
  }
  
  //Read analogs
  if (command[0] == 'R') {
    if (command.length() > 1) { // Read some pins
      String pin_list = command.substring(1);
      for(int i = 0; i < pin_list.length(); i += 1) {
        pin_to_read = pin_list[i] - '0';
        read_temp = analogRead(pin_to_read);
        read_temp = analogRead(pin_to_read);
        Serial.print((double)read_temp*5.0/1024, 5);
        Serial.print(" ");
      }
      Serial.print("\n");
    } else { // Read all pins

      for(int i = 0; i < 6; i+= 1) {
      read_temp = analogRead(i);
      read_temp = analogRead(i);
      Serial.print((double)read_temp*5.0/1024, 5);
      Serial.print(" ");
      }
      Serial.print("\n");
    }
  }
  //Digital out
  else if (command[0] == 'D') {
    if (command.length() >= 3) {
      int pin_num = command.substring(1, command.length()-1).toInt();
      String value = command.substring(command.length()-1);
      Serial.print("Pin number ");
      Serial.print(pin_num, DEC);
      Serial.print(" ");
      Serial.println(value);
      if (value == "H") {
        // pull up pin
        digitalWrite(pin_num, HIGH);
      } else if (value == "L") {
        // pull low
        digitalWrite(pin_num, LOW);
      }
    }
  }
  // Analog out
  else if (command[0] == 'A') {
    if (command.length() >= 3) { //A9255 for example
      int pin_num = command.substring(1, command.length()-3).toInt();
      // Analog pin?
      if (!(pin_num == 3 || pin_num == 5 || pin_num == 6 || pin_num == 9 || pin_num == 10 || pin_num == 11)) {
        Serial.println("Not analog pin");
      } else {
      int value = command.substring(command.length()-3).toInt();
      Serial.print("Pin number ");
      Serial.print(pin_num, DEC);
      Serial.print(" ");
      Serial.println(value);
      analogWrite(pin_num, value);
      }
    }
  }

  //delay(500);
  command = '\0';
  delay(10);
}
