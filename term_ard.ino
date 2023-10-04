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
  String response = "";
  String list_rep;
  String pinlist;
  String values;
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
      list_rep = command.substring(1);
      split_reps(list_rep, &pinlist, &reps);

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
      list_rep = command.substring(2);
      split_output(list_rep, &pinlist, &values);

      switch (command[1]) 
      {
        case 'D':
          for (int nthpin = 0; nthpin < pinlist.length(); nthpin += 1) {
            int pin_num = pinlist[nthpin] - '0';
            if (values[nthpin] == 'H') {
              digitalWrite(pin_num, HIGH);
            } else if (values[nthpin] == 'H') {
              digitalWrite(pin_num, LOW);
            }
          }
          response = "OK";
          break;
        case 'A':
          for (int nthpin = 0; nthpin < pinlist.length(); nthpin += 1) {
            int pin_num = pinlist[nthpin] - '0';
            int value = values.substring(nthpin*3, nthpin*3 + 3).toInt();
            analogWrite(pin_num, value);
            response.concat(pin_num);
            response.concat('-');
            response.concat(value);
            response.concat('|');
          }
          break;
        default:
        talk(command);

      }

      talk(response);
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

// Split pinlist-repetition
void split_reps(String list_rep, String *pinlist, int *reps) {
  int hyphen_position = list_rep.indexOf('-'); // -1 if single shot
  if (hyphen_position > -1) {
    *reps = list_rep.substring(hyphen_position+1, list_rep.length()).toInt();
    *pinlist = list_rep.substring(0, hyphen_position);
  }
}

// Split pinlist-values
void split_output(String list_rep, String *pinlist, String *values) {
  int hyphen_position = list_rep.indexOf('-'); // -1 if single shot
  if (hyphen_position > -1) {
    *values = list_rep.substring(hyphen_position+1, list_rep.length());
    *pinlist = list_rep.substring(0, hyphen_position);
  }
}