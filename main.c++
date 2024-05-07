// C++ code
//
int trigpin = 2;   // O sinal é enviado pelo pino 2
int echopin = 3;   // O sinal de retorno é recebido pelo pino 3
int pingtime;       // Tempo para o sinal viajar
float d;            // Variável para armazenar a distância

int greenLed = 13;   // Pino para o LED verde
int yellowLed = 12;  // Pino para o LED amarelo
int redLed = 11;     // Pino para o LED vermelho

void setup() {
  pinMode(trigpin, OUTPUT);  // Configura o pino trigpin como saída
  pinMode(echopin, INPUT);   // Configura o pino echopin como entrada
  pinMode(greenLed, OUTPUT); // Configura o pino do LED verde como saída
  pinMode(yellowLed, OUTPUT);// Configura o pino do LED amarelo como saída
  pinMode(redLed, OUTPUT);   // Configura o pino do LED vermelho como saída
  Serial.begin(9600);        // Inicializa a comunicação serial com taxa de 9600 bauds
}

void loop() {
  digitalWrite(trigpin, LOW);   // Define o pino trigpin como LOW
  delayMicroseconds(2);          // Aguarda 2 microssegundos
  digitalWrite(trigpin, HIGH);  // Define o pino trigpin como HIGH por 10 microssegundos
  delayMicroseconds(10);        // Aguarda 10 microssegundos
  digitalWrite(trigpin, LOW);   // Define o pino trigpin como LOW

  pingtime = pulseIn(echopin, HIGH); // Lê o pulso do pino echopin

  // Calcula a distância em 'cm' 
  d = pingtime * 0.0343 / 2;

  // Imprime as distâncias 
  Serial.print("Pingtime is: ");
  Serial.print(pingtime);
  Serial.print(" microseconds. Distance is: ");
  Serial.print(d);
  Serial.println(" cm");
  
  updateLeds(d); // Atualiza os LEDs com base na distância medida
  
  delay(400);  // Delay até a próxima medição
}

void updateLeds(float distance) {
  // Define os limiares de distância para as diferentes cores de LED
  float redThreshold = 80.0;  // Distância para o LED verde
  float yellowThreshold = 180.0; // Distância para o LED amarelo
  // Distância para o LED vermelho (não há um limite máximo específico)

  // Desliga todos os LEDs inicialmente
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, LOW);

  // Liga o LED verde se a distância for menor que o limite verde
  if (distance < redThreshold) {
    digitalWrite(redLed, HIGH);
  }
  // Liga o LED amarelo se a distância for menor que o limite amarelo, mas maior que o limite verde
  else if (distance < yellowThreshold) {
    digitalWrite(yellowLed, HIGH);
  }
  // Liga o LED vermelho se a distância for maior que o limite amarelo
  else {
    digitalWrite(greenLed, HIGH);
  }
}