#define westButton 7
#define eastButton 13
#define westRed 2
#define westYellow 1
#define westGreen 0
#define eastRed 12
#define eastYellow 11
#define eastGreen 10
#define yellowBlinkTime 500 // 0.5 seconds for yellow light blink

void setELights(int red, int yellow, int green);
void setWLights(int red, int yellow, int green);

boolean trafficWest = true; // west = true, east = false
int flowTime = 10000; // amount of time to let traffic flow
int changeDelay = 2000; // amount of time between color changes
void setup()
{
	// setup digital I/O pins
	pinMode(westButton, INPUT);
	pinMode(eastButton, INPUT);
	pinMode(westRed, OUTPUT);
	pinMode(westYellow, OUTPUT);
	pinMode(westGreen, OUTPUT);
	pinMode(eastRed, OUTPUT);
	pinMode(eastYellow, OUTPUT);
	pinMode(eastGreen, OUTPUT);
	// set initial state for lights - west side is green first
	digitalWrite(westRed, LOW);
	digitalWrite(westYellow, LOW);
	digitalWrite(westGreen, HIGH);
	digitalWrite(eastRed, HIGH);
	digitalWrite(eastYellow, LOW);
	digitalWrite(eastGreen, LOW);
}
void loop()
{
	if (digitalRead(westButton) == HIGH) // request west>east traffic flow
	{
		if (trafficWest != true)
			// only continue if traffic flowing in the opposite (east) direction
		{
			trafficWest = true; // change traffic flow flag to west>east
			delay(flowTime); // give time for traffic to flow
			//digitalWrite(eastGreen, LOW); // change east-facing lights from green
			//							  // to yellow to red
			//digitalWrite(eastYellow, HIGH);
			//delay(changeDelay);
			//digitalWrite(eastYellow, LOW);
			//digitalWrite(eastRed, HIGH);
			setELights(LOW, HIGH, LOW);
			delay(changeDelay);
			setELights(HIGH, LOW, LOW);
			delay(changeDelay);
			for (int a = 0; a < 5; a++) // blink yellow light
			{
				/*digitalWrite(westYellow, LOW);*/
				setWLights(LOW, LOW, LOW);
				delay(yellowBlinkTime);
				/*digitalWrite(westYellow, HIGH);*/
				setWLights(LOW, HIGH, LOW);
				delay(yellowBlinkTime);
			}
			//digitalWrite(westYellow, LOW);
			//digitalWrite(westRed, LOW); // change west-facing lights from red to green
			//digitalWrite(westGreen, HIGH);
			setWLights(LOW, LOW, HIGH);
		}
	}
	if (digitalRead(eastButton) == HIGH) // request east>west traffic flow
	{
		if (trafficWest == true)
			// only continue if traffic flow is in the opposite (west) direction
		{
			trafficWest = false; // change traffic flow flag to east>west
			delay(flowTime); // give time for traffic to flow
			//digitalWrite(westGreen, LOW);
			//// change west lights from green to yellow to red
			//digitalWrite(westYellow, HIGH);
			setWLights(LOW, HIGH, LOW);
			delay(changeDelay);
			/*digitalWrite(westYellow, LOW);
			digitalWrite(westRed, HIGH);*/
			setWLights(HIGH, LOW, LOW);
			delay(changeDelay);
			for (int a = 0; a < 5; a++) // blink yellow light
			{
				/*digitalWrite(eastYellow, LOW);*/
				setELights(LOW, LOW, LOW);
				delay(yellowBlinkTime);
				/*digitalWrite(eastYellow, HIGH);*/
				setELights(LOW, HIGH, LOW);
				delay(yellowBlinkTime);
			}
			//digitalWrite(eastYellow, LOW);
			//digitalWrite(eastRed, LOW); // change east-facing lights from red to green
			//digitalWrite(eastGreen, HIGH);
			setELights(LOW, LOW, HIGH);
		}
	}
}

void setELights(int red, int yellow, int green)
{
	digitalWrite(eastRed, red);
	digitalWrite(eastYellow, yellow);
	digitalWrite(eastGreen, green);
}

void setWLights(int red, int yellow, int green)
{
	digitalWrite(westRed, red);
	digitalWrite(westYellow, yellow);
	digitalWrite(westGreen, green);
}
