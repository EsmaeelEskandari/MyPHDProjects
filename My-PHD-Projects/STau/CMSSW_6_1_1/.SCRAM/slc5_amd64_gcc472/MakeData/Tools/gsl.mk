gsl             := gsl
ALL_TOOLS      += gsl
gsl_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/gsl/1.10/include
gsl_EX_INCLUDE  := $(gsl_LOC_INCLUDE)
gsl_LOC_LIB := gsl gslcblas
gsl_EX_LIB  := $(gsl_LOC_LIB)
gsl_INIT_FUNC := $$(eval $$(call ProductCommonVars,gsl,,,gsl))

