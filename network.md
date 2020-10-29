# Network

Any-Cubes modules need two things to communicate:

1. A network that it can connect to
2. An MQTT server (runs on the Vision-Cube)

## Local Usage

Any-Cubes currently only communicate locally, they don’t depend on an internet connection being available.

If you have a spare router, you can use it for the Any-Cubes network. This way it is easy to take Any-Cubes to a new location and start them up, without the need to re-configure their WiFi settings.

With an Any-Cubes specific router, the workflow would be like this:

1. Plug in the router. Wait a minute until it is ready.
2. Power up the Vision-Cube. Wait a minute until it is booted up and the MQTT server is ready.
3. Power up the remaining cubes

Using a separate network / router for the Any-Cubes is more secure, because all communication is separate to your regular WiFi network. Everything stays local, so there is no chance that your devices are exposed to the internet (which would require further work to secure the devices).

If you want to use any of the Any-Cubes apps on a tablet device you also need to do the following:

1. Connect the tablet to the same network the Any-Cubes are connected to
2. Serve the `index.html` file of the app, for example using the app [Kiosk Pro](https://www.kioskgroup.com/pages/kiosk-pro-software)
