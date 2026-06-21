#include "roots.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

// Opgave A
// pp::matrix jacobian(
//     std::function<pp::vector(pp::vector)> f,
//     pp::vector x,
//     pp::vector fx
// )
// {
//     std::size_t n = x.size(); // n = len(x)

//     pp::matrix J(n, n); // laver en J matrix

//     for(std::size_t j = 0; j < n; j++){ // c++ version af python kode - oversat af chat
//         double dx = std::max(std::abs(x[j]), 1.0) * std::pow(2.0, -26);

//         x[j] += dx;
//         pp::vector df = f(x) - fx;

//         for(std::size_t i = 0; i < n; i++){
//             J(i,j) = df[i]/dx;
//         }

//         x[j] -= dx;
//     }

//     return J;
// }

// pp::vector newton(
//     std::function<pp::vector(pp::vector)> f,
//     pp::vector x,
//     double acc,
//     double alpha_min,
//     int max_iter
// )
// {
//     pp::vector fx = f(x); // definerer f(x) vektoren 

//     for(int iter = 0; iter < max_iter; iter++){
//         if(fx.norm() < acc){
//             break;
//         }

//         pp::matrix J = jacobian(f, x, fx);

//         pp::vector minus_fx = fx * (-1.0);

//         pp::qr decomp(J);
//         pp::vector Dx = decomp.solve(minus_fx); // Newton's step

//         double alpha = 1.0;

//         pp::vector z;
//         pp::vector fz;

//         while(true){
//             z = x + alpha*Dx;
//             fz = f(z);

//             // if(fz.norm() < (1.0 - alpha/2.0)*fx.norm()){
//             //     break;
//             // }
//             // Simple backtracking condition from the assignment:
//             if(fz.norm() < fx.norm()){
//                 break;
//             }

//             if(alpha < alpha_min){
//                 break; // accept the bad step anyway
//             }

//             alpha /= 2.0; // replace alpha med alpha/2
//         }

//         x = z;
//         fx = fz;

//         // Optional safety stop:
//         // If the Newton step becomes extremely small, stop.
//         if((alpha*Dx).norm() < std::pow(2.0, -26)*std::max(x.norm(), 1.0)){
//             break;
//         }
//     }

//     return x;
// }

// Opgave C:
void jacobian(
    std::function<pp::vector(pp::vector)> f,
    pp::vector x,
    const pp::vector& fx,
    pp::matrix& J
)
{
    std::size_t n = x.size();

    for(std::size_t j = 0; j < n; j++){
        double dx =
            std::max(std::abs(x[j]), 1.0) * std::pow(2.0, -26);

        x[j] += dx;
        pp::vector df = f(x) - fx;

        for(std::size_t i = 0; i < n; i++){
            J(i,j) = df[i]/dx;
        }

        x[j] -= dx;
    }
}


pp::vector newton(
    std::function<pp::vector(pp::vector)> f,
    pp::vector x,
    double acc,
    double alpha_min,
    int max_iter
)
{
    pp::vector fx = f(x);

    // Allocate the Jacobian only once.
    pp::matrix J(x.size(), x.size());

    for(int iter = 0; iter < max_iter; iter++){
        if(fx.norm() < acc){
            break;
        }

        // Update the existing matrix.
        jacobian(f, x, fx, J);

        pp::qr decomp(J);
        pp::vector Dx = decomp.solve(-1.0*fx);

        double alpha = 1.0;

        // Quantities known at alpha = 0.
        double phi0 = 0.5*fx.dot(fx);
        double dphi0 = -fx.dot(fx);

        pp::vector z = x + alpha*Dx;
        pp::vector fz = f(z);

        while(
            fz.norm() >= (1.0 - alpha/2.0)*fx.norm()
            && alpha >= alpha_min
        ){
            double phi_trial = 0.5*fz.dot(fz);

            // Quadratic coefficient from equation (11).
            double c =
                (phi_trial - phi0 - dphi0*alpha)
                /(alpha*alpha);

            double alpha_next;

            if(c > 0.0 && std::isfinite(c)){
                // Minimum of the quadratic interpolation.
                alpha_next = -dphi0/(2.0*c);
            }
            else{
                // Fallback if the quadratic has no useful minimum.
                alpha_next = alpha/2.0;
            }

            // Ensure that this is actually a backtracking step.
            alpha = std::min(alpha_next, alpha/2.0);

            z = x + alpha*Dx;
            fz = f(z);
        }

        x = z;
        fx = fz;

        double dx_scale =
            std::pow(2.0, -26)*std::max(x.norm(), 1.0);

        if((alpha*Dx).norm() < dx_scale){
            break;
        }
    }

    return x;
}