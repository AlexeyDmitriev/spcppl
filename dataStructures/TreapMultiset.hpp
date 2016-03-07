#include <cstddef>
#include <cstdint>
#include "../random/random.hpp"

template <typename T>
class TreapMultiset {
private:
	struct _node {
		T value;
		std::size_t count;
		_node* l;
		_node* r;
		int32_t priority;

		template <typename... Args>
		_node(Args&&... args):
				value(std::forward<Args>(args)...),
				count(1),
				l(nullptr),
				r(nullptr),
				priority(randomInteger()) {

		}

		void push() {

		}

		void recalc() {
			count = 1 + cnt(l) + cnt(r);
		}
	};
	using Node = _node*;

	static std::size_t cnt(Node v) {
		if (!v)
			return 0;
		return v->count;
	}

	Node root;

	std::size_t size_;

	Node merge(Node l, Node r) {
		if (!l) {
			return r;
		}
		if (!r) {
			return l;
		}
		if (l->priority < r->priority) {
			l->push();
			l->r = merge(l->r, r);
			l->recalc();
			return l;
		}
		else {
			r->push();
			r->l = merge(l, r->l);
			r->recalc();
			return r;
		}
	}

	void splitByIndex(Node v, std::size_t index, Node& l, Node& r) {
		l = nullptr;
		r = nullptr;
		if (!v) {
			return;
		}
		v->push();
		if (cnt(v->l) < index) {
			l = v;
			splitByIndex(l->r, index - cnt(v->l) - 1, l->r, r);
			l->recalc();
		}
		else {
			r = v;
			splitByIndex(r->l, index, l, r->l);
			r->recalc();
		}
	}

	void splitByValue(Node v, const T& value, Node& l, Node& r) {
		l = nullptr;
		r = nullptr;
		if (!v) {
			return;
		}
		v->push();
		if (v->value < value) {
			l = v;
			splitByValue(l->r, value, l->r, r);
			l->recalc();
		}
		else {
			r = v;
			splitByValue(r->l, value, l, r->l);
			r->recalc();
		}
	}

	void insertNode(Node newNode) {
		Node l = nullptr;
		Node r = nullptr;
		splitByValue(root, newNode->value, l, r);
		root = merge(merge(l, newNode), r);
		++size_;
	}

public:
	TreapMultiset() {
		root = nullptr;
		size_ = 0;
	}

	std::size_t size() const {
		return size_;
	}

	template <typename... Args>
	void emplace(Args&&... args) {
		insertNode(new _node(std::forward<Args>(args)...));
	}

	void insert(const T& value) {
		insertNode(new _node(value));
	}

	void insert(T&& value) {
		insertNode(new _node(std::move(value)));
	}

	void erase_one(const T& value) {
		Node l = nullptr;
		Node m = nullptr;
		Node r = nullptr;
		splitByValue(root, value, l, r);
		splitByIndex(r, 1, m, r);
		SPCPPL_ASSERT(m->value == value);
		delete m;
		root = merge(l, r);
		--size_;
	}
	const T& operator [] (std::size_t index) {
		Node l = nullptr;
		Node m = nullptr;
		Node r = nullptr;
		splitByIndex(root, index, l, r);
		splitByIndex(r, 1, m, r);
		SPCPPL_ASSERT(m != nullptr);
		root = merge(merge(l, m), r);
		return m->value;
	}
};
