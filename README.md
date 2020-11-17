# CourierCXX
##### v0.9.0.1
C++ framework for standart operations simplification

### Requirements (Linux)
[1] Cmake

[2] libevent-dev

[3] libpq-dev

[4] libpqxx-dev

[5] libpcap-dev

[6] libbluetooth-dev

[7] libghc-iconv-dev

[8] libjpeg-dev

[9] doxygen

### Requirements (Windows)
[1] Cmake

[2] postgresql 10 ( https://www.postgresql.org/download/windows/ )

[3] libpqxx 6.4 ( https://github.com/jtv/libpqxx/tree/6.4 )

### Documentation
To generate documentation, execute command:

	$ doxygen config.doxygen

After generation it will be placed in /docs folder

### Build
1) Make build directory in project root folder and cd to it

	$ mkdir build
	$ cd build
	
2) Init CMake config
	
	$ cmake ..
	
3) Build targets with desired configuration (Debug/Release

	$ cmake --build . --config Debug 
 