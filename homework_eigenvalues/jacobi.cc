# include "jacobi.h"
# include <cmath>
# include <vector>
# include <algorithm>
# include <utility>


// Opgave A.1:
void timesJ(pp::matrix& A, std::size_t p, std::size_t q, double theta) { 
    // bruger std::size_t i stedet for int, men p og q er indices
    double c = std::cos(theta);
    double s = std::sin(theta);
    
    for (std::size_t i = 0; i < A.rows(); ++i) {
        // bruger A.rows() i stedet for A.size() (en anden måde at skrive rows på basically) 
        // (Jeg har definieret A.rows() til at være number of rows i min linalg.h fil så det
        // er den jeg bruger her)
        double aip = A(i, p); // bruger () i stedet for [] fordi min matrix class
                              // har defineret min operator() til at forstå () og ikke []
                              // Jeg kunne også ændre min operator til double& operator[](int i, int j); 
        double aiq = A(i, q);
        A(i, p) = c * aip - s * aiq; 
        A(i, q) = s * aip + c * aiq;
    }
}

// Opgave A.2: 
void Jtimes(pp::matrix& A, std::size_t p, std::size_t q, double theta) {
    double c = std::cos(theta);
    double s = std::sin(theta);

    for (std::size_t j = 0; j < A.cols(); ++j) {
        double apj = A(p, j);
        double aqj = A(q, j);
        A(p, j) = c * apj + s * aqj;
        A(q, j) = -s * apj + c * aqj;
    }
}


// Opgave A.3:
JacobiResult jacobi(pp::matrix A, double eps, int maxSweeps) {  
    // Her har vi the function definition af den function declaration vi lavede i .h filen
    // Function declaration: return_type function_name(parameters)
    // JacobiResult er return_typen og den refererer til den struct i jacobi.h filen som returnerer 
    // eigenvectorer, eigenværdier, sweeps og rotationer.
    // double eps er hvornår et off-diagonal element er lille nok til basically at være 0
    // int maxSweeps er for at undgå et uendeligt loop
    std::size_t n = A.rows(); // n definerers som antallet af rows i matrix A
    pp::matrix V = pp::matrix::identity(n); // definerer V som er en identitetsmatrix med n rows og n columns

    int sweeps = 0; // initialiserer sweeps til 0. tæller antal sweeps
    int rotations = 0; // initialiserer rotations til 0. tæller antal rotations

    for (int sweep = 0; sweep < maxSweeps; ++sweep) { 
        // her starter vi et forloop der kører så længe
        // sweep er mindre end maxSweeps. Efter hvert loop lægger
        // vi 1 til sweep med ++sweep. 

        // Den her del er samme kode som fra opgaven:
        bool changed;

        do {
            changed = false; 

            for (std::size_t p = 0; p < n-1; p++) {
                for (std::size_t q = p+1; q < n; q++) {

                    double apq = A(p,q);
                    if (std::abs(apq) < eps) continue; // added so eps doesn't show a warning
                                                        // forstår ikke helt hvorfor den skal
                                                        // være der men chat siger jeg ikke
                                                        // skal slette det så jeg lader være lol

                    double app = A(p,p);
                    double aqq = A(q,q);

                    double theta = 0.5 * std::atan2(2*apq, aqq-app);
                    double c = std::cos(theta);
                    double s = std::sin(theta);
                    double new_app = c*c*app-2*s*c*apq+s*s*aqq;
                    double new_aqq=s*s*app+2*s*c*apq+c*c*aqq;
                    if(new_app!=app || new_aqq!=aqq) // do rotation
			                {
                            changed = true;
                            ++rotations;
                            timesJ(A,p,q,theta);
                            Jtimes(A,p,q,-theta);
                            timesJ(V,p,q,theta);
                            }
                }
            }

        } while(changed);

        ++sweeps; // increments the sweep counter
        if (!changed) break; // if nothing changed during the sweep, stop the algorithm
    }

    pp::vector eigenvalues(n);
    for (std::size_t i = 0; i < n; ++i) {
        eigenvalues[i] = A(i, i);
    }

    std::vector<std::pair<double, std::size_t>> pairs(n);
    for (std::size_t i = 0; i < n; ++i) {
        pairs[i] = {eigenvalues[i], i};
    }
    std::sort(pairs.begin(), pairs.end());

    pp::vector sortedVals(n);
    pp::matrix sortedVecs(n, n, 0.0);

    for (std::size_t k = 0; k < n; ++k) {
        sortedVals[k] = pairs[k].first;
        std::size_t oldCol = pairs[k].second;
        for (std::size_t i = 0; i < n; ++i) {
            sortedVecs(i, k) = V(i, oldCol);
        }
    }

    return {sortedVals, sortedVecs, sweeps, rotations};
}