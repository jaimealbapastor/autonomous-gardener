const int Pas = 3;
const int Dir = 2;

void setup()
{
	Serial.begin(115200);
	pinMode(Pas, OUTPUT);
	pinMode(Dir, OUTPUT);
	digitalWrite(Dir, HIGH);
}

void loop()
{
	for (int x = 0; x < 600; x++)
	{ /// x = nombre de tours
		digitalWrite(Pas, HIGH);
		delayMicroseconds(500);
		digitalWrite(Pas, LOW);
		delay(4);
	}
	delay(1000);
}