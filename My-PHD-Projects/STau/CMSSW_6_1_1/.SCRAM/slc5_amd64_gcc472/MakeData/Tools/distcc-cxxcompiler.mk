distcc-cxxcompiler             := distcc-cxxcompiler
ALL_TOOLS      += distcc-cxxcompiler
distcc-cxxcompiler_LOC_USE := gcc-cxxcompiler
distcc-cxxcompiler_EX_USE  := $(distcc-cxxcompiler_LOC_USE)
distcc-cxxcompiler_INIT_FUNC := $$(eval $$(call ProductCommonVars,distcc-cxxcompiler,,,distcc-cxxcompiler))

