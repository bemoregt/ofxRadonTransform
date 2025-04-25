# addon name
meta:
	ADDON_NAME = ofxRadonTransform
	ADDON_DESCRIPTION = Radon Transform (Sinogram) addon for OpenFrameworks
	ADDON_AUTHOR = bemoregt
	ADDON_TAGS = "image processing" "radon transform" "sinogram" "computer vision"
	ADDON_URL = https://github.com/bemoregt/ofxRadonTransform

common:
	# dependencies
	ADDON_DEPENDENCIES = ofxCv ofxOpenCv ofxGui
	
	# include search paths
	ADDON_INCLUDES = src
	
	# source search paths
	ADDON_SOURCES = src/ofxRadonTransform.cpp
	ADDON_SOURCES += src/ofxRadonTransform.h
	
	# exclude sources
	# ADDON_SOURCES_EXCLUDE = 
	
	# header search paths
	# ADDON_HEADER_SEARCH_PATHS =
	
	# frameworks to add
	# ADDON_FRAMEWORKS =
