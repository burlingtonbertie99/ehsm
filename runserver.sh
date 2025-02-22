#!/bin/bash

#set -v

EHSM_KMS_PORT="9002"
EHSM_RUN_MODE="single"

EHSM_COUCHDB_IMG="couchdb:3.2"
EHSM_COUCHDB_DOCKER_NAME="c_couchdb"
EHSM_COUCHDB_USER="admin"
EHSM_COUCHDB_PASSWORD="password"
EHSM_COUCHDB_PORT="5984"


# Copy the build binaries to the nodejs folder
cp out/ehsm-core/libehsmprovider.so ehsm_kms_service/
cp out/ehsm-core/libenclave-ehsm-core.signed.so ehsm_kms_service/
echo "ehsm libehsmprovider and libenclave-ehsm-core copied."


if ! [ "$(node -v)" ]; then
    wget https://nodejs.org/dist/v20.1.0/node-v20.1.0-linux-x64.tar.xz \
        && tar xf node-v20.1.0-linux-x64.tar.xz \
        && rm -rf node-v20.1.0-linux-x64.tar.xz \
        && sudo mv node-v20.1.0-linux-x64/ /usr/local/nodejs \
        && sudo ln -s /usr/local/nodejs/bin/node /usr/local/bin \
        && sudo ln -s /usr/local/nodejs/bin/npm /usr/local/bin
fi

# Start the ehsm-kms webserver
cd ehsm_kms_service

if [ ! -d  "node_modules" ]; then
    npm install
fi

#sudo 
node ./ehsm_kms_server.js run_mode=$EHSM_RUN_MODE port=$EHSM_KMS_PORT

