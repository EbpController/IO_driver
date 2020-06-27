# IO_driver
'IO driver' is a driver for the 'EBP Controller' project

EbpSerial must be included (refer to https://github.com/EbpController/EbpSerial)

The 6 inputs are connected to port D bit 2 to bit 7 (input 0 to 5)
The 6 outputs are connected to port B bit 0 to bit 5 (output 0 to 5)

Protocol for transmitting/receiving data is as follow: In the 6 bit data word, bit 0 = pin status (LOW or HIGH), bit 1 to bit 3 = pin port (value = 0 to 5)

(also refer to EbpSerial_protocol_flowchart.pdf, https://github.com/EbpController/EbpSerial/blob/master/EbpSerial_protocol_flowchart.pdf)
