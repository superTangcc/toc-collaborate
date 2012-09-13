load('adaptive_2D_0.mdat', '-ascii');
%load('heat_2D_0_P_hotPar_3D_pl.mdat', '-ascii');
%load('heat_2D_0_P_hotPar_3D_pochoir.mdat', '-ascii');
% load('heat_2D_0_P_hotPar_3D_pochoir_bt.mdat', '-ascii');
size = adaptive_2D_0(:, 1);
%y = [200:200:3200];
z = (size .^ 2) .* 200;
adaptive = adaptive_2D_0(:, 2);
all1 = adaptive_2D_0(:, 3);
all10 = adaptive_2D_0(:, 4);
all20 = adaptive_2D_0(:, 5);
all40 = adaptive_2D_0(:, 6);
all100 = adaptive_2D_0(:, 7);

% sLoop = heat_2D_0_P_shotPar_3D(:, 1:size(heat_2D_0_P_hotPar_3D_sl, 2));
% pLoop = heat_2D_0_P_hotPar_3D(:, 1:size(heat_2D_0_P_hotPar_3D_pl, 2));
% pochoir = heat_2D_0_P_hotPar_3D(:, 1:size(heat_2D_0_P_hotPar_3D_pochoir, 2));
% pochoir_bt = heat_2D_0_P_hotPar_3D_pochoir_bt(:, 16);

%semilogy(z, z' ./ sLoop, 'gx-', z, z' ./ pLoop, 'b+-', z, z' ./ pochoir, 'ro-');
%plot(z, z' ./ macro, 'gx-', z, z' ./ pointer, 'b+-', z, z' ./ optPointer, 'ro-');
loglog(z, adaptive, 'bx-', z, all1, 'ro-', z, all100, 'g+-');
xlabel('Grid Points');
ylabel('execution time in ms');
legend('Adaptive', 'All grain = 1', 'All grain = 100');
grid off;
% hold on;
% plot(x, y_parallel_for ./ y_iter);
% hold on;
% plot(x, pfor1 ./ pointer, x, pfor2 ./ iter, x, pfor1 ./ macro);
% hold on;
% plot(x, pfor2 ./ iter);