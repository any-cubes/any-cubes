# Light-Cube

![any-cubes-in-row](https://user-images.githubusercontent.com/1055819/135766221-404b78fb-4b14-4bdb-a711-79e25eaa8566.jpg)


The Light-Cube (in the image above on the right) is part of the Any-Cubes family and can be used to visualise what the Vision-Cube (another cube from the Any-Cubes family) detects.

It listens to a special MQTT message from the Vision-Cube.

## Why Is This Useful?

The Light-Cube can be used in two ways:

1. As a helper to train the Vision-Cube – it shows which class the Vision-Cube currently sees and therefore makes training easier
2. As an alarm device – you can set up the Vision-Cube in one room, and the Light-Cube in another. When the Vision-Cube sees something that you trained it on, the light of the Light-Cube will change accordingly.

## Folder Contents

- [3D](3d/README.md): 3D-printable files to print the Light-Cube case, connection-rims and base plate
- [Code](code/README.md): The Arduino code
- [Wiring](wiring/README.md): Explains how to connect the electronic parts

## Required Electronic Parts

- **Arduino Nano 33 IoT**
  - [docs.arduino.cc/hardware/nano-33-iot](https://docs.arduino.cc/hardware/nano-33-iot)
- **LED Matrix**
  - [Adafruit NeoPixel Matrix 8x8](https://www.adafruit.com/product/1487) (or compatible LED matrix)
- **Logic Level Converter**
  - [SN74AHCT125N](https://eu.mouser.com/ProductDetail/Texas-Instruments/SN74AHCT125N?qs=1wQRf3HkBjyxwrHMwAiMfw%3D%3D) – we recommend this one, as most normal logic level converters don’t work well with NeoPixels
- **USB Powerbank**
  - Only needed if you want to carry the Light-Cube around
  - Make sure it delivers enough Ampere
  - We use Ansmann USB Powerbank 5.4: 5V, 2.4 Ampera max: https://www.ansmann.de/consumer/powerbanks/powerbank-54
  - Some powerbanks have a *clever* automation to automatically power off when the connected device is disconnected. With microcontroller-boards this can result in the power bank shutting off randomly, even when the board is still connected (because it might draw only very little power). The powerbank we are using didn’t do that, but some others that we tried did.
- **USB cable**
  - Make sure to use a quality cable, especially super thin ones might not work

## Getting Started

1. Connect the board and LED matrix as described in [wiring](wiring/README.md)
2. Train the Vision-Cube
3. The Light-Cube will update its color according to the detected class of the Vision-Cube
