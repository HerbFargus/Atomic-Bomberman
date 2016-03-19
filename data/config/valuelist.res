// v0.9 by gm (created and maintained)
; Modify at your own risk!

; default = 1024
VAL_RES_W 1024

; default = 768
VAL_RES_H 768


; default = 64
VAL_CELL_W 64

; default = 58
VAL_CELL_H 58


; default = 32
VAL_FIELD_OFFSET_X 32

; default = 103
VAL_FIELD_OFFSET_Y 103


; default = 20
VAL_SHOVE_W 20

; default = 18
VAL_SHOVE_H 18


; default = 15
VAL_FIELD_WIDTH 15

; default = 11
VAL_FIELD_HEIGHT 11


; TODO: determine by files!
VAL_MAX_MAPS 11


; default = 10
VAL_MAX_PLAYERS 10

;----------------------------------------------------------------------------------------------------------------
; some default values (customized in options.cfg)

; number of wins / kill to win a match
; default = 3
VAL_NUM_TO_WIN_MATCH 3

; 1: VAL_NUM_TO_WIN_MATCH means the wins
; 0: VAL_NUM_TO_WIN_MATCH means the kills
; default = 1
VAL_WIN_ON_WINS 1

; 0..3: how deep should the "Hurry" go into the field
; 0: no hurry
; 3: all the way
; default = 3
VAL_ENCLOSEMENT_DEPTH 3

; HURRY:
; TODO: doc
VAL_STOMPED_BOMBS_DETONATE 1

; 1: teamplay enabled
; default = 0
VAL_TEAMPLAY 0

; 1: play music during game
; default = 1
VAL_GAME_MUSIC 1

; 1: play music in menus
; default = 1
VAL_MENU_MUSIC 1

; number of the default map
; default = 0
VAL_MAP 0

; maximum time of a round
; -1: infinite
; default = 150
; 4 options? 100, 150, 250, -1 (TODO)
VAL_ROUNDTIME 150

; fullscreen enabled
; default = 1
VAL_FULLSCREEN 1

; TODO: doc
; default = 1
VAL_PLAYER_RANDOM_START 1

; TODO: doc
VAL_GOLDBOMBERMAN 0

; TODO: doc
VAL_CONVEYOR_SPEED 1

; TODO: doc
VAL_LOST_NET_REVERT_AI 0

;----------------------------------------------------------------------------------------------------------------

; default = 5 seconds
VAL_INTRO_TIME_LOGO 5

; default = 20 seconds
VAL_INTRO_TIME_TITLE 20

;----------------------------------------------------------------------------------------------------------------

; player's base speed
; 145 pixel / seconed fits to the original AB
VAL_PLAYER_SPEED 290        ;145                   TODO: Werte überprüfen

; 25 pixel / second fits to the original AB
VAL_PLAYER_SPEED_ADD 50      ;25

VAL_PLAYER_SPEED_MOLASSES 100

; TODO: Werte
VAL_PLAYER_SPEED_CRACK 400
VAL_PLAYER_SPEED_CRACK_ADD 200

; ???? TODO
;300,1000	; how fast does a kicked bomb move?  (1000 is nice)		; PGT
;301,1300	; how fast does a punched bomb move? (1300 is nice)		; PGT
; ???
VAL_BOMB_ROLL_SPEED 250

VAL_BOMB_PUNCH_SPEED 300

;-----------------------------------------------------------------------------------------------------------------

VAL_MAINMENU_FONT_COLOR_R 255
VAL_MAINMENU_FONT_COLOR_G 255
VAL_MAINMENU_FONT_COLOR_B 255

; default = 250 ms
VAL_MENU_KEYREPEAT_DELAY 250

; default = 100 ms
VAL_MENU_KEYREPEAT_INTERVAL 100

; double click time for the spooger powerup
; default = 100 ms (???)
VAL_DOUBLECLICK_TIME 100

;----------------------------------------------------------------------------------------------------------------

; default = 2000 ms
VAL_FUZE_TIME_NORMAL 2000

; default = 1000 ms    (TODO: check)
VAL_FUZE_TIME_SHORT 1000

;;;;; dud bomb ;;;;;;;;;;;;;;;;;

; default = 6000 ms
VAL_FUZE_TIME_DUD_MIN 6000

; default = 10000 ms
VAL_FUZE_TIME_DUD_ADD 10000


;; todo

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; 25 ms seems to be nice (or 20?)
VAL_TIME_FLAME_TRIGGER 20

; default = 500 ms
VAL_TIME_FLAME 500

; default = 500 ms
VAL_TIME_BRICK_DISINTEGRATE 500

; default = 1000 ms
VAL_TIME_SURVIVE_TILL_WIN 1000

; default = 150 ms                ; TODO: wenn zu hoch (> 95 = 10,5 Frames / sec), dann kann der Spieler in Bricks laufen, wenn das Spiel beginnt.
VAL_MAX_TIME_PER_FRAME 95

; default = 2000 ms
VAL_TEAMPLAY_TIME_TRUECOLORS 2000

; default = 0, 1: show a little thumbnail of the powerup in the breakable brick
VAL_SHOW_POWERUPS_IN_BRICKS 1

; default = 0, 1: players won't die in own flames (semi god mode)
VAL_SUICIDE_IMPOSSIBLE 0

; (???)
VAL_FIREINTHEHOLE_TIME 1000
VAL_FIREINTHEHOLE_BOMBS 5


;----------------------------------------------------------------------------------------------------------------
; Powerup Management (begin):

; 0: if a player gets a powerup but the number of this powerup exceeds the VAL_PU_MAX_... value
;    the powerup will be thrown onto the field again after some time (VAL_TIME_POWERUP_RECYCLE)
; 1: the player keeps the powerup and gives it not back to field until he dies.
; default = 1 (???)
VAL_PLAYER_KEEPS_ADDITIONAL_PUS 0

; how many seconds does the powerup recycler wait until he put the powerup back onto the field
; default = 3 s (???)
VAL_TIME_POWERUP_RECYCLE 3

; if a flame hits a powerup...
; 1: it will be lost forever (in current round)
; 0: it will be recycled
; default = 0
VAL_POWERUPS_DESTROYABLE 0

; if a flame hits a disease...
; 1: it will be lost forever (in the round)
; 0: it will be recycled
; default = 1
VAL_DISEASES_DESTROYABLE 1

;; will a disease "recycle" like other powerups when it comes out of you?     ??? einbauen???
;; gbl_diseases_will_recycle;
;; zur Zeit ist es aktiv!!!
;;122,0		

; after a player's death he gives his powerups back to field
; 1: if there are any breakable cells the powerups are distributed there
; 0: the powerups will be put on blank field cells
; default = 0
VAL_TRY_HIDING_DEAD_PLAYER_PUS 0

; some powerups excludes some others (e. g. Jelly and Trigger)
; example: if a player gets Trigger he must return Jelly to the field
; 1: if there are any breakable cells the powerups are distributed there
; 0: the powerups will be put on blank field cells
; default = 0
VAL_TRY_HIDING_EXCLUSION_PUS 0


; like VAL_TRY_HIDING_DEAD_PLAYER_PUS but for powerups that are recycled for another reason
; than the death of a player (powerups that were destroyed by flames, if VAL_PLAYER_KEEPS_ADDITIONAL_PUS == 0)
; default = 1
VAL_TRY_HIDING_OTHER_RECYCLED_PUS 1


; end (Powerup Management)
;----------------------------------------------------------------------------------------------------------------


; number of powerups that the player get at the beginning of every round
; may be overridden by current scheme

; default = 1
VAL_PU_INIT_BOMB 3

; default = 2
VAL_PU_INIT_FLAME 2

; default = 0
VAL_PU_INIT_DISEASE 0
VAL_PU_INIT_ABILITY_KICK 0
VAL_PU_INIT_EXTRA_SPEED 0
VAL_PU_INIT_ABLITY_PUNCH 0
VAL_PU_INIT_ABILITY_GRAB 0
VAL_PU_INIT_SPOOGER 0
VAL_PU_INIT_GOLDFLAME 0
VAL_PU_INIT_TRIGGER 0
VAL_PU_INIT_JELLY 0
VAL_PU_INIT_EBOLA 0
VAL_PU_INIT_RANDOM 0

; the following are the LIMITS as to how many of each powerup a player
; can accumulate.
; if the number is zero (0), there is no limit to how many you can accumulate.

; default = 8
VAL_PU_MAX_BOMB 8

; default = 8
VAL_PU_MAX_FLAME 8

; not used...
VAL_PU_MAX_DISEASE 0

VAL_PU_MAX_ABILITY_KICK 1
VAL_PU_MAX_EXTRA_SPEED 4
VAL_PU_MAX_ABILITY_PUNCH 1
VAL_PU_MAX_ABILITY_GRAB 1
VAL_PU_MAX_SPOOGER 1
VAL_PU_MAX_GOLDFLAME 1
VAL_PU_MAX_TRIGGER 1
VAL_PU_MAX_JELLY 1

; not used...
VAL_PU_MAX_EBOLA 0

; not used...
VAL_PU_MAX_RANDOM 0

; for runtime error detection
VAL_PU_MAX_LAST -2000


;; these are how many of each type of powerup appear on a level
;; a negative number here indicates how many times we'll do a 1-in-10 chance
;; of putting the powerup down (high absolute value = high probability)

; default = 10
VAL_PU_FIELD_BOMB 10

; default = 10
VAL_PU_FIELD_FLAME 10

; default = 3
VAL_PU_FIELD_DISEASE 10

; default = 4
VAL_PU_FIELD_ABILITY_KICK 4

; default = 8
VAL_PU_FIELD_EXTRA_SPEED 8

; default = 2
VAL_PU_FIELD_ABLITY_PUNCH 2

; default = 2
VAL_PU_FIELD_ABILITY_GRAB 2

; default = 1
VAL_PU_FIELD_SPOOGER 1

; default = -2
VAL_PU_FIELD_GOLDFLAME -2

; default = -4
VAL_PU_FIELD_TRIGGER 5

; default = 1
VAL_PU_FIELD_JELLY 1

; default = -4
VAL_PU_FIELD_EBOLA -4

; default = -2
VAL_PU_FIELD_RANDOM -2


;----------------------------------------------------------------------------------------------------------------

; stuff about diseases (default settings)

; does a disease "wear off" after some amount of time?
; default = 1 (or 0 if VAL_DSE_MULTIPLY == 0)
VAL_DSE_TIME_LIMITED 1

; does a disease multiply when spread, or just "hand off"?
; default = 1 (or 0 if VAL_DSE_TIME_LIMITED == 0)
VAL_DSE_MULTIPLY 1

; minimum time to "have" a disease before it can be passed again (to prevent
; random passing multiple times upon single contact).  (disease_freshness)
; default = 10 (ms, frames, s???) 10 / 20fps = 0.5 s = 500 ms
VAL_DSE_MIN_KEEP_BEFORE_PASS 500

; does acquiring a fresh powerup (or another disease) "cure" you of the previous disease?
; default = 1
VAL_DSE_ARE_CUREABLE 1

; here's what the chances are that a disease gets cured when you get a new
; powerup (larger numbers are a slimmer chance; it is 1 in N)
; default = 10        (300 / 20 fps)
VAL_DSE_CURE_CHANCE 10

; how long each type of disease lasts
; in seconds; default = 15
VAL_DSE_TIME_MOLASSES 15
VAL_DSE_TIME_CRACK 15
VAL_DSE_TIME_CONSTIPATION 15
VAL_DSE_TIME_POOPS 15
VAL_DSE_TIME_SHORTFLAME 15
VAL_DSE_TIME_CRACKPOOPS 15
VAL_DSE_TIME_SHORTFUZE 15
VAL_DSE_TIME_SWAP 0
VAL_DSE_TIME_REVERSED 15
VAL_DSE_TIME_LEPROSY 15
VAL_DSE_TIME_INVISIBLE 15
VAL_DSE_TIME_DUDS 15
VAL_DSE_TIME_HYPERSWAP 0

; probability to a specific disease if take a disease "powerup"
; the values represent the probability ratio: 10 : 10 : 10 : ...
; default = 10
VAL_DSE_PROB_MOLASSES 10
VAL_DSE_PROB_CRACK 10
VAL_DSE_PROB_CONSTIPATION 10
VAL_DSE_PROB_POOPS 10
VAL_DSE_PROB_SHORTFLAME 10
VAL_DSE_PROB_CRACKPOOPS 10
VAL_DSE_PROB_SHORTFUZE 10
VAL_DSE_PROB_SWAP 10
VAL_DSE_PROB_REVERSED 10
VAL_DSE_PROB_LEPROSY 10
VAL_DSE_PROB_INVISIBLE 10
VAL_DSE_PROB_DUDS 10
VAL_DSE_PROB_HYPERSWAP 10

;----------------------------------------------------------------------------------------------------------------

; white
VAL_COLOR_PLAYER_0R 255
VAL_COLOR_PLAYER_0G 255
VAL_COLOR_PLAYER_0B 255

; black
VAL_COLOR_PLAYER_1R 50
VAL_COLOR_PLAYER_1G 50
VAL_COLOR_PLAYER_1B 50

; red
VAL_COLOR_PLAYER_2R 255
VAL_COLOR_PLAYER_2G 0
VAL_COLOR_PLAYER_2B 0

; blue
VAL_COLOR_PLAYER_3R 0
VAL_COLOR_PLAYER_3G 0
VAL_COLOR_PLAYER_3B 255

; green
VAL_COLOR_PLAYER_4R 0
VAL_COLOR_PLAYER_4G 255
VAL_COLOR_PLAYER_4B 0

; yellow
VAL_COLOR_PLAYER_5R 255
VAL_COLOR_PLAYER_5G 255
VAL_COLOR_PLAYER_5B 0

; cyan
VAL_COLOR_PLAYER_6R 0
VAL_COLOR_PLAYER_6G 255
VAL_COLOR_PLAYER_6B 255

; magenta
VAL_COLOR_PLAYER_7R 255
VAL_COLOR_PLAYER_7G 0
VAL_COLOR_PLAYER_7B 255

; orange
VAL_COLOR_PLAYER_8R 255
VAL_COLOR_PLAYER_8G 128
VAL_COLOR_PLAYER_8B 0

; purple
VAL_COLOR_PLAYER_9R 128
VAL_COLOR_PLAYER_9G 0
VAL_COLOR_PLAYER_9B 255



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; MINIMUM number of seconds to wait at screens so that other computers
; can catch up (does not affect non-net games)
; 13,3




; what are the chances of issuing a post-death taunt ("this is too easy")
;95,5

; the length (in seconds) of a default combat game
;100,150		; 150 is a nice value

; the time remaining when the "hurry" message first flashes
; it is NOT RECOMMENDED that you modify this value!  A lot of strange
; things will happen if you set it to "non standard" values.  Leaving it
; at 60 should keep most of the program happy...
;101,60											; PGT

; how many pixels per reference frame does death anim #9 move upwards (the angel)?
;106,4




;; some bomb speeds...
;300,1000	; how fast does a kicked bomb move?  (1000 is nice)		; PGT
;301,1300	; how fast does a punched bomb move? (1300 is nice)		; PGT

;; minimum number of seconds between potential dud bombs
;320,180
;; additional random number of seconds between potential dud bombs
;321,180
;; chance of a dud bomb (1 in this number; bigger numbers are rarer; don't use zero!)
;322,3
;; how many frames of animation does a dud bomb wait (minimum)
;323,120 = 6
;; how many frames of animation does a dud bomb wait (random additional)
;324,200 = 10
;
;
;; which levels have regenerating tiles, and how many seconds between tile
;; regeneration attempts.  (zero means no regeneration)
;340,0
;341,0
;342,0
;343,0
;344,0
;345,0
;346,0
;347,4	; cemetary/mortuary
;348,0
;349,0
;350,0
;

;; these are the "ice delay" values (how much the controls are slowed by
;; the presence of ice on each level).  This is measured in milliseconds.
;449,0		; just to prevent invalid access in case the net screws up...
;450,0		; new traditionalist green acres		; PGT
;451,0		; classic green acres					; PGT
;452,250		; hockey rink							; PGT
;453,0		; ancient egypt							; PGT
;454,0		; coal mine								; PGT
;455,0		; beach									; PGT
;456,0		; aliens								; PGT
;457,0		; haunted house							; PGT
;458,0		; under the ocean						; PGT
;459,0		; deep forest green						; PGT
;460,0		; inner city trash						; PGT
;
;; this is the curve (upwards) of a bomb being picked up
;500,12,10
;502,25,20
;504,25,30
;506,12,40


; ; here are the default starting X,Y locations for each of the players
; ; (negative numbers wrap around from the right edge/bottom edge of the screen)
; 600,0,0
; 602,-1,-1
; 604,0,-1
; 606,-1,0
; 608,6,4
; 610,8,0
; 612,-3,4
; 614,2,-5
; 616,-5,-3
; 618,6,-1
; 
; ; for the many-dropped bomb powerup, this determines the chance (1 in N) of
; ; the "Clear" or "Fire In The Hole" type audio playing
; 650,4
; ; and this is what constitutes "many" dropped bombs
; 651,4
; 
; ; how high an "arc" does a punched bomb make?
; 660,65		; initial three-space punch bounces
; 661,20		; subsequent small 1-space punch bounces
; 
; 665,2		; how long do you "pause" when picking up a bomb?	; PGT
; 
; ; at each 0,0 intersection, what is the chances that a punched
; ; jelly bomb will change directions crazily?
; 667,3											; PGT
; 
; 670,1		; what's the minimum number of powers you lose when hit on the head?		; PGT
; 671,3		; what's the additional random number of powers you might lose?				; PGT
; 
; ; how many frames do you bounce on a trampoline?
; 680,30											; PGT
; 681,35		; how many pixels vertically do you move each frame?		; PGT
; 
; ; blink rate of the little bomber-dude cursor (base, random)
; 690,2,2
; 
; ; the "clear" cell radius that must exist around a potentially-regenerating
; ; tile spot.  Nobody can be within this radius.
; 695,4
; 
; ; how many different AI personalities are predefined?
; 900,1
; 
; ; how farahead does the fire-god (final closing-in bricks) tell the
; ; AIs that it is in itself a threat?
; 910,15
; 
; ; chance that an AI will execute the "blast bricks" routine
; 915,5
; 
; ; how close does a powerup have to be for an AI to go for it?
; 920,4
; 
; 
; ; how many seconds the twinkling of goldman lasts
; ; (zero will make it last indefinitely)
; 1010,5
; 
; ; how many milliseconds to wait before a critical packet is declared overdue
; ; and needs to be re-sent.
; ; this can be adjusted based on expected network latency.  if it is set too
; ; low then you will have many gratuitous retransmits and network performance
; ; will suffer.  if it is set too high then the potential lag between the
; ; games (due to missed packets) can become noticeable and affect game
; ; integrity/synchronization.
; 1100,200		; cancel - no net play.
; 1101,200		; IPX
; 1102,750		; modem
; 1103,400		; serial
; 1104,400		; TCP/IP
; 
; ; the following array enables/disables various levels in the RANDOM LEVEL
; ; selection (so that you can lock out some levels you Never want to play).
; 1150,1
; 1151,1
; 1152,0		; too annoying to have control delays!
; 1153,1
; 1154,1
; 1155,1
; 1156,0		; too hard to see visually!
; 1157,1
; 1158,1
; 1159,1
; 1160,1
; 1161,1



;;;;;;;;;;;;;;;;;;;;;;;;;;;;; done ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




; how many frames (standard rate) do you have to out-survive the other guy?
; ** this is only a nominal frame rate that is used as a reference for other
;    frame-count-based values in this file!  Do not change this value because
;    it will not improve your performance at all, and may cause other things
;    to malfunction!
;25,20											; PGT

; how many frames to cycle the regular flame animation
; OK; 10 = 0.5 seconds

; how many frames to cycle the brick disintegration animation
; OK; 10 = 0.5 seconds

; what is the maximum milliseconds the game can advance in any given
; "frame."  this prevents a disk hit from moving everybody a whole
; huge distance on the screen and screwing things up.
; OK; 31,150											; PGT

;; how many "standard" frames do we show true colors before switching over to
; show team colors (on team play only).
; OK 32,40 = 2 seconds

; some setup stuff for you:
; fuze length (frames)
; OK; 41,40											; PGT

;default starting speed (100ths of a pixel/frame)
; (???) (done); 42,923											; PGT

; how much extra speed (100ths of a pixel/frame) does a skate give you?
;90, (done) 150											; PGT
; how much speed the CLOGS (special roulette power-"down") take away
;91, (same as 90) 150											; PGT


; color remaping default values (RGB pairs, from 0 to 9 of the .RMP files)
; (done)
;200,100				; 0.RMP: white
;201,100
;202,100

;205,20				; 1.RMP: black
;206,20
;207,20
;
;210,100				; 2.RMP: red
;211,0
;212,0
;
;215,0				; 3.RMP: blue
;216,0
;217,100
;
;220,0				; 4.RMP: green
;221,100
;222,0
;
;225,100				; 5.RMP: yellow
;226,100
;227,0
;
;230,0				; 6.RMP: cyan
;231,100
;232,100
;
;235,100				; 7.RMP: magenta
;236,0
;237,100
;
;240,100				; 8.RMP: orange
;241,50
;242,0
;
;245,50				; 9.RMP: purple
;246,0
;247,100


;; these are how many of each type of powerup appear on a level
;; a negative number here indicates how many times we'll do a 1-in-10 chance
;; of putting the powerup down.
; (done)
;400,10	; bombs
;401,10	; flames
;402,3	; diseases
;403,4	; kickers
;404,8	; skates
;405,2	; punch
;406,2	; grab
;407,1	; spooge
;408,-2	; goldflame
;409,-4	; trigger bombs
;410,1	; jelly bombs
;411,-4	; super bad diseases
;412,-2	; random powerups
;

;; the following are the LIMITS as to how many of each powerup a player
;; can accumulate.  Make this too big and a lot of stuff starts to break...
;; if the number is zero (0), there is no limit to how many you can accumulate.
;; (done)
;550,8		; number of bombs									; PGT
;551,8		; flame length (cells beyond epicenter blast)		; PGT
;552,0		; disease (this is not used!!)						; PGT
;553,1		; kickers											; PGT
;554,4		; skates (speed powerups)							; PGT
;555,1		; punches (red glove)								; PGT
;556,1		; grabs (blue gloves)								; PGT
;557,1		; spooges											; PGT
;558,1		; goldflames										; PGT
;559,1		; trigger bombs										; PGT
;560,1		; jelly bombs										; PGT
;561,0		; super bad diseases( this is not used!!)			; PGT
;562,0		; randoms (this is not used!!)						; PGT
;563,0		; not used yet										; PGT
;564,0		; not used yet										; PGT