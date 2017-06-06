#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
//#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#define DHTTYPE   DHT11
#define DHTPIN    14

 
const char* ssid = "OnePlus3";
const char* password = "kulkarni";
 
int ledPin1 = 12;// GPIO13
int ledPin2 = 13;// GPIO13
int ledPin3 = 15;// GPIO13
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);

  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);

  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  int value = LOW;
 
  
  if (request.indexOf("/LED=ON1") != -1)  {
    digitalWrite(ledPin1, HIGH);
    value = HIGH;
    delay(4000);
    digitalWrite(ledPin1, LOW);
    value= LOW;
  }
  if (request.indexOf("/LED=ON2") != -1)  {
    digitalWrite(ledPin2, HIGH);
    value = HIGH;
    delay(4000);
    digitalWrite(ledPin2, LOW);
    value= LOW;
  }

  if (request.indexOf("/LED=ON3") != -1)  {
    digitalWrite(ledPin3, HIGH);
    value = HIGH;
    delay(4000);
    digitalWrite(ledPin3, LOW);
    value= LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
   if(value == LOW) {
    client.print("Off");
  } else {
    client.print("On");
  }
  
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON1\"\"><button>Medium </button></a>");
  client.println("<a href=\"/LED=ON2\"\"><button>Low</button></a><br />");  
  client.println("<a href=\"/LED=ON3\"\"><button>High</button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
