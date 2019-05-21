CPP_SRCS := $(shell find -name *.cpp)
PY_SRCS := $(shell find -name *.py)

check:
	cpplint --linelength=100 --extensions=cpp --filter=-legal/copyright,-runtime/references $(CPP_SRCS)
	pylint --disable=duplicate-code,bad-whitespace,invalid-name,missing-docstring,too-many-locals,star-args,no-member,fixme,superfluous-parens --max-line-length=100 --extension-pkg-whitelist=numpy $(PY_SRCS)

.PHONY: check
