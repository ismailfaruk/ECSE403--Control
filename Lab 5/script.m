%% Q1
s = tf('s');
G = 1200/(s*(s+8.569));


%% Q2
H = 1200*0.45/(s*(s+8.569));
bode(H)
margin(H)

%% Q5
C = (0.067*s+1)/(0.012*s+1);

Z=C*H;
margin(Z);
bode(Z);

%% Q6
X = 6.899*(1.4451*s+1)/(1.4451*7.7625*s+1);
margin(Z*X)
bode(Z*X);

%% Q9
% time = (simout.time);
% H1 = (simout.signals.values); 
% H2 = (simout.signals.values); %kp = 0.178, ki = 0.092, kd = 0.0075

% used to find length
% length(H1); length 4722
% length(H2); length 4682
% length(time); length 4682
% H_t = length(H2); %4682
% 
% H3 = H1(1:H_t); %extract data of set size H_t
% H4 = H2(1:H_t); %extract data of set size H_t
% t = time(1:H_t);

plot(t,H3,t,H2,'r');
legend('Lead-Lag', 'PID');

