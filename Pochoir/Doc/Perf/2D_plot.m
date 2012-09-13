load('heat_4D_NP_loop_perf.mdat', '-ascii');
load('heat_4D_NP_seq_perf.mdat', '-ascii');
load('heat_4D_NP_sim_perf.mdat', '-ascii');
x = [10 20 40 80 160];
%y = [200:200:3200];
z = (x .^ 4) * 1000;
heat_4D_NP_loop_cache_ref = heat_4D_NP_loop_perf(:, 2);
heat_4D_NP_loop_cache_miss = heat_4D_NP_loop_perf(:, 3);
heat_4D_NP_loop_branch = heat_4D_NP_loop_perf(:,4);
heat_4D_NP_loop_branch_miss = heat_4D_NP_loop_perf(:, 5);

heat_4D_NP_seq_cache_ref = heat_4D_NP_seq_perf(:, 2);
heat_4D_NP_seq_cache_miss = heat_4D_NP_seq_perf(:, 3);
heat_4D_NP_seq_branch = heat_4D_NP_seq_perf(:,4);
heat_4D_NP_seq_branch_miss = heat_4D_NP_seq_perf(:, 5);

heat_4D_NP_sim_cache_ref = heat_4D_NP_sim_perf(:, 2);
heat_4D_NP_sim_cache_miss = heat_4D_NP_sim_perf(:, 3);
heat_4D_NP_sim_branch = heat_4D_NP_sim_perf(:,4);
heat_4D_NP_sim_branch_miss = heat_4D_NP_sim_perf(:, 5);

heat_4D_NP_loop_cache_miss_ratio = heat_4D_NP_loop_cache_miss ./ heat_4D_NP_loop_cache_ref;
heat_4D_NP_seq_cache_miss_ratio = heat_4D_NP_seq_cache_miss ./ heat_4D_NP_seq_cache_ref;
heat_4D_NP_sim_cache_miss_ratio = heat_4D_NP_sim_cache_miss ./ heat_4D_NP_sim_cache_ref;

heat_4D_NP_loop_branch_miss_ratio = heat_4D_NP_loop_branch_miss ./ heat_4D_NP_loop_branch;
heat_4D_NP_seq_branch_miss_ratio = heat_4D_NP_seq_branch_miss ./ heat_4D_NP_seq_branch;
heat_4D_NP_sim_branch_miss_ratio = heat_4D_NP_sim_branch_miss ./ heat_4D_NP_sim_branch;

%semilogy(z, z' ./ sLoop, 'gx-', z, z' ./ pLoop, 'b+-', z, z' ./ pochoir, 'ro-');
%plot(z, z' ./ macro, 'gx-', z, z' ./ pointer, 'b+-', z, z' ./ optPointer, 'ro-');
semilogx(z, heat_4D_NP_loop_branch_miss, 'gx-', z, heat_4D_NP_seq_branch_miss, 'b+-', z, heat_4D_NP_sim_branch_miss, 'ro-');
xlabel('Grid Points');
ylabel('Branch Miss Rate');
legend('parallel loop', 'seq space cut', 'sim space cut');
grid on;
% hold on;
% plot(x, y_parallel_for ./ y_iter);
% hold on;
% plot(x, pfor1 ./ pointer, x, pfor2 ./ iter, x, pfor1 ./ macro);
% hold on;
% plot(x, pfor2 ./ iter);