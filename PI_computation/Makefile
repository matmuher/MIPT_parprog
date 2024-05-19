EXECS=compute_PI.exe
MPICC?=mpic++
SLOTS=4

all: ${EXECS}

compute_PI.exe : compute_PI.c
	${MPICC} -o $@ $^

run: compute_PI.exe

	mpirun --oversubscribe -n ${SLOTS} ./compute_PI.exe

clean:
	rm ${EXECS}