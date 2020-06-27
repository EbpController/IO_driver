# IO_driver
'IO driver' is a driver for the 'EBP Controller' project

EbpSerial must be included (refer to https://github.com/EbpController/EbpSerial)

Protocol for sending/receiving data is as follow:
In the 6 bit data word, bit 0 = pin status (LOW or HIGH), bit 1 to bit 3 = pin port (value = 0 to 5)
(also refer to EbpSerial_protocol_flowchart.pdf, https://github.com/EbpController/EbpSerial/blob/master/EbpSerial_protocol_flowchart.pdf)
