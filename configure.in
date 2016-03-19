dnl 2003-05-16 - by Gregor Mitsch <gregormitsch@gmx.de>
dnl Process this file with automake.
dnl configure.in for "AtomicBomberman Clone".

AC_INIT(./src/main.cpp)

AM_CONFIG_HEADER(config.h)

AM_INIT_AUTOMAKE(./src/main.cpp, 0.1)

AC_LANG_CPLUSPLUS
AC_PROG_CXX

dnl AM_PROG_LIBTOOL

dnl ---------------------------------------------------------------------
dnl Checks for libraries.
dnl ---------------------------------------------------------------------

dnl Does not work under Linux:
dnl dnl Check for SDL
dnl SDL_VERSION=1.2.0
dnl AM_PATH_SDL($SDL_VERSION,
dnl             :,
dnl  	     AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
dnl )
dnl CFLAGS="$CFLAGS $SDL_CFLAGS"
dnl LIBS="$LIBS $SDL_LIBS"
dnl 

dnl dnl configure option for win32 (deprecated - will be replaced soon):
dnl AC_ARG_ENABLE(win32,
dnl     [  --enable-win32       Operating System Type is Linux],
dnl     [case "${enableval}" in
dnl      yes) win32=true ;;
dnl      no)  win32=false ;;
dnl      *) AC_MSG_ERROR(bad value ${enableval} for --enable-win32) ;;
dnl     esac],[win32=false])
dnl AM_CONDITIONAL(WIN32, test x$win32 = xtrue)
dnl 
dnl echo "IS_WIN32 = $win32"


# Check to see if this `configure' is being run in the `Cygwin32' environment
AC_EGREP_CPP(yes,
[#ifdef __MINGW32__
 yes
 #endif
],is_mingw=yes, is_mingw=no)
echo "IS_MINGW = $is_mingw"
AM_CONDITIONAL(IS_MINGW, test "x$is_mingw" = "xyes")



dnl # Enable Sound?
dnl AC_ARG_ENABLE(sound,
dnl 
dnl     [  --enable-sound       Does AtomicBomberman should make any sounds?],
dnl     [case "${enableval}" in
dnl      yes) sound=true ;;
dnl      no)  sound=false ;;
dnl      *) AC_MSG_ERROR(bad value ${enableval} for --enable-sound) ;;
dnl     esac]
dnl     [AC_DEFINE([DISABLE_SOUND], [1], [Do not use Sounds.])],
dnl 
dnl     [sound=true])
dnl 
dnl echo "ENABLE_SOUND = $sound"
dnl AM_CONDITIONAL(DISABLE_SOUND, test x$sound = xfalse)


# Enable ligsigc?
AC_ARG_ENABLE(libsigc,

    [  --enable-libsigc       Compile with libsigc++],
    [case "${enableval}" in
     yes) libsigc=true ;;
     no)  libsigc=false ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-libsigc) ;;
    esac]
    [AC_DEFINE([DISABLE_LIBSIGC], [1], [Do not compile with libsigc++])],

    [libsigc=true])

echo "ENABLE_LIBSIGC = $libsigc"
AM_CONDITIONAL(DISABLE_LIBSIGC, test x$libsigc = xfalse)



AC_OUTPUT(Makefile src/Makefile)
