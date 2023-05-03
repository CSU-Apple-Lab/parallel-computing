MPICC?=mpicc
MPIRUN?=mpirun
GCC?=gcc
NP?=20

PI_EXECUTABLE=pi
MPI_EXECUTABLE=pi-mpi

PI_OUTPUT=pi.out
MPI_OUTPUT=pi-mpi.out

EXEC_FILES=$(PI_EXECUTABLE) $(MPI_EXECUTABLE)
OUTPUT_FILES=$(PI_OUTPUT) $(MPI_OUTPUT)

.PHONY: all

all: build run generate clean


build: pi.c pi-mpi.c
	@echo "pi & pi_mpi: start building"
	@$(GCC) -c pi.c
	@$(GCC) -o pi pi.o
	@$(MPICC) -o pi-mpi pi-mpi.c
	@echo "pi & pi_mpi: end building"

run:
	@echo "pi & pi_mpi: start running"
	@$(call run,1,$(PI_EXECUTABLE),$(PI_OUTPUT))
	@$(call run,$(NP),$(MPI_EXECUTABLE),$(MPI_OUTPUT))
	@echo "pi & pi_mpi: start running"

generate: generate.py
	@echo "sys: start generating diagrams"
	@python3 generate.py
	@echo "sys: end generating diagram"

clean:
	@echo "sys: remove build files"
	@-rm -rf *.dSYM
	@-rm *.o $(EXEC_FILES) $(OUTPUT_FILES)

define run
	for i in $$(seq 1 $(1)); do \
        times=(); \
        for j in $$(seq 1 10); do \
			if [ "$(2)" = "pi" ]; then \
                result=$$(./$(PI_EXECUTABLE)); \
            else \
                result=$$(mpirun -np $$i ./$(MPI_EXECUTABLE)); \
            fi; \
            time=$$(echo $$result | awk -F ' ' '{print $$2}' | awk -F '=' '{gsub(/s/, "", $$2); print $$2}' ); \
            times+=($$time); \
        done; \
		echo "NP=$$i Time=$${times[@]}" >> $(3); \
    done
endef