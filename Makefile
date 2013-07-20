all:
	
test:
	gcc -o stack_test stack_test.c && ./stack_test && rm stack_test && gcc -o range_test range_test.c && ./range_test && rm range_test