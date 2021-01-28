# Mongo C++ Training

# Installation

## dependencies 

install mongo-cxx-driver 3.6

```
cd dependencies && ./script.sh
```

## Compile 


### 1. CMAKE
```
mkdir build
cd build 
cmake ..
cmake  --build . --config Debug --target all -- -j 10 .. # or make -j 10 
```

### 2. Old School


````
c++ --std=c++11 connection.cpp \
   -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
   -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
   -L/usr/local/lib -lmongocxx -lbsoncxx
```

## Run

```
./conn
```

# Docker
A docker version is available  (based on dDebian image )

```
docker build -t mydev .
docker run -it --name tmp mydev
```


