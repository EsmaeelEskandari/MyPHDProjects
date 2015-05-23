ccache-f77compiler             := ccache-f77compiler
ALL_TOOLS      += ccache-f77compiler
ccache-f77compiler_LOC_USE := gcc-f77compiler
ccache-f77compiler_EX_USE  := $(ccache-f77compiler_LOC_USE)
ccache-f77compiler_INIT_FUNC := $$(eval $$(call ProductCommonVars,ccache-f77compiler,,,ccache-f77compiler))

