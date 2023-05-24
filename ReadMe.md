# About

You have built your own battery pack with the awesome [123 Smart BMS]?
You want to control something based on the BMS data?
Or maybe you want to share this data via WiFi and an ESP32?
Maybe upload it somewhere for monitoring?
Then this code may help you to do just that.

## How it Works

On each battery pack you will have at least one `begin` and one `end` module of the [123 Smart BMS].
Also, there can be many so called `between` modules.
These modules are connected in series via two wires which are used as a communication channel between the modules.
See [manual] for details.

In fact these modules use a (one way) serial/UART connection to send data from the `begin` to the `end` module.
Each `between` modules can then add/modify data and send the data packet to the next module until the `end` module is reached.
The packet size is fixed to 58 bytes and only one of the between modules will add cell specific data per cycle.
Data related to the pack in general is sent each cycle.
The `end` module has a free connector which can be used to grab these packets.
Here is what I found by reverse engineering a bit.
But no guarantee😋.

-  Pin 1: (inverted) data
-  Pin 2: ground/negative of the cell the module is mounted on
-  Interface: UART
-  Baud rate: 9600
-  Voltage: depends on cell voltage, usually 2.5V to 3.65V for LiFePo4
-  58 bytes of data per packet

## Connect it to Arduino

### Wait a Second

Before burning your house down by messing around with the great [123 Smart BMS], please check out their official [123 Smart BMS USB Cable].
It allows you to safely connect the BMS to basically any computer.
It provides important safety features like galvanic isolation and they even created a [Venus OS Integration].
Awesome!
If you still want to DIY it, then feel free to proceed.

### Inverted and Isolated by Hardware (Recommended)

> :information_source: This setup is the safest way of connecting your microcontroller to the BMS.
> It provides galvanic isolation and reduces the risk of shorts circuits drastically.

![Schema](schema.jpg)

-  Connect `BMS_DATA` to pin 1 of the BMS data port
-  Connect `BMS_GROUND` to pin 2 of the BMS
-  Connect `ARDUINO_VCC` to the supply voltage of your Arduino (3.3V or 5V)
-  Connect `ARDUINO_DATA` to any unused pin
-  Connect `ARDUINO_GND` to ground of the Arduino
-  Open [main.cpp](./src/main.cpp)
   -  Set `BMS_SERIAL_RX_PIN` to the used pin
   -  Set `BMS_SERIAL_INVERT` to `false`

### Invert by Software and Connect Directly 🔥

> :warning: When using a direct connection, keep in mind that your microcontroller and/or PC is directly connected to a huge battery.
> It is very easy to create a short circuit that kills your microcontroller, PC, the BMS and/or even you.
> You have been warned!

-  Make sure the voltage does not exceed the allowed voltage of your microcontroller
-  Connect ground of your microcontroller to the negative of the battery cell with the `end` module
-  Connect pin 1 of the BMS data port to any unused Arduio pin
-  Open [main.cpp](./src/main.cpp)
   -  Set `BMS_SERIAL_RX_PIN` to the used pin
   -  Set `BMS_SERIAL_INVERT` to `true`

## So whats next?

Well, upload the code and open your serial monitor.
Your Arduino should print out the battery data received from the [123 Smart BMS].
You can do with this data what every you want.
For example, turn on/off an inverter depending on the SOC.
Or upload the data to the internet with an ESP32 for monitoring.<br>
Or...<br>
Or...<br>
You get it!<br>

<!-- References -->

[123 Smart BMS]: https://123electric.eu/products/123smartbms-gen3/
[123 Smart BMS USB Cable]: https://123electric.eu/products/123smartbms-to-usb/
[Venus OS Integration]: https://github.com/123electric/123SmartBMS-Venus
[manual]: https://123electric.eu/downloads/123smartbms/123SmartBMS_gen3_manual.pdf
