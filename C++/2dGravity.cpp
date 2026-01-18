#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// -------------------- CONSTANTS --------------------
const double G = 6.674e-11;
const double M = 5.972e24;
const double R = 6.371e6;

// -------------------- EFFECTIVE POTENTIAL --------------------
double Veff(double r, double L)
{
    return -G * M / r + (L * L) / (2.0 * r * r);
}

int main()
{
    // -------------------- INITIAL CONDITIONS --------------------
    double r0 = R + 300e3;                     // 300 km altitude
    double x = r0, y = 0.0;
    double vx = 0.0;
    double k = 1.3;                            // velocity multiplier
    double vy = k * sqrt(G * M / r0);

    double dt = 1.0;                           // timestep (seconds)

    // -------------------- TRACKERS --------------------
    double vr_prev = 0.0;
    bool firstStep = true;

    double r_apo = -1.0;
    double r_peri = 1e100;

    double t_peri_1 = -1.0;
    double t_peri_2 = -1.0;
    int peri_count = 0;

    double E_min = 1e100, E_max = -1e100;
    double L_min = 1e100, L_max = -1e100;

    // -------------------- FILES --------------------
    ofstream orbitFile("orbitdata.txt");
    orbitFile << "t(s) x y r v E L\n";

    // -------------------- MAIN INTEGRATION LOOP --------------------
    for (int i = 0; i < 200000; i++)
    {
        double t = i * dt;

        double r = sqrt(x*x + y*y);

        // acceleration (Newtonian gravity)
        double ax = -G * M * x / (r*r*r);
        double ay = -G * M * y / (r*r*r);

        // position update (Velocity Verlet)
        x += vx * dt + 0.5 * ax * dt * dt;
        y += vy * dt + 0.5 * ay * dt * dt;

        double r2 = sqrt(x*x + y*y);

        double ax2 = -G * M * x / (r2*r2*r2);
        double ay2 = -G * M * y / (r2*r2*r2);

        vx += 0.5 * (ax + ax2) * dt;
        vy += 0.5 * (ay + ay2) * dt;

        // -------------------- DIAGNOSTICS --------------------
        double v2 = vx*vx + vy*vy;
        double v = sqrt(v2);

        double vr = (x*vx + y*vy) / r2;

        double E = 0.5 * v2 - G * M / r2;
        double L = x*vy - y*vx;

        E_min = min(E_min, E);
        E_max = max(E_max, E);
        L_min = min(L_min, L);
        L_max = max(L_max, L);

        // -------------------- EVENT DETECTION --------------------
        if (!firstStep)
        {
            // Apoapsis
            if (vr_prev > 0 && vr < 0)
            {
                r_apo = r2;
                cout << "Apoapsis at r = " << r_apo
                     << " m  time = " << t/60 << " min\n";
            }

            // Periapsis
            if (vr_prev < 0 && vr > 0)
            {
                r_peri = r2;
                peri_count++;

                if (peri_count == 1)
                {
                    t_peri_1 = t;
                    cout << "Periapsis 1 at r = " << r_peri
                         << " m  time = " << t/60 << " min\n";
                }
                else if (peri_count == 2)
                {
                    t_peri_2 = t;
                    cout << "Periapsis 2 at r = " << r_peri
                         << " m  time = " << t/60 << " min\n";
                    break;   // one full orbit completed
                }
            }
        }

        vr_prev = vr;
        firstStep = false;

        orbitFile << t << " " << x << " " << y << " "
                  << r2 << " " << v << " " << E << " " << L << "\n";
    }

    orbitFile.close();

    // -------------------- ORBITAL ELEMENTS --------------------
    double a = 0.5 * (r_apo + r_peri);
    double e = (r_apo - r_peri) / (r_apo + r_peri);
    double T_sim = t_peri_2 - t_peri_1;

    cout << "\n--- ORBIT SUMMARY ---\n";
    cout << "Semi-major axis a = " << a << " m\n";
    cout << "Eccentricity e   = " << e << "\n";
    cout << "Orbital period   = " << T_sim/60 << " min\n";
    cout << "Energy drift     = " << (E_max - E_min) << "\n";
    cout << "Angular momentum drift = " << (L_max - L_min) << "\n";
    cout << "Emax: " << E_max << endl;
    cout << "Emax: " << E_min << endl;

    // -------------------- EFFECTIVE POTENTIAL OUTPUT --------------------
    ofstream veffFile("veff.txt");
    for (double rr = R; rr <= 5 * r_apo; rr += 1000)
        veffFile << rr << " " << Veff(rr, L_min) << "\n";
    veffFile.close();

    return 0;
}
