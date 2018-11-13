#!/bin/bash
 
cd $PBS_O_WORKDIR
#PBS -l nodes=1:ppn=1

./rps.out 1
