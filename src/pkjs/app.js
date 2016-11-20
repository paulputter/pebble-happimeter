var url = "";
var watchToken = "";

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
    watchToken = Pebble.getWatchToken();
    url = "http://team9.coins.he-hosting.de/api/";
    console.log('(JS) Happimeter API url: ' + url);
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage', function(e) {
    // Get the dictionary from the message
    var dict = e.payload;
  
    console.log('(JS) Got message: ' + JSON.stringify(dict));
  
    var options = {
      enableHighAccuracy: true,
      maximumAge: 10000,
      timeout: 10000
    };
    
    // Request current position
    navigator.geolocation.getCurrentPosition(function(pos) {
      // Create the request
      var request = new XMLHttpRequest();
      request.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
    
      // Specify the callback for when the request is completed
      request.onload = function() {
        console.log('Got response: ' + this.responseText);
      };
      
      // Send the request
      request.open("POST", url + "/sensor/");
      request.send(JSON.stringify({
        'Token': '78930aa018099924de5a93c6683dbbb6', // <-- this is right now my (Pascals) personal token, since we do not have an registration
        'Timestamp': dict.current_time,
        'Steps': dict.steps,
        'AvgBPM': dict.avg_bpm,
        'MinBPM': dict.min_bpm,
        'MaxBPM': dict.max_bpm,
        'AvgLightLevel': dict.avg_light_level,
        'Activity': dict.activity,
        'SleepSeconds': dict.sleep,
        'PositionLat': pos.coords.latitude,
        'PositionLon': pos.coords.longitude
      }));
      }, function(err){
        console.log(err);
      }, options);
});