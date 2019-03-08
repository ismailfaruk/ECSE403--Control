s = tf('s');

% Q2 to Q4
G = 0.002/(0.01*s+0.00104);
figure(1)
stepplot(G);
S = stepinfo(G);

% Q5, Q11
H = 0.002/(s*(0.01*s+0.00104));
figure(2);
stepplot(H);
T = stepinfo(H);

% Q7
StepInfoG = ["Proportional Gain",0,0,0,0;
            "RiseTime",0,0,0,0;
            "SettlingTime",0,0,0,0];
figure(3);
hold on;
K = [0.1 1 10 100];
for i = 1:4 
        J = 0.002*K(i)/(0.002*K(i)+0.01*s+0.00104);
        stepplot(J);
        S = stepinfo(J);
        StepInfoG(1,i+1) = K(i);
        StepInfoG(2,i+1) = S.RiseTime;
        StepInfoG(3,i+1) = S.SettlingTime;
        legendInfo{i} = [num2str(K(i))];
end
legend(legendInfo);
hold off;

% Q8
StepInfoH = ["Proportional Gain",0,0,0,0;
            "Overshoot",0,0,0,0;
            "RiseTime",0,0,0,0;
            "SettlingTime",0,0,0,0];
figure(4);
hold on;
K = [0.1 1 10 100];
for i = 1:4 
        L = 0.002*K(i)/(0.002*K(i)+s*(0.01*s+0.00104));
        stepplot(L);
        S = stepinfo(L);
        StepInfoH(1,i+1) = K(i);
        StepInfoH(2,i+1) = S.Overshoot;
        StepInfoH(3,i+1) = S.RiseTime;
        StepInfoH(4,i+1) = S.SettlingTime;
        legendInfo{i} = [num2str(K(i))];
end
legend(legendInfo);
hold off;

% Q11
figure(5);
bode(H);

% Q12
figure(6);
rlocus(H);

% Q13
figure(7);
Ks = (s+0.35)/(s+0.75);
M = Ks*H;
rlocus(M);