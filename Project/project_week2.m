%% Q1

Km=0.0077;
Rm=2.6;
Lm=180;
Vmax=5.0;
Kg=3.7;
rg=0.0064;
mc=0.526;
Kx=2.28*(10^-5);
Kth=0.00153;
mp=0.106*2;
lp=0.168*2;
g=9.81;

b = (Kg*Km)/(rg);

A = [0,1,0,0;
    0,(-b^2)/(mc*Rm),-(mp*g)/(mc),0;
    0,0,0,1;
    0, (b^2)/(mc*lp*Rm),((mc+mp)*g)/(mc*lp),0];

B = [0;
    b/(mc*Rm);
    0;
    -b/(mc*lp*Rm)];

C = eye(4);

D = [0,0,0,0]';

%% 
sys  = ss(A,B,C,D);
tf_sys = ss2tf(A,B,C,D);

s = tf('s');
G = tf(sys);

%% 
pzmap(G);

%% 
eig(A)

%% Q
Co = ctrb(A,B);
k = rank(Co);

%%
% We should not check because the Controlbility matrix was full rank

%%
Mp = 11.5;  % 11.5
Z = ((log(Mp)^2)/(pi^2+(log(Mp)^2)))^0.5;    
Ts = 2.5;
Wn = 3.9/(Z*Ts) 
Pd1 = -(Z*Wn) + 1i* Wn*(1-Z^2)^0.5    
Pd2 = -(Z*Wn) - 1i* Wn*(1-Z^2)^0.5    

%% 
Nd1 = 10*Pd1   
Nd2 = 10*Pd2   

%% PP for Con
p = [Pd1, Pd2, Nd1, Nd2];
K = place(A,B,p) % -15.0542   -9.7200  -23.0187   -1.8513

Q=15*[10,0,0,0;
    0,0.666,0,0;
    0,0,10,0;
    0,0,0,0];
R= 0.01;
N= 0;

[K,S,e] = lqr(A,B,Q,R,N) 