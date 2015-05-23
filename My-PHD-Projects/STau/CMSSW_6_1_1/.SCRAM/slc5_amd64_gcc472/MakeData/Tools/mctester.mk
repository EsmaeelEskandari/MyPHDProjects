mctester             := mctester
ALL_TOOLS      += mctester
mctester_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/mctester/1.25.0a-cms7/include
mctester_EX_INCLUDE  := $(mctester_LOC_INCLUDE)
mctester_LOC_LIB := HEPEvent HepMCEvent MCTester
mctester_EX_LIB  := $(mctester_LOC_LIB)
mctester_LOC_USE := root hepmc
mctester_EX_USE  := $(mctester_LOC_USE)
mctester_INIT_FUNC := $$(eval $$(call ProductCommonVars,mctester,,,mctester))

