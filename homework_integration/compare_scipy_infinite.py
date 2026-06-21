import scipy.integrate as integrate
import math

def compare(name, f, a, b, exact):
    result, error_estimate, info = integrate.quad(
        f,
        a,
        b,
        epsabs=0.001,
        epsrel=0.001,
        full_output=True
    )

    print(name)
    print("scipy result =", result)
    print("exact =", exact)
    print("actual error =", abs(result - exact))
    print("scipy error estimate =", error_estimate)
    print("function calls =", info["neval"])
    print()

compare(
    "Integral exp(-x) from 0 to infinity",
    lambda x: math.exp(-x),
    0,
    math.inf,
    1.0
)

compare(
    "Integral exp(-x*x) from -infinity to infinity",
    lambda x: math.exp(-x*x),
    -math.inf,
    math.inf,
    math.sqrt(math.pi)
)