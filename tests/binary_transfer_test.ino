
float number = 0.0;
unsigned char *flptr;
String cmd;
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  while(!Serial) {
    ;
  }
  flptr = (unsigned char*)&number;
}

void loop() {
    unsigned char outbuff[4];
    if (Serial.available() > 0) {
        cmd = Serial.readString();
        outbuff[0] = flptr[0];
        outbuff[1] = flptr[1];
        outbuff[2] = flptr[2];
        outbuff[3] = flptr[3];
        Serial.flush();
        Serial.write(outbuff, 4);
        number += 0.01;

    }
}