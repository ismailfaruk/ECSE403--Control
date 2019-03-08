%% Q7 a)
% time1 = (simout1.time);
H1 = (simout1.signals.values); %kp = 0.05
% H2 = (simout1.signals.values); %kp = 0.05, kd = 0.00015

% used to find length
% length(H1); length 4394
% length(H2); length 4837
% length(time1); length 4394
% H_t = length(H1); %4394
% 
% H3 = H1(1:H_t); %extract data of set size H_t
% H4 = H2(1:H_t); %extract data of set size H_t
% t = time1(1:H_t);
% 
% plot(t,H1,t,H4,'r');
% legend('P','PD')

%% Q8 a)
% time1 = (simout1.time);
% H1 = (simout1.signals.values);  %kp = 0.05
% H2 = (simout1.signals.values);    %kp = 0.05, ki = 0.003

% used to find length
% length(H1); length 4993
% length(H2); length 4681
% length(time1); length 4681
% H_t = length(H2); %4681

% H3 = H1(1:H_t); %extract data of set size H_t
% H4 = H2(1:H_t); %extract data of set size H_t
% t = time1(1:H_t);
% 

% plot(time1,H3,time1,H2,'r');
% legend('P','PI')


%% Q9 a)
% time1 = (simout1.time);
% H1 = (simout1.signals.values); %kp = 0.051;  kd = 0.00009
% H2 = (simout1.signals.values); %kp = 0.051;  kd = 0.00009; ki = 0.00098 

% used to find length
% length(H1); length 4910
% length(H2); length 4643
% length(time1); length 4643
% H_t = length(H2); %4643

% H3 = H1(1:H_t); %extract data of set size H_t
% H4 = H2(1:H_t); %extract data of set size H_t
% t = time1(1:H_t);
% 
% plot(time1,H3,time1,H2,'r');
% legend('PD','PID')


%% Q9 b)
% time1 = (simout1.time);
% H1 = (simout1.signals.values); %kp=0.051, ki = 0.0035
% H2 = (simout1.signals.values); %kp=0.051, ki = 0.0035, kd = 0.00015

% used to find length
% length(H1); length 4744
% length(H2); length 4852
% length(time1); length 4744
H_t = length(H1); %2602

% H3 = H1(1:H_t); %extract data of set size H_t
% H4 = H2(1:H_t); %extract data of set size H_t
% t = time1(1:H_t);
% 
plot(time1,H1,time1,H4,'r');
legend('PI','PID')
%%





