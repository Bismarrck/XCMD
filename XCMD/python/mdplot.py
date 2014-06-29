from matplotlib.pyplot import *

f = open("/Users/bismarrck/Desktop/md.out", "r")
etot = []
ekin = []
epot = []
step = []
k = 0
i = 0
for line in f:
	e = line.split()
	if line[0] == "\t":
		k += 1
	if k == 2:
		step.append(i)
		etot.append(float(e[5]))
		ekin.append(float(e[4]))
		epot.append(float(e[3]))
		k = 0
		i += 1
	pass
f.close()

# Set the title
title("MD Energy")
xlabel("Simulation Step")
ylabel("Energy (eV)")

# Set the legend
l1, = plot(step, etot, "b")
l2, = plot(step, epot, "r")
l3, = plot(step, ekin, "g")
legend([l1, l2, l3], ["Total Energy", "Potential", "Kinetic"], loc=9)

# Set the y range
ymin, ymax = ylim()
if ymin > 0:
	ymin = -ymin
else:
	ymin = 1.5*ymin
if ymax > 0:
	ymax = 2*ymax
else:
	ymax = 0.5 * ymax
ylim([ymin, ymax])

show()