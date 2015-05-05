# pixy-spark-core-rover
Getting the pixy CMUcam5 from Charmed labs http://charmedlabs.com/default/products/  working on a spark core rover

April 23, 2015

This rover has two motor drivers, one cheap and one expensive, so you may have to change the code a little bit to work with your motor driver.

Copy the pixy-rover.ino file to your spark IDE. Save.
click + in the top right corner and copy Pixy.h to the IDE. Save
click + again and copy TPixy.h to the IDE. Save

Flash the code to your core.


Really important to train the Pixy with the color you want the rover to follow and then check on Pixymon that the reading is a good one. I had all kinds of issues since I thought the color was preperly trained but it wasn't.



Sorry. I only just learnt how to make a proper Spark.io library file and I have not done that yet.


May 5, 2015
Having some trouble with the Pixy having false positives, makes my rover go racing down the street searching for the wrong color. Had a better look using PixyMon and found out the inperfections in the backpack I was using was allowing several false readings. Will have to get an object with a really consistent color.

I have included the images to help setup things. Have a look at all the images they should make some sense

Just a reminder image of the Spark Cores PINS

![](PixyConnector.png)

The Pixy to Spark Core Serial Connections

pixy-serial-spark-core.png


The Pololu Small Double motor driver (For low amps motors under 1 AMP at https://www.pololu.com/product/2135 about $8.00

pololu-small-double-2135.png

The Pololu big single motor driver for up to 30 AMP and like 41 Volts at https://www.pololu.com/product/1451  about $25.00

pololu-big-single-1451.png
















