function child_nodes = child_nodes_cal(parent_node, m, n, obs, closeList)

child_nodes = [];
field = [1,1; n,1; n,m; 1,m];

% ��1���ӽڵ�
child_node = [parent_node(1)-1, parent_node(2)+1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))%�жϵ��Ƿ��ڶ������
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% ��2���ӽڵ�
child_node = [parent_node(1), parent_node(2)+1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% ��3���ӽڵ�
child_node = [parent_node(1)+1, parent_node(2)+1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% ��4���ӽڵ�
child_node = [parent_node(1)-1, parent_node(2)];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% ��5���ӽڵ�
child_node = [parent_node(1)+1, parent_node(2)];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% ��6���ӽڵ�
child_node = [parent_node(1)-1, parent_node(2)-1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% ��7���ӽڵ�
child_node = [parent_node(1), parent_node(2)-1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

% ��8���ӽڵ�
child_node = [parent_node(1)+1, parent_node(2)-1];
if inpolygon(child_node(1), child_node(2), field(:,1), field(:,2))
    if ~ismember(child_node, obs, 'rows')
        child_nodes = [child_nodes; child_node];
    end
end

%% �ų��Ѿ�������closeList�Ľڵ�
delete_idx = [];
for i = 1:size(child_nodes, 1)
    if ismember(child_nodes(i,:), closeList , 'rows')
        delete_idx(end+1,:) = i;
    end
end
child_nodes(delete_idx, :) = [];