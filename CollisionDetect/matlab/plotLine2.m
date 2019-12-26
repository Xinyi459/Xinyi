function plotLine2(p,q,color)
  x=linspace(p(1),q(1),10);
  y=linspace(p(2),q(2),10);
  z=linspace(p(3),q(3),10);
  plot3(x,y,z,color,'LineWidth',1); hold on;
end