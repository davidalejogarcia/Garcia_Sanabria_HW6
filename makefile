all: trajectory.pdf trajectory_xy.pdf

trajectory.pdf: graficar.py
	python graficar.py

graficar.py: trayectoria_1000_60.dat
	./a.out 1000 60

trayectoria_1000_60.dat:Solucion.c
	cc Solucion.c -lm


clean: 
	rm trajectory.pdf trajectory_xy.pdf trayectoria_1000_60 a.out
