clhepheader             := clhepheader
ALL_TOOLS      += clhepheader
clhepheader_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/clhep/2.1.1.0-cms2/include
clhepheader_EX_INCLUDE  := $(clhepheader_LOC_INCLUDE)
clhepheader_INIT_FUNC := $$(eval $$(call ProductCommonVars,clhepheader,,,clhepheader))

