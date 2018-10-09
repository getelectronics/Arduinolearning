int delayValue = 100;


void setup()
{
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
}


void loop()
{
    for (int pin = 2; pin < 7; pin++) 
    {
        digitalWrite(pin, HIGH);
        delay(delayValue);
        digitalWrite(pin, LOW);
        delay(delayValue);
    }

    for (int pin = 5; pin > 1; pin--)
    {
        digitalWrite(pin, HIGH);
        delay(delayValue);
        digitalWrite(pin, LOW);
        delay(delayValue);        
    }
}
