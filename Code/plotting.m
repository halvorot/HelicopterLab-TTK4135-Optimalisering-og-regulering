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
plot(travel.ans(1,:),travel.ans(2,:));
grid on
ylabel('Travel angle [deg]');
xlabel('Time');
title('Travel angle with LQR feedback')