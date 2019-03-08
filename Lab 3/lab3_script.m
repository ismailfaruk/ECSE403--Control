%% Q1 Part 1
% time1 = (simout.time);
% H1 = (simout.signals.values); %sawtooth amp = 2
% H2 = (simout.signals.values); %sine amp = 1.5

% used to find length
% length(H1); length 418
% length(H2); length 519
% length(time1); length 418
% H_t = length(H2) 418

% H3 = H1(1:H_t); %extract data of set size H_t
% H4 = H2(1:H_t); %extract data of set size H_t
% t = time1(1:H_t);

% a = 2;
% b = 1.5;

% H = H1+H4;
% plot(t,H);

%% Q1 Part 1
% time = (simout.time); %418
% t = time(1:418);
% H_t = simout.signals.values; %418
% H_T2 = H_t(1:418); 
figure (1)
hold on
plot(t,H_T2);
plot(t,H);
hold off

%% Q1 Part 2
sine_res = (simout1.signals.values);
t = (simout1.time); 
plot(t,sine_res);

%% Q1 Part 3



%% Q2 Part 5 
s= tf('s');
G = 140/(0.1167*s+1);
figure (1)
hold on
G2 = (simout1.signals.values);
t = (simout1.time); 
stepplot(G);
plot(t,G2);
hold off
