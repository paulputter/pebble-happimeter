## API Description
###### A REST API

Preliminary v1 specification. Using PHP/Slim at the development server of Rain.

### Attention(s)
1. URL: [http://team9.coins.he-hosting.de/api](http://team9.coins.he-hosting.de/api)
2. The timezone is Europe/Berlin.

### Response format of failed request

If request **fails** or has some *warnings*, the response format is as follows:

Name | Type | Description
--- | --- | ---
Status | *int* | 0: fail <br> 1: success <br> 2: warning
Description | *string* | The brief description of the error or the warning

### User
#### Initial Signup
##### [POST] /user/
###### Request Body
Name | Required | Type | Description
--- | --- | --- | ---
Mail | yes | *string* | E-Mail
DeviceID | no | *string* | Unique device ID, You can set it later.

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status
Password | *string* | Password that system generate
Token | *string* | Auth token for the session

#### Login
##### [POST] /auth/
###### Request Body
Name | Required | Type | Description
--- | --- | --- | ---
Mail | yes | *string* | Mail
Password | yes | *string* | Password

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status
Token | *string* | Auth token for the session


#### Set or change user's personal infomation
##### [POST] /userinfo/
###### Request Body
Name | Required | Type | Description
--- | --- | --- | ---
Token | yes | *string* | user's token
Name | no |  *string* | name
Age | no | *int* | age of the user
Avatar | no | *string* | URL to the users avatar/picture
Weight | no | *double* | Weight in kg of the user
Sportiness |no | *int* | Sportiness of the user (0:low, 1:medium, 2:high)

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status

#### Bind user and device
##### [POST] /bind/
###### Request Body
Name | Required | Type | Description
--- | --- | --- | ---
Token | yes | *string* | User's token
DeviceID | yes | *string* | Bepple watch device id

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status

### Happimeter
#### Post Data
##### [POST] /happiness/
###### Request Body
Name | Required | Type | Description
--- | --- | --- | ---
Token | yes | *string* | Auth token that identifies the user
Timestamp | yes | *DateTime* | The DateTime this datasheet is associated with
Happiness | no | *uint* | Happiness Likert Scale
WhoHaveYouBeenWith | no | *uint* | Enum that indicates who has the user been with
DidYouDoSports | no | *boolean* | Indicates whether the user did any sports activity

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status

### Sensor
#### Post Data
##### [POST] /sensor/
###### Request Body
Name | Required | Type | Description
--- | --- | --- | ---
Token | yes | *string* | Auth token that identifies the user
Timestamp | yes | *DateTime* | The DateTime this datasheet is associated with
Steps | no | *uint* | The number of steps
AvgBPM | no | *uint* | Average Heart Rate in BPM
MinBPM | no | *uint* | Minimum Heart Rate in BPM
MaxBPM | no | *uint* | Maximum Heart Rate in BPM
AvgLightLevel | no | *uint* | The average ambient light level
Activity | no | *uint* | The current activity the user is doing
SleepSeconds | no | *uint* | The number of seconds the user was sleeping
PositionLat | no | *Decimal(9,6)* | Current lat position of the user (GPS)
PositionLon | no | *Decimal(9,6)* | Current lon position of the user (GPS)

###### Response Body
Name | Type | Description
--- | --- | ---
Status | *int* | Status
