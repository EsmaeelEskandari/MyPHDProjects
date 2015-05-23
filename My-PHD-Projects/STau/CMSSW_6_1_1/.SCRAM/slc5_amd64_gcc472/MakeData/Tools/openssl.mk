openssl             := openssl
ALL_TOOLS      += openssl
openssl_LOC_INCLUDE := /public/V_CMSSW64/slc5_amd64_gcc472/external/openssl/0.9.8e__1.0.1/include
openssl_EX_INCLUDE  := $(openssl_LOC_INCLUDE)
openssl_LOC_LIB := ssl crypto
openssl_EX_LIB  := $(openssl_LOC_LIB)
openssl_INIT_FUNC := $$(eval $$(call ProductCommonVars,openssl,,,openssl))

