#include "clave_valor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc/rpc.h>


int init(){
    CLIENT *clnt;
    enum clnt_stat retval_1;
    int result_1;

    char *host = getenv("IP_TUPLAS");

    clnt = clnt_create(host, CLAVE_VALOR, CLAVE_VALOR_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    retval_1 = init_1(&result_1, clnt);
    if (retval_1 != RPC_SUCCESS) {
        clnt_perror(clnt, "call failed");
    }

    return result_1;
}

int set_value(int clave, char *valor1, int N_value2, double *V_value2){
    CLIENT *clnt;
    enum clnt_stat retval_2;
    int result_2;
    value_args set_value_1_arg1;

    char *host = getenv("IP_TUPLAS");

    clnt = clnt_create(host, CLAVE_VALOR, CLAVE_VALOR_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    set_value_1_arg1.key = clave;
    set_value_1_arg1.value1 = valor1;
    set_value_1_arg1.N_value2 = N_value2;
    set_value_1_arg1.V_value2.double_array_len = N_value2;
    set_value_1_arg1.V_value2.double_array_val = (double *)malloc(N_value2 * sizeof(double));
    for (int i = 0; i < N_value2; i++) {
        set_value_1_arg1.V_value2.double_array_val[i] = V_value2[i];
    }

    retval_2 = set_value_1(set_value_1_arg1, &result_2, clnt);
    if (retval_2 != RPC_SUCCESS) {
        clnt_perror(clnt, "call failed");
    }

    return result_2;
}

int get_value(int key, char *value1, int *N_value2, double *V_value2){
    CLIENT *clnt;
    enum clnt_stat retval_3;
    get_value_result result_3;
    int get_value_1_key;

    char *host = getenv("IP_TUPLAS");

    clnt = clnt_create(host, CLAVE_VALOR, CLAVE_VALOR_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    get_value_1_key = key;

    memset(&result_3, 0, sizeof(result_3));

    retval_3 = get_value_1(get_value_1_key, &result_3, clnt);
    if (retval_3 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

    if (result_3.status == 0) {
        // Comprueba si value1 y V_value2 son NULL antes de usarlos
        if (result_3.value1 == NULL || result_3.V_value2.double_array_val == NULL) {
            printf("Error: memoria no asignada\n");
            return -1;
        }

        strcpy(value1, result_3.value1);
        *N_value2 = result_3.N_value2;
        for (int i = 0; i < result_3.N_value2; i++) {
            V_value2[i] = result_3.V_value2.double_array_val[i];
        }
    }

    return result_3.status;
}


int modify_value(int clave, char *valor1, int N_value2, double *V_value2){
    CLIENT *clnt;
    enum clnt_stat retval_4;
    int result_4;
    value_args modify_value_1_arg1;

    char *host = getenv("IP_TUPLAS");

    clnt = clnt_create(host, CLAVE_VALOR, CLAVE_VALOR_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    modify_value_1_arg1.key = clave;
    modify_value_1_arg1.value1 = valor1;
    modify_value_1_arg1.N_value2 = N_value2;
    modify_value_1_arg1.V_value2.double_array_len = N_value2;
    modify_value_1_arg1.V_value2.double_array_val = (double *)malloc(N_value2 * sizeof(double));
    for (int i = 0; i < N_value2; i++) {
        modify_value_1_arg1.V_value2.double_array_val[i] = V_value2[i];
    }

    retval_4 = modify_value_1(modify_value_1_arg1, &result_4, clnt);
    if (retval_4 != RPC_SUCCESS) {
        clnt_perror(clnt, "call failed");
    }

    return result_4;
}

int delete_key(int clave){
    CLIENT *clnt;
    enum clnt_stat retval_5;
    int result_5;

    char *host = getenv("IP_TUPLAS");

    clnt = clnt_create(host, CLAVE_VALOR, CLAVE_VALOR_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    retval_5 = delete_key_1(clave, &result_5, clnt);
    if (retval_5 != RPC_SUCCESS) {
        clnt_perror(clnt, "call failed");
    }

    return result_5;
}

int exist(int clave){
    CLIENT *clnt;
    enum clnt_stat retval_6;
    int exist_1_key;

    char *host = getenv("IP_TUPLAS");

    clnt = clnt_create(host, CLAVE_VALOR, CLAVE_VALOR_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }

    exist_1_key = clave;

    retval_6 = exist_1(exist_1_key, &exist_1_key, clnt);
    if (retval_6 != RPC_SUCCESS) {
        clnt_perror(clnt, "call failed");
    }

    return exist_1_key;
}