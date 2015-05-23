py2-lint             := py2-lint
ALL_TOOLS      += py2-lint
py2-lint_LOC_USE := python
py2-lint_EX_USE  := $(py2-lint_LOC_USE)
py2-lint_INIT_FUNC := $$(eval $$(call ProductCommonVars,py2-lint,,,py2-lint))

