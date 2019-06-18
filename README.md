# OpenGL-JetPackJoyride

## About the game
The game is an arcade game (inspired by Jetpack Joyride ) where the player controls the object and
move it up, forward and backward while collecting coins. The player should also dodge the
obstacles/enemies as they have penalties.
Objective of the game is to maximize score by collecting coins.

## Objects
+ Player: The main character of the game, who can navigate through the world and has 3 lives
initially, with each life having 100 health.
+ Wall
+ Platform
+ Coins: 2 types of coins (yellow:5 points and orange:10 points)
+ Magnet
+ Special Flying Objects / Powerups: +50 points
+ Circular Ring / Tunnel: A semicircular tunnel like ring in which the player can get into and will
be protected from all the enemies.
+ Enemies:
1) Fire Lines: Inclined at any angle to the horizontal.
2) Fire Beams: One horizontal fire beams appear and can move vertically up and down.
3) Boomerang: Appears in Level-2. Moves in a horizontal-U shape and is deadly.
4) Viserion - The Dragon: Moves according to the position of the player. Throws deadly fire
balls which consume his health or even lives.
+ Water Balloons : To extinguish fire beams and fire lines. They also reduce dragon’s health.
BONUS OBJECTS:
+ Lightsaber: A lightsaber/sword which will be available to the player after he obtains a certain
amount of score. It can kill all the enemies, including the dragon.
+ Seven Segment Display Objects: Used to display – Score, Lives, Health

## Physics implemented
+ Gravity influenced movement of objects.
+ Horizontal-U movement of the boomerang.
+ Projectile nature of objects.
+ Magnet affects player's path of motion.

## How to run
Enter the command "./graphics_asgn1" on the terminal in the output folder.

## Controls
+ Left arrow: Move Left
+ Right arrow: Move Right
+ SPACE: Move Up
+ B: Throw water balloons
+ Mouse scroll-wheel: Zooming


