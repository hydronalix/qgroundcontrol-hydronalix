## weird build stuff:   

* had to add the nlohmann json library and make include changes to libevents (wound up forking)  
* had to change to c++14 in the .pro file bc there's this library that's deprecated in c++17

## summarizing changes:

* added a button with a cool svg icon i made lol
    - made a textbox popup by modifying the `src/ui/toolbar/MainToolBar.qml` (see  c3f9159cfa7603d8c25b3d9789162bc355218740)
    - currently there's no functionality in the cpp class or whatever I made...but the textbox meme is cool
* added another button with a terrible svg icon
    - added `tdxactuatorcontroller.cpp`/`.h` to do udp stuff that normally i shid out in a python script
    - extended the QGCTool class
    - made `TdxActuatorController` objects in the `QGCToolbox` and `QGroundControlQmlGlobal` files
    - *all that just to make it so that i could call `changeTdxState()` in `MainToolBar.qml` lmaaaoooooo*
    - check the git log for evidence of this (bulk of work done 19 july)  

## general notes:  

* the thing that shows values at the bottom of QGC is the TelemetryValuesBar. i didn't know until working on this that you can edit the displayed telem values with the GUI, so that's cool. perhaps the move is to just pip the engine telem values over whatever link connects the GS to the FC.   
* inkscape is a good tool for making svgs   
* resources (svg files, for example) that are placed in resources or whever need to be defined in the qgcresources.qrc file.     
* forums suggest that learing about the UI starts from "MainWindowInner.qml", which I suspect is now "MainRootWindow.qml"

OMG: add new modules to the global `QGroundControl` object in `QGroundControlQmlGlobal.h` ?!?!?!
## errors and resolutions

hopefully this will be a good tracker of errors and crap with resolutions. starting this because I couldn't get onto SO on a plane and i'm TWEAKING up here!!

`linker command failed due to signal (use -v to see invocation)
clang: error: linker command failed due to signal (use -v to see invocation)
make: *** [QGroundControl.app/Contents/MacOS/QGroundControl] Error 254`
  
  
`No rule to make target `QGroundControl'.  Stop.`
delete build files
  


