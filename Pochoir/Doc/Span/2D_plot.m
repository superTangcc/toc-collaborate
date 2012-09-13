load('heat_2D_P_span.mdat', '-ascii');
%load('heat_2D_P_hotPar_3D_pl.mdat', '-ascii');
%load('heat_2D_P_hotPar_3D_pochoir.mdat', '-ascii');
% load('heat_2D_P_hotPar_3D_pochoir_bt.mdat', '-ascii');
x = heat_2D_P_span(:, 1);
%y = [200:200:3200];
z = (x .^ 2) .* 1000;
seq = heat_2D_P_span(:, 2);
sim = heat_2D_P_span(:, 3);

% sLoop = heat_2D_P_shotPar_3D(:, 1:size(heat_2D_P_hotPar_3D_sl, 2));
% pLoop = heat_2D_P_hotPar_3D(:, 1:size(heat_2D_P_hotPar_3D_pl, 2));
% pochoir = heat_2D_P_hotPar_3D(:, 1:size(heat_2D_P_hotPar_3D_pochoir, 2));
% pochoir_bt = heat_2D_P_hotPar_3D_pochoir_bt(:, 16);

%semilogy(z, z' ./ sLoop, 'gx-', z, z' ./ pLoop, 'b+-', z, z' ./ pochoir, 'ro-');
%plot(z, z' ./ macro, 'gx-', z, z' ./ pointer, 'b+-', z, z' ./ optPointer, 'ro-');
semilogx(z, seq, 'bx-', z, sim, 'ro-');
xlabel('Grid Points');
ylabel('Parallelism');
legend('Seq', 'Sim');
grid on;
% hold on;
% plot(x, y_parallel_for ./ y_iter);
% hold on;
% plot(x, pfor1 ./ pointer, x, pfor2 ./ iter, x, pfor1 ./ macro);
% hold on;
% plot(x, pfor2 ./ iter);