# Shapes App

![Shapes App Mockup](https://user-images.githubusercontent.com/1055819/170129045-64e360d7-9320-486a-8685-f220606ec701.png)

The Shapes App uses MQTT to listen to state-changes of the Vision-Cube.
It can be used as an alternative to the Light-Cube, by visualizing the active class *seen* by the Vision-Cube, or serve as a starting point for other apps that interact with Any-Cubes.

## Installation

Run the following command to install all dependencies:

```
npm install
```

## Development

Before you can use the Shapes App, you need to specify the MQTT Server hostname / IP address:

1. Duplicate the file ".env.example" and rename it to ".env"
2. Enter the hostname or IP address of your MQTT server (e.g. "192.168.10.2" or "raspberrypi.local")
3. If your MQTT server uses authentication, also specify the MQTT username and password
3. Make sure that your computer is connected to the same network that the Any-Cubes are connected to

Run the following command to serve the shapes app:

```
npm run serve
```

The Terminal should output something like the following:

```
Server running at http://localhost:1234
```

You can visit "http://localhost:1234" in a web-browser now. Whenever the Vision-Cube detects another class, you will see the geometric shape in the app change.

## Building the app

To build the app (for example to upload the files to a smartphone, tablet or server), run the following command:

```
npm run build
```

This will generate a `dist` directory that contains all required files.

## Serving the Shapes App via iOS app

To use the Shapes App on an iOS device, you might use an app like [Kiosk Pro Basic / Plus](https://www.kioskgroup.com/pages/kiosk-pro-pricing).

Whenever you want to use the Shapes app, make sure you are connected to the same network as the Any-Cubes.
