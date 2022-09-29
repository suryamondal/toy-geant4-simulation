# Toy GEANT4 Monte-Carlo
In this package, particles are generated and propagated in a block of material. The material
is sliced in thin partitions. Each particles are then tracked for energy deposition in each slice.

## Use
```
git clone git@github.com:suryamondal/git@github.com:suryamondal/toy-geant4-simulation.git
mkdir build
cd build
rm -rf *	# sometimes, just 'make clean' works
cmake ..	# or the following
cmake .. -DCMAKE_CXX_COMPILER=`which g++` -DCMAKE_C_COMPILER=`which gcc`	# in case, target_compile_features The compiler feature "cxx_std_17" is not known to CXX compiler
make -j 2
./exampleB2a			# to hold the event display
./exampleB2a init_vis.mac	# to quit immediately after processing
```

## Scheme:
Name of the output file and a few more can be can be set using the following.
```
/vis/disable					# disable event display to save time
/B2/run/output_file test_seed_8904139_1546570	# .root extension is added in the code.
```

## Geometry

### Tested with the following versions of softwares
```
root_v6.26.04
clhep_v2.4.5.1
geant_v4.11.00.p02
```
To run with earlier geant4 versions, a slight modification to `exampleB2a.cc` file is required,
especifically `G4RunManagerFactory` does not exist in earlier versions, and should be replaced
with `G4RunManager`.

## Precautions:
Maximum number of particles which can be stored in the ROOT file is hard coded in `src/ObjManager.hh`
```
const UInt_t max_ngent = 500;
const UInt_t max_step = 500;
```
