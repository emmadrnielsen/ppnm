Run everything with

make clean
make

Individual tasks can be run as

./main A2
./main A3
./main A4
./main B2
./main B4
./main C

A2 prints tests of the adaptive integrator on known integrals.

A3 prints values of erf(z), compares them with std::erf(z), and is used
to make erf.svg.

A4 studies how the error in erf(1) changes when acc is made smaller.
The output is used to make erf_convergence.svg.

B2 compares ordinary adaptive integration with the Clenshaw-Curtis
transformation.

B4 tests integrals with infinite limits.

C compares the estimated integration error with the actual error.


The files that are generated are:

erf_data.txt              data for erf.svg
erf_convergence.txt       data for erf_convergence.svg
B2compare.txt             output from ./main B2
infinite_tests.txt        output from ./main B4
error_estimate.txt        output from ./main C
erf.svg                   plot of erf(z)
erf_convergence.svg       convergence plot for erf(1)




The following is a description of what the code does:
Opgave A
Explanation of the problem:

We want to make an adaptive integrator that estimates the
integral of a given function f(x)

What is an adaprive integrator?
A non-adaptive integrator would decide in advance how many
points to use
For example:
a                                              b
|----|----|----|----|----|----|----|----|----|

An adaptive integrator does not decide all the points in
advance. Instead, it first tries the whole interval:
[a--------------------------------------------b]

It estimates the integral and asks:
"is my estimated error small enough?"
If yes, it stops.
If no, it splits the interval in half:
[a---------------------m][m-------------------b]
Maybe the left half is easy so it stops there but the
right half is difficult, so it splits again:
[m----------n][n--------b]
So after a while, you may get something like:
[a---------------------m][m----------n][n---p][p---b]

This means it uses large intervals where the function is
smooth, and small intervals where the function changes
quickly or is difficult.

Recursive means that the function calls itself on smaller
intervals.

So overall what we wanna do is

1. Estimate the integral on [a, b].
2. Estimate the error.
3. If the error is small enough, accept the result.
4. If the error is too large, split the interval into two
   parts: [a, (a+b)/2] and [(a+b)/2, b]
5. Repeat the same process recursively on each half.

I koden fra opgaven defineres h = b - a, hvorefter
de fire evaluation points er
x1 = a + h/6
x2 =  a + 2h/6
x3 = a + 4h/6
x4 = a + 5h/6

The algorithm computes two estimates of the same integral.
The higher-order estimate is:
double Q = (2*f1 + f2 + f3 + 2*f4)/6 * (b-a);

The lower-order estimate is:
double q = (f1 + f2 + f3 + f4)/4 * (b-a);

The error estimate is then the difference between these
double err = std::abs(Q - q);

We accept the result if the estimated error is smaller
than the tolerance:
acc = absolute accuracy goal
eps = relative accuracy goal
double tol = acc + eps*std::abs(Q);

If err < tol then we return Q. If not, we split the
interval into two halves.

Reusing of points:
Suppose we split [a, b] into [a, m] and [m, b] where
m = (a+b)/2.
Some of the points already evaluated on the big interval
are exactly reused on the smaller intervals.

Opgave B
We make a change of variable.
For the standard interval [-1, 1], the transformation is
x = cos(theta)

When theta = 0 we get x = 1
When theta = pi we get x = -1

So as theta goes from 0 to pi, x goes from 1 to -1.
The derivative is -sin(theta)
So dx = -sin(theta)dtheta

Because the limits reverse direction, we get the first
formula in the question:
∫-11 f(x)dx = ∫0π f(cos(θ))sinθdθ

For a general interval [a, b], we need a transformation
that maps theta = 0 to x = b
and theta = pi to x = a

The formula is
x = (a+b)/2 + (b-a)/2 * cos(theta)

The derivative is
-(b-a)/2 * sin(theta)

Again, the minus sign is handled by reversing the limits so
the integral gives the second formula in the question
∫abdx f(x) = ∫0πdθ f( (a+b)/2+(b-a)/2*Cos(θ) )*Sin(θ)*(b-a)/2

Opgave B4:
Ligning 61 in lecture notes

For infinite limits, the code transforms the infinite interval into a
finite interval and then uses the same integration routine as before.

For an integral from a to infinity, the substitution is

x = a + (1-t)/t

where t goes from 0 to 1.

For an integral from minus infinity to infinity, the substitution is

x = t/(1-t^2)

where t goes from -1 to 1.

Opgave C:
This extends the integrator so that it returns both the integral and
the estimated error.

Instead of returning only Q, the function returns

(result, estimated_error)

If the interval is accepted, the estimated error is abs(Q-q).
If the interval is split into two parts, the total integral is the sum of
the two results, and the total error is combined as

sqrt(err_left^2 + err_right^2)