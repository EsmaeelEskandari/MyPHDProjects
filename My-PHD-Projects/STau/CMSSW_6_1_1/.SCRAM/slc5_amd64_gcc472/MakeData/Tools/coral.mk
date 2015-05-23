coral             := coral
ALL_TOOLS      += coral
ALL_SCRAM_PROJECTS += coral
coral_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/cms/coral/CORAL_2_3_21-cms10/include/LCG
coral_EX_INCLUDE  := $(coral_LOC_INCLUDE)
coral_INIT_FUNC := $$(eval $$(call ProductCommonVars,coral,,98000,coral))

