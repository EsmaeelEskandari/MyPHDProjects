libxml2             := libxml2
ALL_TOOLS      += libxml2
libxml2_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/libxml2/2.7.7/include/libxml2
libxml2_EX_INCLUDE  := $(libxml2_LOC_INCLUDE)
libxml2_LOC_LIB := xml2
libxml2_EX_LIB  := $(libxml2_LOC_LIB)
libxml2_INIT_FUNC := $$(eval $$(call ProductCommonVars,libxml2,,,libxml2))

