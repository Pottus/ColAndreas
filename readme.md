#ColAndreas

ColAndreas is a plugin for SA-MP which creates a simulation of the San Andreas world. Using the [Bullet Physics library](http://bulletphysics.org/), ColAndreas
gives the server knowledge of the game environment itself.

**Watch it in action:** [https://www.youtube.com/watch?v=aSabQWqQBkI](https://www.youtube.com/watch?v=aSabQWqQBkI)

##Download

Go to the [releases page](https://github.com/Pottus/ColAndreas/releases) and grab the latest *ColAndreas_Precompiled* zip file, it contains the Windows and Linux versions of the plugin, the include file for PAWN and the Wizard executable. The wizard generated file goes in /scriptfiles/ColAndreas/ with the name of ColAndreas.cadb!

##Linux note

* If you get this error: `Failed (libBulletCollision.so.2.82: cannot open shared object file: No such file or directory)` it means your system doesn't have the required libraries. There are 2 possible solutions for this issue:
	* Use the statically linked version of the plugin (*ColAndreas_static.so*).
	* Install the Bullet libraries using your distro's package manager.
		* **Ubuntu:** `sudo apt-get install libbulletcollision2.82:i386 libbulletdynamics2.82:i386 liblinearmath2.82:i386 libbulletsoftbody2.82:i386`
		* Please note that you must install the *32bit* (i386) version of the libraries, even if you use a 64bit OS.
		
