include buildenv.mk

SUB_DIR := core dkeycache dkeyserver
SSL_DIR := third_party/intel-sgx-ssl
export DESTDIR = ${OPENSSL_PATH}

.PHONY: all clean

all: 
	for dir in $(SUB_DIR); do \
		$(MAKE) -C $$dir || exit 1; \
	done

ifeq ($(Build_Mode), HW_DEBUG)
	@echo "The project has been built in hardware debug mode."
else ifeq ($(Build_Mode), HW_RELEAESE)
	@echo "The project has been built in hardware release mode."
else ifeq ($(Build_Mode), HW_PRERELEAESE)
	@echo "The project has been built in hardware pre-release mode."
else ifeq ($(Build_Mode), SIM_DEBUG)
	@echo "The project has been built in simulation debug mode."
else ifeq ($(Build_Mode), SIM_RELEAESE)
	@echo "The project has been built in simulation release mode."
else ifeq ($(Build_Mode), SIM_PRERELEAESE)
	@echo "The project has been built in simulation pre-release mode."
endif

ssl:
ifeq ("$(wildcard $(SSL_DIR/Linux))", "")
	@git submodule update --init --recursive
endif
ifeq ("$(wildcard $(DESTDIR))", "")
	@wget https://www.openssl.org/source/openssl-3.0.10.tar.gz -P $(SSL_DIR)/openssl_source/ || exit 1
	$(MAKE) -C $(SSL_DIR)/Linux clean all install || exit 1
	$(MAKE) -C $(SSL_DIR)/Linux clean
	@rm -rf $(SSL_DIR)/openssl_source/openssl-* $(SSL_DIR)/Linux/package/include/crypto
endif

clean:
	@rm -rf $(OUTDIR)
	for dir in $(SUB_DIR); do \
		$(MAKE) -C $$dir clean; \
	done
