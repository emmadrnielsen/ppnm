import scipy.integrate as integrate
import math

def compare(name, f, a, b, exact):
    result, error_estimate, info = integrate.quad(
        f,
        a,
        b,
        epsabs=1e-6,
        epsrel=1e-6,
        full_output=True
    )

    print(name)
    print("scipy result =", result)
    print("actual error =", abs(result - exact))
    print("scipy error estimate =", error_estimate)
    print("function calls =", info["neval"])
    print()

compare(
    "Integral of 1/sqrt(x)",
    lambda x: 1/math.sqrt(x),
    0,
    1,
    2.0
)

compare(
    "Integral of log(x)/sqrt(x)",
    lambda x: math.log(x)/math.sqrt(x),
    0,
    1,
    -4.0
)