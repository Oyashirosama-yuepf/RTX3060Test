rotate_matrix = [-0.0714491, -0.997444, 0; 0.997444, -0.0714491, 0; -0, 0, 1];
rotate_matrix = [0.996438, -0.0843233, 0; 0.0843233, 0.996438, 0; -0, 0, 1];

thetax = atan2(rotate_matrix(3,2),rotate_matrix(3,3));
thetay = atan2(-rotate_matrix(3,1),sqrt(rotate_matrix(3,2)^2 + rotate_matrix(3,3)^2));
thetaz = atan2(rotate_matrix(2,1), rotate_matrix(1,1));

theta1 = acosd(rotate_matrix(1,1));
theta2 = asind(rotate_matrix(2,1));

atan2(1,1);