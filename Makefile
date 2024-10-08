DIRS := 'facebook-hacker-cup' 'google-code-jam'

check:
	find . -iname *.cpp | xargs cpplint --linelength=100 --extensions=cpp --filter=-build/c++11,-legal/copyright,-runtime/references --exclude=backup
	for d in $(DIRS); do pylint --disable=duplicate-code,invalid-name,missing-docstring,too-many-locals,no-member,fixme,superfluous-parens,consider-using-f-string --max-line-length=100 --extension-pkg-whitelist=numpy $$d; done

.PHONY: check
