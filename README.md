# Data from Home

This is the codebase for a mesh network of IoT devices used to sense and report environmental data, made with ESP8266 and ESP32 microcontrollers, the PainlessMesh library, and various sensors to measure temperature, humidity, ambient noise, vibration, and whatever other data you want.

The nodes in the network are made up of these devices:

* **Edge node** - ESP32/ESP8266 coupled with a Raspberry Pi
* **Other nodes** - ESP32/ESP8266 standalone.

## Authors

* Ivor Benderavage - [@ivorysoap](github.com/ivorysoap)
* Humam Shwaikh - [@HumamShwaikh](github.com/HumamShwaikh)

### How to use - Raspberry Pi logger

The Raspberry Pi logger, (`rpi_logger` directory) runs continuously and stores messages received by the Pi (through the master node via serial connection) in a SQLite3 DB.  To run it:

* Make sure the master node is connected to Pi via USB using port `/dev/ttyUSB0`
* Make sure `meshlog.db` is created, and initialize the schema with `schema.sql`
* Make sure you have all the dependencies:
    * sqlite3
    * libsqlite3-dev

Then build it using the following command:

`g++ -Wall main.cpp serialMonitor.cpp rs232.c -o a.out -std=c++11 -lsqlite3`

Finally, run:

`./a.out`

## How to flash code to one of the ESP nodes

All the nodes run one of the following .cpp files:

* `logServer.cpp` - run by the 
central server.
* `logClient.cpp` - run by the 
nodes in the mesh.

### How to upload ONE of the .cpp files to a board in PlatformIO?

In `platformio.ini`, you have to 
use the `src_filter` option to exclude and 
include the files to be built and 
uploaded.  For example, 
`src_filter = +<logClient.cpp> 
-<logServer.cpp>` will exclude 
logServer.cpp.



## Attribution

* [Painless Mesh](https://github.com/gmag11/painlessMesh)
* [Teuniz C RS-232 library](https://gitlab.com/Teuniz/RS-232)
* [nlohmann's C++ JSON library](https://github.com/nlohmann/json)
