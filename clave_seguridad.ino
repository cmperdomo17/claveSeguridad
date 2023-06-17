// Incluir las bibliotecas necesarias:
#include <LiquidCrystal.h>
#include <Keypad.h>

// Definir el tamaño del teclado
const byte ROWS = 4;
const byte COLS = 4;

// Definir la disposición de las teclas en el teclado
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Definir los pines del Arduino conectados a las filas y columnas del teclado
byte rowPins[ROWS] = {39, 41, 43, 45};
byte colPins[COLS] = {47, 49, 51, 53};

// Crear una instancia de Keypad con los parámetros anteriores
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Definir los pines del Arduino conectados a la pantalla LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Crear una instancia de LiquidCrystal para la pantalla LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Contraseña esperada: 1234
char password[8] = {'1', '2', '3', '4'};

// Contraseña ingresada por el usuario
char inputPassword[8];

// Índice actual para ingresar la contraseña
unsigned char idx = 0;

// Número de intentos de contraseña fallidos
int attempts = 0;

// Bandera para indicar si se han realizado tres intentos fallidos consecutivos
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

/**
 * Inicializa el LCD, crea caracteres personalizados, muestra un mensaje de bienvenida y establece la posición inicial del cursor para ingresar la clave.
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

/**
 * Lee las teclas presionadas en el teclado numérico, verifica si se ha ingresado una clave correcta, imprime mensajes en el LCD y realiza acciones correspondientes en función de las teclas presionadas. Bloquea el sistema si hay más de 3 intentos fallidos.
 */
void loop()
{
    char key = keypad.getKey();
    if (attempts >= 3)
    {
        lcd.clear();
        lcd.print("Siste. Bloqueado");
        exit(0);
    }
    if (key)
    {
        if (key == '#')
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
            return;
        }
        inputPassword[idx] = key;
        lcd.print('*');
        idx++;
        (idx >= 8) ? idx : 0;
    }
}

/**
 * Imprime un mensaje en el LCD y restablece los valores.
 *
 * @param Message El mensaje a imprimir en el LCD.
 */
void print(String Message)
{
    lcd.clear();
    lcd.print(Message);
    delay(2000);
    lcd.clear();
    reset();
}

/**
 * Verifica si la contraseña ingresada es correcta.
 *
 * @return true si la contraseña es correcta, false de lo contrario.
 */
bool isPasswordCorrect()
{
    return strcmp(inputPassword, password) == 0;
}

/**
 * Restablece los valores y muestra un mensaje en el LCD.
 */
void reset()
{
    memset(inputPassword, 0, sizeof(inputPassword));
    idx = 0;
    lcd.setCursor(0, 0);
    lcd.print("Ingrese clave:");
    lcd.setCursor(0, 1);
}
