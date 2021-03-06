/*
	test.cpp	测试openssl的功能
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <openssl/aes.h>

int main(void)
{
    unsigned char userkey[AES_BLOCK_SIZE];
    unsigned char *date = (unsigned char *)malloc(AES_BLOCK_SIZE*3);
    unsigned char *encrypt = (unsigned char *)malloc(AES_BLOCK_SIZE*3 + 4);
    unsigned char *plain = (unsigned char *)malloc(AES_BLOCK_SIZE*3);
    AES_KEY key;

    memset((void*)userkey, 'k', AES_BLOCK_SIZE);
    memset((void*)date, 'p', AES_BLOCK_SIZE*3);
    memset((void*)encrypt, 0, AES_BLOCK_SIZE*6);
    memset((void*)plain, 0, AES_BLOCK_SIZE*3);

    /*设置加密key及密钥长度*/
    AES_set_encrypt_key(userkey, AES_BLOCK_SIZE*8, &key);

    int len = 0;
    /*循环加密，每次只能加密AES_BLOCK_SIZE长度的数据*/
while(len < AES_BLOCK_SIZE*3) {
        AES_encrypt(date+len, encrypt+len, &key);    
        len += AES_BLOCK_SIZE;
    }

    /*设置解密key及密钥长度*/    
    AES_set_decrypt_key(userkey, AES_BLOCK_SIZE*8, &key);

    len = 0;
    /*循环解密*/
while(len < AES_BLOCK_SIZE*3) {
        AES_decrypt(encrypt+len, plain+len, &key);    
        len += AES_BLOCK_SIZE;
    }

    /*解密后与原数据是否一致*/
    if(!memcmp(plain, date, AES_BLOCK_SIZE*3)){
        printf("test success\n");    
    }else{
        printf("test failed\n");    
    }

    printf("encrypt: ");
    int i = 0;
    for(i = 0; i < AES_BLOCK_SIZE*3 + 4; i++){
        printf("%.2x ", encrypt[i]);
        if((i+1) % 32 == 0){
            printf("\n");    
        }
    }
    printf("\n");    

    return 0;
}

/*
	编译指令:g++ test.cpp -o test -I /usr/local/ssl/include/ -L /usr/local/ssl/lib/ -lcrypto -lssl
*/
