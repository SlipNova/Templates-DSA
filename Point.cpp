
template <typename T>
class P {
public:
    T x, y;

    P() : x(0), y(0) {}
    P(T _x, T _y) : x(_x), y(_y) {}

    P& operator+=(const P& p2) {
        x += p2.x; y += p2.y; return *this;
    }

    P& operator-=(const P& p2) {
        x -= p2.x; y -= p2.y; return *this;
    }

    P& operator/=(const P& p2) {
        x /= p2.x; y /= p2.y; return *this;
    }

    P operator+(const P& p2) const {
        return P(x + p2.x, y + p2.y);
    }

    P operator-(const P& p2) const {
        return P(x - p2.x, y - p2.y);
    }

    T operator*(const P& p2) const {
        return x * p2.x + y * p2.y;
    }

    T cross(const P& p2) const {
        return x * p2.y - y * p2.x;
    }
    
    int onLeft(const P& p2, const P& p3) {
        P<T> line2 = p3 - p2;
        P<T> line1 = *this - p2;
        T val = line2.cross(line1);
        if (val > 0) {
            return 1;
        }
        else if (val < 0) {
            return -1;
        }
        else {
            return 0;
        }
    }

    template <typename U>
    friend ostream& operator<<(ostream& os, const P<U>& p);

    template <typename U>
    friend istream& operator>>(istream& is, P<U>& p);
};

template <typename T>
ostream& operator<<(ostream& os, const P<T>& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

template <typename T>
istream& operator>>(istream& is, P<T>& p) {
    return is >> p.x >> p.y;
}

template <typename T>
T norm(const P& a) {
    return a.dot(a);
}

ld abs(const P& a) {
    return sqrt(norm(a));
}


