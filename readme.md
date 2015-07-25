#ColAndreas

ColAndreas is a plugin for SA-MP which creates a simulation of the San Andreas world. Using the [Bullet Physics library](http://bulletphysics.org/), ColAndreas 
gives the server knowledge of the game environment itself.

**Watch it in action:** [https://www.youtube.com/watch?v=aSabQWqQBkI](https://www.youtube.com/watch?v=aSabQWqQBkI)

##Download

Go to the [releases page](https://github.com/Pottus/ColAndreas/releases) and grab the latest *ColAndreas_Precompiled* zip file, it contains the Windows and Linux versions of the plugin, the include file for PAWN and the Wizard executable.

##Linux note

* If you get this error: `Failed (libBulletCollision.so.2.82: cannot open shared object file: No such file or directory)` it means your system doesn't have the required libraries. There are 2 possible solutions for this issue: 
      * Use the statically linked version of the plugin (*ColAndreas_static.so*).
      * Install the Bullet libraries using your distro's package manager.
          * **Ubuntu:** `sudo apt-get install libbulletcollision2.82:i386 libbulletdynamics2.82:i386 liblinearmath2.82:i386 libbulletsoftbody2.82:i386`
          * Please note that you must install the *32bit* (i386) version of the libraries, even if you use a 64bit OS.

##Installing

1. If you haven't done it yet, generate the ColAndreas database (*ColAndreas.cadb*). For doing this, run the Wizard executable (*ColAndreasWizard.exe*) and follow the instructions. Save the file in the folder *scriptfiles/colandreas*
2. Add the server plugin:
   * **Windows:** Copy *ColAndreas.dll* to the *plugins* folder of your server and add "ColAndreas" to the *plugins* line in *server.cfg*
   * **Linux:** Copy *ColAndreas.so* or *ColAndreas_static.so* (see the note above) and add "ColAndreas.so" or "ColAndreas_static.so" to the *plugins* line in *server.cfg*
3. Copy *ColAndreas.inc* to the folder *pawno/include*
4. Call `CA_Init()` from `OnGameModeInit` in order to initialize the plugin:
```pawn
public OnGameModeInit()
{
    // Objects need to be removed BEFORE calling CA_Init
    CA_RemoveBuilding();
	
    // Initialize the plugin
    CA_Init();
	
    // Objects can only be added AFTER calling CA_Init
    CreateDynamicObject_SC();

    return 1;
}
```
