ccache-cxxcompiler             := ccache-cxxcompiler
ALL_TOOLS      += ccache-cxxcompiler
ccache-cxxcompiler_LOC_USE := gcc-cxxcompiler
ccache-cxxcompiler_EX_USE  := $(ccache-cxxcompiler_LOC_USE)
ccache-cxxcompiler_INIT_FUNC := $$(eval $$(call ProductCommonVars,ccache-cxxcompiler,,,ccache-cxxcompiler))

