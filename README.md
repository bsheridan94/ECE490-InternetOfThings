ECE490 Project

Internet of Things - Wifi Connected Door Lock

The deadbolt on my apartment was connected to a servo.

The servo was connected to a Arduino which was connected to a xbee on a shield and a NFC reader.

A raspberry pi with Node-Red was then connected to another xbee.
![](https://github.com/bsheridan94/ECE490-InternetOfThings/blob/master/Images/20140826_183822.jpg)

Node-Red would periodically check a special twitter account called @ECE490DoorLock.

An authorized account could message the lock at the twitter handle. Certain phrases would lock the door, unlock the door, or direct message back the status of the door lock.
![](https://github.com/bsheridan94/ECE490-InternetOfThings/blob/master/Images/Capture5.JPG)

![](https://github.com/bsheridan94/ECE490-InternetOfThings/blob/master/Images/Capture6.JPG)


The door could also be unlocked and locked through waving an NFC id infront of the door panel.

![](https://github.com/bsheridan94/ECE490-InternetOfThings/blob/master/Images/Capture7.JPG)

Overall the project was a success, though i still wish to make the code more robust and functional and remove the use of node red. 
