#export ROOT_DIR = /opt/intel/ehsm


######## SGX SSL Settings ########
#export OPENSSL_PATH = $ROOT_DIR/utils/sgxssl
#export OPENSSL_LIBRARY_PATH = $OPENSSL_PATH/lib64
#export SOCKET_DIR 	= $ROOT_DIR/utils/sgx_socket
#export LOG_DIR = $ROOT_DIR/utils/log4cplus
#export SGXSSL_Library_Name = sgx_tsgxssl
#export OpenSSL_Crypto_Library_Name = sgx_tsgxssl_crypto
#export SGXSSL_Untrusted_Library_Name = sgx_usgxssl
#export OpenSSL_SSL_Library_Name = sgx_tsgxssl_ssl

#export SgxSSL_Link_Libraries = -L$OPENSSL_LIBRARY_PATH -Wl,--whole-archive -l$SGXSSL_Library_Name -Wl,--no-whole-archive -l$OpenSSL_SSL_Library_Name -l$OpenSSL_Crypto_Library_Name -lsgx_pthread



#gcc -c -o function_test.o -Wall -Wextra -Werror -I/home/chris/src/ehsmBB/include $(pkg-config --cflags gtk+-2.0 libxml-2.0) $(SgxSSL_Link_Libraries) -fPIC function_test.cpp

#gcc -c -o function_test.o 	-I. -I/home/chris/src/ehsmBB/include -I/home/chris/src/ehsmBB/sgxsdk/include -I/home/chris/src/ehsmBB/core/App -I/home/chris/src/ehsmBB/utils/log4cplus $(pkg-config --cflags gtk+-2.0 libxml-2.0) --fPIC function_test.cpp

#gcc -c -o main.o  		-I. -I/home/chris/src/ehsmBB/include -I/home/chris/src/ehsmBB/sgxsdk/include -I/home/chris/src/ehsmBB/core/App -I/home/chris/src/ehsmBB/utils/log4cplus  $(pkg-config --cflags gtk+-2.0 libxml-2.0)  -fPIC main.cpp

#gcc -o main function_test.o main.o -L$OPENSSL_LIBRARY_PATH -l$SGXSSL_Library_Name  -l$OpenSSL_SSL_Library_Name -l$OpenSSL_Crypto_Library_Name -lsgx_pthread

g++ -o main function_test.o main.o -L$OPENSSL_LIBRARY_PATH -l$SGXSSL_Library_Name -l$OpenSSL_SSL_Library_Name -l$OpenSSL_Crypto_Library_Name -lsgx_pthread -fopenmp -O3 -ljsoncpp -llog4cplus


#-L$OPENSSL_LIBRARY_PATH -Wl,--whole-archive -l$SGXSSL_Library_Name -Wl,--no-whole-archive -l$OpenSSL_SSL_Library_Name -l$OpenSSL_Crypto_Library_Name -lsgx_pthread 
#-L$OPENSSL_LIBRARY_PATH -Wl,--whole-archive -l$SGXSSL_Library_Name -Wl,--no-whole-archive -l$OpenSSL_SSL_Library_Name -l$OpenSSL_Crypto_Library_Name -lsgx_pthread
