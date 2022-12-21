

clc;
clear;

A = [3.87553, -2.87558];

B = [4.80142, -2.58527];

C = [6.2895, -7.33193];

D = [5.40075, -7.60791];

Aa = [-7.0824, 9.95779];

Ba = [-6.76779, 6.78002];

Ca = [-4.64369, 9.7815];

Da = [-4.55078, 7.8141];

plot(A(1), A(2), "r*-", "LineWidth",3); hold on;
line([A(1),B(1)],[A(2), B(2)]);
txt = ['\leftarrow  = ' , 'A'];  %strcat ('\leftarrow i = ' , num2str(i))
text(A(1),A(2),txt)

plot(B(1), B(2), "r*-", "LineWidth",3); hold on;
line([B(1),C(1)],[B(2), C(2)]);
txt = ['\leftarrow  = ' , 'B'];  %strcat ('\leftarrow i = ' , num2str(i))
text(B(1),B(2),txt)

plot(C(1), C(2), "r*-", "LineWidth",3); hold on;
line([C(1),D(1)],[C(2), D(2)]);
txt = ['\leftarrow  = ' , 'C'];  %strcat ('\leftarrow i = ' , num2str(i))
text(C(1),C(2),txt)

plot(D(1), D(2), "r*-", "LineWidth",3); hold on;
line([D(1),A(1)],[D(2), A(2)]);
txt = ['\leftarrow  = ' , 'D'];  %strcat ('\leftarrow i = ' , num2str(i))
text(D(1),D(2),txt)

Xcenter = (A(1) + B(1) + C(1) + D(1)) / 4;
Xacenter = (Aa(1) + Ba(1) + Ca(1) + Da(1)) / 4;
Ycenter = (A(2) + B(2) + C(2) + D(2)) / 4;
Yacenter = (Aa(2) + Ba(2) + Ca(2) + Da(2)) / 4;


% plot(Aa(1), Aa(2), "b*-", "LineWidth",3); hold on;
% line([Aa(1),Ba(1)],[Aa(2), Ba(2)]);
% 
% plot(Ba(1), Ba(2), "b*-", "LineWidth",3); hold on;
% line([Ba(1),Ca(1)],[Ba(2), Ca(2)]);
% 
% plot(Ca(1), Ca(2), "b*-", "LineWidth",3); hold on;
% line([Ca(1),Da(1)],[Ca(2), Da(2)]);
% 
% plot(Da(1), Da(2), "b*-", "LineWidth",3); hold on;
% line([Da(1),Aa(1)],[Da(2), Aa(2)]);

plot(Xcenter, Ycenter, "k*-", "LineWidth",3); hold on;

% plot(Xacenter, Yacenter, "k*-", "LineWidth",3); hold on;





% line([A(1),Aa(1)],[A(2),Aa(2)]);
% line([B(1),Ba(1)],[B(2),Ba(2)]);
% line([C(1),Ca(1)],[C(2),Ca(2)]);
% line([D(1),Da(1)],[D(2),Da(2)]);
