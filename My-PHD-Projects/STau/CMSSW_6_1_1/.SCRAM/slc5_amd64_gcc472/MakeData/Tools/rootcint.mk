rootcint             := rootcint
ALL_TOOLS      += rootcint
rootcint_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/lcg/root/5.34.03-cms4/cint
rootcint_EX_INCLUDE  := $(rootcint_LOC_INCLUDE)
rootcint_LOC_LIB := Core Cint
rootcint_EX_LIB  := $(rootcint_LOC_LIB)
rootcint_LOC_USE := root_interface sockets pcre zlib
rootcint_EX_USE  := $(rootcint_LOC_USE)
rootcint_INIT_FUNC := $$(eval $$(call ProductCommonVars,rootcint,,,rootcint))

