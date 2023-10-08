DoJoy-Stick
========================
* Joystick Looper:  Allows you to control  ***[sooperlooper](http://essej.net/sooperlooper)***  with your joystick.  
* Joystick as a Midi-Device (planned)

Looper Control
------------------------
Record Tap footswitch once.

Switch to playback Tap footswitch again.

Undo/Redo last recording Press and hold footswitch.

Stop Double-tap footswitch.

Stop and delete the loop Double-tap and hold footswitch.

Resume playback Tap footswitch again.

Delete the loop Press and hold footswitch (when Ditto Looper is disengaged). 

Each button controls the first Loop of the software looper. 

Control is based on the **ditto looper** https://toneprints.com/media/1633414/tc_ditto_looper_manual_english.pdf

Runtime requirements
------------------------
liblo-tools (used for oscsend)

### looper backend

only ***[sooperlooper](http://essej.net/sooperlooper)*** is supported

Build requirements
------------------------
boost msm

Build
------------------------
    make


Run
------------------------



Developer Notes
------------------------
Backend Sooperlooper is controlled by Open Sound Control (OSC)

Sooperlooper OSC commands (some of them)
http://essej.net/sooperlooper/doc_osc.html

### projects worth mentioning
MidiJoystick: could not be compiled on modern ubuntu22.04
QJoyStick: use JoyStick with Qt Library

### interesting packages    

    joystick evtest inputattach

