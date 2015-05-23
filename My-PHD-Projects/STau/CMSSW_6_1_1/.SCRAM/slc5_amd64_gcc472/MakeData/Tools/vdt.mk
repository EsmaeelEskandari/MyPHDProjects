vdt             := vdt
ALL_TOOLS      += vdt
vdt_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/cms/vdt/v0.2.3/include
vdt_EX_INCLUDE  := $(vdt_LOC_INCLUDE)
vdt_LOC_LIB := vdt
vdt_EX_LIB  := $(vdt_LOC_LIB)
vdt_INIT_FUNC := $$(eval $$(call ProductCommonVars,vdt,,,vdt))

