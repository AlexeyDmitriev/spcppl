#pragma once

#include "../random/random.hpp"

template <typename Key, typename Data, typename Update, typename UpdateMerger, typename UpdateApplier>
class Treap {
public:
	struct Node {
		Key key;
		Data data;

		Node(const Key& key, const Data& data): key(key), data(data) {
			priority = randomInteger();
		}

		int32_t priority;
		Update update;

		Node *l;
		Node *r;

		void recalc() {
			data = merge(l ? &l->data : nullptr, data, r ? &r->data : nullptr);
		}
	};

	void split(Node* v, Node*& l, Node*& r, const Key& key) {
		if (v == nullptr) {
			l = nullptr;
			r = nullptr;
			return;
		}
		push(v);
		if (v->key < key) {
			l = v;
			split(l->r, l->r, r);
		}
		else {
			r = v;
			split(r->l, l, r->l);
		}
		v->recalc();
	}

	void add(const Key& key, const Data& data) {
		Node node
	}

private:

	Node* merge(Node* l, Node* r) const {
		if (l == nullptr) {
			return r;
		}
		if (r == nullptr) {
			return l;
		}
		if (l->priority > r->priority) {
			l->push();
			l->r = merge(l->r, r);
			l->recalc();
			return l;
		} else {
			r->push();
			r->l = merge(l, r->l);
			l->recalc();
		}
	}
	void applyUpdate(Node* node, const Update& update) {
		if (node == nullptr) {
			return;
		}
		node->data = updateApplier(node->data, update);
		node->update = updateMerger(node->update, update);
	}
	void push(Node* node) {
		applyUpdate(node->l, node->update);
		applyUpdate(node->r, node->update);
	}
	Node* root;

	UpdateMerger updateMerger;
	UpdateApplier updateApplier;
};