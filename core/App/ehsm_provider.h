/*
 * Copyright (C) 2021-2022 Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3. Neither the name of Intel Corporation nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _EHSM_RPOVIDER_H
#define _EHSM_RPOVIDER_H

#include <string>
#include <stdint.h>
#include "datatypes.h"

#define _T(x) x

#define ENCLAVE_PATH "libenclave-ehsm-core.signed.so"

errno_t memcpy_s(
    void *dest,
    size_t numberOfElements,
    const void *src,
    size_t count);

typedef enum
{
    EH_INITIALIZE = 0,
    EH_FINALIZE,
    EH_CREATE_KEY,
    EH_ENCRYPT,
    EH_DECRYPT,
    EH_ASYMMETRIC_ENCRYPT,
    EH_ASYMMETRIC_DECRYPT,
    EH_SIGN,
    EH_VERIFY,
    EH_GENERATE_DATAKEY,
    EH_GENERATE_DATAKEY_WITHOUT_PLAINTEXT,
    EH_EXPORT_DATAKEY,
    EH_GET_PUBLIC_KEY,
    EH_GET_VERSION,
    EH_ENROLL,
    EH_GENERATE_QUOTE,
    EH_VERIFY_QUOTE,
    EH_GEN_HMAC,
    EH_GEN_TOKEN_HMAC,



  EH_IMPORT_KEY_MATERIAL,


  EH_GET_PARAMETERS_FOR_IMPORT,



        EH_EXPORT_KEY_MATERIAL,
        EH_GET_PARAMETERS_FOR_EXPORT,
    EH_IMPORT_PUBLIC


} ehsm_action_t;

extern "C"
{
    /**
     * @brief The unique ffi entry for the ehsm provider libaray.
     *
     * @param reqJson the request parameters in the form of JSON string
     * [string] json string
        {
            Action: string [CreateKey, Encrypt, Decrypt, Sign, Verify...]
            payload: {
                [additional parameter]
            }
        }
     *
     * @param respJson response in json string
        {
            code: int,
            message: string,
            result: {
                xxx : xxx
            }
        }
     */
    uint32_t EHSM_FFI_CALL(const char *reqJson, char *respJson);
} // extern "C"

ehsm_status_t Initialize(bool run_on_cluter);

ehsm_status_t Finalize();

/*
Description:
Create a customer master key with the following metadatas
.keyspec;
    -EH_AES_GCM_128,
    -EH_AES_GCM_256,
    -EH_RSA_2048,
    -EH_RSA_3072,
    -EH_EC_P256,
    -EH_EC_P521,
    -EH_SM2,
    -EH_SM4_CBC,
.origin;
    -EH_INTERNAL_KEY (generated from the eHSM inside)
    -EH_EXTERNAL_KEY (generated by the customer and want to import into the eHSM),
.keyusage;
    -EH_KEYUSAGE_ENCRYPT_DECRYPT,
    -EH_KEYUSAGE_SIGN_VERIFY,
.apiversion;
    -Reserved
.descrption;
    -Reserved
.createdate
    -Reserved
Note: the CMK will be wrapped by the DK(DomainKey)
*/
ehsm_status_t CreateKey(ehsm_keyblob_t *cmk);







/*


Description:


Output:


cmk -- An external cmk


*/


ehsm_status_t ImportPublic(ehsm_keyblob_t *cmk,


                                ehsm_padding_mode_t padding_mode,


                                ehsm_data_t *encryptedimportkeymarital);







/*
Description:
Encrypt an arbitrary set of bytes using the CMK.(only support symmetric types)
Input:
cmk -- A symmetric cmk,
plaintext -- the datas of the plaintext
aad -- some extra datas input by the user, which could help to to ensure data integrity, and not
be included in the cipherblobs
Output:
ciphertext -- the data of the ciphertext
Note: Only data of 6KB or less can be encrypted
*/
ehsm_status_t Encrypt(ehsm_keyblob_t *cmk,
                      ehsm_data_t *plaintext,
                      ehsm_data_t *aad,
                      ehsm_data_t *ciphertext);

/*
Description:
Get public key from asymmetric keypair.
Input:
cmk -- A symmetric cmk,
Output:
pubkey -- the data of the asymmetric public key
*/
ehsm_status_t GetPublicKey(ehsm_keyblob_t *cmk,
                           ehsm_data_t *pubkey);











/*
Description:
Decrypt user's key and store in ehsm db
Input:
cmk -- An external cmk,
encryptedimportkeymarital -- encrypted user's key,
Output:
cmk -- An external cmk
*/
ehsm_status_t ExportKeyMaterial(ehsm_keyblob_t *cmk,
                                ehsm_padding_mode_t padding_mode
                                ,ehsm_data_t *encryptedexportkeymaterial

                                );

/*
Description:
Generate RSA keypair and store in external key temporarily
RSA public key will be return for user
Input:
import_cmk -- A symmetric external cmk,
keyspec -- asymmetric keyspec
*/
ehsm_status_t GetParametersForExport(ehsm_keyblob_t *import_cmk,
                                     ehsm_keyspec_t keyspec,
                                     ehsm_data_t *pubkey);

















/*
Description:
Decrypt user's key and store in ehsm db
Input:
cmk -- An external cmk,
encryptedimportkeymarital -- encrypted user's key,
Output:
cmk -- An external cmk
*/
ehsm_status_t ImportKeyMaterial(ehsm_keyblob_t *cmk,
                                ehsm_padding_mode_t padding_mode,
                                ehsm_data_t *encryptedimportkeymarital);

/*
Description:
Generate RSA keypair and store in external key temporarily
RSA public key will be return for user
Input:
import_cmk -- A symmetric external cmk,
keyspec -- asymmetric keyspec
*/
ehsm_status_t GetParametersForImport(ehsm_keyblob_t *import_cmk,
                                     ehsm_keyspec_t keyspec,
                                     ehsm_data_t *pubkey);

/*
Description:
Decrypts ciphertext using the CMK.(only support symmetric types)
Input:
cmk -- A symmetric cmk
ciphertext -- the data of the ciphertext
aad -- some extra datas input by the user, which could help to to ensure data integrity
Output:
plaintext -- the datas of the plaintext
*/
ehsm_status_t Decrypt(ehsm_keyblob_t *cmk,
                      ehsm_data_t *ciphertext,
                      ehsm_data_t *aad,
                      ehsm_data_t *plaintext);

/*
Description:
Encrypt an arbitrary set of bytes using the CMK.(only support asymmetric types)
Input:
cmk -- An asymmetric cmk,
plaintext -- the datas of the plaintext
Output:
ciphertext -- the data of the ciphertext
Note:
the data size is limited decided by the keyspec:
RSA_OAEP_2048_SHA_256_MAX_ENCRYPTION_SIZE       190
RSA_2048_OAEP_SHA_1_MAX_ENCRYPTION_SIZE       214
RSA_OAEP_3072_SHA_256_MAX_ENCRYPTION_SIZE       318
RSA_3072_OAEP_SHA_1_MAX_ENCRYPTION_SIZE       342
SM2PKE_MAX_ENCRYPTION_SIZE                      6047
*/
ehsm_status_t AsymmetricEncrypt(ehsm_keyblob_t *cmk,
                                ehsm_padding_mode_t padding_mode,
                                ehsm_data_t *plaintext,
                                ehsm_data_t *ciphertext);

/*
Description:
Decrypt an arbitrary set of bytes using the CMK.(only support asymmetric types)
Input:
cmk -- An asymmetric cmk,
ciphertext -- the data of the ciphertext
Output:
plaintext -- the datas of the plaintext
Note:
the data size is limited decided by the keyspec:
RSA_OAEP_2048_SHA_256_MAX_ENCRYPTION_SIZE       190
RSA_2048_OAEP_SHA_1_MAX_ENCRYPTION_SIZE       214
RSA_OAEP_3072_SHA_256_MAX_ENCRYPTION_SIZE       318
RSA_3072_OAEP_SHA_1_MAX_ENCRYPTION_SIZE       342
SM2PKE_MAX_ENCRYPTION_SIZE                      6047
*/

ehsm_status_t AsymmetricDecrypt(ehsm_keyblob_t *cmk,
                                ehsm_padding_mode_t padding_mode,
                                ehsm_data_t *ciphertext,
                                ehsm_data_t *plaintext);
/*
Description:
Generates a random data key that is used to locally encrypt data.
the datakey will be wrapped by the specified CMK(only support asymmetric keyspec),
and it will return the plaintext and ciphertext of the data key.
You can use the plaintext of the data key to locally encrypt your data without using KMS
and store the encrypted data together with the ciphertext of the data key, then clear the
plaintext data from memory as soon as possible.
when you want to obtain the plaintext of datakey again, you can call the Decrypt with the
cmk to get the plaintext data.
Input:
cmk -- A symmetric cmk,
aad -- some extra datas input by the user, which could help to to ensure data integrity
plaintext -- the datas of the plaintext
Output:
ciphertext -- the data of the ciphertext
*/
ehsm_status_t GenerateDataKey(ehsm_keyblob_t *cmk,
                              ehsm_data_t *aad,
                              ehsm_data_t *plaintext,
                              ehsm_data_t *ciphertext);

/*
Description:
The same as GenerateDataKey, but doesn’t return plaintext of generated DataKey.
*/
ehsm_status_t GenerateDataKeyWithoutPlaintext(ehsm_keyblob_t *cmk,
                                              ehsm_data_t *aad,
                                              ehsm_data_t *plaintext,
                                              ehsm_data_t *ciphertext);

/*
Description:
ehsm-core enclave will decrypt user-supplied ciphertextblob with specified CMK to get the
plaintext of DataKey, then use the user-supplied Public key to encrypt this DataKey
(aka ExportedDataKey). This ExportedDataKey (ciphertext) will be returned to caller.
Input:
cmk -- A symmetric cmk,
ukey -- An asymmetric key,
aad -- some extra datas input by the user, which could help to to ensure data integrity
olddatakey -- the ciphertext of the datakey wrapped by the cmk
Output:
newdatakey -- the ciphertext of the datakey wrapped by the ukey
*/
ehsm_status_t ExportDataKey(ehsm_keyblob_t *cmk,
                            ehsm_keyblob_t *ukey,
                            ehsm_data_t *aad,
                            ehsm_data_t *olddatakey,
                            ehsm_data_t *newdatakey);

/*
Description:
Performs sign operation using the cmk(only support asymmetric keyspec).
Input:
cmk -- An asymmetric cmk,
digest -- the hash of datas want to be signed.
Output:
signature -- the signature of the digest signed by the cmk
*/
ehsm_status_t Sign(ehsm_keyblob_t *cmk,
                   ehsm_digest_mode_t digest_mode,
                   ehsm_padding_mode_t padding_mode,
                   ehsm_message_type_t message_type,
                   ehsm_data_t *message,
                   ehsm_data_t *signature);

/*
Description:
Performs verify operation using the cmk(only support asymmetric keyspec).
Input:
cmk -- An asymmetric cmk,
digest -- the hash of datas want to be signed.
signature -- the signature of the digest signed by the cmk
Output:
result -- true/false
*/
ehsm_status_t Verify(ehsm_keyblob_t *cmk,
                     ehsm_digest_mode_t digest_mode,
                     ehsm_padding_mode_t padding_mode,
                     ehsm_message_type_t message_type,
                     ehsm_data_t *message,
                     ehsm_data_t *signature,
                     bool *result);

/*
Description:
Performs quote generation and return the quote.
Input/Output:
quote -- the quote for the target encalve.
*/
ehsm_status_t GenerateQuote(ehsm_data_t *quote);

/*
Description:
Performs quote verification and return the result.
Input:
quote -- the quote need to be verified.
Output:
result -- result with type sgx_ql_qv_result_t.
*/
ehsm_status_t VerifyQuote(ehsm_data_t *quote,
                          const char *mr_signer,
                          const char *mr_enclave,
                          int *result);

/*
Description:
Obtain a valid appid and apikey
Output:
appid -- an uuid
apikey -- 32byte random number
*/
ehsm_status_t Enroll(ehsm_data_t *appid, ehsm_data_t *apikey);

/*
Description:
Generate HMAC(SHA-256) of payload with given apikey
Input:
cmk -- A symmetric cmk
apikey -- 32byte random number (in ciphertext)
payload -- the payload, a string
Output:
hmac -- the hmac
*/
ehsm_status_t GenerateHmac(ehsm_keyblob_t *cmk, ehsm_data_t *apikey, ehsm_data_t *payload, ehsm_data_t *hmac);

/*
Description:
Generate HMAC(SHA-256) of payload with given sessionkey
Input:
sessionkey -- A symmetric cmk
import_token -- the import_token, a string
Output:
hmac -- the hmac
*/
ehsm_status_t GenerateTokenHmac(ehsm_keyblob_t *sessionkey, ehsm_data_t *import_token, ehsm_data_t *hmac);

#endif
