# PI computation in MPI

Key idea of computing PI in parallel:
PI is included in the formula of circle's area.
If we know the radius of circle, PI can be expressed:

$ \pi = \frac{S_{circle}}{R^2}$

Estimating of circle can be done with Monte-Carlo technique.
This technique can be described like this:

Imagine we have square are that is divided in 2 halves
by some continious curve:

![](pictures/monte_carlo1.png)

Our mission is to estimate area of space under the curve.
We randomly choose point from the square and check if it inside the circle
or not.

Probability for random point to get inside circle is proportional to the area of circle.

$ \frac{S_{circle}}{S_{square}} = \frac{Number of point inside circle}{Number of points} $

But if we connect it with previous formula we get:

$ \pi = \frac{Number of point inside circle}{Number of points} \cdot \frac{S_{square}}{R^2}$

That's it!

To compute PI we need:

'''
for N points:

	throw point
	check if it belongs to circle

pi = N_in_circle / N * SquareArea / (R^2)
'''

This process can be nicely parallized by
dividing square space into regions and assigning
single executor to every region. Thus programm for every
executor would look like:

'''
area = get_area(rank)
my_N = N / rank_size

my_N_in_circle = compute_points_in_circle(area, my_N)

send_to_main_process(my_N_in_circle)
'''