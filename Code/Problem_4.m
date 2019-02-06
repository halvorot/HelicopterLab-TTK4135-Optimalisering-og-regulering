init;

delta_t	= 0.25; % sampling time
x_ref = pi;

alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;

A = [1 1 0 0 0 0;
     0 1 -K_2 0 0 0;
     0 0 1 1 0 0;
     0 0 -K_1*K_pp 1-K_1*K_pd 0 0;
     0 0 0 0 1 1;
     0 0 0 0 -K_3*K_ep 1-K_3*K_ed]*delta_t;
 
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

Aeq = gen_aeq(A,B,N,mx,mu);
beq = zeros(mx*N,1);       
beq(1:mx) = A*x0;


[z,fval] = fmincon(obj_func, x0, [],[], Aeq, beq, vlb, vub, c_con);

% Extract optimal inputs and states
u1 = [z(N*mx+1:mu:N*mx+M*mu); z(N*mx+M*mu-1)];
u2 = [z(N*mx+2:mu:N*mx+M*mu); z(N*mx+M*mu)];
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



