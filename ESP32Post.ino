//Librerias de ESP32
#include "esp_camera.h"
#include <WiFi.h>

//Librerias JSON y Web
#include <HTTPClient.h>
#include <ArduinoJson.h>

//Librerias de Telegram
#include <dummy.h>
#include <CTBot.h>
#include <CTBotDataStructures.h>
#include <CTBotDefines.h>
#include <CTBotInlineKeyboard.h>
#include <CTBotReplyKeyboard.h>
#include <CTBotSecureConnection.h>
#include <CTBotStatusPin.h>
#include <CTBotWifiSetup.h>
#include <Utilities.h>
CTBot mibot; 

#define CAMERA_MODEL_AI_THINKER 
#include "camera_pins.h"

//Credenciales de WI-FI y Telegram 
const char* ssid = "Personal C";
const char* password = "llanos2017";
#define CHAT_ID 1761335767
#define TOKEN "6177107414:AAEoUKwI_eAud7FKiSHwDonSsulHYm29rD0"

//Configuracion del PIR
#define pirPin 2
int val = 0;
bool motionState = false ;

//const char* Ip = "192,168,10,9" 
 //IPAddress ip(192,168,10,9);     
 //IPAddress gateway(192,168,10,1);   
 //IPAddress subnet(255,255,255,0);   


void startCameraServer();

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  
  //Configuracion de la camara 
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // iniciacion de la camara 
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }
  // drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  //Inicio de la conexion a WIFI
  pinMode(pirPin, INPUT);
  
  WiFi.persistent(false); //Permite que la configuracion del Wifi no sea afectada.
  WiFi.mode(WIFI_STA);    //Configura el Wifi en modo estatico
  
  Serial.println("Conectando");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("Conectado Exitosamente...");
  
  //Inicio de la camara
  startCameraServer();
  Serial.print("Camara iniciada 'http://");
  Serial.print(WiFi.localIP());
    
  mibot.setTelegramToken(TOKEN); 

  
  if (mibot.testConnection()) {
    Serial.println("\n Conectado a telegram...");
    mibot.sendMessage(CHAT_ID, "Conectado al chat exitosamente...");

  }
  else {
    Serial.println("\n lo sentimos hemos detectado un problema :(");
  }

}

void loop() {
val = digitalRead(pirPin);

if (val == HIGH) {
  if (motionState == false) {
  
    if(WiFi.status() == WL_CONNECTED )
    {
      Serial.println("¡Movimiento detectado!");
      mibot.sendMessage(CHAT_ID, "Movimiento detectado");
      motionState = true;
        
      //Realiza las acciones en JSON
      DynamicJsonDocument doc(2048);
      doc["ID"] = analogRead(1)+1;
      doc["Sensor_PIR"] = motionState;
      
      // documento serializado
      String json;
      serializeJson(doc, json);
      WiFiClient client;  // or WiFiClientSecure for HTTPS
      HTTPClient http;
      
      // Send request
      http.begin("https://diabolos-system.onrender.com/insertar");
      
      //cabeceras JSON
      http.addHeader("Content-Type", "application/json");
      int res = http.POST(json);
      Serial.println(json);
      
      // respuesta 
      Serial.println(http.getString());
      Serial.println(res);
      
      // desconecta
      http.end();
      delay(60000);
      }    
    }
    
  }
}
