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

color='r';
n_box=size(Box,1)
hold on;
for i=2:n_box
    data=Box(i,:);
    p1=[data(1);data(3);data(5)];
    p2=[data(2);data(4);data(6)];
    a=[data(2)-data(1);0;0];
    b=[0;data(4)-data(3);0];
    c=[0;0;data(6)-data(5)];
    plotLine2(p1,p1+a,color);
    plotLine2(p1,p1+b,color);
    plotLine2(p1,p1+c,color);
    plotLine2(p2,p2-a,color);
    plotLine2(p2,p2-b,color);
    plotLine2(p2,p2-c,color);
    
    plotLine2(p1+a,p2-b,color);
    plotLine2(p1+a,p2-c,color);
    plotLine2(p1+b,p2-a,color);
    plotLine2(p1+b,p2-c,color);
    plotLine2(p1+c,p2-a,color);
    plotLine2(p1+c,p2-b,color);
end
title('Mesh Partition');

