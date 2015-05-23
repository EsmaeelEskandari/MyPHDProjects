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
