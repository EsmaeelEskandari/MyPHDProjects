dcap             := dcap
ALL_TOOLS      += dcap
dcap_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/dcap/2.47.5.0/include
dcap_EX_INCLUDE  := $(dcap_LOC_INCLUDE)
dcap_LOC_LIB := dcap
dcap_EX_LIB  := $(dcap_LOC_LIB)
dcap_INIT_FUNC := $$(eval $$(call ProductCommonVars,dcap,,,dcap))

