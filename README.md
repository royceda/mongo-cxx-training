# Mongo C++ Training

# Installation

## dependencies 

install mongo-cxx-driver 3.6

```
cd dependencies && ./script.sh
```

## Compile 

```
mkdir build
cd build 
cmake ..
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


