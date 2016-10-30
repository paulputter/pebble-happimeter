# Pebble Happimeter
###### A COINs Project by University of Bamberg, University of Cologne, and University of Jilin

Our mind feels and our body senses when we are happy – or unhappy. Knowing when we are happy, and telling others about it will make them and us happier.

*Goal*: Build a body sensing system that measures and visualizes our happiness. It will consist of a Smartwatch or Android (later also iPhone) App that polls us 5-7 times per day to collect our emotional states. At the same time a Pebble smartwatch will collect a variety of body readings (temperature, light, steps, sleep, speech, energy,…).

*Research Hypothesis*: Comparing Pebble sensor readings with emotional state will allow us to correlate mood state with Pebble readings to automatically calculate mood state from Pebble sensor readings.

## Preliminary Database Structure
###### Relational Database Structure (e.g. using MySQL)

### User
A table that stores information about every user using the app.

Name | Type | Description
--- | --- | ---
ID | *uint* | Unique ID of the user (auto increment)
GUID | string | Unique device iD
Name | string | Random (funny) name
Password | int | Random four digits
SignupAt | DateTime | DateTime when the user was created
LastLogin | DateTime | Last time the user logged in


### Measuring Sensor Data
A table that stores all sensor measuring data associated to an user.

Name | Type | Description
--- | --- | ---
ID | *uint* | Unique ID of the dataset
UserID | *unit* | Unique ID of the user associated with this dataset
InsertedAt | *DateTime* | The DateTime this datasheet was inserted
Steps | *uint* | The number of steps
AvgBPM | *uint* | Average Heart Rate in BPM
MinBPM | *uint* | Minimum Heart Rate in BPM
MaxBPM | *uint* | Maximum Heart Rate in BPM
AvgLightLevel | *uint* | The average ambient light level
Activity | *uint* | The current activity the user is doing
RestingKCalories | *uint* | The burned kilo calories during rest
SleepSeconds | *uint* | The number of seconds the user was sleeping
SleepRestfulSeconds | *uint* | The number of seconds the user was deeply sleeping
ActiveSeconds | *uint* | The number of seconds the user was active
ActiveKCalories | *uint* | The burned kilo calories during activity
WalkedDistanceInMeters | *uint* | The number of meteres the user walked
PositionLat | *tdb.* | Current GPS position of the user (Lat)
PositionLon | *tdb.* | Current GPS position of the user (Lon)


### Happiness Data
A table that stores all happiness data associated to an user.

Name | Type | Description
--- | --- | ---
ID | *uint* | Unique ID of the dataset
UserID | *unit* | Unique ID of the user associated with this dataset
Happiness | *uint* | Happiness Likert Scale
... | ... | ...


## API Description
###### A REST API for pushing data and authentication

*tdb.*
