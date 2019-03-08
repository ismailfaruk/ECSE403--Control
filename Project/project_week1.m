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
mp=0.106;
lp=0.168;
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

%% Q2
sys  = ss(A,B,C,D);
tf_sys = ss2tf(A,B,C,D);

s = tf('s');
G = tf(sys);

%% Q3
pzmap(G);

%% Q4
eig(A)

%% Q5 
Co = ctrb(A,B);
k = rank(Co);

%% Q6
% We should not check because the Controlbility matrix was full rank

%% Q7
Mp = 8.5;  % ~6 deg
Z = ((log(Mp)^2)/(pi^2+(log(Mp)^2)))^0.5;    
Ts = 2;
Wn = 3.9/(Z*Ts) 
Pd1 = -(Z*Wn) + 1i* Wn*(1-Z^2)^0.5    
Pd2 = -(Z*Wn) - 1i* Wn*(1-Z^2)^0.5    

%% Q8
Nd1 = 10*Pd1   
Nd2 = 10*Pd2   

%% Q9 PP for Con
p = [Pd1, Pd2, Nd1, Nd2];
K = place(A,B,p) % -75.7219 -31.5292 -86.7308 -6.7632

%% Q15
% each of the value of K correspond to a proportioanl gain to the state feedback

