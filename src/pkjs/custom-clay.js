module.exports = function(minified) {
  var clayConfig = this;
  var _ = minified._;
  var $ = minified.$;
  var HTML = minified.HTML;

  // set the correct description according to sport level 1 - 5
  function toggleSportyDesc() {
    var sport_num = clayConfig.getItemByMessageKey('userinfo_sportiness');
    var sport_desc = clayConfig.getItemById('sportiness_description');
    var smallFontStartTag="<span style='font-size:0.8em'>";
    var smallFontEndTag="</span>";
    var sportiText;
    if (this.get()) {
      switch(sport_num.get()){
        case 1:
            sportiText = "I am a couchpotato";
            break;
        case 2:
            sportiText = "I like to run to catch my bus";
            break;
        case 3:
            sportiText = "I do sports regularly";
            break;
        case 4:
            sportiText = "I am fitter than most of my friends";
            break;
        case 5:
            sportiText = "Me > Jan Frodeno";
            break;
        default:
            sportiText = "༼ つ ◕_◕ ༽つ";
            break;
      } 
      sport_desc.set(smallFontStartTag + sportiText + smallFontEndTag);
    }
  }

  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
    var changeSportLevel = clayConfig.getItemByMessageKey('userinfo_sportiness');
    toggleSportyDesc.call(changeSportLevel);
    changeSportLevel.on('change', toggleSportyDesc);
    
    // the following may not be needed
    // var linkToWebsite = clayConfig.getItemByMessageKey('linktoWebsite');
    
    
  });
  
//  clayConfig.on(clayConfig.EVENTS.)

};