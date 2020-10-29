import mqtt from'mqtt';

const scenes = document.querySelectorAll('.scene');

let activeScene = 0;

function setActiveSceneById(sceneId) {
  scenes.forEach((scene) => {
    const id = +scene.dataset.sceneId;
    if (id === +sceneId) {
      scene.classList.add('scene--active');
      activeScene = +sceneId;
    } else {
      scene.classList.remove('scene--active');
    }
  });
}

const PING_INTERVAL = 5000;
const CONNECTION_REPORT_INTERVAL = 10000;

let pingInterval;

/**
 * Duplicate the file ".env.example" and rename it to ".env", then
 * replace the environment variables according to your MQTT server.
 * 
 * When using with a Raspberry Pi, a complete server URL might look like the following:
 * 
 * With username / password authentication:
 * mqtt://username:password@192.168.123.123:9001
 * 
 * Without username / password authentication:
 * mqtt://192.168.123.123:9001
 */
const PROTOCOL = "mqtt";
const PORT = 9001;

const username = process.env.MQTT_USERNAME;
const password = process.env.MQTT_PASSWORD;
const useAuthentication = username !== undefined && password !== undefined;

const serverHostnameOrIp = process.env.MQTT_SERVER_HOSTNAME_OR_IP;

if (!serverHostnameOrIp) {
  throw new Error("You need to specify the MQTT server environment variable!");
}

const serverUrl = useAuthentication
  ? `${PROTOCOL}://${username}:${password}@${serverHostnameOrIp}:${PORT}`
  : `${PROTOCOL}://${serverHostnameOrIp}:${PORT}`

const client = mqtt.connect(serverUrl, {
  clientId: 'shapes-app',
  reconnectPeriod: 1000,
  resubscribe: true,
});

setInterval(() => {
  if (client) {
    console.log('Client is connected: ', client.connected);
  }
}, CONNECTION_REPORT_INTERVAL);

function sendPing() {
  if (client.connected) {
    client.publish('/any-cubes/visio-cube-vis/ping', 'alive');
  }
}

client.on('connect', function () {
  console.log('client has (re-)connected!');
  client.subscribe('/any-cubes/visio-cube/active-class');
  if (!pingInterval) {
    pingInterval = setInterval(sendPing, PING_INTERVAL);
  }
});

client.on('message', function (topic, message) {
  if (activeScene === +message) { return; }
  console.log('new message:', topic, message.toString());
  setActiveSceneById(+message);
});
