load('heat_2D_NP_sl_hotPar_3D.mdat', '-ascii');
load('heat_2D_NP_pl_hotPar_3D.mdat', '-ascii');
load('heat_2D_NP_pochoir_hotPar_3D.mdat', '-ascii');
%load('heat_2D_NP_pochoir_bt_hotPar_3D.mdat', '-ascii');
y = [200:200:3200];
x = [200:200:3200];
[X,Y] = meshgrid(x, y);
Z = (X .* X .* Y);
sloop = heat_2D_NP_sl_hotPar_3D(:, 1:size(heat_2D_NP_sl_hotPar_3D, 2));
surf(X, Y, Z ./ sloop , 'FaceColor', 'red');
hold on;
ploop = heat_2D_NP_pl_hotPar_3D(:, 1:size(heat_2D_NP_pl_hotPar_3D, 2));
surf(X, Y, Z ./ ploop , 'FaceColor', 'blue');
hold on;
pochoir = heat_2D_NP_pochoir_hotPar_3D(:, 1:size(heat_2D_NP_pochoir_hotPar_3D, 2));
surf(X, Y, Z ./ pochoir , 'FaceColor', 'green');
hold on;
%pochoir_bt = heat_2D_NP_pochoir_bt_hotPar_3D(:, 1:size(heat_2D_NP_pochoir_bt_hotPar_3D, 2));
%surf(X, Y, Z ./ pochoir_bt , 'FaceColor', 'cyan');
% colormap hsv;
% alpha(.4);
%hold on;
% load('dfd_pLoop_hotPar.dat', '-ascii');
% pLoop = dfd_pLoop_hotPar(:, 1:size(dfd_pLoop_hotPar, 2));
% surf(X, Y, pLoop, 'FaceColor', 'blue');
% colormap hsv;
% hold on;
% load('dfd_pochoir_hotPar.dat', '-ascii');
% pochoir = dfd_pochoir_hotPar(:, 1:size(dfd_pochoir_hotPar, 2));
% surf(X, Y, pochoir, 'FaceColor', 'green');
% colormap hsv;
% hold off;
% hold on;
% plot(x, y_parallel_for ./ y_iter);
% hold on;
% plot(x, pfor1 ./ pointer, x, pfor2 ./ iter, x, pfor1 ./ macro);
% hold on;
% plot(x, pfor2 ./ iter);