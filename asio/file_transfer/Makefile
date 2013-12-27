file_transfer : file_transfer_client file_transfer_server

file_transfer_client : file_transfer_client.cpp file_transfer_common.h
	clang++ -o file_transfer_client -I$(BOOST_ROOT) -L$(BOOST_ROOT)/Libs/linux/release file_transfer_client.cpp -lboost_system -lpthread

file_transfer_server : file_transfer_server.cpp file_transfer_common.h
	clang++ -o file_transfer_server -I$(BOOST_ROOT) -L$(BOOST_ROOT)/Libs/linux/release file_transfer_server.cpp -lboost_system -lpthread

.PHONY : clean

clean:
	rm file_transfer_server file_transfer_client
