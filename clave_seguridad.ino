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
char password[8] = {'1', '2', '3', '4'}; // contraseña: 1234
char inputPassword[8];
unsigned char idx = 0;
int attempts = 0;
boolean threeAttempts = false;

// Definiciones de caracteres personalizados

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

/*
 Se encarga de inicializar el LCD,
 crear caracteres personalizados,
 mostrar un mensaje de bienvenida con
 caracteres personalizados y establecer
 la posición inicial del cursor para
 ingresar la clave.
*/

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
    lcd.setCursor(0, 1);
}

/*
 Se encarga de leer las teclas presionadas en
 el teclado numérico, verificar si se ha
 ingresado una clave correcta, imprimir
 mensajes en el LCD y realizar acciones
 correspondientes en función de las teclas presionadas
 y bloquear el sistema si hay mas de 3 intentos fallidos.
*/

void loop()
{
    char key = keypad.getKey();

    if (attempts >= 3)
    {
        printWithLineBreak("Sistema", "Bloqueado");
        return;
    }

    if (key)
    {
        if (key == '=')
        {
            if (isPasswordCorrect())
            {
                print("Clave Correcta!");
                attempts = 0;
                return;
            }

            print("Clave Incorrecta!");
            attempts++;
            return;
        }

        if (idx >= 8)
        {
            print("Fuera de Rango!");
            attempts++;
            return;
        }

        inputPassword[idx] = key;
        lcd.print('*');
        idx++;
        (idx >= 8) ? idx : 0;
    }
}

// Imprimir mensaje en el LCD y restablecer

void print(String Message)
{
    lcd.clear();
    lcd.print(Message);
    delay(2000);
    lcd.clear();
    reset();
}

// Imprimir mensaje con salto de línea en el LCD

void printWithLineBreak(String Message1, String Message2)
{
    lcd.clear();
    lcd.print(Message1);
    lcd.setCursor(0, 1);
    lcd.print(Message2);
    delay(10000);
    lcd.clear();
}

// Verificar si la contraseña ingresada es correcta

bool isPasswordCorrect()
{
    return strcmp(inputPassword, password) == 0;
}

// Restablecer valores y mostrar mensaje en el LCD

void reset()
{
    memset(inputPassword, 0, sizeof(inputPassword));
    idx = 0;
    lcd.setCursor(0, 0);
    lcd.print("Ingrese clave:");
    lcd.setCursor(0, 1);
}