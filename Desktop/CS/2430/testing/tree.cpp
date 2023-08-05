void Tree::printLevelOrder() {
	queue<TreeNode*> q;
	TreeNode* current = root;
	if(current != NULL) {
		q.push(current);
		while(!q.isEmpty()) {
			current = q.front();
			q.pop();
			if(current->left != NULL)
				q.push(current->left);
			if(current->right != NULL)
				q.push(current->right);
			cout << current->key;	
		}
	}
}