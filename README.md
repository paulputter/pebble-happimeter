# Pebble Happimeter
###### A COINs Project by University of Bamberg, University of Cologne, and University of Jilin

Our mind feels and our body senses when we are happy – or unhappy. Knowing when we are happy, and telling others about it will make them and us happier.

*Goal*: Build a body sensing system that measures and visualizes our happiness. It will consist of a Smartwatch or Android (later also iPhone) App that polls us 5-7 times per day to collect our emotional states. At the same time a Pebble smartwatch will collect a variety of body readings (temperature, light, steps, sleep, speech, energy,…).

*Research Hypothesis*: Comparing Pebble sensor readings with emotional state will allow us to correlate mood state with Pebble readings to automatically calculate mood state from Pebble sensor readings.

## Data Specification
###### Relational Data Structure (e.g. using MySQL)

### User
A table that stores information about every user using the app.

Name | Type | Description
--- | --- | ---
ID | *uint* | Unique ID of the user (auto increment)
DeviceID | *string* | Unique device ID
Mail | *string* | Unique mail
Name | *string* | Name
Age | *uint* | Age of the user
Password | *string* | Password of the user (Encrypted/Hashed)
Avatar | *string* |URL to the users avatar/picture
SignupAt | *DateTime* | DateTime when the user was created
LastLogin | *DateTime* | Last time the user logged in

### Auth
A table that stores auth sessions and their assocations to the user.

Name | Type | Description
--- | --- | ---
ID | *uint* | Unique ID of the auth entry (auto increment)
UserID | *uint* | ID of the user
Token | *string* | Random GUID for the session
Created | *DateTime* | DateTime when the session was created

### Happiness Data
A table that stores all happiness data associated to an user.

Name | Type | Description
--- | --- | ---
ID | *uint* | Unique ID of the dataset
UserID | *unit* | Unique ID of the user associated with this dataset
Happiness | *uint* | Happiness Likert Scale
WhoHaveYouBeenWith | *uint* | Enum that indicates who has the user been with
DidYouDoSports | *boolean* | Indicates whether the user did any sports activity

### Sensor Data
A table that stores all measuring data associated to an user.

Name | Type | Description
--- | --- | ---
ID | *uint* | Unique ID of the dataset
UserID | *unit* | Unique ID of the user associated with this dataset
Timestamp | *DateTime* | The DateTime this datasheet is associated with
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
PositionLat | *Decimal(9,6)* | Current lat position of the user (GPS)
PositionLon | *Decimal(9,6)* | Current lon position of the user (GPS)

## API Description
###### A REST API

Preliminary v0 specification. Using Python/Flask at the development server of Rain.

### User
#### Initial Signup
##### [POST] /user/
###### Request Body
Name | Type | Description
--- | --- | ---
GUID | *string* | Unique device ID
Mail | *string* | E-Mail
Name | *string* | Name
Age | *uint* | Age of the user

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status
Token | *string* | Auth token for the session

#### Login
##### [POST] /auth/
###### Request Body
Name | Type | Description
--- | --- | ---
Mail | *string* | Mail
Password | *string* | Password

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status
Token | *string* | Auth token for the session

### Happimeter
#### Post Data
##### [POST] /happiness/
###### Request Body
Name | Type | Description
--- | --- | ---
Token | *string* | Auth token that identifies the user
Happiness | *uint* | Happiness Likert Scale
WhoHaveYouBeenWith | *uint* | Enum that indicates who has the user been with
DidYouDoSports | *boolean* | Indicates whether the user did any sports activity

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status

### Sensor
#### Post Data
##### [POST] /sensor/
###### Request Body
Name | Type | Description
--- | --- | ---
Token | *string* | Auth token that identifies the user
Timestamp | *DateTime* | The DateTime this datasheet is associated with
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
PositionLat | *Decimal(9,6)* | Current lat position of the user (GPS)
PositionLon | *Decimal(9,6)* | Current lon position of the user (GPS)

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status
