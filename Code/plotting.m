%% 10.2.3 plotting different q's
load('q01.mat')

subplot(211)
plot(t,u*180/pi), grid
ylabel('u')
title('Manipulated variable u = p_c and corresponding output \lambda')
hold on

subplot(212)
plot(t,x1*180/pi), grid
ylabel('\lambda')
hold on
load('q1.mat')

subplot(211)
plot(t,u*180/pi), grid

subplot(212)
plot(t,x1*180/pi), grid
load('q10.mat')

subplot(211)
plot(t,u*180/pi), grid
legend('q = 0.1','q = 1', 'q = 10');
xlim([0 25])
ylim([-35 35])

subplot(212)
plot(t,x1*180/pi), grid
legend('q = 0.1','q = 1', 'q = 10');
xlim([0 25])
ylim([-20 200])

%% Travel angle 10.2.4
travel = load('travel.mat');
figure()
plot(travel.ans(1,:),travel.ans(2,:)+180);
hold
plot(t, x1*(180/pi));
grid on
ylabel('Travel angle [deg]');
xlabel('Time [s]');
xlim([0 25])
legend('Measured trajectory', 'Optimal trajectory')
title('Travel angle without LQR feedback')

%% Travel angle 10.3.2
travel = load('travel.mat');
figure()
plot(travel.ans(1,:),travel.ans(2,:));
hold
plot(t, x1*(180/pi));
grid on
ylabel('Travel angle [deg]');
xlabel('Time [s]');
xlim([0 25])
legend('Measured trajectory', 'Optimal trajectory')
title('Travel angle with LQR feedback')
%% Pitch Elevation 10.4.4
global alpha beta lambda_t
elevation = load('elevation.mat');
pitch = load('pitch.mat');
travel = load('travel.mat');
figure()
subplot(211)
plot(travel.ans(1,:),travel.ans(2,:));
grid on
ylabel('Travel angle [deg]');
xlabel('Time [s]');
title({'Optimal control with constraint on elevation angle, \alpha = 0.2','Travel angle with LQR feedback'})
xlim([0 20])
subplot(212)
plot(elevation.ans(1,:),elevation.ans(2,:));
hold;
plot(elevation.ans(1,:),alpha*exp(-beta*(travel.ans(2,:)*(pi/180)-lambda_t).^2)*(180/pi));
grid on
ylabel('Elevation angle [deg]');
xlabel('Time [s]');
title('Elevation angle with LQR feedback')
legend('Measured elevation angle','Elevation constraint','Location','best');
xlim([0 20]);

% subplot(313)
% plot(pitch.ans(1,:),pitch.ans(2,:));
% grid on
% ylabel('Pitch angle [deg]');
% xlabel('Time');
% title('Pitch angle with LQR feedback')

%% 10.4.6

elevation = load('elevation.mat');
travel = load('travel.mat');
travelrate = load('traveltrate.mat');
figure()
subplot(211)
plot(travelrate.ans(1,:),travelrate.ans(2,:));
hold
plot(travelrate.ans(1,:),0.5*180/pi*ones(size(travelrate.ans(1,:))),'r');
plot(travelrate.ans(1,:),-0.5*180/pi*ones(size(travelrate.ans(1,:))),'r');
legend('Measured travel rate','Travel rate constraint')
grid on
ylabel('Travel rate [deg/s]');
xlabel('Time [s]');
title({'Optimal control with two constraints, \alpha = 0.2','Travel rate with LQR feedback'})
xlim([0 20])
subplot(212)
plot(elevation.ans(1,:),elevation.ans(2,:));
hold;
plot(elevation.ans(1,:),alpha*exp(-beta*(travel.ans(2,:)*(pi/180)-lambda_t).^2)*(180/pi));
grid on
ylabel('Elevation angle [deg]');
xlabel('Time [s]');
title('Elevation angle with LQR feedback')
legend('Measured elevation angle','Elevation constraint','Location','best');
xlim([0 20]);

%% plot optimal trajectories
figure(2)
subplot(511)
stairs(t,u2),grid
ylabel('e_c')
title('Optimal trajectory with LQ feedback')
xlim([0 20])
subplot(512)
plot(t,x1,'m',t,x1,'r'),grid
ylabel('\lambda')
xlim([0 20])
subplot(513)
plot(t,x2,'m',t,x2','r'),grid
ylabel('r','Interpreter','Latex')
xlim([0 20])
subplot(514)
plot(t,x3,'m',t,x3,'r'),grid
ylabel('p','Interpreter','Latex')
xlim([0 20])
subplot(515)
plot(t,x4,'m',t,x4','r'),grid
xlim([0 20])
xlabel('Time [s]'),ylabel('$\dot{p}$','Interpreter','Latex')


