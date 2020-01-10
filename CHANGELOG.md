### Version 0.4.0.0
[*] dataLen -> dataSize

[*] improved Windows support

### Version 0.3.0.0
[+] added initial Windows support

[+] added system signal watcher

### Version 0.2.2.1
[*] updated server event loop

### Version 0.2.2.0
[+] added datasources support

[+] added SerialPortBaseDatasource, SerialPortBusDatasource and SerialPortBusEventDrivenDatasource

[\*] fixed errors with **String.read*** functions

[*] fixed bug with resource cleaning

[\*] fixed bug for postgres **uint8_t** and **int8_t** values

### Version 0.2.1.0
[+] added serial port bus support

[*] refactoring

### Version 0.2.0.0
[+] added buffer read/write functions

[*] connectors and protocols refactoring

[\*] renamed hex2ascii -> **writeBufferASCII**, ascii2hex - **readBufferASCII**

### Version 0.1.1.0
[+] added write list for **TCPPortBase**

[*] small fixes

### Version 0.1.0.0 (Released 15.10.2019)
[+] added db properties support

[*] configuration/properties work full refactoring

### Version 0.0.6.0 (Released 27.08.2019)
[+] add binary data convertion to JPG

[*] fixed debug info for serial port

[*] minor refactoring

### Version 0.0.5.0 (Released 22.08.2019)
[+] add binary data convertion to BMP

### Version 0.0.4.0 (Released 07.08.2019)
[+] added stop mutex for **Sniffer**, **DispatcherBase**, **WrappedListener**, **GPIOSPIPortBase** and **Connection**

[+] added fileSize func for **IO**

[\*] fixed bug with **pcap_next** for **Sniffer**

[*] fixed bug in **DispatcherBase** for unhandled events

### Version 0.0.3.1
[*] bugfixes

[*] optimization

### Version 0.0.3.0
[+] added bluetooth support

[+] added mutex for **PostgresConnector**

[*] bugfixes

### Version 0.0.2.1
[*] refactoring

### Version 0.0.2.0
[*] initial version
