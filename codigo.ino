#include <DHT.h>

#define DHTPIN A1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
const int digito1 = 13, digito2 = 10, digito3 = 9, digito4 = 2;
const int a = 12, f = 11, b = 8, e = 7, d = 6, p = 5, c = 4, g = 3;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(digito1, OUTPUT); pinMode(digito2, OUTPUT);
  pinMode(digito3, OUTPUT); pinMode(digito4, OUTPUT);
  pinMode(a, OUTPUT); pinMode(f, OUTPUT); pinMode(b, OUTPUT);
  pinMode(e, OUTPUT); pinMode(d, OUTPUT); pinMode(p, OUTPUT);
  pinMode(c, OUTPUT); pinMode(g, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Error al leer el sensor DHT11!");
    return;
  }
  mostrarTemperatura(temp);
  Serial.print("Temperatura: "); Serial.print(temp); Serial.println(" °C");
  delay(1000);
}

void mostrarTemperatura(float temp) {
  int parteEntera = int(temp);
  int parteDecimal = round((temp - parteEntera) * 100); 
  
  mostrarDigito(digito1, parteEntera / 10, false); delay(5); apagarDigito(digito1);
  mostrarDigito(digito2, parteEntera % 10, true); delay(5); apagarDigito(digito2);
  mostrarDigito(digito3, parteDecimal / 10, false); delay(5); apagarDigito(digito3);
  mostrarDigito(digito4, parteDecimal % 10, false); delay(5); apagarDigito(digito4);
}

void mostrarDigito(int dig, int num, bool punto) {
  apagarSegmentos();
  switch (num) {
    case 0: encenderSegmentos(a, b, c, d, e, f); break;
    case 1: encenderSegmentos(b, c); break;
    case 2: encenderSegmentos(a, b, g, e, d); break;
    case 3: encenderSegmentos(a, b, g, c, d); break;
    case 4: encenderSegmentos(f, g, b, c); break;
    case 5: encenderSegmentos(a, f, g, c, d); break;
    case 6: encenderSegmentos(a, f, g, c, d, e); break;
    case 7: encenderSegmentos(a, b, c); break;
    case 8: encenderSegmentos(a, b, c, d, e, f, g); break;
    case 9: encenderSegmentos(a, b, c, f, g); break;
  }
  if (punto) digitalWrite(p, HIGH);
  digitalWrite(dig, HIGH);
}

void encenderSegmentos(int segs...) {
  va_list args;
  va_start(args, segs);
  for (int seg; (seg = va_arg(args, int)) != 0;) digitalWrite(seg, HIGH);
  va_end(args);
}

void apagarSegmentos() {
  int segmentos[] = {a, f, b, e, d, c, g}; 
  for (int i = 0; i < sizeof(segmentos) / sizeof(segmentos[0]); i++) {
    digitalWrite(segmentos[i], LOW);
  }
}

void apagarDigito(int dig) {
  digitalWrite(dig, LOW);
}
