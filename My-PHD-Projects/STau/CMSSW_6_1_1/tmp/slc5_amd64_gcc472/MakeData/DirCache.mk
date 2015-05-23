ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02/MT2Analysis)
subdirs_src_MT2_Tau_V02-03-02_MT2Analysis := 
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3/Efficiencies)
subdirs_src_MT2_Tau_V02-03-02_Dev3_Efficiencies := src_MT2_Tau_V02-03-02_Dev3_Efficiencies_InputHistos src_MT2_Tau_V02-03-02_Dev3_Efficiencies_test
src_HiggsAnalysis_CombinedLimit_scripts_files := $(filter-out \#% %\#,$(notdir $(wildcard $(foreach dir,$(LOCALTOP)/src/HiggsAnalysis/CombinedLimit/scripts,$(dir)/*))))
$(eval $(call Src2StoreCopy,src_HiggsAnalysis_CombinedLimit_scripts,src/HiggsAnalysis/CombinedLimit/scripts,$(SCRAMSTORENAME_BIN),*))
ALL_COMMONRULES += src_HiggsAnalysis_CombinedLimit_test
src_HiggsAnalysis_CombinedLimit_test_parent := HiggsAnalysis/CombinedLimit
src_HiggsAnalysis_CombinedLimit_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_HiggsAnalysis_CombinedLimit_test,src/HiggsAnalysis/CombinedLimit/test,TEST))
ALL_SUBSYSTEMS+=$(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2)
subdirs_src_MT2_Tau_V02-03-02_Dev2 = src_MT2_Tau_V02-03-02_Dev2_Efficiencies src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection src_MT2_Tau_V02-03-02_Dev2_ECALDeadCell src_MT2_Tau_V02-03-02_Dev2_JEStxtfiles src_MT2_Tau_V02-03-02_Dev2_Certification src_MT2_Tau_V02-03-02_Dev2_MT2Analysis src_MT2_Tau_V02-03-02_Dev2_JetResolutions
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3/MT2Analysis)
subdirs_src_MT2_Tau_V02-03-02_Dev3_MT2Analysis := 
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02/JEStxtfiles)
subdirs_src_MT2_Tau_V02-03-02_JEStxtfiles := src_MT2_Tau_V02-03-02_JEStxtfiles_mc
ALL_SUBSYSTEMS+=$(patsubst src/%,%,src/MT2_Tau_V02-03-02)
subdirs_src_MT2_Tau_V02-03-02 = src_MT2_Tau_V02-03-02_Efficiencies src_MT2_Tau_V02-03-02_JetEnergyCorrection src_MT2_Tau_V02-03-02_JEStxtfiles src_MT2_Tau_V02-03-02_Certification src_MT2_Tau_V02-03-02_MT2Analysis src_MT2_Tau_V02-03-02_JetResolutions
ALL_SUBSYSTEMS+=$(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3)
subdirs_src_MT2_Tau_V02-03-02_Dev3 = src_MT2_Tau_V02-03-02_Dev3_Efficiencies src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection src_MT2_Tau_V02-03-02_Dev3_ECALDeadCell src_MT2_Tau_V02-03-02_Dev3_JEStxtfiles src_MT2_Tau_V02-03-02_Dev3_Certification src_MT2_Tau_V02-03-02_Dev3_MT2Analysis src_MT2_Tau_V02-03-02_Dev3_JetResolutions
ALL_SUBSYSTEMS+=$(patsubst src/%,%,src/HiggsAnalysis)
subdirs_src_HiggsAnalysis = src_HiggsAnalysis_CombinedLimit
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2/JEStxtfiles)
subdirs_src_MT2_Tau_V02-03-02_Dev2_JEStxtfiles := src_MT2_Tau_V02-03-02_Dev2_JEStxtfiles_data
ALL_COMMONRULES += src_MT2_Tau_V02-03-02_Efficiencies_test
src_MT2_Tau_V02-03-02_Efficiencies_test_parent := MT2_Tau_V02-03-02/Efficiencies
src_MT2_Tau_V02-03-02_Efficiencies_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_MT2_Tau_V02-03-02_Efficiencies_test,src/MT2_Tau_V02-03-02/Efficiencies/test,TEST))
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2/Certification)
subdirs_src_MT2_Tau_V02-03-02_Dev2_Certification := src_MT2_Tau_V02-03-02_Dev2_Certification_pileUp_mc src_MT2_Tau_V02-03-02_Dev2_Certification_pileUp_data src_MT2_Tau_V02-03-02_Dev2_Certification_overlap_JSONS src_MT2_Tau_V02-03-02_Dev2_Certification_crab_JSONs src_MT2_Tau_V02-03-02_Dev2_Certification_2011 src_MT2_Tau_V02-03-02_Dev2_Certification_lumicalc
ifeq ($(strip $(combine)),)
combine_files := $(patsubst src/HiggsAnalysis/CombinedLimit/bin/%,%,$(foreach file,combine.cpp,$(eval xfile:=$(wildcard src/HiggsAnalysis/CombinedLimit/bin/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/HiggsAnalysis/CombinedLimit/bin/$(file). Please fix src/HiggsAnalysis/CombinedLimit/bin/BuildFile.))))
combine := self/src/HiggsAnalysis/CombinedLimit/bin
combine_BuildFile    := $(WORKINGDIR)/cache/bf/src/HiggsAnalysis/CombinedLimit/bin/BuildFile
combine_LOC_USE := self HiggsAnalysis/CombinedLimit boost_program_options
combine_PACKAGE := self/src/HiggsAnalysis/CombinedLimit/bin
ALL_PRODS += combine
combine_INIT_FUNC        += $$(eval $$(call Binary,combine,src/HiggsAnalysis/CombinedLimit/bin,src_HiggsAnalysis_CombinedLimit_bin,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_BIN),bin,$(SCRAMSTORENAME_LOGS)))
else
$(eval $(call MultipleWarningMsg,combine,src/HiggsAnalysis/CombinedLimit/bin))
endif
ALL_COMMONRULES += src_HiggsAnalysis_CombinedLimit_bin
src_HiggsAnalysis_CombinedLimit_bin_parent := HiggsAnalysis/CombinedLimit
src_HiggsAnalysis_CombinedLimit_bin_INIT_FUNC += $$(eval $$(call CommonProductRules,src_HiggsAnalysis_CombinedLimit_bin,src/HiggsAnalysis/CombinedLimit/bin,BINARY))
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2/JetEnergyCorrection)
subdirs_src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection := src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_GR_R_52_V9 src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_GR_R_42_V19_AK5PFchs src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_FT_53_V6_AN3 src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_START53_V7G src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_FT_P_V42_AN3 src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_GR_R_52_V7C src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_FT_P_V42C_AN3 src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_GR_R_52_V7 src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_GR_R_42_V23_AK5PF src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_GR_P_V42_AN3 src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_Fall10_CMSSW_3_8_x src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_GR_R_42_V19_AK5PF src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_FT_53_V6C_AN3 src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_START52_V9B src_MT2_Tau_V02-03-02_Dev2_JetEnergyCorrection_FT53_V10A_AN3
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2/MT2Analysis)
subdirs_src_MT2_Tau_V02-03-02_Dev2_MT2Analysis := src_MT2_Tau_V02-03-02_Dev2_MT2Analysis_Code
ALL_PACKAGES += $(patsubst src/%,%,src/HiggsAnalysis/CombinedLimit)
subdirs_src_HiggsAnalysis_CombinedLimit := src_HiggsAnalysis_CombinedLimit_bin src_HiggsAnalysis_CombinedLimit_scripts src_HiggsAnalysis_CombinedLimit_python src_HiggsAnalysis_CombinedLimit_src src_HiggsAnalysis_CombinedLimit_data src_HiggsAnalysis_CombinedLimit_test
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2/ECALDeadCell)
subdirs_src_MT2_Tau_V02-03-02_Dev2_ECALDeadCell := src_MT2_Tau_V02-03-02_Dev2_ECALDeadCell_python
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3/JEStxtfiles)
subdirs_src_MT2_Tau_V02-03-02_Dev3_JEStxtfiles := 
ifeq ($(strip $(PyHiggsAnalysisCombinedLimit)),)
PyHiggsAnalysisCombinedLimit := self/src/HiggsAnalysis/CombinedLimit/python
PyHiggsAnalysisCombinedLimit_files := $(patsubst src/HiggsAnalysis/CombinedLimit/python/%,%,$(wildcard $(foreach dir,src/HiggsAnalysis/CombinedLimit/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyHiggsAnalysisCombinedLimit_LOC_USE := self
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/HiggsAnalysis/CombinedLimit/python)
ALL_PRODS += PyHiggsAnalysisCombinedLimit
src_HiggsAnalysis_CombinedLimit_python_parent := HiggsAnalysis/CombinedLimit
PyHiggsAnalysisCombinedLimit_INIT_FUNC        += $$(eval $$(call PythonProduct,PyHiggsAnalysisCombinedLimit,src/HiggsAnalysis/CombinedLimit/python,src_HiggsAnalysis_CombinedLimit_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyHiggsAnalysisCombinedLimit,src/HiggsAnalysis/CombinedLimit/python))
endif
ALL_COMMONRULES += src_HiggsAnalysis_CombinedLimit_python
src_HiggsAnalysis_CombinedLimit_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_HiggsAnalysis_CombinedLimit_python,src/HiggsAnalysis/CombinedLimit/python,PYTHON))
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02/JetEnergyCorrection)
subdirs_src_MT2_Tau_V02-03-02_JetEnergyCorrection := src_MT2_Tau_V02-03-02_JetEnergyCorrection_GR_R_52_V9 src_MT2_Tau_V02-03-02_JetEnergyCorrection_FT_53_V6_AN3 src_MT2_Tau_V02-03-02_JetEnergyCorrection_START53_V7G src_MT2_Tau_V02-03-02_JetEnergyCorrection_GR_R_52_V7C src_MT2_Tau_V02-03-02_JetEnergyCorrection_FT_P_V42C_AN3 src_MT2_Tau_V02-03-02_JetEnergyCorrection_GR_R_42_V23_AK5PF src_MT2_Tau_V02-03-02_JetEnergyCorrection_GR_P_V42_AN3 src_MT2_Tau_V02-03-02_JetEnergyCorrection_Fall10_CMSSW_3_8_x src_MT2_Tau_V02-03-02_JetEnergyCorrection_FT_53_V6C_AN3 src_MT2_Tau_V02-03-02_JetEnergyCorrection_START52_V9B src_MT2_Tau_V02-03-02_JetEnergyCorrection_FT53_V10A_AN3
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2/JetResolutions)
subdirs_src_MT2_Tau_V02-03-02_Dev2_JetResolutions := 
ALL_COMMONRULES += src_MT2_Tau_V02-03-02_Dev3_Efficiencies_test
src_MT2_Tau_V02-03-02_Dev3_Efficiencies_test_parent := MT2_Tau_V02-03-02_Dev3/Efficiencies
src_MT2_Tau_V02-03-02_Dev3_Efficiencies_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_MT2_Tau_V02-03-02_Dev3_Efficiencies_test,src/MT2_Tau_V02-03-02_Dev3/Efficiencies/test,TEST))
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02/Certification)
subdirs_src_MT2_Tau_V02-03-02_Certification := src_MT2_Tau_V02-03-02_Certification_crab_JSONs src_MT2_Tau_V02-03-02_Certification_2011
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2/Efficiencies)
subdirs_src_MT2_Tau_V02-03-02_Dev2_Efficiencies := src_MT2_Tau_V02-03-02_Dev2_Efficiencies_InputHistos src_MT2_Tau_V02-03-02_Dev2_Efficiencies_test
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02/JetResolutions)
subdirs_src_MT2_Tau_V02-03-02_JetResolutions := 
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3/JetResolutions)
subdirs_src_MT2_Tau_V02-03-02_Dev3_JetResolutions := 
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3/JetEnergyCorrection)
subdirs_src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection := src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_GR_R_52_V9 src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_FT_53_V6_AN3 src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_GR_R_52_V7C src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_FT_P_V42C_AN3 src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_GR_P_V42_AN3 src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_Fall10_CMSSW_3_8_x src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_GR_R_42_V19_AK5PF src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_START52_V9B src_MT2_Tau_V02-03-02_Dev3_JetEnergyCorrection_FT53_V10A_AN3
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3/ECALDeadCell)
subdirs_src_MT2_Tau_V02-03-02_Dev3_ECALDeadCell := src_MT2_Tau_V02-03-02_Dev3_ECALDeadCell_python
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3/Certification)
subdirs_src_MT2_Tau_V02-03-02_Dev3_Certification := src_MT2_Tau_V02-03-02_Dev3_Certification_pileUp_data src_MT2_Tau_V02-03-02_Dev3_Certification_2011 src_MT2_Tau_V02-03-02_Dev3_Certification_lumicalc
ALL_PACKAGES += $(patsubst src/%,%,src/MT2_Tau_V02-03-02/Efficiencies)
subdirs_src_MT2_Tau_V02-03-02_Efficiencies := src_MT2_Tau_V02-03-02_Efficiencies_test
ifeq ($(strip $(PyMT2_Tau_V02-03-02_Dev2ECALDeadCell)),)
PyMT2_Tau_V02-03-02_Dev2ECALDeadCell := self/src/MT2_Tau_V02-03-02_Dev2/ECALDeadCell/python
PyMT2_Tau_V02-03-02_Dev2ECALDeadCell_files := $(patsubst src/MT2_Tau_V02-03-02_Dev2/ECALDeadCell/python/%,%,$(wildcard $(foreach dir,src/MT2_Tau_V02-03-02_Dev2/ECALDeadCell/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyMT2_Tau_V02-03-02_Dev2ECALDeadCell_LOC_USE := self
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev2/ECALDeadCell/python)
ALL_PRODS += PyMT2_Tau_V02-03-02_Dev2ECALDeadCell
src_MT2_Tau_V02-03-02_Dev2_ECALDeadCell_python_parent := MT2_Tau_V02-03-02_Dev2/ECALDeadCell
PyMT2_Tau_V02-03-02_Dev2ECALDeadCell_INIT_FUNC        += $$(eval $$(call PythonProduct,PyMT2_Tau_V02-03-02_Dev2ECALDeadCell,src/MT2_Tau_V02-03-02_Dev2/ECALDeadCell/python,src_MT2_Tau_V02-03-02_Dev2_ECALDeadCell_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyMT2_Tau_V02-03-02_Dev2ECALDeadCell,src/MT2_Tau_V02-03-02_Dev2/ECALDeadCell/python))
endif
ALL_COMMONRULES += src_MT2_Tau_V02-03-02_Dev2_ECALDeadCell_python
src_MT2_Tau_V02-03-02_Dev2_ECALDeadCell_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_MT2_Tau_V02-03-02_Dev2_ECALDeadCell_python,src/MT2_Tau_V02-03-02_Dev2/ECALDeadCell/python,PYTHON))
ALL_COMMONRULES += src_MT2_Tau_V02-03-02_Dev2_Efficiencies_test
src_MT2_Tau_V02-03-02_Dev2_Efficiencies_test_parent := MT2_Tau_V02-03-02_Dev2/Efficiencies
src_MT2_Tau_V02-03-02_Dev2_Efficiencies_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_MT2_Tau_V02-03-02_Dev2_Efficiencies_test,src/MT2_Tau_V02-03-02_Dev2/Efficiencies/test,TEST))
ifeq ($(strip $(PyMT2_Tau_V02-03-02_Dev3ECALDeadCell)),)
PyMT2_Tau_V02-03-02_Dev3ECALDeadCell := self/src/MT2_Tau_V02-03-02_Dev3/ECALDeadCell/python
PyMT2_Tau_V02-03-02_Dev3ECALDeadCell_files := $(patsubst src/MT2_Tau_V02-03-02_Dev3/ECALDeadCell/python/%,%,$(wildcard $(foreach dir,src/MT2_Tau_V02-03-02_Dev3/ECALDeadCell/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyMT2_Tau_V02-03-02_Dev3ECALDeadCell_LOC_USE := self
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/MT2_Tau_V02-03-02_Dev3/ECALDeadCell/python)
ALL_PRODS += PyMT2_Tau_V02-03-02_Dev3ECALDeadCell
src_MT2_Tau_V02-03-02_Dev3_ECALDeadCell_python_parent := MT2_Tau_V02-03-02_Dev3/ECALDeadCell
PyMT2_Tau_V02-03-02_Dev3ECALDeadCell_INIT_FUNC        += $$(eval $$(call PythonProduct,PyMT2_Tau_V02-03-02_Dev3ECALDeadCell,src/MT2_Tau_V02-03-02_Dev3/ECALDeadCell/python,src_MT2_Tau_V02-03-02_Dev3_ECALDeadCell_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyMT2_Tau_V02-03-02_Dev3ECALDeadCell,src/MT2_Tau_V02-03-02_Dev3/ECALDeadCell/python))
endif
ALL_COMMONRULES += src_MT2_Tau_V02-03-02_Dev3_ECALDeadCell_python
src_MT2_Tau_V02-03-02_Dev3_ECALDeadCell_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_MT2_Tau_V02-03-02_Dev3_ECALDeadCell_python,src/MT2_Tau_V02-03-02_Dev3/ECALDeadCell/python,PYTHON))
