# pixy-spark-core-rover
Getting the pixy CMUcam5 from Charmed labs http://charmedlabs.com/default/products/  working on a spark core rover



This rover has two motor drivers, one cheap and one expensive, so you may have to change the code a little bit to work with your motor driver.

Copy the pixy-rover.ino file to your spark IDE. Save.
click + in the top right corner and copy Pixy.h to the IDE. Save
click + again and copy TPixy.h to the IDE. Save

Flash the code to your core.


Really important to train the Pixy with the color you want the rover to follow and then check on Pixymon that the reading is a good one. I had all kinds of issues since I thought the color was preperly trained but it wasn't.



Sorry. I only just learnt how to make a proper Spark.io library file and I have not done that yet.
