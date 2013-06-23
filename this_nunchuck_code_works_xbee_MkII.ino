#include <Wire.h>

int nunchuckdirectionx;
int nunchuckdirectiony;

void setup()
{
  Serial.begin(57600);
  nunchuck_init();
}

void loop()
{
  nunchuck_get_data();
  nunchuckdirectionx = nunchuck_data_y();

  switch (nunchuckdirectiony)
  {
  case 9:
    Serial.println(9);
    break;
  case 3:
    Serial.println(3);
    break;
  case 0:
    Serial.println(0);
    break;
  }
  
  nunchuckdirectiony = nunchuck_data_x();
  
  switch (nunchuckdirectionx)
  {
  case 1:
    Serial.println(1);
    break;
  case 6:
    Serial.println(6);
    break;
  case 0:
    Serial.println(0);
    break;
  default:
    break;
  }

}



//
// Nunchuck functions
//

static uint8_t nunchuck_buf[6];   // array to store nunchuck data,

void nunchuck_init()
{ 
  Wire.begin();	                // join i2c bus as master
  Wire.beginTransmission(0x52);	// transmit to device 0x52
  Wire.write(0x40);		// sends memory address
  Wire.write(0x00);		// sends sent a zero.  
  Wire.endTransmission();	// stop transmitting
}

void nunchuck_send_request()
{
  Wire.beginTransmission(0x52);	// transmit to device 0x52
  Wire.write(0x00);		// sends one byte
  Wire.endTransmission();	// stop transmitting
}

int nunchuck_get_data()
{
  int cnt=0;
  Wire.requestFrom (0x52, 6);	// request data from nunchuck
  while (Wire.available ()) {
    nunchuck_buf[cnt] = nunchuk_decode_byte(Wire.read());
    cnt++;
  }
  nunchuck_send_request();  // send request for next data payload
  if (cnt >= 5) {
    return 1;   // success
  }
  return 0; //failure
}

int nunchuck_data_x()
{ 
  int joy_x_axis = nunchuck_buf[0];

  if (joy_x_axis <= 50)
  {
    return(9);
  }
  else if(joy_x_axis >=220)
  {
    return(3);
  }
}

int nunchuck_data_y()
{ 
  int joy_y_axis = nunchuck_buf[1];

  if (joy_y_axis <= 50)
  {
    return(6);
  }
  else if(joy_y_axis >=220)
  {
    return(1);
  }
  else
  {
    return(0);
  }     
}
// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char nunchuk_decode_byte (char x)
{
  x = (x ^ 0x17) + 0x17;
  return x;
}

