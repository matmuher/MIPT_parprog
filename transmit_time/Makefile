NAME=transmit_time
EXEC=${NAME}.exe
SRC=${NAME}.c
MPICC?=mpic++
SLOTS=4

all: ${EXEC}

${EXEC} : ${SRC}
	@ ${MPICC} -o $@ $^

run: ${EXEC}

	@ mpirun --oversubscribe -n ${SLOTS} ${EXEC}

clean:
	rm ${EXEC}