import random
x_range=[-0.1, 0.1]
y_range=[0, 0.3]
z_range=[-0.1, 0.15]
f = open("sphere.csv","w")
f.write("x,y,z\n")
f.write("0.005\n")
t=10000;
f.write(str(t)+"\n")
for i in range(t):
    f.write( "{},{},{}\n".format(round(random.uniform(x_range[0],x_range[1])*100000)/100000,
                               round(random.uniform(y_range[0],y_range[1])*100000)/100000,
                               round(random.uniform(z_range[0],z_range[1])*100000)/100000))
f.close()
