root_interface             := root_interface
ALL_TOOLS      += root_interface
root_interface_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/lcg/root/5.34.03-cms4/include
root_interface_EX_INCLUDE  := $(root_interface_LOC_INCLUDE)
root_interface_INIT_FUNC := $$(eval $$(call ProductCommonVars,root_interface,,,root_interface))

