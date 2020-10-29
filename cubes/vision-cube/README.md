# Vision-Cube

![Vision-Cube being used to recognize a giraffe](https://user-images.githubusercontent.com/1055819/170131673-8bb16d97-a157-46d0-bfd9-dd627f50dbe2.jpg)

The Vision-Cube uses machine learning to recognize different objects and scenes (in the image above, to recognize a giraffe). It can be trained using just a few images.
The Vison-Cube is based on [Google Coral’s Project Teachable](https://coral.ai/projects/teachable-machine/).

## Hardware

- Raspberry Pi 3 B+
- Google Coral USB Accelerator
- 5V USB Powerbank (with 2.5A or more)
- Four buttons (three for classification, one to reset the model)

## Software

We use a modified version of the [Google Coral’s Teachable Machine](https://github.com/google-coral/project-teachable) project.

Our modifications include:

- Installed an MQTT server ([mosquitto](https://mosquitto.org/)) to the Raspberry Pi
- Added auto-start of the detection script, so it starts automatically when the Raspberry Pi starts (see [Sparkfun – How to Run a Raspberry Pi Program on Startup](https://learn.sparkfun.com/tutorials/how-to-run-a-raspberry-pi-program-on-startup/all))

We might provide an SD-card image of the Vision-Cube on request that contains all modifications.
