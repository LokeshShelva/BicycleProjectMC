#include "WiFiEsp.h"

// ********************************************************* DEFINITIONS *********************************************************
char ssid[] = "********";             // your network SSID (name)
char pass[] = "********";             // your network password
int status = WL_IDLE_STATUS;          // the Wifi radio's status

// ********************************************************* INITIALIZE *********************************************************
void setup() {
  Serial.begin(115200);                                     // initialize serial 0 for debugging
  Serial1.begin(115200);                                    // initialize serial 1 for ESP module
  WiFi.init(&Serial1);                                      // initialize ESP module
  if (WiFi.status() == WL_NO_SHIELD) {                      // check for the presence of the shield
    Serial.println("WiFi shield not present");              // If shield not present, don't continue
    while (true);
  }
  while ( status != WL_CONNECTED) {                         // attempt to connect to WiFi network
    Serial.print("Attempting to connect to WPA SSID: ");    // Print message to serial monitor
    Serial.println(ssid);                                   // Print SSID to serial monitor
    status = WiFi.begin(ssid, pass);                        // Connect to WPA/WPA2 network
  }
  Serial.println("You're connected to the network");        // Print success message to serial monitor
}

// ********************************************************* MAIN LOOP *********************************************************
void loop()
{
  // check the network connection once every 10 seconds
  Serial.println();
  printCurrentNet();
  printWifiData();
  
  delay(10000);
}

// *********************************************************  FUNCTION DEFINITIONS *********************************************************
// Print WiFi data to serial Monitor  --------------------------------------------------------
void printWifiData()
{
  // *** print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // *** print your MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  char buf[20];
  sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  Serial.print("MAC address: ");
  Serial.println(buf);
}

// Print WiFi connection details to serial Monitor  --------------------------------------------------------
void printCurrentNet()
{
  // *** print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // *** print the MAC address of the router you're attached to
  byte bssid[6];
  WiFi.BSSID(bssid);
  char buf[20];
  sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X", bssid[5], bssid[4], bssid[3], bssid[2], bssid[1], bssid[0]);
  Serial.print("BSSID: ");
  Serial.println(buf);

  // *** print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.println(rssi);
}