// WiFi Bee example server with Arduino
// This code requires the following hardware
//  * DFRduino
//  * DFRobot IO shield
//  * WiFi Bee

 
String ESSID = "THE_INTERNET";  //Change it to your home ESSID
String password = "Nutgrove37";  // Change it to your secret password
 
String inputString;  // string to store HTML stuff
String inputString2;  // string to store IP stuff
String ip;
 
void setup() {
  Serial.begin(9600);

  pinMode(13, HIGH);
  Serial.println("program start");

  // To set up the Wireless uncomment the next line
#define firsttime
  // This function should be run once whenever you change Wireless Network.
  // Should be disabled once the Wireless configuration is setup and working.
#ifdef firsttime
  delay(1000);
  digitalWrite(13, HIGH);  //Turn on LED to debug configuration mode
  Serial.print("$$$"); //enter command mode
  delay(300);
  Serial.println();
  Serial.print("set w s "); // set your wireless name
  Serial.println(ESSID);
  delay(300);
  Serial.print("set w p ");  // Set your wireless password
  Serial.println(password);
  delay(300);
  Serial.println("set ip localport 80"); // set default port to access your device. 80 for webservers
  delay(300);
  Serial.println("set c r 0"); // disable all default messages from the bee
  Serial.println("set c o 0"); // disable all default messages from the bee
  Serial.println("set c c 0"); // disable all default messages from the bee
  delay(300);
  Serial.println("save"); // save it forever and ever
  Serial.println("reboot"); // reboot to load configuration
  delay(2000);
  digitalWrite(13, LOW); 
#endif
  Serial.print("The IP is= ");
  printIP();
}

 
void loop() {
  //If we have a client Read all the browser data.
  while(Serial.available()>0){
    char inChar = (char)Serial.read(); 
    inputString += inChar;  
    if(inputString.length()>0 && inChar == '\n'){
      inputString.trim();  // trim it down to avoid using too much RAM
 
      if(inputString.indexOf("HTTP") >0)
      {
        putHTML("test");  // your custom HTML tag
      }
      inputString = "";
    }
  }
}
 
void putHTML(String iStr){
  Serial.println("HTTP/1.1 200 OKn");
  Serial.println("Content-Type: text/html");
  Serial.println("Connection: close");  // the connection will be closed after completion of the response
  Serial.print("\r");
  Serial.print("\n");
  Serial.println("<!DOCTYPE HTML>");
  Serial.println("<html>");
  Serial.println("<meta http-equiv=\"refresh\" content=\"5\">");  // refresh for sensor update
  Serial.println("<link rel=\"stylesheet\" type=\"text/css\" href=\"http://www.dfrobot.com/ihome/stylesheet/stylesheet.css\" />");
  Serial.println("<center> <a href=\"http://www.dfrobot.com\"><img src=\"http://alturl.com/qf6vz\"></a> </center> ");
  Serial.println("<head><title> DFRobot </title></head>");
  Serial.println("<body>");
  Serial.println("<h1>DFRobot WiFi Bee</h1>");
  Serial.println("<p>My Robot data.</p>");
  Serial.println(iStr);
  Serial.println("<p>My crazy temperature sensor");
  Serial.println(analogRead(2));
  Serial.println("</p>");
  Serial.println("</body></HTML>");  
  // Close the connection from the Bee manually
  Serial.println();  
  delay(300);
  Serial.print("$$$"); //enter command mode
  delay(300);
  Serial.println();
  Serial.println("close"); // Close the connection so the port is open for others
  Serial.println("exit"); // Exit command mode
}
 
void printIP(){
  delay(300);
  Serial.print("$$$"); //enter command mode
  delay(300);
  Serial.println();
  Serial.println("get i");  // enter get ip command
  delay(600);
  while(Serial.available()>0){ // read output from command
    char inChar;
    if((char)Serial.read() == 'I' && (char)Serial.read() == 'P') { // parse it to get rid of non required stuff
    Serial.print(Serial.read());
      Serial.read();
      inputString2 += inChar; 
      while(Serial.available()>0){
        char inChar = (char)Serial.read();
        inputString2 += inChar; 
      }
    }
  }
  Serial.println(inputString2);
  inputString2="";
  delay(300);
  Serial.println("exit");
}
