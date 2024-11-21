#include <iostream>
#include <functional>

struct AsNat {
    int value;

    AsNat(int v = 0) : value(v >= 0 ? v : 0) {}

    AsNat operator+(const AsNat& other) const {
        return AsNat(this->value + other.value);
    }

    AsNat operator-(const AsNat& other) const {
        return AsNat(this->value - other.value);
    }

    friend std::ostream& operator<<(std::ostream& os, const AsNat& an) {
        os << an.value;
        return os;
    }
};


AsNat z(const AsNat&) {
    return AsNat(0);
}


AsNat n_func(const AsNat& x) {
    return x + AsNat(1);
}




AsNat r(const AsNat& n, const AsNat& init_value,
        std::function<AsNat(const AsNat&)> base,
        std::function<AsNat(const AsNat&, const AsNat&)> r_step) {
    return (n.value == 0) ? base(init_value) : r_step(init_value, r(n - AsNat(1), init_value, base, r_step));
}


AsNat pred(const AsNat& x) {
    // Рекурсивное вычисление через подстановку
    return r(x, x, z, [](const AsNat& a, const AsNat&) -> AsNat { return a - AsNat(1); });
}


AsNat sub_base(const AsNat& x) {
    return x;
}

AsNat sub_r_step(const AsNat& x, const AsNat& y) {
    return pred(y);
}

AsNat sub(const AsNat& x, const AsNat& y) {
    return r(y, x, sub_base, sub_r_step);
}


AsNat add_base(const AsNat& x) {
    return x;
}


AsNat add_r_step(const AsNat&, const AsNat& y) {
    return n_func(y);
}


AsNat add(const AsNat& x, const AsNat& y) {
    return r(y, x, add_base, add_r_step);
}


AsNat multiply_base(const AsNat&) {
    return AsNat(0);
}

AsNat multiply_r_step(const AsNat& x, const AsNat& y) {
    return add(x, y);
}

AsNat multiply(const AsNat& x, const AsNat& y) {
    return r(y, x, multiply_base, multiply_r_step);
}

int main() {
    AsNat m = multiply(AsNat(25), AsNat(5));
    std::cout << "25 * 5 = " << m << " (Ожидается 125)\n";

    AsNat s = sub(AsNat(108), AsNat(101));
    std::cout << "108 - 101 = " << s << " (Ожидается 7)\n";

    std::cout << "pred(0) = " << pred(AsNat(0)) << " (Ожидается 0)\n";
    std::cout << "pred(1) = " << pred(AsNat(1)) << " (Ожидается 0)\n";
    std::cout << "pred(2) = " << pred(AsNat(2)) << " (Ожидается 1)\n";
    std::cout << "pred(3) = " << pred(AsNat(3)) << " (Ожидается 2)\n";

    std::cout << "sub(10, 5) = " << sub(AsNat(10), AsNat(5)) << " (Ожидается 5)\n";
    std::cout << "sub(5, 10) = " << sub(AsNat(5), AsNat(10)) << " (Ожидается 0)\n";
    std::cout << "sub(7, 7) = " << sub(AsNat(7), AsNat(7)) << " (Ожидается 0)\n";

    return 0;
}
