meschach             := meschach
ALL_TOOLS      += meschach
meschach_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/meschach/1.2.pCMS1/include
meschach_EX_INCLUDE  := $(meschach_LOC_INCLUDE)
meschach_LOC_LIB := meschach
meschach_EX_LIB  := $(meschach_LOC_LIB)
meschach_INIT_FUNC := $$(eval $$(call ProductCommonVars,meschach,,,meschach))

