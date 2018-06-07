#include "com.h"
#include "stdlib.h"

DHT11_Data_TypeDef DHT11_Data;
uint8_t command_index = 0;

extern int SMG_Num;

uint8_t color[ 1 ][ 3 ] =
{
{0, 26, 229 },
};

char IRF_ok;
extern unsigned char decode[4];

union
{
    char byteVal[4];
    float floatVal;
    long longVal;
}val;

void writeHead()
{
  printf("%c",0xff);
  printf("%c",0x55);
}
void writeEnd()
{
  printf("%c",0x0d);
  printf("%c",0x0a);
}
void writeSerial(unsigned char c)
{
	printf("%c",c);
}
/*
ff 55 len idx action device port  slot  data a
0  1  2   3   4      5      6     7     8
*/
void parseData()
{
  int idx = Readbuffer[3];
  int action = Readbuffer[4];
  int device = Readbuffer[5];
	
	command_index = (uint8_t)idx;

  switch(action){
    case GET:
			if(device != ULTRASONIC_SENSOR)
			{
				writeHead();
				writeSerial(idx);
			}
			readSensor(device);
      writeEnd();
     break;
					
     case RUN:
       runModule(device);
       callOK();
      break;
		 
     case RESET:{
        //reset
        
        callOK();
      }
     break;
     case START:{
        //start
        callOK();
      }
     break;
  }
}

void callOK()
{
   writeHead();
   writeEnd();
}
void sendByte(char c)
{
  printf("%c",1);
  printf("%c",c);
}
void sendFloat(float value)
{
  writeSerial(0x2);
  val.floatVal = value;
  writeSerial(val.byteVal[0]);
  writeSerial(val.byteVal[1]);
  writeSerial(val.byteVal[2]);
  writeSerial(val.byteVal[3]);
}
int readmotor(int idx)
{
	char buffervalue,value;
	if(Readbuffer[idx+1]==0x00)
	{
		value=Readbuffer[idx];
	}
	else
	{
		buffervalue=Readbuffer[idx+1];
		value=65535-(buffervalue*255)-Readbuffer[idx]+1;
	}
	return value;
}

void runModule(int device)
{
  //0xff 0x55 0x6 0x0 0x1 0xa 0x9 0x0 0x0 0xa
  int port = 0;
	
	int speed=0;
	char slot=0;
	char num=0;
		
	char idx = 0;
	char r =0,g=0,b=0;
	
	port = Readbuffer[6];
	
  switch(device)
	{
   case MOTOR:
     speed = readmotor(7);     
		 Runmotor(port,speed);
   break;
	 
	 case SERVO:
     slot = Readbuffer[7];
     Runservo(port,slot);
   break;
	 
	 case SEVSEG:
		 num = Readbuffer[7];
		 SMG_Num=num;
	 break;
	 
	 case RGBLED:
     //slot = Readbuffer[7];
     idx = Readbuffer[8];
     r = Readbuffer[9];
     g = Readbuffer[10];
     b = Readbuffer[11];
		 
		 color[0][0]=r;
		 color[0][1]=g;
		 color[0][2]=b;
     
     WS2812_send(&color[0],1);

   break;
	 
	 case DIGITAL:
		 slot = Readbuffer[7];
		 Rundigitalout(port,slot);
	 break;
	 
	 case PWM:
		 speed = readmotor(7);     
		 Runmotor(port,speed);
	 break;
	 
	 case BUZZER:
		 slot = Readbuffer[7];
		 Runbuzzer(port,slot);
	 break;
  }
}

void readSensor(int device)
{
  /**************************************************
      ff 55 len idx action device port slot data a
      0  1  2   3   4      5      6    7    8
  ***************************************************/
//  float value=0.0;
  char port,pin;//,slot;
	char IR_status;
	uint8_t index =0;
	int value=0;
	char code =0;
	char button_status;
	char digial_status;
	
  port = Readbuffer[6];
  pin = port;
	
  switch(device)
	{
   case  ULTRASONIC_SENSOR:
		 value=UltrasonicWave_StartMeasure();
		 writeHead();
     writeSerial(command_index);
     sendFloat(value);
   break;
	 
   case  BUTTON_INNER:
		 button_status=read_botton_status(port);
     sendByte(button_status == Readbuffer[7]);	 		 
   break;
		 
	 case HUMITURE:
	   index = Readbuffer[7];
		 DHT11_update();//DHT11_Data.humi_deci,,DHT11_Data.temp_deci;
		 switch(index)
		 {
				case 0:
					sendByte(DHT11_Data.humi_int);
				break;
				case 1:
					sendByte(DHT11_Data.temp_int);
				break;
		 }			   
   break;
		 
	 case  LIGHT_SENSOR:
		 value = ReadLightsevro(Readbuffer[6]);
     sendFloat(value);
   break;
	 
   case  SOUND_SENSOR:
		 value = ReadSoundsevro(Readbuffer[6]);
     sendFloat(value);
   break;
	 
   case  POTENTIONMETER:
     value = ReadPotentionmeterRsevro(Readbuffer[6]);
     sendFloat(value);
   break;
	 
	 case PIRMOTION:
     IR_status=read_PIRmotion_status(port);
     sendByte(IR_status == Readbuffer[7]);
   break;
		 
	 case IRREMOTE:
     code = Readbuffer[7];
     while(!IRF_ok);         //接收完1次后处理   
		 bit_byte();     //提取到32位数据
		 IRF_ok=0;       //清标志位
		 //printf("%d",decode[2]);
     sendByte(decode[2]==code);
   break;
	 
	 case DIGITAL:
		 digial_status=read_digial_status(port);
     sendByte(digial_status);
	 break;
	 
	 case ANALOG:
		 value = Readanalogvalue(Readbuffer[6]);
     sendFloat(value);
	 break;
	 	 
  }
}

