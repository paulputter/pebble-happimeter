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

  function emailIsValid(email){
    var re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(email);
  }
  
  // checks on each char entered if the email address is valid according to REGEX
  // if it is valid enable submit button
  // else disable submit button
  function verifyEmailOnChange(){
    var email = clayConfig.getItemByMessageKey("userinfo_email");
    var submit = clayConfig.getItemsByType("submit")[0];
    if (emailIsValid(email.get()))
      {
        submit.enable();
      }   
    else
      submit.disable();
  }
  
  // Aaand double check email addrees ... 
  // cause maybe the user thinks he is smarter than the developers... -_-
  function verifyEmailOnSubmit(){
    var email = clayConfig.getItemByMessageKey("userinfo_email");
    if (!emailIsValid(email.get()))
      {
        email.set("invalid@email.com");
      }      
  }
  
  
  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
    // verify email address according to REGEXP
    var email = clayConfig.getItemByMessageKey("userinfo_email");
    var submit = clayConfig.getItemsByType("submit")[0];
    
    verifyEmailOnChange.call(email);
    email.on("change", verifyEmailOnChange);
    
    // change sport description according to sport number
    var changeSportLevel = clayConfig.getItemByMessageKey("userinfo_sportiness");
    toggleSportyDesc.call(changeSportLevel);
    changeSportLevel.on('change', toggleSportyDesc);
    
    // check if email address is a valid Email address when user wants to submit the form
    submit.on('click', verifyEmailOnSubmit);
  });

};