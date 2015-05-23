castor_header             := castor_header
ALL_TOOLS      += castor_header
castor_header_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/castor/2.1.13.6-cms/include /public/V_CMSSW64/slc5_amd64_gcc472/external/castor/2.1.13.6-cms/include/shift
castor_header_EX_INCLUDE  := $(castor_header_LOC_INCLUDE)
castor_header_INIT_FUNC := $$(eval $$(call ProductCommonVars,castor_header,,,castor_header))

