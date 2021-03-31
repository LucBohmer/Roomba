var WebSocket_MQTT_Broker_URL = "";
var MQTT_Client_ID = "";
var MQTT_Topic = "";
var MQTT_Client = "";
var MQTT_topic_root = "";

function initVars() {
      Set_New_Console_Msg("initVars");
      MQTT_device = "webapp";
      MQTT_topic_root = "BestRoomba/";
}

function mqtt_Connect_with_Broker() {
      // Set variables
      WebSocket_MQTT_Broker_URL =
            document.getElementById("txt_MQTT_Broker_URL").value;
      MQTT_Client_ID =
            document.getElementById("txt_MQTT_Client_ID").value;
      MQTT_topic_root =
            document.getElementById("txt_MQTT_topicroot").value;

      // Create a MQTT Client nstance
      MQTT_Client =
            new Paho.MQTT.Client(WebSocket_MQTT_Broker_URL, MQTT_Client_ID);

      // set callback handlers
      MQTT_Client.onConnectionLost = onConnectionLost;
      MQTT_Client.onMessageArrived = onMessageArrived;

      MQTT_Client.connect({
            onSuccess: onConnect
      });
}

// Called when the client connects
function onConnect() {
      // Once a connection has been made, make a subscription.
      Set_New_Console_Msg("Connected to " + WebSocket_MQTT_Broker_URL);
      document.getElementById("btn_Connect_to_Broker").disabled = true;
      document.getElementById("txt_MQTT_Broker_URL").disabled = true;
      document.getElementById("txt_MQTT_Client_ID").disabled = true;
      // ??document.getElementById("pubsub").style.display = 'visible';
      // document.getElementById("button1on").disabled = false;
      // document.getElementById("button1off").disabled = false;
      // document.getElementById("button2on").disabled = false;
      // document.getElementById("button2off").disabled = false;
      // document.getElementById("button3on").disabled = false;
      // document.getElementById("button3off").disabled = false;
      MQTT_Client.subscribe("BestRoomba/#");
      MQTT_Client.subscribe("ESEiot/1718sem4/#");
}

// Called when the client loses its connection
function onConnectionLost(responseObject) {
      if (responseObject.errorCode !== 0) {
            Set_New_Console_Msg("ERROR: connection lost with MQTT Broker: " +
                  "\"" + responseObject.errorMessage + "\"");
            document.getElementById("btn_Connect_to_Broker").disabled = false;
            document.getElementById("txt_MQTT_Broker_URL").disabled = false;
            document.getElementById("txt_MQTT_Client_ID").disabled = false;
      }
}

// called when a message arrives
function onMessageArrived(message) {
      Set_New_Console_Msg("MQTT message recieved: " +
            "\"" + message.payloadString + "\"" + " MQTT topic: " +
            "\"" + message.destinationName + "\"" + " QoS: " + "\"" +
            message.qos + "\"");
      // if (message.destinationName === MQTT_topic_root + "ledgreen") {
      //    if (message.payloadString === '1') {
      //       $('#ledgreenO').attr('color', 'green');
      //    } else {
      //       $('#ledgreenO').attr('color', 'grey');
      //    }
      // }
      // if (message.destinationName === MQTT_topic_root + "ledyellow") {
      //    if (message.payloadString === '1') {
      //       $('#ledyellowO').attr('color', 'yellow');
      //    } else {
      //       $('#ledyellowO').attr('color', 'grey');
      //    }
      // }
      // if (message.destinationName === MQTT_topic_root + "ledred") {
      //    if (message.payloadString === '1') {
      //       $('#ledredO').attr('color', 'red');
      //    } else {
      //       $('#ledredO').attr('color', 'grey');
      //    }
      // }

      if (message.destinationName === MQTT_topic_root + "clean") {
      }

      if (message.destinationName === MQTT_topic_root + "dock") {
      }

      if (message.destinationName === MQTT_topic_root + "spot") {
      }
}

// Document Ready Event
$(document).ready(function () {
      //Set default MQTT Broker WebSocket URL
      document.getElementById("txt_MQTT_Broker_URL").value =
            "ws://broker.hivemq.com:8000/mqtt";
      document.getElementById("txt_MQTT_topicroot").value =
            "BestRoomba/";
      //Generate Random MQTT Clinet ID
      gen_MQTT_Client_ID();
      // document.getElementById("button1on").disabled = true;
      // document.getElementById("button1off").disabled = true;
      // document.getElementById("button2on").disabled = true;
      // document.getElementById("button2off").disabled = true;
      // document.getElementById("button3on").disabled = true;
      // document.getElementById("button3off").disabled = true;
})

// Randomly generate Client ID
function gen_MQTT_Client_ID() {
      document.getElementById("txt_MQTT_Client_ID").value =
            Math.floor(100000000000 + Math.random() * 900000000000);
}

function led(color, msg) {
      var message = new Paho.MQTT.Message(msg);
      message.destinationName = MQTT_topic_root + "led" + color;
      MQTT_Client.send(message);
}

function publish(topic, msg) {
      var message = new Paho.MQTT.Message(msg);
      message.destinationName = MQTT_topic_root + topic;
      MQTT_Client.send(message);
}

function publishRPI(topic, msg) {
      var message = new Paho.MQTT.Message(msg);
      message.destinationName = "ESEiot/1718sem4/RPI584852/" + topic;
      MQTT_Client.send(message);
}

// Set MQTT Messages to TextArea
function Set_New_Console_Msg(text) {
      document.getElementById("txtAr_Console").value =
            document.getElementById("txtAr_Console").value +
            get_Fromatted_Time().toString() +
            "   " + text + "\n";
      document.getElementById("txtAr_Console").scrollTop =
            document.getElementById("txtAr_Console").scrollHeight;
}

//Clear Console
function clear_Console() {
      document.getElementById("txtAr_Console").value = "";
}

// Get Formatted time in Hour:Minute:Seconds AM/PM format
function get_Fromatted_Time() {
      var dt = new Date();
      var hours = dt.getHours() == 0 ? "12" : dt.getHours() > 12 ? dt.getHours() - 12 : dt.getHours();
      var minutes = (dt.getMinutes() < 10 ? "0" : "") + dt.getMinutes();
      var seconds = (dt.getSeconds() < 10 ? "0" : "") + dt.getSeconds();
      var ampm = dt.getHours() < 12 ? "AM" : "PM";
      var formattedTime = hours + ":" + minutes + ":" + seconds + " " + ampm;
      return formattedTime;
}