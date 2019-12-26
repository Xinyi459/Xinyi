function [] = plotBox( aabb )
color='r';
    data=aabb;
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

