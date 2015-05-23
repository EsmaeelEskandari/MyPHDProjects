roofitcore             := roofitcore
ALL_TOOLS      += roofitcore
roofitcore_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/lcg/roofit/5.34.04-cms2/include
roofitcore_EX_INCLUDE  := $(roofitcore_LOC_INCLUDE)
roofitcore_LOC_LIB := RooFitCore
roofitcore_EX_LIB  := $(roofitcore_LOC_LIB)
roofitcore_LOC_USE := rootcore roothistmatrix rootgpad rootminuit
roofitcore_EX_USE  := $(roofitcore_LOC_USE)
roofitcore_INIT_FUNC := $$(eval $$(call ProductCommonVars,roofitcore,,,roofitcore))

