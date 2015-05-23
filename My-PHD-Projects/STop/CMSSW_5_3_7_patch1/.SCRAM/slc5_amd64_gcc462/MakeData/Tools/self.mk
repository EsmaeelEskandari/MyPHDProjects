self             := self
ALL_TOOLS      += self
self_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc462/cms/cmssw-patch/CMSSW_5_3_7_patch1/src /public/V_CMSSW64/slc5_amd64_gcc462/cms/cmssw-patch/CMSSW_5_3_7_patch1/include/LCG
self_EX_INCLUDE  := $(self_LOC_INCLUDE)
self_LOC_LIBDIR := /public/V_CMSSW64/slc5_amd64_gcc462/cms/cmssw-patch/CMSSW_5_3_7_patch1/lib/slc5_amd64_gcc462 /public/V_CMSSW64/slc5_amd64_gcc462/cms/cmssw-patch/CMSSW_5_3_7_patch1/external/slc5_amd64_gcc462/lib
self_EX_LIBDIR  := $(self_LOC_LIBDIR)
self_LOC_LIBDIR += $(cmssw_EX_LIBDIR)
self_EX_LIBDIR  += $(cmssw_EX_LIBDIR)
self_LOC_FLAGS_SYMLINK_DEPTH_CMSSW_SEARCH_PATH  := 2
self_EX_FLAGS_SYMLINK_DEPTH_CMSSW_SEARCH_PATH   := $(self_LOC_FLAGS_SYMLINK_DEPTH_CMSSW_SEARCH_PATH)
self_LOC_FLAGS_SKIP_TOOLS_SYMLINK  := cxxcompiler ccompiler x11 dpm
self_EX_FLAGS_SKIP_TOOLS_SYMLINK   := $(self_LOC_FLAGS_SKIP_TOOLS_SYMLINK)
self_LOC_FLAGS_EXTERNAL_SYMLINK  := PATH LIBDIR CMSSW_SEARCH_PATH
self_EX_FLAGS_EXTERNAL_SYMLINK   := $(self_LOC_FLAGS_EXTERNAL_SYMLINK)
self_LOC_FLAGS_NO_EXTERNAL_RUNTIME  := LD_LIBRARY_PATH PATH CMSSW_SEARCH_PATH
self_EX_FLAGS_NO_EXTERNAL_RUNTIME   := $(self_LOC_FLAGS_NO_EXTERNAL_RUNTIME)
self_INIT_FUNC := $$(eval $$(call ProductCommonVars,self,,20000,self))

