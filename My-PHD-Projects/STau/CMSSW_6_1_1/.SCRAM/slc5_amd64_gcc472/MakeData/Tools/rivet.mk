rivet             := rivet
ALL_TOOLS      += rivet
rivet_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/rivet/1.8.1/include
rivet_EX_INCLUDE  := $(rivet_LOC_INCLUDE)
rivet_LOC_LIB := Rivet
rivet_EX_LIB  := $(rivet_LOC_LIB)
rivet_INIT_FUNC := $$(eval $$(call ProductCommonVars,rivet,,,rivet))

