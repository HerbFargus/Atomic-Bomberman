;*****************************************************************************
;
; Author:		Kurt W. Dekker
; Started:		02/03/97 @ 16:13
; Updated:		07/02/97
; Filename:		soundlist.res
;
; Description:	Sound list file for Atomic Bomberman.
;
; These files all should have a .rss extension and be raw 22khz Stereo 16bit
; signed, Intel-endian.
; NOTE: NEW DESIGNED BY DOMINIK HAUMANN
;*****************************************************************************
;
[SND_MENU_EXIT]
menuexit.ogg

[SND_MENU_MOVE]
letter1.ogg
letter2.ogg

; some kind of "you can't do that here" sound
[SND_NOT_ALLOWED]
enrt1.ogg
enrt2.ogg

; dropping a bomb sounds
[SND_BOMB_DROP]
bmdrop2.ogg
bmdrop3.ogg
; die nächste Zeile war ausgeklammert -- ich lasse sie so!
;bmdrop1.ogg

; kicking a bomb sounds
[SND_BOMB_KICK]
kbomb1.ogg
kbomb2.ogg
kicker3.ogg
kicker10.ogg

; stopping a bomb
[SND_BOMB_STOP]
bombstop.ogg
bmbstop1.ogg
bmbstop2.ogg

; jelly bomb bouncing
[SND_JELLY_BOUNCING]
bombboun.ogg
1017.ogg
1036.ogg

; (obsolete: 139 is last jelly boing sound)

; a solid tile slamming in place (after "hurry" is displayed)
; NOTE! the code is HARD-CODED to play one of the three below randomly.
; if you add more sounds below 142, they will not be used!!!
[SND_HURRY_BRICK]
clikplat.ogg
sqrdrop2.ogg
sqrdrop4.ogg
sqrdrop5.ogg
sqrdrop6.ogg
sqrdrop7.ogg
sqrdrop8.ogg

; punching a bomb
[SND_BOMB_PUNCH]
kbomb1.ogg
kbomb2.ogg

; a punched/grabbed bomb bouncing along
[SND_BOMB_BOUNCING]
bmdrop3.ogg

; when you grab a bomb
[SND_BOMB_GRAB]
grab1.ogg
grab2.ogg
bmbthrw1.ogg
bmbthrw3.ogg
bmbthrw4.ogg
bmbthrw5.ogg

; bomb explosion sounds
[SND_BOMB_EXPLOSION]
expl6.ogg
explo1.ogg
explode2.ogg
explode3.ogg
explode4.ogg
bomb_01.ogg
bomb_02.ogg
bomb_04.ogg
bomb_04b.ogg
bomb_05.ogg
bomb_06.ogg
bomb_07.ogg
bomb_07b.ogg
bomb_09.ogg
bomb_11.ogg
bomb_12.ogg
bomb_12b.ogg
bomb_17.ogg
bomb_19.ogg
bomb_24.ogg
; (obsolete!299 is the last exploding bomb sound...)

; you die in flames sounds
[SND_DIE]
scream1.ogg
die1.ogg

; we have a winner of the match
[SND_MATCH_WIN]
proud.ogg
theman.ogg
youwin1.ogg

; death anim sounds BASED on which anim is chosen (this is just clunk-type
; sound effects to sync with the anim, no screams or anything);
[SND_BURNEDUP]
burnedup.ogg

; step on a trampoline
[SND_TRAMPOLINE]
1017.ogg
1036.ogg
1045.ogg
trampo.ogg

; you are stunned by a bomb landing on your head
[SND_BOMB_HIT]
360,bombhit1
361,bombhit2
362,bombhit3
363,bombhit4

; you get a powerup (a good one)
[SND_POWERUP] 
woohoo1.ogg
get1.ogg
get2.ogg
coolpop.ogg
allrite.ogg
schwing.ogg
1001.ogg
1006.ogg
1028.ogg
1041.ogg
1055.ogg
1059.ogg
1062.ogg
1074.ogg
zahpu1b.ogg
zahpu20b.ogg
zahpu20c.ogg
zahpu21b.ogg
zahpu2b.ogg
zahpu113.ogg
zahpu2c.ogg
pgapu10a.ogg
pgapu11b.ogg
pgapu16a.ogg
pgapu17a.ogg
pgapu18a.ogg
pgapu18b.ogg
pgapu19a.ogg
pgapu19b.ogg
pgapu1a.ogg
pgapu1b.ogg
pgapu1b1.ogg
pgapu20a.ogg
pgapu20b.ogg
pgapu21a.ogg
pgapu21b.ogg
pgapu22a.ogg
pgapu22b.ogg
pgapu2a.ogg
pgapu2b.ogg
pgapu3a.ogg
pgapu4a.ogg
pgapu4a1.ogg
pgapu4b.ogg
pgapu7a.ogg
pgapu7a1.ogg
pgapu8a.ogg
pgapu8b.ogg
pgapu9a.ogg
pupp29a.ogg
pupp29b.ogg
zahpu11a.ogg
zahpu16a.ogg
zahpu17a.ogg
zahpu17b.ogg
zahpu18a.ogg
zahpu1a.ogg
zahpu20a.ogg
zahpu21a.ogg
zahpu22a.ogg
zahpu2a.ogg
zahpu3a.ogg
zahpu5a.ogg
zahpu6a.ogg
zahpu7a.ogg
zahpu9a.ogg
zai13a.ogg
pu1.ogg
pu10.ogg
pu11.ogg
pu12.ogg
pu13.ogg
pu14.ogg
pu15.ogg
pu16.ogg
pu17.ogg
pu19.ogg
pu2.ogg
pu3.ogg
pu4.ogg
pu5.ogg
pu6.ogg
pu7.ogg
pu8.ogg
; (obsolete: 499 is the last standard "you get a powerup" sound)

; ploppy poop sounds
[SND_POOP]
poops1.ogg
poops2.ogg
poops3.ogg
poops4.ogg
poops5.ogg

; after a player death
[SND_DEATH_TAUNT]
cribrown.ogg
cul8r.ogg
gotahurt.ogg
gotcha.ogg
later.ogg
roasted.ogg
toeasy.ogg
youblow.ogg
eatdust.ogg
smelsmok.ogg
stupidio.ogg
suckitdn.ogg
tastpain.ogg
tastpai2.ogg
cribrown.ogg
jdd12.ogg
jdd11.ogg
jdd16.ogg
jdd18.ogg
jdd19.ogg
jdd25.ogg
jdd3.ogg
jdd37.ogg
add63c.ogg
add64a.ogg
add64c.ogg
add65a.ogg
add65b.ogg
add65c.ogg
add66a.ogg
add66b.ogg
add66c.ogg
add67a.ogg
jdd4.ogg
jdd41.ogg
jdd58.ogg
add26a.ogg
add26b.ogg
add26c.ogg
add27c.ogg
add29a.ogg
add2a.ogg
add2b.ogg
add2bb.ogg
add2c.ogg
add30a.ogg
add30b.ogg
add30c.ogg
add31a.ogg
add31b.ogg
add32a.ogg
add33a.ogg
add33b.ogg
add34c.ogg
add37a.ogg
add37b.ogg
add38a.ogg
add38b.ogg
add38c.ogg
add3a.ogg
add3b.ogg
add3c.ogg
add40b.ogg
add40c.ogg
add41a.ogg
add41b.ogg
add41c.ogg
add42a.ogg
add43a.ogg
add43b.ogg
add45a.ogg
add47a.ogg
add47b.ogg
add47c.ogg
add48a.ogg
add48b.ogg
add48c.ogg
add4b.ogg
add50b.ogg
add50c.ogg
add51b.ogg
add51c.ogg
add52a.ogg
add52b.ogg
add52c.ogg
add53a.ogg
add53b.ogg
add54b.ogg
add54c.ogg
add56a.ogg
add56b.ogg
add58a.ogg
add58c.ogg
add59a.ogg
add5a.ogg
add5b.ogg
add5c.ogg
add60a.ogg
add60b.ogg
add60c.ogg
add61a.ogg
add62c.ogg
add63a.ogg
add63c.ogg
add64a.ogg
add64c.ogg
add65a.ogg
add65b.ogg
add65c.ogg
add66a.ogg
add66b.ogg
add66c.ogg
add67a.ogg
add67b.ogg
add67c.ogg
add70a.ogg
add70c.ogg
add71a.ogg
add71b.ogg
add71c.ogg
add72a.ogg
add73a.ogg
add74a.ogg
add74b.ogg
add75a.ogg
add75b.ogg
add76a.ogg
add76b.ogg
add76c.ogg
add77a.ogg
add78b.ogg
add7a.ogg
add8b.ogg
add9a.ogg
add9b.ogg
add9c.ogg
zaa11a.ogg
zaa11b.ogg
zaa11c.ogg
zaa12a.ogg
zaa12b.ogg
zaa12c.ogg
zaa12d.ogg
zaa13a.ogg
zaa15a.ogg
zaa16a.ogg
zaa16b.ogg
zaa18a.ogg
zaa18b.ogg
zaa19a.ogg
zaa19b.ogg
zaa19c.ogg
zaa1a.ogg
zaa1b.ogg
zaa1c.ogg
zaa22a.ogg
zaa22d.ogg
zaa22e.ogg
zaa23a.ogg
zaa23b.ogg
zaa24a.ogg
zaa24b.ogg
zaa24c.ogg
zaa24d.ogg
zaa25a.ogg
zaa25c.ogg
zaa27a.ogg
zaa27b.ogg
zaa27c.ogg
zaa29b.ogg
zaa2a.ogg
zaa2b.ogg
zaa2c.ogg
zaa30a.ogg
zaa30b.ogg
zaa30c.ogg
zaa31a.ogg
zaa31b.ogg
zaa32a.ogg
zaa32c.ogg
zaa33b.ogg
zaa33d.ogg
zaa34a.ogg
zaa34b.ogg
zaa34c.ogg
zaa35c.ogg
zaa37b.ogg
zaa38b.ogg
zaa38c.ogg
zaa39a.ogg
zaa39b.ogg
zaa39e.ogg
zaa3a.ogg
zaa3ab.ogg
zaa3ac.ogg
zaa3b.ogg
zaa3c.ogg
zaa40a.ogg
zaa40b.ogg
zaa40d.ogg
zaa41a.ogg
zaa41aa.ogg
zaa41c.ogg
zaa42a.ogg
zaa42b.ogg
zaa43a.ogg
zaa43b.ogg
zaa43c.ogg
zaa45b.ogg
zaa47d.ogg
zaa48a.ogg
zaa48c.ogg
zaa49a.ogg
zaa4a.ogg
zaa4b.ogg
zaa4c.ogg
zaa4d.ogg
zaa50c.ogg
zaa52a.ogg
zaa52b.ogg
zaa53b.ogg
zaa54b.ogg
zaa55a.ogg
zaa56c.ogg
zaa58a.ogg
zaa58b.ogg
zaa58c.ogg
zaa5a.ogg
zaa5b.ogg
zaa5g.ogg
zaa63b.ogg
zaa66a.ogg
zaa67a.ogg
zaa68a.ogg
zaa71a.ogg
zaa71b.ogg
zaa71c.ogg
zaa71d.ogg
zaa71e.ogg
zaa71f.ogg
zaa71g.ogg
zaa71h.ogg
zaa72a.ogg
zaa72c.ogg
zaa72d.ogg
zaa74c.ogg
zaa75b.ogg
zaa77a.ogg
zaa7b.ogg
zaa8a.ogg
zaa8b.ogg
zaa8c.ogg
zaa8d.ogg
zaa8e.ogg
zaa9a.ogg
jdd60.ogg
jdd61.ogg
jdd64.ogg
jdd65.ogg
jdd66.ogg
jdd67.ogg
jdd68.ogg
jdd7.ogg
jdd71.ogg
jdd72.ogg
add12a.ogg
add12b.ogg
add12c.ogg
add16a.ogg
add17b.ogg
add17a.ogg
add1a.ogg
add1b.ogg
add1c.ogg
add21c.ogg
add22a.ogg
add23c.ogg
add24b.ogg
add24c.ogg
add24a.ogg
add25a.ogg
add25b.ogg
; (obsolete: 999 is the last possible death taunt.)

; title page music
[SND_MUSIC_TITLE]
title.ogg

; main menu music
[SND_MUSIC_MENU_MAIN]
menu.ogg

; music for input selection
[SND_MUSIC_MENU_INPUT]
win.ogg

; game is over screen music
[SND_MUSIC_GAME_OVER]
lose.ogg

; join/start a network game
[SND_MUSIC_MENU_NETWORK]
network.ogg

; music for actual game play
; TODO: nicht klar, wies gemacht wird!!!!!!!!!
[SND_BACKGROUND_MUSIC]
grnacres.ogg
generic.ogg
hockey.ogg
pyramid.ogg
mineshft.ogg
battle.ogg
gieger.ogg
haunted.ogg
ocean.ogg
swamp.ogg
sewer.ogg

; (used for end of a game, generally)
; tie game/draw game
[SND_DRAW_GAME]
gump1.ogg
gen11a.ogg
gen11b.ogg
gen11c.ogg
zaa28a.ogg
zaa28b.ogg
zaa28c.ogg
zaa40a.ogg
zaa40b.ogg
zaa40c.ogg
zaa40d.ogg
zaa49a.ogg
zaa49b.ogg
zaa49c.ogg
zaa53a.ogg
zaa53b.ogg
zaa55a.ogg
zaa55b.ogg
zaa55c.ogg
zaa59a.ogg
zaa59b.ogg
zaa59c.ogg
zaa62a.ogg
zaa62c.ogg
zaa7a.ogg
zaa7b.ogg
zaa7c.ogg
zacm5a.ogg
zacm5b.ogg
zacm5c.ogg
zagotake.ogg
zai06a.ogg
zai11a.ogg
zai11b.ogg
zai11c.ogg
zai06b.ogg
zai06c.ogg
; 1999 is the last tie game/draw game sound

[SND_MUSIC_ENDOFGAME]
draw.ogg

; after laying out a HUGE string of bombs
[SND_ON_MANY_BOMBS]
clear.ogg
fireinh.ogg
lookout.ogg
litemup.ogg
runaway1.ogg
runaway2.ogg
dmb12a.ogg
dmb14a.ogg
dmb15a.ogg
dmb16a.ogg
dmb18a.ogg
dmb1a.ogg
dmb1b.ogg
dmb2a.ogg
dmb2b.ogg
dmb3a.ogg
dmb3b.ogg
dmb4a.ogg
dmb4a1.ogg
dmb4b.ogg
dmb5a.ogg
dmb5b.ogg
dmb6a.ogg
dmb6b.ogg
dmb7a.ogg
dmb8a.ogg
dmb8b.ogg
dmb9a.ogg
dmb9b.ogg
zae01a.ogg
zae02a.ogg
zae03a.ogg
zae04a.ogg
zae05a.ogg
zae06a.ogg
zae07a.ogg
zae08a.ogg
zae11a.ogg
zae12a.ogg
zae13a.ogg
zae14a.ogg
zafp13ab.ogg
jmb1.ogg
jmb11.ogg
jmb14.ogg
jmb2.ogg
jmb3.ogg
jmb4.ogg
jmb5.ogg
jmb6.ogg
zae01b.ogg
zae01c.ogg
zae01d.ogg
zae01e.ogg
zae02b.ogg
zae02c.ogg
zae03f.ogg
zae03e.ogg
zae03d.ogg
zae03c.ogg
zae03b.ogg
zae04c.ogg
zae05b.ogg
zae05c.ogg
zae06c.ogg
zae06b.ogg
zae07b.ogg
zae07c.ogg
zae08b.ogg
zae11b.ogg
zae11c.ogg
zae11d.ogg
zae12b.ogg
zae12c.ogg
zae13b.ogg
zae13c.ogg
zae14d.ogg
zae14c.ogg
zae14b.ogg
zae14e.ogg
; (obsolete: 1299 is last "huge string of bombs" sound value)

; periodic roulette "tick" sound
[SND_ROULETTE_TICK]
1041.ogg

; clapping people, happy sound
[SND_HANDS_CLAPPING]
1000.ogg

; buzzer sound, you got the molasses roulette powerup (powerdown)
[SND_BUZZER]
1049.ogg

; a warp-hole transfer sound
[SND_WARP_HOLE]
warp1.ogg
transin.ogg
transout.ogg

; you are now AWESOME (7th powerup and 3rd thereafter)
[SND_POWERUP_MANY]
pu1.ogg
pu2.ogg
pu3.ogg
backup.ogg
backup1.ogg
bringon.ogg
bringon.ogg
comeget.ogg
dabomb.ogg
elaugh1.ogg
feelpowr.ogg
ohyeah.ogg
packin.ogg
theman.ogg
whatrush.ogg
whodad.ogg
yeehaw.ogg
destu1.ogg
destu2.ogg
zen1.ogg
zen2.ogg
calldad.ogg
drabom.ogg
fillcrak.ogg
inzone.ogg
hitstrid.ogg
inzone.ogg
lovnit1.ogg
luvyap.ogg
playprop.ogg
serendip.ogg
shakeboo.ogg
wantmnky.ogg
wlktal1.ogg
wlktal2.ogg
wantmnky.ogg
jupp10a.ogg
jupp10b.ogg
jupp10c.ogg
jupp11.ogg
jupp12.ogg
eofm3a.ogg
eofm6a.ogg
eofm6c.ogg
pupp10a.ogg
pupp11a.ogg
pupp12a.ogg
pupp13a.ogg
pupp13b.ogg
pupp13c.ogg
pupp19b.ogg
pupp22a.ogg
pupp22b.ogg
pupp24a.ogg
pupp24c.ogg
pupp25a.ogg
pupp26a.ogg
pupp27a.ogg
pupp2a.ogg
pupp2b.ogg
pupp2c.ogg
pupp31a.ogg
pupp31b.ogg
pupp32a.ogg
pupp32b.ogg
pupp34a.ogg
pupp35a.ogg
pupp35c.ogg
pupp36a.ogg
pupp36c.ogg
pupp37a.ogg
pupp37b.ogg
pupp37c.ogg
pupp38a.ogg
pupp39a.ogg
pupp3a.ogg
pupp3b.ogg
pupp42a.ogg
pupp4a.ogg
pupp4b.ogg
pupp5a.ogg
pupp5a1.ogg
pupp5b.ogg
pupp6a.ogg
pupp6b.ogg
pupp7b.ogg
pupp7c.ogg
pupp8a.ogg
pupp8b.ogg
pupp8c.ogg
sofm4a.ogg
sofm4b.ogg
sofm4c.ogg
zaa22e.ogg
zaa29b.ogg
zafp2a.ogg
zafp30a.ogg
zafp31a.ogg
zafp36a.ogg
zafp39a.ogg
zafp3a.ogg
zafp5a.ogg
zafp6a.ogg
zafp7a.ogg
zafp8a.ogg
zagotake.ogg
jupp13.ogg
jupp14.ogg
jupp2.ogg
jupp20.ogg
jupp21.ogg
jupp22.ogg
jupp25.ogg
jupp29.ogg
jupp3.ogg
jupp30.ogg
jupp31.ogg
jupp32.ogg
jupp33b.ogg
jupp39.ogg
jupp4.ogg
jupp6.ogg
jupp7.ogg
jupp8.ogg
jupp9.ogg
zafp27c.ogg
zafp2b.ogg
zafp2c.ogg
zafp30b.ogg
zafp34b1.ogg
zafp34c.ogg
zafp35d.ogg
zafp36b.ogg
zafp36c.ogg
zafp38b.ogg
zafp39b.ogg
zafp3b.ogg
zafp6b.ogg
zafp6c.ogg
zafp7c.ogg
zafp8c.ogg
zafp8d.ogg
zafp8e.ogg
zafp9b.ogg
; (obsolete: 1699 is the last AWESOME powerup sound...)

; these are the "we have a winner" sounds... we have a winner of the match
[SND_YOU_WIN]
proud.ogg
theman.ogg
youwin1.ogg
EOFM1A.ogg
EOFM1C.ogg
EOFM2C.ogg
EOFM2D.ogg
EOFM3A.ogg
EOFM3B.ogg
EOFM3C.ogg
EOFM3D.ogg
GEN4A.ogg
GEN4B.ogg
GEN4B2.ogg
GEN4C.ogg
ZAA15A.ogg
ZAA29A.ogg
ZAA29B.ogg
ZAA7A.ogg
ZAA7B.ogg
ZAA7C.ogg
ZAA8A.ogg
ZAA8B.ogg
ZAA8C.ogg
ZACM1A.ogg
ZACM1C.ogg
ZACM1D.ogg
ZACM2A.ogg
ZACM2B.ogg
ZACM2C.ogg
ZACM3A.ogg
ZACM3B.ogg
ZACM3C.ogg
JJFM1.ogg
JJFM2.ogg
JJFM3.ogg
ZAFP12C.ogg
; (obsolete: 2299 is the last "we have a winner" sound number.)

; generic (non-specific) disease sound
[SND_DISEASE]
pgad12b.ogg
pgad12c.ogg
pgad12d.ogg
pgad16a.ogg
pgad16b.ogg
pgad17b.ogg
pgad1a.ogg
pgad1b.ogg
pgad1c.ogg
pgad1c1.ogg
pgad20c.ogg
pgad21b.ogg
pgad22a.ogg
pgad22b.ogg
pgad22c.ogg
pgad25a.ogg
pgad25c.ogg
pgad2d.ogg
pgad2e.ogg
pgad2f.ogg
pgad3a.ogg
pgad3b.ogg
pgad3c.ogg
pgad3c1.ogg
pgad3d.ogg
pgad3e.ogg
pgad3g.ogg
pgad4a.ogg
pgad4b.ogg
pgad4c.ogg
pgad4d.ogg
pgad4e.ogg
pgad4f.ogg
pgad5a.ogg
pgad5b.ogg
pgad5c.ogg
pgad5d.ogg
pgad5e.ogg
pgad5f.ogg
pgad5g.ogg
pgad5h.ogg
pgad5i.ogg
pgad9a.ogg
pgad9b.ogg
zahd10a.ogg
zahd12a.ogg
zahd15a.ogg
zahd16a.ogg
zahd1a.ogg
zahd21a.ogg
zahd22a.ogg
zahd2a.ogg
zahd3a.ogg
zahd5a.ogg
zahd9a.ogg
jgad1.ogg
jgad10.ogg
jgad11.ogg
jgad12.ogg
jgad14.ogg
jgad15.ogg
jgad16.ogg
jgad2.ogg
jgad20.ogg
jgad21.ogg
jgad25.ogg
jgad3.ogg
jgad4.ogg
jgad8.ogg
jgad9.ogg
zahd12b.ogg
zahd12c.ogg
zahd12f.ogg
zahd14c.ogg
zahd15d.ogg
zahd15c.ogg
zahd15b.ogg
zahd16c.ogg
zahd16b.ogg
zahd22b.ogg
zahd22c.ogg
zahd22d.ogg
zahd2b.ogg
zahd2c.ogg
zahd3b.ogg
zahd5b.ogg
zahd5c.ogg
zahd8d.ogg
; (obsolete: 2599 is the last generic (non-specific) disease sound)

; exiting game (go outside and play now!
[SND_GAME_EXIT]
quitgame.ogg
eofm7a.ogg
eofm7b.ogg
eofm7c.ogg
eofm7d.ogg
eofm8a.ogg
eofm8b.ogg
eofm8c.ogg
eofm8d.ogg
eofm8e.ogg
eofm8f.ogg
eofm8g.ogg
gen9a.ogg
gen9b.ogg
gen9c.ogg
zaa38a.ogg
zaa38b.ogg
zaa38c.ogg
zaa3a.ogg
zaa3aa.ogg
zaa3ab.ogg
zaa3ac.ogg
zaa3b.ogg
zaa3c.ogg
zaa55a.ogg
zaa55b.ogg
zaa55c.ogg
zaa5a.ogg
zaa5b.ogg
zaa5c.ogg
zaa5d.ogg
zaa5e.ogg
zaa5f.ogg
zaa5g.ogg
zacm7a.ogg
zacm7b.ogg
zacm7c.ogg
zacm8a.ogg
zacm8aa.ogg
zacm8ab.ogg
zacm8ac.ogg
zacm8ad.ogg
zacm8ae.ogg
zacm8af.ogg
zacm8b.ogg
zacm8c.ogg
zai09a.ogg
zai09b.ogg
zai09c.ogg
; (obsolete: 2699 is the last "leaving the program" sound)

; plays when "hurry" flashes across the screen.
[SND_HURRY]
hurry.ogg
hurytuf.ogg
eofm5c.ogg
eofm5d.ogg
gen10a.ogg
gen10b.ogg
gen10c.ogg
gen12a.ogg
gen12b.ogg
gen12c.ogg
gen1a.ogg
gen1b.ogg
gen1c.ogg
gen2a.ogg
gen2b.ogg
gen2c.ogg
gen5a.ogg
gen5b.ogg
gen6a.ogg
gen6b.ogg
gen6c.ogg
zai01a.ogg
zai02a.ogg
zai05a.ogg
zai06a.ogg
zai12a.ogg
zai02c.ogg
zai02b.ogg
zai01f.ogg
zai01e.ogg
zai01d.ogg
zai01c.ogg
zai01b.ogg
zai06c.ogg
zai06b.ogg
zai05c.ogg
zai05b.ogg
zai12c.ogg
zai12b.ogg
; (obsolete: 2799 is last "hurry up!" sound)

; title intro statement "ATOMIC BOMBERMAN!"
[SND_TITLE_INTRO]
gen8a.ogg
gen8b.ogg
gen8c.ogg
gen8c2.ogg
zai08a.ogg
zai08b.ogg
zai08c.ogg
zai08d.ogg
zai08e.ogg
zai08f.ogg
zai08g.ogg
; (obsolete: 2899 is the last intro "Atomic Bomberman!" sound)

; (obsolete: 2900,0 ;; dummy value; do not take this out!)

; specific sounds for each disease type
; molasses
[SND_DISEASE_MOLASSES]
disease1.ogg
molases.ogg
ohno1.ogg

; crack
[SND_DISEASE_CRACK]
disease2.ogg
disease2.ogg
dis12a.ogg
dis12b.ogg
dis12c.ogg
dis12d.ogg
dis5a.ogg
dis5b.ogg
dis5c.ogg
pgapu11a.ogg
pgapu11b.ogg
pgapu12a.ogg
pgapu12b.ogg
pgapu13a.ogg
pgapu13b.ogg
pgapu15a.ogg
pgapu15b.ogg
zad05d.ogg
zad05e.ogg
zad12a.ogg
zahpu111.ogg
zahpu11a.ogg
zahpu13a.ogg
zahpu15a.ogg
zad12b.ogg
zad12c.ogg
zad12d.ogg
zad12e.ogg
zad12f.ogg
zahpu11b.ogg
zahpu12b.ogg
zahpu12c.ogg
zahpu13b.ogg
zahpu13c.ogg
zahpu15b.ogg
zahpu15c.ogg

; constipation
[SND_DISEASE_CONSTIPATION]
disease3.ogg
dis4a.ogg
dis4b.ogg
dis4c.ogg

; poops
[SND_DISEASE_POOPS]
dis2a.ogg
dis2b.ogg
dis2c.ogg
pgad18b.ogg
pgad18c.ogg
zad02a.ogg
zad02b.ogg
zad02c.ogg
zahd18a.ogg
jgad18.ogg
jgad2.ogg
jgad8.ogg
jgad9.ogg
zahd18b.ogg
zahd18c.ogg
zahd18d.ogg
zahd18e.ogg

; short flame
[SND_DISEASE_SHORTFLAME]
disease1.ogg
ewtahh.ogg
dis3a.ogg
dis3b.ogg
dis3c.ogg
zad03a.ogg
zad03b.ogg
zad03c.ogg

; crack poops
[SND_DISEASE_CRACKPOOPS]
ewtahh.ogg
dis13a.ogg
dis13b.ogg
dis13c.ogg
zad13a.ogg
zad13b.ogg

; short fuze
[SND_DISEASE_SHORTFUZE]
disease2.ogg
2mucpain.ogg
dis6a.ogg
dis6b.ogg
dis6c.ogg
zad06a.ogg
zad06b.ogg

; swap 2 players
[SND_DISEASE_SWAP]
disease3.ogg
ohhhh.ogg
dis16a.ogg
dis16b.ogg
zad16a.ogg
zad16b.ogg
zad16c.ogg

; controls reversed
[SND_DISEASE_REVERSED]
disease1.ogg
dis8a.ogg
dis8b.ogg
dis8c.ogg
zad08a.ogg
zad08aa.ogg
zad08b.ogg
zad08c.ogg
zad08d.ogg
zad09d.ogg
zad09f.ogg

; leprosy
[SND_DISEASE_LEPROSY]
disease2.ogg

; invisible
[SND_DISEASE_INVISIBLE]
disease3.ogg

; duds
[SND_DISEASE_DUDS]
disease1.ogg

; what we play when we're doing net play on minimum install.
; Hä? Die Datei generic.ogg gibts nicht!!!!
[???] we do not use this at the moment
generic.ogg
