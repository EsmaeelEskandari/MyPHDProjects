qt             := qt
ALL_TOOLS      += qt
qt_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/qt/4.8.1/include/QtOpenGL /public/V_CMSSW64/slc5_amd64_gcc472/external/qt/4.8.1/include/QtGui
qt_EX_INCLUDE  := $(qt_LOC_INCLUDE)
qt_LOC_LIB := QtOpenGL QtGui
qt_EX_LIB  := $(qt_LOC_LIB)
qt_LOC_USE := qtbase qt3support x11 opengl
qt_EX_USE  := $(qt_LOC_USE)
qt_INIT_FUNC := $$(eval $$(call ProductCommonVars,qt,,,qt))

