module.exports = [
  {
    "type": "heading",
    "defaultValue": "App Configuration"
  },
  {
    "type": "text",
    "defaultValue": "Customize Happimeter here for more accurate results"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Tell us who you are"
      },
      {
        "type": "input",
        "messageKey": "userinfo_name",
        "defaultValue": "",
        "label": "Name"
      },
      {
        "type": "input",
        "messageKey": "userinfo_email",
        "defaultValue": "",
        "label": "Email",
        "attributes": "email"
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "It's getting personal"
      },
      {
        "type": "slider",
        "messageKey": "userinfo_age",
        "label": "What is your age?",
        "min" : 4,
        "max" : 100,
        "defaultValue" : 18
      },
      {
        "type": "slider",
        "messageKey": "userinfo_weight",
        "label": "What is your weight (in Kg)?",
        "defaultValue": "70",
        "min": 20,
        "max": 200
      },
       {
        "type": "slider",
        "messageKey": "userinfo_sportiness",
        "label": "How sporty are you?",
     // "description": "i am the slider description",
        "devaultValue": 3,
        "min": 1,
        "max": 5
      },
      { //text to show how sporty the user is. this is controlled via a function in custom-clay.js
        "type": "text",
        "id": "sportiness_description",
       "defaultValue": "<span style='font-size:0.8em'>I dont do sports regularly</span>"
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type" : "text",
//        "messageKey": "linkToWebsite",
        "defaultValue": "<a href='http://team9.coins.he-hosting.de/login'>Analyze your data on our website</a>"
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];