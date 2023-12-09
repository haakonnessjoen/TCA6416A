# TCA6416A Arduino Library

This is an Arduino library for the TCA6416A, a 16-bit I/O expander for the I2C bus.

## Installation in Arduino IDE

You should be able to install this library from the Arduino IDE's Library Manager. If you prefer to install it manually, follow these steps:

1. Download the library as a ZIP file.
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library and select the downloaded file.

## Usage

Include the library in your sketch:

```cpp
#include <TCA6416A.h>
```

Create an instance of the TCA6416A class:

```cpp
TCA6416A expander;
```

In your setup function, initialize the TCA6416A:

```cpp
void setup() {
	while (!pins.begin(0, &Wire)) { // replace 0 with the address bit of your TCA6416A
    	Serial.println("TCA6416A not found");
		delay(1000);
	}
}
```

You can then use the various methods provided by the library to interact with the TCA6416A. For example, to set a pin as output and write a HIGH signal:

```cpp
expander.pin_mode(0, OUTPUT);
expander.pin_write(0, HIGH);
```

To read the state of a pin:

```cpp
int state = expander.pin_read(0);
```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request on GitHub.

## License

This library is licensed under the MIT License. See the LICENSE file for more information.