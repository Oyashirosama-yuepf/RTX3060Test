s = struct('strings',{{'hello','yes'}},'lengths',[5 3]); %结构体定义
origindata = importdata("data.txt"); %数据输出
A=xlsread('test.xlsx'); %读取excel文件
a = textscan('data.txt','％2s％.3f％.3f％.3f'); %读取txt文件
fid = fopen('data.txt'); % 打开
axis([0 26 -1 1]); % 限制坐标轴范围
A(2,3); %为第二行第三列的元素。
A(:,n); %提取第n列的所有元素，如A(：，3)提取第三列的所有元素；
A(m,:); %提取第m行的所有元素，如A(3，：)提取第三行的所有元素；
A([1 2 3 4],[2 3]); %返回1 2 3 4行2 3 列的数据；
A(1:2:end,:);
A(2:2:end,:); %分别提取矩阵A的奇数行和偶数行数据；
A(end:-1:1,:);
A(:,end:-1:1); %分别返回A矩阵行倒序和列倒序的矩阵
A(B(:,1),:); %其中B的第一列含有数据，用来指定取矩阵A的哪些行。
