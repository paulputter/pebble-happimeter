Pebble.addEventListener("ready", function(e){
  console.log("ready for interaction");
});

Pebble.addEventListener("appmessage", function(e){
  console.log("got testkey with value " + e .payload.testkey);
});