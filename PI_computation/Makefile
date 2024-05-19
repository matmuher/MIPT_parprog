EXEC=compute_PI.exe
SRC=compute_PI.c
MPICC?=mpic++
SLOTS=4
SAMPLES=1000000

all: ${EXEC}

${EXEC} : ${SRC}
	@ ${MPICC} -o $@ $^ -D GlobalSampleNum=${SAMPLES}

run: ${EXEC}

	@ mpirun --oversubscribe -n ${SLOTS} ${EXEC}

clean:
	rm ${EXEC}