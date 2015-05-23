distcc-ccompiler             := distcc-ccompiler
ALL_TOOLS      += distcc-ccompiler
distcc-ccompiler_LOC_USE := gcc-ccompiler
distcc-ccompiler_EX_USE  := $(distcc-ccompiler_LOC_USE)
distcc-ccompiler_INIT_FUNC := $$(eval $$(call ProductCommonVars,distcc-ccompiler,,,distcc-ccompiler))

