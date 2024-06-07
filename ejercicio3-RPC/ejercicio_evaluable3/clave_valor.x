typedef double double_array<>;

struct value_args {
    int key;
    string value1<>;
    int N_value2;
    double_array V_value2;
};


struct get_value_result {
    int status;
    string value1<256>;
    int N_value2;
    double_array V_value2;
};

program CLAVE_VALOR {
    version CLAVE_VALOR_V1 {
        int INIT(void) = 1;
        int SET_VALUE(value_args) = 2;
        get_value_result GET_VALUE(int key) = 3;
        int MODIFY_VALUE(value_args) = 4;
        int DELETE_KEY(int key) = 5;
        int EXIST(int key) = 6;
    } = 1;
} = 99; 
