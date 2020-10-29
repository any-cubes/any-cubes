# Maker-Cube

![Maker-Cube with Vision Cube and Cow](https://user-images.githubusercontent.com/1055819/170130809-4a4a9bfe-7443-42df-92e0-c23b81e19188.jpg)

The Maker-Cube is part of the Any-Cubes family and can be used to turn up to four external circuits on or off. Internally it uses relays, which either open or close another connected circuit. In the image above, it is being used to turn on a windmill toy whenever the Vision-Cube detects a cow.

It listens to a special MQTT message from the Vision-Cube (another cube from the Any-Cubes family that uses a camera and machine learning to recognise different scenes, so called «classes»).

## Why Is This Useful?

Let’s say you trained the Vison-Cube to recognise your cat and you also built a custom cat door that can electronically be opened or closed. You could use the Maker-Cube to connect the two projects, so whenever the Vision-Cube detects the cat, the cat door automatically opens.

## Folder Contents

In this repository you will find the following sub-folders:

- [3D](3d/README.md): 3D-printable files to print the Maker-Cube case, connection-rims and base plate
- [Code](code/README.md): The Arduino code
- [Wiring](wiring/README.md): Explains how to connect the electronic parts

## How Can a Circuit Be Connected to the Maker-Cube?

The Maker-Cube can be used to control any other (low-power) circuit, for example one of your Arduino projects or an electronic toy running on batteries, with minimal modifications.

To connect the Maker-Cube to other circuits, banana cables are being used.

**Attention:** While connecting high power circuits (e.g. a coffee machine) to the Maker-Cube might work, we do not recommend it, because it is very dangerous. Only use the Maker-Cube to control low-power devices / circuits, for example battery-driven projects.

To control another circuit using the Maker-Cube, you need to cut its power line. For an Arduino project this might be its VCC / 3.3V / 5V line.

One side of the cable then goes into one of the two ports of a Maker-Cube’s side, the other side of the cable goes into the other port. Whenever this side of the Maker-Cube is activated (via the Vision-Cube), the connection between the two ports is closed, and therefore the circuit of the connected project is closed as well.

**Please note:** The connected circuit must have its own power source. The Maker-Cube simply closes the circuit, but it does not provide power.

## Required Electronic Parts

- **NodeMCU V2**
  - We use a similar version to this one: https://joy-it.net/de/products/SBC-NodeMCU
- **Logic Level Converter**
  - We use 4-channel I2C-safe Bi-directional Logic Level Converter - BSS138: https://www.adafruit.com/product/757
- **Relais**
  - We use a Velleman 4x Relay VMA400: https://www.velleman.eu/products/view/?id=435558
  - Other relays might or might not work with a 3.3V development board. We tried a few other ones that only worked with 5V development boards.
- **Banana jacks / connector cables**
  - There are a multitude of banana jacks / connector cables. The most important thing is that the plug fits to the connector
  - For example: https://uk.farnell.com/hirschmann-testmeasurement/972354102/socket-4mm-safety-blue-mvl-s/dp/1011403
  - Search for «banana jack surface mount» to find others
  - For the Vision-Cube you need 2 jacks for each side, so 8 in total
  - You need one (long) banana cable per project that you want to connect
- **USB Powerbank**
  - Only needed if you want to carry the Maker-Cube around
  - Make sure it delivers enough Ampere
  - We use Ansmann USB Powerbank 5.4: 5V, 2.4 Ampera max: https://www.ansmann.de/consumer/powerbanks/powerbank-54
  - Some powerbanks have a *clever* automation to automatically power off when the connected device is disconnected. With microcontroller-boards this can result in the power bank shutting off randomly, even when the board is still connected (because it might draw only very little power). The powerbank we are using didn’t do that, but some others that we tried did.
- **USB cable**
  - Make sure to use a quality cable, especially super thin ones might not work

## Getting Started

1. Connect the board, relay and banana jacks as described in [wiring](wiring/README.md)

2. Cut the banana cable in half

3. Solder on one end of the banana cable to the end of the cable that opens the circuit of your other project
4. Do the same with the other half / side of the cable
