# All variables and paths must be defined on the command line when invoking the ofx addon template system
meta:
	ADDON_NAME = ofxRadonTransform
	ADDON_DESCRIPTION = Radon Transform (Sinogram) implementation for Openframeworks
	ADDON_AUTHOR = bemoregt
	ADDON_TAGS = "image processing" "computer vision" "radon transform" "sinogram"
	ADDON_URL = https://github.com/bemoregt/ofxRadonTransform

common:
	# dependencies with other addons, a list of them separated by spaces 
	ADDON_DEPENDENCIES = ofxCv ofxGui ofxOpenCv
	
	# include search paths, this will be usually parsed from the file system
	# but if the addon or addon libraries need special search paths they can be
	# specified here separated by spaces or one per line using +=
	ADDON_INCLUDES = src
	
	# any special flag that should be passed to the compiler when using this
	# addon
	ADDON_CFLAGS = 
	
	# any special flag that should be passed to the linker when using this
	# addon, also used for system libraries with -lname
	ADDON_LDFLAGS = 
	
	# linux only, any library that should be included in the project using
	# pkg-config
	ADDON_PKG_CONFIG_LIBRARIES = 
	
	# osx/iOS only, any framework that should be included in the project
	ADDON_FRAMEWORKS =
	
	# source files, these will be usually parsed from the file system looking
	# in the src folders in libs and the root of the addon. if your addon needs
	# to include files in different places or a different set of files per platform
	# they can be specified here
	ADDON_SOURCES = src/ofxRadonTransform.cpp
	
	# some addons need resources to be copied to the bin/data folder of the project
	# specify here any files that need to be copied, you can also use wildcards like
	# images/*.png
	ADDON_DATA = 
	
	# when parsing the file system looking for libraries exclude this for all or
	# a specific platform
	ADDON_LIBS_EXCLUDE =
