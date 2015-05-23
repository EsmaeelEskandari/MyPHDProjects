ccache-ccompiler             := ccache-ccompiler
ALL_TOOLS      += ccache-ccompiler
ccache-ccompiler_LOC_USE := gcc-ccompiler
ccache-ccompiler_EX_USE  := $(ccache-ccompiler_LOC_USE)
ccache-ccompiler_INIT_FUNC := $$(eval $$(call ProductCommonVars,ccache-ccompiler,,,ccache-ccompiler))

