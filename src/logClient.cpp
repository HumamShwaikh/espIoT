//************************************************************
// this is a simple example that uses the painlessMesh library to 
// setup a node that logs to a central logging node
// The logServer example shows how to configure the central logging nodes
//************************************************************
#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

// Sensor defines
#define LIS3DH_CS SS
#define ADC_INPUT_VOLTAGE_MAX 3.03  // Shouldn't this be 3.3?  Whatever..
#define ADC_RESOLUTION 1024
#define MCP9700_TEMP_OFFSET_VOLTS 0.5
#define MCP9700_TEMP_INCREMENT_VOLTS 0.01

Scheduler     userScheduler; // to control your personal task
painlessMesh  mesh;

// Prototypes
void receivedCallback( uint32_t from, String &msg );
double convertToTemperature(double voltage);

size_t logServerId = 0;

// Send message to the logServer every 10 seconds 
Task myLoggingTask(10000, TASK_FOREVER, []() {
#if ARDUINOJSON_VERSION_MAJOR==6
        DynamicJsonDocument jsonBuffer(1024);
        JsonObject msg = jsonBuffer.to<JsonObject>();
#else
        DynamicJsonBuffer jsonBuffer;
        JsonObject& msg = jsonBuffer.createObject();
#endif

    double adcInput = analogRead(A0) * ADC_INPUT_VOLTAGE_MAX / ADC_RESOLUTION;
    double tempValueC = convertToTemperature(adcInput);

    msg["nodeId"] = mesh.getNodeId();
    msg["topic"] = "tempSensor";
    msg["value"] = tempValueC;
    msg["unit"] = "\u00b0C";

    String str;
#if ARDUINOJSON_VERSION_MAJOR==6
    serializeJson(msg, str);
#else
    msg.printTo(str);
#endif
    if (logServerId == 0) // If we don't know the logServer yet
        mesh.sendBroadcast(str);
    else
        mesh.sendSingle(logServerId, str);

    // log to serial
#if ARDUINOJSON_VERSION_MAJOR==6
    serializeJson(msg, Serial);
#else
    msg.printTo(Serial);
#endif
    Serial.printf("\n");
});

// Setup
void setup() {
  Serial.begin(115200);
    
  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 6 );
  mesh.onReceive(&receivedCallback);

  // Add the task to the your scheduler
  userScheduler.addTask(myLoggingTask);
  myLoggingTask.enable();
}

// Loop
void loop() {
  // it will run the user scheduler as well
  mesh.update();
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("logClient: Received from %u msg=%s\n", from, msg.c_str());

  // Saving logServer
#if ARDUINOJSON_VERSION_MAJOR==6
  DynamicJsonDocument jsonBuffer(1024 + msg.length());
  DeserializationError error = deserializeJson(jsonBuffer, msg);
  if (error) {
    Serial.printf("DeserializationError\n");
    return;
  }
  JsonObject root = jsonBuffer.as<JsonObject>();
#else
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(msg);
#endif
  if (root.containsKey("topic")) {
      if (String("logServer").equals(root["topic"].as<String>())) {
          // check for on: true or false
          logServerId = root["nodeId"];
          Serial.printf("logServer detected!!!\n");
      }
      Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
  }
}

/**
 * Converts a voltage value from the ADC into a celsius temperature
 * @param voltage the A0 pin voltage
 * @return the temperature in degrees celsius
 */
double convertToTemperature(double voltage){
  return (voltage - MCP9700_TEMP_OFFSET_VOLTS) / MCP9700_TEMP_INCREMENT_VOLTS;
}