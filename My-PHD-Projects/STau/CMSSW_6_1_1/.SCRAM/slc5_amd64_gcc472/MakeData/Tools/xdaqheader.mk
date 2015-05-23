xdaqheader             := xdaqheader
ALL_TOOLS      += xdaqheader
xdaqheader_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/xdaq/VR17173-cms2/include
xdaqheader_EX_INCLUDE  := $(xdaqheader_LOC_INCLUDE)
xdaqheader_INIT_FUNC := $$(eval $$(call ProductCommonVars,xdaqheader,,,xdaqheader))

