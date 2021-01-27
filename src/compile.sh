c++ --std=c++11 connection.cpp \
  -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
  -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
  -L/usr/local/lib -lmongocxx -lbsoncxx  -o exe


# /usr/local/include/mongocxx/v_noabi/mongocxx/