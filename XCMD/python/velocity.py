from scipy import array, sqrt, arange, pi, exp
from matplotlib import pyplot


def xcmd_read_output_data(filepath, N):
	""" Read the data file (coordinates, velocities and forces) output by XCMD. 

	Parameters
	----------
	filepath : str
		The path to the file.
	N : int
		The total number of atoms in each configuration.

	Returns
	-------
	List : list
		A list of configurations. Each configuration is a N-by-3 ndarray.

	"""
	f = open(filepath, "r")
	conf = []
	List = []
	for line in f:
		e = line.split()
		if len(e) != 4:
			continue
		x = float(e[1])
		y = float(e[2])
		z = float(e[3])
		conf.append([x, y, z])
		if len(conf) == N:
			List.append(array(conf))
			conf = []
		pass
	return List


def gaussian(mu, sigma, xmin, xmax):
	delt = (xmax - xmin) * 0.001
	c = 1.0 / (sqrt(2.0 * pi) * sigma)
	x = arange(xmin, xmax, delt)
	s = 0.5 / sigma / sigma
	return x, c * exp(-((x - mu)**2) * s)


def xcmd_plot_velocity_distribution(V):
	""" Plot the velocity distribution. 

	Parameters
	----------
	V : ndarray
		A N-by-3 ndarray containing the velocities of each atom.
	
	"""
	dist = sqrt((V**2).sum(axis=1))
	mu = dist.mean()
	sigma = sqrt(((dist - mu)**2).sum())
	gx, gy = gaussian(mu, sigma, -5.0, 5.0)
	pyplot.subplot(121)
	pyplot.title("Histogram")
	pyplot.hist(dist, bins=int(V.shape[0]/2.5))
	pyplot.subplot(122)
	pyplot.title("Approximated Distribution")
	pyplot.plot(gx, gy, "r")
	pyplot.show()


vout = ""
D = xcmd_read_output_data(vout, 125)
print("Total {:d} configurations found!".format(len(D)))
xcmd_plot_velocity_distribution(D[2])

