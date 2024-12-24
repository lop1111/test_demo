import processing.serial.*;

import meter.*;

Meter M;
Meter M1;



Serial port;

int bsize= 50, bx=100, by=65, b2x= 0, b2y=160, b3x = 100, b3y=240, b4x = 200, b4y = 160, bex = 40, bey = 460, bes = 75;

int lightCount = 0, light_red=0, light_green=0;


void setup()
{
  size(1200, 800);

  port = new Serial(this, "COM5", 9600);


  M_setup();
  M1_setup();
}

int D;

void draw()
{

  background(100, 160, 120);

  Text();

  Buttons();

  Forward();

  Left();

  Back();

  Right();

  Light();

  int value = (int)random(0, 40);
  M.updateMeter(value);
  M1.updateMeter(value);
  delay(500);
}



void Buttons()
{
  // Layout for the Joystick //
  fill(0, 0, 180);
  rect(0, 50, 250, 250);

  fill(255, 0, 0);  
  rect(bx, by, bsize, bsize);

  fill(255, 0, 0);  
  rect(b2x, b2y, bsize, bsize);

  fill(255, 0, 0);  
  rect(b3x, b3y, bsize, bsize);

  fill(255, 0, 0);  
  rect(b4x, b4y, bsize, bsize);

  // Layout for the Light Toggle //

  fill(20, 40, 20);
  rect(0, 400, 240, 120);

  fill(100, 0, 26);
  ellipse(bex, bey, bes, bes);

  fill(light_red, light_green, 0);
  ellipse(180, 455, bes, bes);
}

void Text()
{
  // Main Heading //
  textSize(50);
  fill(0, 120, 612);
  text("JARVIS", 550, 60);

  // Joystick //

  textSize(20);
  fill(255, 0, 0);
  text("JOYSTICK", 60, 40);

  // Light Control Text //

  textSize(20);
  fill(255, 0, 0);
  text("LIGHT SWITCH", 20, 380);
}

void Forward()
{
  if (mousePressed && mouseX > bx-bsize && mouseX < bx+bsize && mouseY > by-bsize && mouseY < by+bsize) 
  {
    background(0, 0, 255);
    print('F');
  }
}

void Left()
{
  if (mousePressed && mouseX > b2x-bsize && mouseX < b2x+bsize && mouseY > b2y-bsize && mouseY < b2y+bsize) 
  {
    background(0, 0, 255);
  }
}

void Back()
{
  if (mousePressed && mouseX > b3x-bsize && mouseX < b3x+bsize && mouseY > b3y-bsize && mouseY < b3y+bsize) 
  {
    background(0, 0, 255);
  }
}

void Right()
{
  if (mousePressed && mouseX > b4x-bsize && mouseX < b4x+bsize && mouseY > b4y-bsize && mouseY < b4y+bsize) 
  {
    background(0, 0, 255);
  }
}


void Light()
{


  if (mousePressed && mouseX > bex-bsize && mouseX < bex+bsize && mouseY > bey-bsize && mouseY < bey+bsize) 
  {
    lightCount = lightCount + 1;

    print(lightCount);

    if (lightCount == 1)
    {
      // fill(0, 255, 0);
      // ellipse(700, 100, bes, bes);
      light_green = 255;
      light_red = 0;
      port.write(1);
    } 
    if (lightCount == 2)
    {
      //   fill(255, 0, 0);
      //  ellipse(700, 100, bes, bes);
      light_red = 255;
      light_green = 0;
      lightCount = 0;
      port.write(2);
    }
  }
}


void M_setup()
{
  M = new Meter(this, 25, 10);
  M.setTitle("Humidity"); 
  String[] scale = {"0", "10", "20", "30", "40"};
  M.setScaleLabels(scale);
  M.setDisplayDigitalMeterValue(true);
}


void M1_setup()
{
  M1 = new Meter(this, 500, 10);
  M1.setTitle("Temp"); 
  String[] scale = {"0", "10", "20", "30", "40"};
  M1.setScaleLabels(scale);
  M1.setDisplayDigitalMeterValue(true);
}