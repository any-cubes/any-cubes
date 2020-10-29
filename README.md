# Any-Cubes

_Didactic toy for machine teaching and IoT_  

[![teaser](https://user-images.githubusercontent.com/1055819/170082598-7ad80950-37db-4582-81c4-ee1620ff6d76.jpg)](https://vimeo.com/488949042)


Any-Cubes is a prototype didactic toy for schools and maker spaces, with which children can intuitively and playfully explore and understand machine learning as well as Internet of Things technology. Our prototype is a combination of deep learning-based image classification and machine-to-machine (m2m) communication via [MQTT](https://mqtt.org/). The system consists of three physical and tangible cubes.

Cube 1 («cubes/vision-cube/README.md») is a modification of [Google Coral’s Teachable Machine](https://coral.ai/projects/teachable-machine/) and can be trained to recognize objects or scenes.
The machine learning functionality is running directly on the Raspberry Pi board, accelerated using a Google Edge TPU Stick.

Via the MQTT protocol, the Vision-Cube broadcasts its detected class ("1", "2" or "3") to other Any-Cubes devices ("Light-Cube" and "Maker-Cube").

Cube 2 («[Light-Cube](cubes/light-cube/README.md)») visualises the detected class of the Vision-Cube by changing the color of its LEDs.

Cube 3 («[Maker-Cube](cubes/maker-cube/README.md)») can be used to control other circuits using relays. It can for example be used to open an electronic cat door, whenever the Vision-Cube detects a cat.

It addition to the physical cubes, apps using web-technologies can be created easily to react to the changes of the Vision-Cube.
One such app is «[Shapes](apps/shapes-app/README.md)» – it shows different graphical shapes to visualise the classes being detected by the Vision-Cube. It can be used as a boilerplate to create custom apps that react to the Vision-Cube.

# Publications
 
Scheidt, A., & Pulver, T. (2019). Any-Cubes: A Children’s Toy for Learning AI: Enhanced Play with Deep Learning and MQTT. Proceedings of Mensch Und Computer 2019. [https://doi.org/10.1145/3340764.3345375](doi.org/10.1145/3340764.3345375)

# Contributors

Any-Cubes is a project by [Alexander Scheidt](https://www.fh-potsdam.de/studium-lehre/projekte/any-cubes) and [Tim Pulver](https://timpulver.de/) with contributions by [Meliani Meliani](https://www.linkedin.com/in/meliani-meliani-7a856b1a4/?originalSubdomain=de) (research and organisation of workshops), [Lukas Schmidt Wiegand](https://www.linkedin.com/in/lukas-schmidt-wiegand-67b990172/) (industrial design) and [Sabina Fimbres Sabugal](https://www.linkedin.com/in/sabina-fimbres-sabugal-7a253a213/) (graphic design for posters).





 
