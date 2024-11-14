#include <iostream>



int z(int) {
    return 0;
}



int n(int x) {
    return x + 1;
}

int pred(int x) {
    int k = 0;
    if (x == 0) {
        return 0;
    }
    while(n(k) < x) {
        k = n(k);
    }
    return k;
}

int u1(int x, int) {
    return x;
}

int u2(int, int y) {
    return y;
}

int r(int n, int init_value, int (*base)(int), int (*r_step)(int, int)) {
    if (n == 0) {
        return base(init_value);
    }
    return r_step(init_value, r(n-1, init_value, base, r_step));
}

int add_base(int x) {
    return x;
}

int add_r_step(int, int y) {
    return n(y);
}

int add(int x, int y) {
    return r(y, x, add_base, add_r_step);
}

int multiply_base(int) {
    return 0;
}

int multiply_r_step(int x, int y) {
    return add(x, y);
}

int multiply(int x, int y) {
    return r(y, x, multiply_base, multiply_r_step);
}

int sub_base(int x) {
    return x;
}

int sub_r_step(int x, int y) {
    return pred(y);
}

int sub(int x, int y) {
    return r(y, x, sub_base, sub_r_step);
}


int main() {
    std::cout<<multiply(25, 5)<<" ";
    std::cout<<sub(108,101)<<" ";
}
