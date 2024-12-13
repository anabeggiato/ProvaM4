#include <WiFi.h>
#include <HTTPClient.h>

#define led_azul 41 // Pino utilizado para controle do led azul
#define led_verde 2 // Pino utilizado para controle do led verda
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led azul

const int pinoBotao = 18;  // Pino utilizado para controle do botão
int estadoBotao = 0;  // variavel para controle do estado do botão

const int pinoLdr = 4;  // Pino utilizado para controle do ldr
int threshold=600;

// definindo variáveis a serem utilizadas para controle de intervalos sem usar o delay
unsigned long tempoAtual = millis();
unsigned long tempoAnterior = 0;

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_azul,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
  pinMode(led_amarelo, OUTPUT);

  // Inicialização das entradas
  pinMode(pinoBotao, INPUT_PULLUP); // Inicializa o pino do botão como INPUT

  digitalWrite(led_azul, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  // Verifica estado do botão
  estadoBotao = digitalRead(pinoBotao);
  if (estadoBotao == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

    if (httpResponseCode>0) {
      Serial.print("Código de resposta HTTP: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Código de erro: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi Desconectado");
  }
}

void semaforoVerde() { //definição de uma função para abrir o semaforo
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_verde, HIGH);
}

void semaforoAmarelo() { //definição de uma função para deixar o semaforo amarelo
    digitalWrite(led_vermelho, LOW);
    digitalWrite(led_amarelo, HIGH);
    digitalWrite(led_verde, LOW);
}

void semaforoVermelho() { //definição de uma função para fechar o semaforo
    digitalWrite(led_vermelho, HIGH);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_verde, LOW);
}

void loop() {

  int ldrstatus=analogRead(pinoLdr);

  if(ldrstatus<=threshold){ // modo escuro
    Serial.print("Está escuro, ligue o led");
    Serial.println(ldrstatus);
    if (tempoAtual - tempoAnterior >= 1000){
      if (led_amarelo == HIGH) {
        digitalWrite(led_amarelo, LOW);
      } else {
        digitalWrite(led_amarelo, HIGH);
      }
    tempoAnterior = tempoAtual;
    }

  }else{ // modo convencional
    Serial.print("Está claro, desligue a luz");
    Serial.println(ldrstatus);

    semaforoVerde();
    delay(3000);
    semaforoAmarelo();
    delay(2000);
    semaforoVermelho();
    delay(5000);

    if(led_vermelho == HIGH) {
      if(estadoBotao == HIGH) {
        delay(1000);
        semaforoVerde();
      }
    }
  }
}