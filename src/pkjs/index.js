var url = "";

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
    url = "http://192.168.1.47:3000/v1/devices/" + Pebble.getWatchToken();
    console.log('(JS) Happimeter API url: ' + url);
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage', function(e) {
    // Get the dictionary from the message
    var dict = e.payload;
  
    console.log('(JS) Got message: ' + JSON.stringify(dict));
    
    // Create the request
    var request = new XMLHttpRequest();
    request.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
  
    // Specify the callback for when the request is completed
    request.onload = function() {
      console.log('Got response: ' + this.responseText);
    };
    
    // Send the request
    request.open("POST", url + "/steps");
    request.send(JSON.stringify(dict));
});