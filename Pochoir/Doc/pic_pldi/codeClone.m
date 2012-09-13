load('codeClone_0.mdat', '-ascii');
%load('heat_2D_P_hotPar_3D_pl.mdat', '-ascii');
%load('heat_2D_P_hotPar_3D_pochoir.mdat', '-ascii');
% load('heat_2D_P_hotPar_3D_pochoir_bt.mdat', '-ascii');
size = codeClone_0(:, 1);
%y = [200:200:3200];
z = (size .^ 2) .* 200;
twoClones = codeClone_0(:, 2);
oneClone = codeClone_0(:, 3);

% sLoop = heat_2D_P_shotPar_3D(:, 1:size(heat_2D_P_hotPar_3D_sl, 2));
% pLoop = heat_2D_P_hotPar_3D(:, 1:size(heat_2D_P_hotPar_3D_pl, 2));
% pochoir = heat_2D_P_hotPar_3D(:, 1:size(heat_2D_P_hotPar_3D_pochoir, 2));
% pochoir_bt = heat_2D_P_hotPar_3D_pochoir_bt(:, 16);

%semilogy(z, z' ./ sLoop, 'gx-', z, z' ./ pLoop, 'b+-', z, z' ./ pochoir, 'ro-');
%plot(z, z' ./ macro, 'gx-', z, z' ./ pointer, 'b+-', z, z' ./ optPointer, 'ro-');
loglog(z, twoClones, 'bx-', z, oneClone, 'ro-');
xlabel('Grid Points');
ylabel('execution time in ms');
legend('Two Code Clones', 'One Code Clone');
grid off;
% hold on;
% plot(x, y_parallel_for ./ y_iter);
% hold on;
% plot(x, pfor1 ./ pointer, x, pfor2 ./ iter, x, pfor1 ./ macro);
% hold on;
% plot(x, pfor2 ./ iter);