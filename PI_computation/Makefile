EXEC=compute_PI.exe
SRC=compute_PI.c
MPICC?=mpic++
SLOTS=4

all: ${EXEC}

${EXEC} : ${SRC}
	${MPICC} -o $@ $^

run: ${EXEC}

	mpirun --oversubscribe -n ${SLOTS} ${EXEC}

clean:
	rm ${EXEC}