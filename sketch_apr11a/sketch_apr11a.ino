

void setup() {
  // put your setup code here, to run once:
File dataFile = FileSystem.open("/mnt/sd/datalog.txt", FILE_READ); // open the file as read (must be present)
 if(dataFile) // if file is present
 {
   Serial.println("  Success - File Open");
   Serial.println("Reading File Content");
   while(dataFile.available())
   {
     data = dataFile.read(); // read incomming bytes
     dataString = dataString + data; // store them to string
   }
 }
}

void loop() {
  // put your main code here, to run repeatedly:

}
