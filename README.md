# CourierCXX
##### v0.7.0.1
C++ framework for standart operations simplification

### Requirements (Linux)
[1] libevent-dev

[2] libpq-dev

[3] libpqxx-dev

[4] libpcap-dev

[5] libbluetooth-dev

[6] libghc-iconv-dev

[7] libjpeg-dev

[8] doxygen

### Requirements (Windows)
[1] postgresql 10 ( https://www.postgresql.org/download/windows/ )

[2] libpqxx 6.4 ( https://github.com/jtv/libpqxx/tree/6.4 )

### Documentation
To generate documentation, execute command:

	$ doxygen config.doxygen

After generation it will be placed in /docs folder

### Makefile commands
- clean - clean files
- all - make all files
- install - install library
- uninstall - uninstall library
- examples - make examples
- utils - make utils
- docs - generate docs
 