
% Q3
%% experimental bode plot
% w_omega = [0.1 1 10 100 1000];
% amplitude = [14 0.1985 2e-3 0 0];
% 
% x = 10.*log10(w_omega);
% y = 20.*log10(amplitude);
% plot(x,y);

%% theoretical bode plot
G = 0.02/(0.1*s*s + 0.0104*s);

bode(G);


%% Q4 experimental bode plot
w_omega = [0.1 1 10 100 1000];
amplitude = [1.05 0.25 2.075e-3 4.1e-4 7e-3];

x = 10.*log10(w_omega);
y = 20.*log10(amplitude);
plot(x,y);

%% theoretical bode plot
G2 = 0.02/(0.02+(0.1*s*s + 0.0104*s));
bode(G2);

%% Q5
stepinfo(G2)
