boost_python             := boost_python
ALL_TOOLS      += boost_python
boost_python_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/boost/1.51.0-cms2/include
boost_python_EX_INCLUDE  := $(boost_python_LOC_INCLUDE)
boost_python_LOC_LIB := boost_python
boost_python_EX_LIB  := $(boost_python_LOC_LIB)
boost_python_LOC_USE := elementtree gccxml python
boost_python_EX_USE  := $(boost_python_LOC_USE)
boost_python_INIT_FUNC := $$(eval $$(call ProductCommonVars,boost_python,,,boost_python))

