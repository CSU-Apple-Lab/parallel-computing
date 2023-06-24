GCC?=gcc
N?=50 500 5000 50000 500000 5000000

QUSORT_EXECUTABLE=qusort
QUSORT_MULTI_EXECUTABLE=qusort_multi
QUSORT_POOL_EXECUTABLE=qusort_pool

QUSORT_OUTPUT=qusort.out
QUSORT_MULTI_OUTPUT=qusort_multi.out
QUSORT_POOL_OUTPUT=qusort_pool.out

EXEC_FILES=$(QUSORT_EXECUTABLE) $(QUSORT_MULTI_EXECUTABLE) $(QUSORT_POOL_EXECUTABLE)
OUTPUT_FILES=$(QUSORT_OUTPUT) $(QUSORT_MULTI_OUTPUT) $(QUSORT_POOL_OUTPUT)

.PHONY: all

all: build run generate clean

build: qusort.c qusort_multi.c qusort_pool.c
	@echo "qusort: start building"
	@$(GCC) -o qusort qusort.c
	@$(GCC) -o qusort_multi qusort_multi.c
	@$(GCC) -o qusort_pool qusort_pool.c
	@echo "qusort: end building"

run: $(EXEC_FILES)
	@echo "qusort: start running"
	@$(call run,$(QUSORT_EXECUTABLE),$(QUSORT_OUTPUT))
	@$(call run,$(QUSORT_MULTI_EXECUTABLE),$(QUSORT_MULTI_OUTPUT))
	@$(call run,$(QUSORT_POOL_EXECUTABLE),$(QUSORT_POOL_OUTPUT))
	@echo "qusort: end running"

generate: generate.py
	@echo "sys: start generating diagrams"
	@python3 generate.py
	@echo "sys: end generating diagram"

clean:
	@echo "sys: remove build files"
	@-rm $(EXEC_FILES) $(OUTPUT_FILES)

define run
for i in $N; do \
	times=;\
	for j in $$(seq 1 10); do \
		result=$$(./$(1) $$i); \
		time=$$(echo $$result | awk '{print $$NF}' | awk -F 's' '{print $$1}'); \
		times=$(join $$times, $$time); \
	done; \
	echo "N=$$i Time=$$times" >> $(2); \
done
endef