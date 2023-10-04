void setup() {

  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial.setTimeout(10);
  while(!Serial);
  delay(10);
}

unsigned long cycle_length = 5000; // Cycle delay in ms

void loop() {
  String command = "";
  String response;
  String pinlist;
  int reps = 1;
  int read_temp;

  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
#ifdef DEBUG
    Serial.println("Received cmd");
#endif
  switch (command[0])
  {
    case 'I':
      // Initialization
      talk("OK");
      break;
    
    case 'R':
      pinlist = command.substring(1);
      int hyphen_position = pinlist.indexOf('-'); // -1 if single shot
      if (hyphen_position > -1) {
        reps = pinlist.substring(hyphen_position+1, pinlist.length()).toInt();
        pinlist = pinlist.substring(0, hyphen_position);
      }

      for (int rep = 0; rep < reps; rep +=1) {
        for (int nthpin = 0; nthpin < pinlist.length(); nthpin +=1) {
          int pin_to_read = pinlist[nthpin] - '0';
          read_temp = analogRead(pin_to_read);
          response.concat(read_temp);
          response.concat(',');
        }
        response.concat(',');
      }

      talk(response);
      break;

    case 'O':
      break;

    default:
      talk(command);
  }

  // Write output
  }
}

void talk(String message) {
  if (message.length() > 0) {
    Serial.write(02); //STX start of text
    Serial.write(message.length());
    Serial.print(message);
    Serial.write(3); //ETX end of text
  }
}