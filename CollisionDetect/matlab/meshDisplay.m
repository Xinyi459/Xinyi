close all;
Mesh=csvread('mesh.csv');
Sphere=csvread('sphere.csv');
Box=csvread('out.csv');
size(Box);
r=0.005;

n_mesh=size(Mesh,1)/3;
figure(1);
for i=1:3:n_mesh
    p1 = Mesh( (i-1)*3+1 , : )'; 
    p2 = Mesh( (i-1)*3+2 , : )';
    p3 = Mesh( (i-1)*3+3 , : )';
    p=(p1+p2+p3)/3;
    plot3(p(1),p(2),p(3),'.');hold on;
    if mod(i,1000)==0
        pause(0.1);
    end
end


n_box=size(Box,1)
hold on;
for i=1:7
    data=Box(i,:);
    plotBox(data)
end
title('Mesh Partition');

