CFLAGS = -I$(BOOST_ROOT) -O
Libs = -L$(BOOST_ROOT)/Libs/linux/release

all : http_server
.PHONY : all
http_server : server.o connection.o connection_manager.o mime_types.o reply.o request_parser.o request_handler.o
	clang++ -o http_server $(CFLAGS) $(Libs) main.cpp server.o connection.o connection_manager.o mime_types.o reply.o request_parser.o request_\
handler.o -lboost_system -lpthread -lrt

server.o : server.hpp server.cpp
	clang++ -c -o server.o $(CFLAGS) server.cpp

connection.o : connection.hpp connection.cpp
	clang++ -c -o connection.o $(CFLAGS) connection.cpp

connection_manager.o : connection_manager.hpp connection_manager.cpp
	clang++ -c -o connection_manager.o $(CFLAGS) connection_manager.cpp

mime_types.o : mime_types.hpp mime_types.cpp
	clang++ -c -o mime_types.o $(CFLAGS) mime_types.cpp

reply.o : reply.hpp reply.cpp
	clang++ -c -o reply.o $(CFLAGS) reply.cpp

request_parser.o : request_parser.hpp request_parser.cpp
	clang++ -c -o request_parser.o $(CFLAGS) request_parser.cpp

request_handler.o : request_handler.hpp request_handler.cpp
	clang++ -c -o request_handler.o $(CFLAGS) request_handler.cpp

.PHONY : clean
clean :
	rm *.o http_server
