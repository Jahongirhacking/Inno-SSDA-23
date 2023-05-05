// Jahongir Hayitov CS-01
// J.Hayitov@innopolis.university
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define rep(i,n) for (ll i = 0; i < (n); ++i)
#define ERROR "Error: the dimensional problem occurred\n"
#define NOT_APPLICABLE "The method is not applicable!"
#define DIFF 1e-6
#define PREC 2
double EPSILON;

#ifdef WIN32
    #define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
    #define GNUPLOT_NAME "gnuplot -persist"
#endif

int main() {
    ifstream inFile ("input.txt");
    double  V0, K0, a1, b1, a2, b2, T, v0, k0;
    int N;
    // Enter the Input
    inFile >> V0 >> K0 >> a1 >> b1 >> a2 >> b2 >> T >> N;
    vector<double> victims(N+1, 0.0);
    vector<double> killers(N+1, 0.0);
    vector<double> moments(N+1, 0.0);
    v0= V0 -(a2 / b2);
    k0= K0- (a1 / b1);
    victims[0] = V0;
    killers[0] = K0;
    moments[0] = 0;
    double moment = 0;
    // Calculation Part
    rep(k, N) {
        int i = k+1;
        // for each moment
        moment +=  T / N;
        moments[i] = moment;
        victims[i] = (v0 * cos(sqrt(a1 * a2) * moment)) - (k0 * ((sqrt(a2) * b1)
                / (b2 * sqrt(a1)) ) * sin(sqrt(a1 * a2) * moment)) + (a2 / b2);
        killers[i] = (v0 * ((sqrt(a1) * b2) / (b1 * sqrt(a2))) * sin(sqrt(a1 * a2)
                * moment)) + (k0 * cos(sqrt(a1 * a2) * moment)) + (a1 / b1);
    }

    #ifdef WIN32
        FILE* pipe = _popen(GNUPLOT_NAME, "w");
    #else
        FILE* pipe = popen(GNUPLOT_NAME, "w");
    #endif

        if (pipe != NULL)
        {
            fprintf(pipe, "set yrange [%f:%f]\n", 0.0,  150.0);
            fprintf(pipe, "set xrange [%f:%f]\n",  0.0, 50.0);
            fprintf(pipe, "set xlabel 't'\n");
            fprintf(pipe, "set ylabel 'Population'\n");
            fprintf(pipe, "set title 'Predator/Prey Populations Over Time'\n");
            fprintf(pipe, "plot '-' using 1:2 title 'Killer population' with lines, '-' using 1:2 title 'Victim population' with lines\n");

            // Graph of Killers
            rep(i, N+1){
                fprintf(pipe, "%f\t%f\n", moments[i], killers[i]);
            }
            fprintf(pipe, "e\n");
            fflush(pipe);

            // Graph of Victims
            rep(i, N+1){
                fprintf(pipe, "%f\t%f\n", moments[i], victims[i]);
            }
            fprintf(pipe, "e\n");
            fflush(pipe);

            #ifdef WIN32
                    _pclose(pipe);
            #else
                    pclose(pipe);
            #endif
        } else  cout << "Could not open file" << endl;

    return 0;
}
