Everything is run by running
make clean
make

The tasks are split into these parts:
./main A3
./main A4
./main B1
./main B2
./main B3
./main C

The outputs are placed in files:
./main A3 > data.txt
./main A4 > pendulum.txt
./main B1 > orbit_B1.txt
./main B2 > orbit_B2.txt
./main B3 > orbit_B3.txt
./main C > three_body_C.txt

For the harmonic-oscillator plot:
./main A3 > data.txt
gnuplot plot.gpi

Note to self: Numerical u should follow cos(x), and numerical u' should follow -sin(x).

AI was used for coding in general. 


Code explanation:
This homework is about solving ordinary differential equations numerically.

The main idea is that higher order differential equations are rewritten as systems
of first order differential equations. For example, if
u'' = g(x, u, u') 
then we define
y0 = u
y1 = u'
so that
y0' = y1
y1' = g(x, y0, y1)

The implementation is split into the files ode.h and ode.cc.
The file ode.h declares the functions and ode.cc contains the actual
implementation. I use pp::vector from linalg.h because the ODE solver should
work for systems with more than one component.

Task A1 is the implementation of the stepper rkstep12.
I use the function from the assignment.
Explanation for code is written in the code. 

The stepper takes one step from x to x+h for an equation of the form
y' = f(x,y)

The code uses the embedded Euler/midpoint method from the assignment:

k0 = f(x, y)
k1 = f(x + h/2, y + k0*h/2)
yh = y + k1*h
dy = (k1 - k0)*h

k0 is the Euler slope at the beginning of the interval.
k1 is the midpoint slope. First the code estimates the value halfway through
the interval using Euler's method, and then it evaluates the slope there.

yh is the better estimate for y(x+h).
dy is the error estimate. It is found by comparing the lower order Euler
estimate with the higher order midpoint estimate.

The function returns both yh and dy as a tuple.


Task A2 is the implementation of the adaptive driver.

The driver takes the function f, the interval from a to b, the initial value
yinit, an initial step size h, and the accuracy parameters acc and eps.

The driver starts by storing the initial point:
xlist.push_back(x)
ylist.push_back(y)

Then it keeps taking steps until x reaches b.
Before each step it checks whether x+h goes past b. If it does, the step size is
changed so that the final step lands exactly on b.

For every attempted step the driver calls rkstep12:

auto [yh, dy] = rkstep12(f, x, y, h)

Then it calculates the tolerance

tol = (acc + eps*yh.norm()) * sqrt(h/(b-a))

and compares it to the estimated error

err = dy.norm()

If err <= tol, the step is accepted. Then x and y are updated and the new point
is stored in xlist and ylist.

After each attempted step the step size is adjusted using

h *= min((tol/err)^0.25 * 0.95, 2.0)

The power 0.25 and the safety factor 0.95 come from the adaptive step-size rule
in the notes. The factor 2.0 prevents the step size from growing too quickly.

If the estimated error is zero, the code simply doubles the step size.
I also added a check that throws an error if h becomes non-positive.

In my implementation I also set hmax = 0.05, so the step size cannot become
larger than 0.05. This makes the plotted curves smoother.


Task A3 is the harmonic oscillator test.

The equation is

u'' = -u

I rewrite it as

y0 = u
y1 = u'
y0' = y1
y1' = -y0

The initial conditions are

u(0) = 1
u'(0) = 0

The exact solution is

u(x) = cos(x)
u'(x) = -sin(x)

The code integrates from x = 0 to x = 10 and prints

x, u_numeric, u_exact, uprime_numeric, uprime_exact

This is used as a test because the numerical solution can be compared directly
with cos(x) and -sin(x).

The output is saved with

./main A3 > data.txt

and plotted with

gnuplot plot.gpi

This produces harmonic_oscillator.svg.


Task A4 is the damped pendulum example.

The equation is written as a first order system:

theta' = omega
omega' = -b*omega - c*sin(theta)

In the code I use

b = 0.25
c = 5.0
theta(0) = pi - 0.1
omega(0) = 0

The code integrates from t = 0 to t = 10 and prints

t, theta, omega

The output is saved with

./main A4 > pendulum.txt

and plotted with

gnuplot plot_pendulum.gpi

This produces pendulum.svg.


Task B is about planetary orbits.

The equation used in the code is

u'' = 1 - u + epsilon*u^2

where u = 1/r and phi is the independent variable.

Again this is rewritten as a first order system:

y0 = u
y1 = u'
y0' = y1
y1' = 1 - y0 + epsilon*y0^2

After solving for u(phi), the code converts to Cartesian coordinates for
plotting:

r = 1/u
x = r*cos(phi)
y = r*sin(phi)

The program prints

phi, u, uprime, x, y

The plots use columns 4 and 5, which are x and y.


Task B1 is the circular Newtonian orbit.

Here I use

epsilon = 0
u(0) = 1
u'(0) = 0

Since u stays equal to 1, r also stays equal to 1. This gives a circular orbit.

The output is saved with

./main B1 > orbit_B1.txt

and plotted with

gnuplot plot_B1.gpi

This produces orbit_B1.svg.


Task B2 is the elliptical Newtonian orbit.

Here I still use

epsilon = 0

but I change the initial derivative to

u'(0) = -0.5

This makes u change with phi, so r = 1/u also changes. Therefore the orbit is
elliptical instead of circular.

The output is saved with

./main B2 > orbit_B2.txt

and plotted with

gnuplot plot_B2.gpi

This produces orbit_B2.svg.


Task B3 is the relativistic correction / precessing orbit.

Here I use

epsilon = 0.01
u(0) = 1
u'(0) = -0.5

The extra epsilon*u^2 term changes the orbit so that it no longer closes exactly
after each rotation. This gives a precessing orbit.

The integration is done over 20 rotations instead of 10 rotations, so the
precession is easier to see in the plot.

The output is saved with

./main B3 > orbit_B3.txt

and plotted with

gnuplot plot_B3.gpi

This produces orbit_B3.svg.

For task C we do the following
1. Store all velocities and positions in one 12-component vector.
2. Define a function that computes all accelerations from Newtonian gravity.
3. Tell the ODE driver to integrate that system in time.
4. Print the positions of all three bodies.
5. Plot x versus y for each body.

The program prints

t, x1, y1, x2, y2, x3, y3

The output is saved with

./main C > three_body_C.txt

and plotted with

gnuplot plot_C.gpi









