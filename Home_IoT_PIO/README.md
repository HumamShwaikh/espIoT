# Data from Home

Mesh network using ESP8266, ESP32, 
PainlessMesh, and some sensors to 
sense and log environmental data.

### How to use

* **logServer.cpp** - run by the 
central server.
* **logClient.cpp** - run by the 
nodes in the mesh.

**How to upload ONE of the .cpp 
files to a board in PlatformIO?**

In platformio.ini, you have to 
use `src_filter` to exclude and 
include the files to be built and 
uploaded.  For example, 
`src_filter = +<logClient.cpp> 
-<logServer.cpp>` will exclude 
logServer.cpp.
