#!/bin/bash

echo "Probando algoritmo genético del vendedor viajero"

#La cantidad de generaciones que se probarán, si no se ingresó
#una cantidad válida, entonces no hace ninguna iteración.
for ((i=0;i<$1;i++))
do
	./vendedorViajero $2 $3
	echo
done

