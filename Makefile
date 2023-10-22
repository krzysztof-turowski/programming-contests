CPP_SRCS := $(shell find -name *.cpp)
PY_SRCS := $(shell find -name *.py)

check:
	cpplint --linelength=100 --extensions=cpp --filter=-legal/copyright,-runtime/references --exclude=backup $(CPP_SRCS)
	pylint --disable=duplicate-code,invalid-name,missing-docstring,too-many-locals,no-member,fixme,superfluous-parens,consider-using-f-string --max-line-length=100 --extension-pkg-whitelist=numpy $(PY_SRCS)

.PHONY: check
