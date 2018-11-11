# flyingByHand
Assignment 03 - Flying by hand using ofxLeapC
IMD 3005
Julianna Clarke & Jack Goodman
November 10, 2018

The following is a game using the Leap Motion handtracker to fly through space on a 2D plane. Using your hand to control the ship, the objective of the game is to collect all the stars by flying over them and pinching to collect them, but you must avoid touching the asteroids! Touching an asteroid will cause the game to end. In our game, we used the following functionalities of the Leap Motion controllers:

- x and y positional tracking to move the ship
- rotational tracking to rotate the ship
- grab gesture to start the game
- pinch gesture to collect stars
- timeVisible tracking to increment score while a hand is being tracked

We wanted to design the game so that every aspect of it was gestural, so we used the grab and pinch gestures to change game states. Additionally, using the pinch gesture to collect the stars was particularly intuitive for gameplay as the user was already controlling the movement with their hand. 

Naturally, we used objects to define the objects in our game, but this ended up being a challenging aspect of it. Setting up the objects was simple, but being able to draw the objects in the appropriate places proved to be difficult because the coordinate system for the objects was different from that used by the hand tracking from Leap Motion. In general, our issues stemmed from the Leap Motion controller, and us needing to learn how it works and how to use it better.

In the end, we got a much better grasp of how to use the Leap Motion device, and we were able to shift our objects so that they used the Leap Motion coordinate system, which was essential for our collision. We feel that our game is a creative application of some of the capabilities of the device.
