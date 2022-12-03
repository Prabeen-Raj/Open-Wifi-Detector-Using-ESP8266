#include <ESP8266WiFi.h>

//Assigning Port Number to our WebServer
WiFiServer espServer(80);

//Add your Wi-fi network SSID and Password 
const char* ssid = "realme 9i";
const char* password = "12345678"; 


void setup() {
  //Begin Serial Communication At Baud Rate 115200
  Serial.begin(115200);
  Serial.println("");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); 
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("*");
    delay(500);
  }

  //Below snippet used to add static IP address to the ESP8266
  Serial.print("Connected to Wi-Fi: ");
  Serial.println(WiFi.SSID());
  delay(100);
  Serial.print("\n");
  Serial.println("Starting ESP8266 Web Server...");
  espServer.begin(); 
  Serial.println("ESP8266 Web Server Started");
  Serial.print("\n");
  Serial.print("The URL of ESP8266 Web Server is: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.print("\n");
  Serial.println("Use the above URL in your Browser to access ESP8266 Web Server\n");
}

void loop() {
  WiFiClient client = espServer.available(); /* Check if a client is available */
  if(!client)
  {
    return;
  }

  Serial.println("New Client!!!");

  String request = client.readStringUntil('\r'); 
  Serial.println(request); 
  client.flush();


  
  /* HTTP Response in the form of HTML Web Page */
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(); //  IMPORTANT
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  /* CSS Styling for Buttons and Web Page */
  client.println("<style>");
  client.println("html { font-family: Courier New; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button {border: none; color: white; padding: 10px 20px; text-align: center;");
  client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
  client.println(".button1 {background-color: #13B3F0;}");
  client.println(".button2 {background-color: #3342FF;}");
  client.println("</style>");
  client.println("</head>");
  
  /* The main body of the Web Page */
  client.println("<body>");
  client.println("<h2>OPEN Wi-Fi Network <span>&#128513;</span></h2>");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
   
  Serial.println("Scan done");
  
  if (n == 0)
    Serial.println("No Networks Found");
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found

    client.println("<p></p>"); 
    client.print("<span>");
    client.print(WiFi.SSID(i));
    client.println("</span>");
     client.println("<span> : </span >"); 
    

     boolean HighLowToggle = (WiFi.encryptionType(i) == ENC_TYPE_NONE);
      if(HighLowToggle == true){
         client.print("<span> Unsecured</span>");  
      }
      else{
         client.print("<span> secured</span>"); 
      }
   
      delay(10);
    }
  }
  Serial.println("");
  client.println("</body>");
  client.println("</html>");
  client.print("\n");
  
  delay(1);
  client.stop();
  Serial.println("Client disconnected");
  Serial.print("\n");

  // Wait a bit before starting New scanning again
  delay(5000);
}
