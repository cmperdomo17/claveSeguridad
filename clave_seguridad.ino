#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;
byte rowPins[KEYPAD_ROWS] = {5, 4, 3, 2};
byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'.', '0', '=', '/'}};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

uint64_t value = 0;
char password[5] = {'1', '2', '3', '4'}; // modificar la contraseña
char inputPassword[5];
unsigned char idx = 0;
int aux = 0;

byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000};

byte smiley[8] = {
    0b00100,
    0b01110,
    0b01110,
    0b01110,
    0b11111,
    0b00000,
    0b00100,
    0b00000};

byte frownie[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b10001};

byte armsDown[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b01010};

byte armsUp[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00100,
    0b01010};

void setup()
{
    lcd.begin(16, 2);
    lcd.createChar(0, heart);
    lcd.createChar(1, smiley);
    lcd.createChar(2, frownie);
    lcd.createChar(3, armsDown);
    lcd.createChar(4, armsUp);

    lcd.setCursor(0, 0);

    lcd.print("I ");
    lcd.write(byte(0));
    lcd.print(" Arduino! ");
    lcd.write((byte)1);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ingrese Clave");
    lcd.setCursor(5, 1);
}

void loop()
{
    char key = keypad.getKey();

    if (key)
    {
        if (key == '=')
        {
            if (isPasswordCorrect())
            {
                lcd.clear();
                lcd.print("Clave Correcta!");
                delay(2000);
                lcd.clear();
                reset();
            }
            else
            {
                lcd.clear();
                lcd.print("Clave Incorrecta!");
                aux++;
                delay(2000);
                lcd.clear();
                reset();

                if (aux > 3)
                {
                    lcd.clear();
                    lcd.print("Sistema ");
                    lcd.setCursor(0, 1);
                    lcd.print("Bloqueado");
                    return;
                }
                aux++;
            }
        }
        else
        {
            inputPassword[idx] = key;
            lcd.print('*');
            idx++;
            if (idx >= 5)
            {
                idx = 0;
            }
        }
    }
}

bool isPasswordCorrect()
{
    return strcmp(inputPassword, password) == 0;
}

void reset()
{
    memset(inputPassword, 0, sizeof(inputPassword));
    idx = 0;
    lcd.setCursor(0, 0);
    lcd.print("Ingrese clave:");
    lcd.setCursor(0, 1);
}