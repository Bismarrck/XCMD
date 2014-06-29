length = 1.0
N = 6
timestep = 0.002

f = open("input.txt", "w")

f.write("# All the length, time, temperature are in reduced unit.\n")
f.write("&MD_ATOM_NUM     {:d}\n".format(N * N * N))
f.write("&MD_TEMPERATURE  {:.4f}\n".format(10.0 / 119.8))
f.write("&MD_MAX_STEPS    100\n")
f.write("&MD_TIMESTEP     {:.3f}\n".format(timestep))
f.write("&MD_BOX          {:.3f}\n".format(length * N))
f.write("&MD_EQUIL_TIME   100.0\n")
f.write("&MD_SIGMA        1.0\n")
f.write("&MD_EPSILON      1.0\n")
f.write("&MD_CUTOFF       {:.1f}\n".format(length * N * 0.5))
f.write("&MD_FOUT         md.fout\n")
f.write("&MD_VOUT         md.vout\n")
f.write("&MD_POUT         md.pout\n")
f.write("&MD_NU           1.0\n")
f.write("\n\n")

for i in xrange(N):
	for j in xrange(N):
		for k in xrange(N):
			x = i * length
			y = j * length
			z = k * length
			f.write("Ar {:9.6f} {:9.6f} {:9.6f}\n".format(x, y, z))
		pass
	pass
pass
f.close()