%% Exercise 10.3 -- Optimal control of pitch/travel with feedback
clc;
init;
load('opt_traj.mat');

delta_t	= 0.25; % sampling time

wait_time = 1; % seconds
zero_padding = zeros(wait_time/delta_t,1);
unit_padding = ones(wait_time/delta_t,1);

u   = [zero_padding; u; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];

t = 0:delta_t:delta_t*(length(u)-1);
t = t';

x_star = [t x1 x2 x3 x4];
u_star = [t u];

A = [1 delta_t 0 0;
      0 1 -delta_t*K_2 0;
      0 0 1 delta_t;
      0 0 -delta_t*K_1*K_pp 1-delta_t*K_1*K_pd];
  
B = [0; 0; 0; delta_t*K_1*K_pp];

Q = [3 0 0 0;
     0 0.01 0 0;
     0 0 0.05 0;
     0 0 0 0.1];

R = 0.1;

[K,S,e] = dlqr(A,B,Q,R,0);

