


left_sh = 0;  
right_sh = 0.5 * radius_3 * alpha_3; 
radius_min = 5;

deviation = 0.001;
for j = deviation : deviation : right_sh 
    disp(j);
    if (fun_SH(j, radius_min, radius_3, alpha_3) > 0)
        find_success = true;
        left_sh      = j - deviation;
        right_sh     = j;
        disp("final j: ");
        disp(j);
        break;
    end
end

function [value] = fun_SH(s_h, radius_min, radius_3, alpha_3)
value = power(s_h,2) / (6 * radius_min) - power(s_h,4) / (336 * power(radius_min, 3)) - radius_min * (1 - cos(s_h / 2 / radius_min)) + ...
 1 / tan(alpha_3 / 2) * (s_h - power(s_h,3) / (40 * power(radius_min,2)) - radius_min * sin(s_h / 2 / radius_min)) + radius_min - radius_3;
end

