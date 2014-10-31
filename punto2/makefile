all: trajectory.pdf trajectory_xy.pdf

trajectory.pdf trajectory_xy.pdf:graficar.py trayectoria_1000_60.dat
	python graficar.py

trayectoria_1000_60.dat:a.out
	./a.out 1000 60

a.out:Solucion.c
	cc Solucion.c -lm

clean: 
	rm trajectory.pdf trajectory_xy.pdf trayectoria_1000_60.dat a.out
