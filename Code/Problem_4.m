<<<<<<< HEAD
clc; clear all; close all;

=======
>>>>>>> a305483aecf07574d8339dd0f691bb650a42c7fe
init;

delta_t	= 0.25; % sampling time
x_ref = pi;

<<<<<<< HEAD
global alpha beta lambda_t mx N lambda_dot_t

alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;
lambda_dot_t = 0.5;


A = [1 delta_t 0 0 0 0;
     0 1 -delta_t*K_2 0 0 0;
     0 0 1 delta_t 0 0;
     0 0 -delta_t*K_1*K_pp 1-delta_t*K_1*K_pd 0 0;
     0 0 0 0 1 delta_t;
     0 0 0 0 -delta_t*K_3*K_ep 1-delta_t*K_3*K_ed];
=======
alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;

A = [1 1 0 0 0 0;
     0 1 -K_2 0 0 0;
     0 0 1 1 0 0;
     0 0 -K_1*K_pp 1-K_1*K_pd 0 0;
     0 0 0 0 1 1;
     0 0 0 0 -K_3*K_ep 1-K_3*K_ed]*delta_t;
>>>>>>> a305483aecf07574d8339dd0f691bb650a42c7fe
 
B = [0 0;
     0 0;
     0 0;
     K_1*K_pp 0;
     0 0;
     0 K_3*K_ep]*delta_t;

% Number of states and inputs
mx = size(A,2); % Number of states (number of columns in A)
mu = size(B,2); % Number of inputs (number of columns in B)

% Time horizon and initialization
<<<<<<< HEAD
N  = 40;                           % Time horizon for states
M  = N;                            % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);           % Initialize z for the whole horizon
z0 = z;                            % Initial value for optimization
z0(1) = x_ref;                     % x_ref = pi 

% Bounds
ul 	    = [-pi/6; -Inf];           % Lower bound on control
uu 	    = [pi/6; Inf];             % Upper bound on control

xl      = -Inf*ones(mx,1);         % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);          % Upper bound on states (no bound)
xl(3)   = ul(1);                   % Lower bound on state x3
xu(3)   = uu(1);                   % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu);
vlb(N*mx+M*mu)  = 0;          
vub(N*mx+M*mu)  = 0;          

q_1 = 1;
q_2 = 1;

Q1 = 2*diag([1 0 0 0 0 0]);       % Weight on states
P1 = 2*diag([q_1 q_2]);           % Weight on input
Q  = gen_q(Q1,P1,N,M);            % Generate Q
c  = [];                           

obj_func = @(z) 1/2 * z'*Q*z;       % Objective function

x0 = [pi 0 0 0 0 0]';               % Initial values for states
=======
N  = 40;                                % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

% Bounds
ul 	    = -pi/6;                        % Lower bound on control
uu 	    = pi/6;                         % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                                % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                                % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
q_1 = 1;
q_2 = 1;

Q1 = diag([1 0 0 0 0 0])*2;
P1 = [q_1 q_2];                         % Weight on input
Q = 2*gen_q(Q1,P1,N,M);                 % Generate Q, hint: gen_q
c = [];                                 % Generate c, this is the linear constant term in the QP

obj_func = @(z) 1/2 * z'*Q*z; 
c_con = @(x, alpha, beta, lambda_t)alpha*exp(-beta*(x(1)-lambda_t)^2) - x(5);

x0 = [pi 0 0 0 0 0]';
>>>>>>> a305483aecf07574d8339dd0f691bb650a42c7fe

Aeq = gen_aeq(A,B,N,mx,mu);
beq = zeros(mx*N,1);       
beq(1:mx) = A*x0;

<<<<<<< HEAD
% Solving the optimization problem
opt = optimoptions('fmincon', 'Algorithm', 'sqp', 'MaxFunEvals', 50000);
[z,fval] = fmincon(obj_func, z0, [],[], Aeq, beq, vlb, vub, @c_con, opt);
=======

[z,fval] = fmincon(obj_func, x0, [],[], Aeq, beq, vlb, vub, c_con);
>>>>>>> a305483aecf07574d8339dd0f691bb650a42c7fe

% Extract optimal inputs and states
u1 = [z(N*mx+1:mu:N*mx+M*mu); z(N*mx+M*mu-1)];
u2 = [z(N*mx+2:mu:N*mx+M*mu); z(N*mx+M*mu)];
<<<<<<< HEAD
x1 = [x0(1);                  z(1:mx:N*mx)];
x2 = [x0(2);                  z(2:mx:N*mx)];
x3 = [x0(3);                  z(3:mx:N*mx)];
x4 = [x0(4);                  z(4:mx:N*mx)];
x5 = [x0(5);                  z(5:mx:N*mx)];
x6 = [x0(6);                  z(6:mx:N*mx)];

% Add padding to start and end to stabilize after init
wait_time       = 3; % seconds
zero_padding    = zeros(wait_time/delta_t,1);
unit_padding    = ones(wait_time/delta_t,1);

u1  = [zero_padding;        u1; zero_padding];
u2  = [zero_padding;        u2; zero_padding];
x1  = [x_ref*unit_padding;  x1; zero_padding];
x2  = [zero_padding;        x2; zero_padding];
x3  = [zero_padding;        x3; zero_padding];
x4  = [zero_padding;        x4; zero_padding];
x5  = [zero_padding;        x5; zero_padding];
x6  = [zero_padding;        x6; zero_padding];

% Create time vector
t = transpose(0:delta_t:delta_t*(length(u1)-1));

% LQR tuning
Q_lqr = diag([100 1 1 10 10 1]);
R_lqr = diag([0.5 0.5]);

[K,S,e] = dlqr(A,B,Q_lqr,R_lqr,0);

% Structuring states and input for Simulink
x_star = [t x1 x2 x3 x4 x5 x6];
u_star = [t u1 u2];
=======
x1 = [x0(1);z(1:mx:N*mx)];
x2 = [x0(2);z(2:mx:N*mx)];
x3 = [x0(3);z(3:mx:N*mx)];
x4 = [x0(4);z(4:mx:N*mx)];
x5 = [x0(5);z(5:mx:N*mx)];
x6 = [x0(6);z(6:mx:N*mx)];

% Add padding to start and end to stabilize after init
wait_time = 1; % seconds
zero_padding = zeros(wait_time/delta_t,1);
unit_padding = ones(wait_time/delta_t,1);

u1   = [zero_padding; u1; zero_padding];
u2   = [zero_padding; u2; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

% Create time
t = 0:delta_t:delta_t*(length(u)-1);
t = t';



>>>>>>> a305483aecf07574d8339dd0f691bb650a42c7fe
