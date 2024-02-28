PROGRAM = jogodavida

MPICC = mpicc

RESULT = result.txt

SRCS = jogodavida.c

all: $(PROGRAM)

$(PROGRAM): $(SRCS)
	$(MPICC) -o $(PROGRAM) $(SRCS)

run: $(PROGRAM)
	mpirun -np 4 -hosts worker1,worker2 ./$(PROGRAM) >> $(RESULT)
clean:
	rm -f $(PROGRAM)