if (revol == 1)
            {
               file << i << " " << r2 << " " << v << " " << vr << " " << (i * dt) / 60 << endl;
                if (r2 <= R)
                cout << "One full revolution completed.\n";
                break;   // ✅ STOP exactly at 1 orbit
            }