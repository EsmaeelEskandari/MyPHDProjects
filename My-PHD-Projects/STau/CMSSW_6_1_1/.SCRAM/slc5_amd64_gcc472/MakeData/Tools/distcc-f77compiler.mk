distcc-f77compiler             := distcc-f77compiler
ALL_TOOLS      += distcc-f77compiler
distcc-f77compiler_LOC_USE := gcc-f77compiler
distcc-f77compiler_EX_USE  := $(distcc-f77compiler_LOC_USE)
distcc-f77compiler_INIT_FUNC := $$(eval $$(call ProductCommonVars,distcc-f77compiler,,,distcc-f77compiler))

