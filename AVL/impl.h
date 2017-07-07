
template <typename T>
bool AVLTree<T>::insert(const T& val) {
	if (insert(val, root)) return true;
	return false;
}

template <typename T>
std::shared_ptr<typename AVLTree<T>::template AVLNode> AVLTree<T>::insert(
	const T& val, std::shared_ptr<AVLNode>& p) {
	// https://stackoverflow.com/questions/30287402/c-nested-class-in-class-template-declaration
	if (p == nullptr) {
		p = std::make_shared<AVLNode>(val);
	}

	else if (val < p->data) {
		p->left = insert(val, p->left);
	}

	else if (val > p->data) {
		p->right = insert(val, p->right);
	}

	else {
		return p;
	}

	int hLeft = getHeight(p->left), hRight = getHeight(p->right);
	if (hLeft > hRight)
		p->height = hLeft + 1;
	else
		p->height = hRight + 1;

	adjustBalanceFactor(p, val);

	return p;
}

template <typename T>
void AVLTree<T>::adjustBalanceFactor(std::shared_ptr<AVLNode>& p,
	const T& val) {
	int balance = getHeight(p->right) - getHeight(p->left);

	if (abs(balance) <= 1) return;

	// Left Left Case
	if (balance < -1 && val < p->left->data) {
		rotateRight(p);
		return;
	}

	// Right Right Case
	if (balance > 1 && val > p->right->data) {
		rotateLeft(p);
		return;
	}

	// Left Right Case
	if (balance < -1 && val > p->left->data) {
		p->left = rotateLeft(p->left);
		rotateRight(p);
		return;
	}

	// Right Left Case
	if (balance > 1 && val < p->right->data) {
		p->right = rotateRight(p->right);
		rotateLeft(p);
		return;
	}
}

template <typename T>
std::shared_ptr<typename AVLTree<T>::template AVLNode> AVLTree<T>::rotateLeft(
	std::shared_ptr<AVLNode>& p) {
	auto temp = p->right;

	p->right = temp->left;
	temp->left = p;

	return temp;
}

template <typename T>
std::shared_ptr<typename AVLTree<T>::template AVLNode> AVLTree<T>::rotateRight(
	std::shared_ptr<AVLNode>& p) {
	auto temp = p->left;

	p->left = temp->right;
	temp->right = p;

	return temp;
}

template <typename T>
bool AVLTree<T>::search(const T& val) {
	if (search(val, root)) return true;
	return false;
}

template <typename T>
std::shared_ptr<typename AVLTree<T>::template AVLNode> AVLTree<T>::search(
	const T& val, std::shared_ptr<AVLNode>& p) {
	if (p == nullptr || p->data == val) {
		return p;
	}

	else if (val < p->data) {
		return search(val, p->left);
	}

	return search(val, p->right);
}

template <typename T>
std::shared_ptr<typename AVLTree<T>::template AVLNode> AVLTree<T>::extract_min(
	std::shared_ptr<AVLNode>& p) {
	if (p->left) {
		// make sure p!=nullptr
		return extract_min(p->left);
	}

	return p;
}

template <typename T>
bool AVLTree<T>::remove(const T& val) {
	// auto temp = search(val, root);
	return remove(root, val);
}

template <typename T>
bool AVLTree<T>::remove(std::shared_ptr<AVLNode>& p, const T& val) {
	if (p && p->data > val) {
		return remove(p->left, val);
	}

	else if (p && p->data < val) {
		return remove(p->right, val);
	}

	else if (p && p->data == val) {
		if (!p->left)
			p = p->right;
		else if (!p->right)
			p = p->left;
		else {
			auto temp = p->right;
			while (temp->left) temp = temp->left;
			p->data = temp->data;
			remove(p->right, p->data);
		}
		return true;
	}
	return false;
}

template <typename T>
void AVLTree<T>::printInorder(
	std::ostream& out, std::shared_ptr<typename AVLTree<T>::template AVLNode> p) const {
	if (p) {
		printInorder(out, p->left);
		out << p->data << " ";
		printInorder(out, p->right);
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const AVLTree<T>& A)  // TODO
{
	A.printInorder(out, A.root);
	return out;
}