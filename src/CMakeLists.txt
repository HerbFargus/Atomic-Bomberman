set(SRC_BASE
	main.cpp
	animmng.cpp
	animmng.h
	cell.cpp
	cell.h
	cellblank.cpp
	cellblank.h
	cellbomb.cpp
	cellbomb.h
	cellbreakable.cpp
	cellbreakable.h
	cellextra.cpp
	cellextra.h
	cellflame.cpp
	cellflame.h
	cellpowerup.cpp
	cellpowerup.h
	cellsolid.cpp
	cellsolid.h
	listreader.cpp
	listreader.h
	defines.h
	diseases.cpp
	diseases.h
	enumblocks.h
	enumdiseases.h
	enumfieldextras.h
	enumkeys.h
	enummainmenuchoice.h
	enumoptions.h
	enumpowerups.h
	enumvalues.h
	field.cpp
	field.h
	fieldextras.cpp
	fieldextras.h
	filefinder.cpp
	filefinder.h
	gameinfo.cpp
	gameinfo.h
	globals.cpp
	globals.h
	guicon.cpp
	guicon.h
	imagelist.cpp
	imagelist.h
	input.cpp
	input.h
	inputai.cpp
	inputai.h
	inputjoystick.cpp
	inputjoystick.h
	inputkeyboard.cpp
	inputkeyboard.h
	inputmanager.cpp
	inputmanager.h
	inputmouse.cpp
	inputmouse.h
	inputnet.cpp
	inputnet.h
	inputupdate.cpp
	inputupdate.h
	keyconfig.cpp
	keyconfig.h
	mainconfig.cpp
	mainconfig.h
	nameddatafile.cpp
	nameddatafile.h
	options.cpp
	options.h
	parser.cpp
	parser.h
	player.cpp
	player.h
	powerupdata.cpp
	powerupdata.h
	powerups.cpp
	powerups.h
	render.cpp
	render.h
	scheme.cpp
	scheme.h
	schememanager.cpp
	schememanager.h
	soundlist.cpp
	soundlist.h
	soundtotext.cpp
	soundtotext.h
	state.cpp
	state.h
	stateabout.cpp
	stateabout.h
	stateconfigurekeys.cpp
	stateconfigurekeys.h
	statedisplaygameresults.cpp
	statedisplaygameresults.h
	statedisplaywinner.cpp
	statedisplaywinner.h
	stateexit.cpp
	stateexit.h
	stategame.cpp
	stategame.h
	stateintro.cpp
	stateintro.h
	statemainmenu.cpp
	statemainmenu.h
	stateoptions.cpp
	stateoptions.h
	stateoutro.cpp
	stateoutro.h
	stateselectgame.cpp
	stateselectgame.h
	stateselectplayers.cpp
	stateselectplayers.h
	statetest.cpp
	statetest.h
	textmessages.cpp
	textmessages.h
	timer.cpp
	timer.h
	typedefs.h
	valuelist.cpp
	valuelist.h
	sound.cpp
	sound.h
)

set(SRC_GUI
	guibase.cpp
	guibase.h
	guibutton.cpp
	guibutton.h
	guicheckbox.cpp
	guicheckbox.h
	guicontainer.cpp
	guicontainer.h
	guienums.h
	guipushbutton.cpp
	guipushbutton.h
	guispinedit.cpp
	guispinedit.h
	guitextedit.cpp
	guitextedit.h
	guilistview.h
	guilistview.cpp
)

add_executable(ab ${SRC_BASE} ${SRC_GUI})

add_dependencies(ab SDL_sound)
ExternalProject_Get_Property(SDL_sound prefix)

target_include_directories(ab PUBLIC ${prefix}/SDL_sound/include)
target_include_directories(ab PUBLIC ${SDL_INCLUDE_DIR})
target_include_directories(ab PUBLIC ${SDL_IMAGE_INCLUDE_DIRS})
target_include_directories(ab PUBLIC ${VORBISFILE_INCLUDE_DIRS})
target_include_directories(ab PUBLIC ${SIGC12_INCLUDE_DIRS})

target_link_libraries(ab ${prefix}/SDL_sound/lib/libSDL_sound.a)
target_link_libraries(ab ${SDL_LIBRARY})
target_link_libraries(ab ${SDLIMAGE_LIBRARY})
target_link_libraries(ab ${VORBISFILE_LIBRARIES})
target_link_libraries(ab ${SIGC12_LIBRARIES})
target_link_libraries(ab ${OPENGL_LIBRARIES})
