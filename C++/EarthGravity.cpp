// #include <iostream>
// #include <fstream>

// using namespace std;

// double gravityAccel(double r, double M)
// {
//     // const double G = 6.674e-11;
//     // return -G * M / (r * r);
//     return -9.81;
// }
// int main()
// {
//     const double G = 6.674e-11;
//     const double M = 5.972e24;
//     double r = 6.371e6 + 1000;
//     double v = 0.0;
//     double dt = 0.1;
//     ofstream file;
// file.open("gravity_data.txt");
// file << "KE PE TE v r\n";
//     for (int i = 0; i < 100000; i++)
//     {

//         double a = gravityAccel(r, M);

//         r = r + v * dt + 0.5 * a * dt * dt;
//         double a_new = gravityAccel(r, M);
//         double v = v + 0.5 * (a + a_new) * dt;

//         double m = 5;

//         double ke = .5 * m * v * v;

//         double pe = -(G * M * m) / r;
//         double te = pe + ke;
//         file << ke << " " << pe << " " << te << " "<< v << " "<<r<<endl;

//         if (r <= 6.371e6)
//         {
//             cout << "collision at i : " << i << " at t: " << i * dt << endl;
//             break;
//         }
//     }
//     file.close();

//     return 0;
// }

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    double h = 1000.0;     // height above ground (m)
    double v = 0.0;
    double dt = 0.1;
    double g = -9.81;
    double m = 5.0;

    ofstream file("gravity_data.txt");
    file << "KE PE TE v h\n";

    for (int i = 0; i < 150; i++) {

        double a = g;

        // Velocity Verlet
        h = h + v * dt + 0.5 * a * dt * dt;
        double a_new = g;
        v = v + 0.5 * (a + a_new) * dt;

        double ke = 0.5 * m * v * v;
        double pe = m * 9.81 * h;
        double te = ke + pe;

        file << ke << " " << pe << " " << te << " " << v << " " << h << "\n";

        if (h <= 0) {
            cout << "collision at i: " << i
                 << " at t: " << i * dt << " s\n";
            break;
        }
    }

    file.close();
    return 0;
}
