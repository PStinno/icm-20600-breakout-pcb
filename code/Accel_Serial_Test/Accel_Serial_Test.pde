import processing.serial.*;

Serial myPort;

String data;

float x;
float y;

void setup() {
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
  
  size(400,400);
  background(0);
  fill(255,255,255);
  noStroke();
}

void draw(){
  if (data != null) {
    String trimmed = trim(data);
    String[] values = split(trimmed, ",");
    if (values.length > 2) {
      x = map(int(float(values[0]) * 100), -200, 200, 350, 50);
      y = map(int(float(values[1]) * 100), -200, 200, 350, 50);
    }
  }
  
 background(0);
 ellipse(x, y, 50, 50);
 text("Data: " + data, 10,20);
}

void serialEvent(Serial p) {
  data = p.readString();
}
