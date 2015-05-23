jimmy_headers             := jimmy_headers
ALL_TOOLS      += jimmy_headers
jimmy_headers_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/jimmy/4.2/include
jimmy_headers_EX_INCLUDE  := $(jimmy_headers_LOC_INCLUDE)
jimmy_headers_INIT_FUNC := $$(eval $$(call ProductCommonVars,jimmy_headers,,,jimmy_headers))

