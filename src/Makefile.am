# updated by Gregor Mitsch <gregormitsch@gmx.de>

bin_PROGRAMS = ab

ab_SOURCES = main.cpp animmng.cpp animmng.h cell.cpp cell.h cellblank.cpp cellblank.h cellbomb.cpp cellbomb.h cellbreakable.cpp cellbreakable.h cellextra.cpp cellextra.h cellflame.cpp cellflame.h cellpowerup.cpp cellpowerup.h cellsolid.cpp cellsolid.h listreader.cpp listreader.h defines.h diseases.cpp diseases.h enumblocks.h enumdiseases.h enumfieldextras.h enumkeys.h enummainmenuchoice.h enumoptions.h enumpowerups.h enumvalues.h field.cpp field.h fieldextras.cpp fieldextras.h filefinder.cpp filefinder.h gameinfo.cpp gameinfo.h globals.cpp globals.h guicon.cpp guicon.h imagelist.cpp imagelist.h input.cpp input.h inputai.cpp inputai.h inputjoystick.cpp inputjoystick.h inputkeyboard.cpp inputkeyboard.h inputmanager.cpp inputmanager.h inputmouse.cpp inputmouse.h inputnet.cpp inputnet.h inputupdate.cpp inputupdate.h keyconfig.cpp keyconfig.h mainconfig.cpp mainconfig.h nameddatafile.cpp nameddatafile.h options.cpp options.h parser.cpp parser.h player.cpp player.h powerupdata.cpp powerupdata.h powerups.cpp powerups.h render.cpp render.h scheme.cpp scheme.h schememanager.cpp schememanager.h soundlist.cpp soundlist.h soundtotext.cpp soundtotext.h state.cpp state.h stateabout.cpp stateabout.h stateconfigurekeys.cpp stateconfigurekeys.h statedisplaygameresults.cpp statedisplaygameresults.h statedisplaywinner.cpp statedisplaywinner.h stateexit.cpp stateexit.h stategame.cpp stategame.h stateintro.cpp stateintro.h statemainmenu.cpp statemainmenu.h stateoptions.cpp stateoptions.h stateoutro.cpp stateoutro.h stateselectgame.cpp stateselectgame.h stateselectplayers.cpp stateselectplayers.h statetest.cpp statetest.h textmessages.cpp textmessages.h timer.cpp timer.h typedefs.h valuelist.cpp valuelist.h sound.cpp sound.h


if DISABLE_LIBSIGC
else
 ab_SOURCES += guibase.cpp guibase.h guibutton.cpp guibutton.h guicheckbox.cpp guicheckbox.h guicontainer.cpp guicontainer.h guienums.h guipushbutton.cpp guipushbutton.h guispinedit.cpp guispinedit.h guitextedit.cpp guitextedit.h guilistview.h guilistview.cpp
endif

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
# ab_CFLAGS = 
# ab_INCLUDES = -I"c:/MinGW/lib/sigc++/include"

# important: do NOT use ab_LDFLAGS. USE ab_LDADD
# It puts the -l stuff before the .o files in the g++ argument. The result is a linker failure.
ab_LDADD = -lSDL -lSDL_image -lSDL_sound -logg -lvorbis -lvorbisfile 

# ab_CFLAGS = /usr/include/sigc++-1.0

if IS_MINGW
 ab_LDADD += -lopengl32 
else
 ab_LDADD += -lGL 
endif

if DISABLE_LIBSIGC
else
  ab_LDADD += -lsigc 
endif

# ab_LDADD = libopengl32

