GCC?=gcc
NP?=32

BIGMAT_EXECUTABLE=bigmat_omp
BIGMAT_OUTPUT=bigmat_omp.out

.PHONY: all

all: build run

build: bigmat_omp.c
	@echo "bigmat_omp: start building"
	@$(GCC) -o bigmat_omp bigmat_omp.c -fopenmp
	@echo "bigmat_omp: end building"

run:
	@echo "bigmat_omp: start running"
	@for i in $$(seq 1 $(NP)); do \
		times=; \
		for j in $$(seq 1 10); do \
			result=$$(./$(BIGMAT_EXECUTABLE) $$i); \
			time=$$(echo $$result | awk '{print $$NF}' | awk -F 's' '{print $$1}'); \
			times=$(join $$times,$$time); \
		done; \
		echo "N=$$i Time=$$times" >> $(BIGMAT_OUTPUT); \
	done
	@echo "bigmat_omp: start running"

generate: generate.py
	@echo "sys: start generating diagrams"
	@python3 generate.py
	@echo "sys: end generating diagram"

clean:
	@echo "sys: remove build files"
	@-rm $(BIGMAT_EXECUTABLE) $(BIGMAT_OUTPUT)
