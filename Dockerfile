FROM debian

RUN apt-get update
RUN apt-get install git cmake build-essential tar curl -y
RUN apt-get install libmongoc-dev libbson-dev -y
RUN apt-get install libbson-1.0-0 libmongoc-1.0-0
RUN apt-get install wget curl zip unzip tar pkg-config  -y

# optional
RUN git clone https://github.com/microsoft/vcpkg 
RUN cd vcpkg && ./bootstrap-vcpkg.sh
# RUN cd vcpkg && ./vcpkg install mongo-cxx-driver  && .vcpkg integrate install 

RUN apt install wget curl -y

COPY . /app
RUN cd /app/dependencies && ./script.sh