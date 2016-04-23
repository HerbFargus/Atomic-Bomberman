cmake_minimum_required(VERSION 2.8)
project(AtomicBomberman)

include(ExternalProject)
find_package(PkgConfig)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(VORBISFILE REQUIRED vorbisfile)
pkg_search_module(SIGC12 REQUIRED sigc++-1.2)

ExternalProject_Add(SDL_sound
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}
	DOWNLOAD_COMMAND hg clone -r stable-1.0 http://hg.icculus.org/icculus/SDL_sound/
	BUILD_IN_SOURCE 1
	CONFIGURE_COMMAND ./bootstrap
		COMMAND ./configure
			--disable-smpeg
			--disable-mikmod
			--disable-flac
			--prefix=${CMAKE_CURRENT_BINARY_DIR}/SDL_sound
	BUILD_COMMAND make
	INSTALL_COMMAND make install
)

add_subdirectory(src)
