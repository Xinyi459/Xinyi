close all
clear
%Collision result: 1

mesh1=[-0.068752 0.036748 -0.004917 -0.069010 0.040112 -0.001104 -0.066945 0.040127 -0.004822]
sph1=[-0.059420 0.040310 0.008430 0.010000]


%Collision result: 0
mesh2=[-0.068752 0.036748 -0.004917 -0.069010 0.040112 -0.001104 -0.066945 0.040127 -0.004822]
sph2=[-0.070700 0.040190 0.004620 0.010000]
mesh3=[-0.5,-1,0,-2,1,0,-2,-1,0]
sph3=[-1.5,-0.5,1.1,1.2]


mesh=mesh3;
sph=sph3;

a1=mesh(1:3);
a2=mesh(4:6);
a3=mesh(7:9);
c='k';
plotLine2(a1,a2,c);
plotLine2(a2,a3,c);
plotLine2(a1,a3,c);
pause(1);

px=sph(1);
py=sph(2);
pz=sph(3);
r=sph(4);
[x y z]=sphere;
hold on;
surf(x*r+px, y*r+py, z*r+pz);
alpha 0.3

