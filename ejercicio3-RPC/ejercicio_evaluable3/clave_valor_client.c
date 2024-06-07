#include "clave_valor.h"

void clave_valor_1(char *host) {
    CLIENT *clnt;
    enum clnt_stat retval_1;
    int result_1;
    enum clnt_stat retval_2;
    int result_2;
    value_args set_value_1_arg1;
    enum clnt_stat retval_3;
    get_value_result result_3;
    int get_value_1_key;
    enum clnt_stat retval_4;
    int result_4;
    value_args modify_value_1_arg1;
    enum clnt_stat retval_5;
    int result_5;
    int delete_key_1_key;
    enum clnt_stat retval_6;
    int result_6;
    int exist_1_key;

#ifndef DEBUG
    clnt = clnt_create (host, CLAVE_VALOR, CLAVE_VALOR_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host);
        exit (1);
    }
#endif  /* DEBUG */

    retval_1 = init_1(&result_1, clnt);
    if (retval_1 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

	printf("INIT\n");

    set_value_1_arg1.key = 1;
    set_value_1_arg1.value1 = "Hola\0";
    set_value_1_arg1.N_value2 = 3;
    set_value_1_arg1.V_value2.double_array_len = 3;
    set_value_1_arg1.V_value2.double_array_val = (double *)malloc(3 * sizeof(double));
    set_value_1_arg1.V_value2.double_array_val[0] = 1.0;
    set_value_1_arg1.V_value2.double_array_val[1] = 2.0;
    set_value_1_arg1.V_value2.double_array_val[2] = 3.0;

    retval_2 = set_value_1(set_value_1_arg1, &result_2, clnt);
    if (retval_2 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

	set_value_1_arg1.key = 2;
    set_value_1_arg1.value1 = "Hola 2\0";
    set_value_1_arg1.N_value2 = 3;
    set_value_1_arg1.V_value2.double_array_len = 3;
    set_value_1_arg1.V_value2.double_array_val = (double *)malloc(3 * sizeof(double));
    set_value_1_arg1.V_value2.double_array_val[0] = 4.0;
    set_value_1_arg1.V_value2.double_array_val[1] = 5.0;
    set_value_1_arg1.V_value2.double_array_val[2] = 6.0;

    retval_2 = set_value_1(set_value_1_arg1, &result_2, clnt);
    if (retval_2 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

	printf("SET\n");

    get_value_1_key = 1;

	// Inicializa result_3 antes de usarlo
	memset(&result_3, 0, sizeof(result_3));

	retval_3 = get_value_1(get_value_1_key, &result_3, clnt);
	if (retval_3 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

	if (result_3.status == 0) {
    // Comprueba si value1 y V_value2.double_array_val son NULL antes de usarlos
    if (result_3.value1 == NULL || result_3.V_value2.double_array_val == NULL) {
        printf("Error: memoria no asignada\n");
        return;
    }

    printf("Valor: %s\n", result_3.value1);
    printf("Vector: ");
    for (int i = 0; i < result_3.N_value2; i++) {
        printf("%f ", result_3.V_value2.double_array_val[i]);
    }
    printf("\n");

    // Liberar la memoria después de usar los datos
    free(result_3.value1);
    free(result_3.V_value2.double_array_val);
}



printf("GET\n");


    modify_value_1_arg1.key = 1;
    modify_value_1_arg1.value1 = "Adios\0";
    modify_value_1_arg1.N_value2 = 3;
    modify_value_1_arg1.V_value2.double_array_len = 3;
    modify_value_1_arg1.V_value2.double_array_val = (double *)malloc(3 * sizeof(double));
    modify_value_1_arg1.V_value2.double_array_val[0] = 4.0;
    modify_value_1_arg1.V_value2.double_array_val[1] = 5.0;
    modify_value_1_arg1.V_value2.double_array_val[2] = 6.0;

    retval_4 = modify_value_1(modify_value_1_arg1, &result_4, clnt);
    if (retval_4 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

	printf("MOD\n");

    delete_key_1_key = 2;
    retval_5 = delete_key_1(delete_key_1_key, &result_5, clnt);
    if (retval_5 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

	printf("DEL\n");

    exist_1_key = 2;
    retval_6 = exist_1(exist_1_key, &result_6, clnt);
    if (retval_6 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed");
    }

    if (result_6 == 0) {
        printf("La clave existe\n");
    } else {
        printf("La clave no existe\n");
    }

	printf("EXIST\n");

	free(set_value_1_arg1.V_value2.double_array_val);
	free(modify_value_1_arg1.V_value2.double_array_val);

#ifndef DEBUG
    clnt_destroy (clnt);
#endif  /* DEBUG */
}

int main (int argc, char *argv[]) {
    char *host;
    if (argc < 2) {
        printf ("usage: %s server_host\n", argv[0]);
        exit (1);
    }
    host = argv[1];
    clave_valor_1 (host);
    exit (0);
}
