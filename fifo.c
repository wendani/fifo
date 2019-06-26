struct list_node_head {
	struct list_node *next;
	struct list_node *prev;

	uint32_t qlen;
};

struct list_node {
	struct list_node *next;
	struct list_node *prev;

	void *data;
};

/**
 * Caller ensures that argument head is not NULL
 */
inline void __list_head_init(struct list_node_head *head)
{
	head->next = (struct list_node *)head;
	head->prev = (struct list_node *)head;

	head->qlen = 0;
}

/**
 * return 1, if list is empty
 * 0, otherwise
 */
inline int __list_empty(struct list_node_head *head)
{
	return head->next == (struct list_node *)head;
}

inline int __list_len(struct list_node_head *head)
{
	return head->qlen;
}

inline void __list_add_tail(struct list_node_head *head, struct list_node *node)
{
	node->next = (struct list_node *)head;
	node->prev = head->prev;

	head->prev = node;
	node->prev->next = node;

	++head->qlen;
}

inline struct list_node *__list_dequeue(struct list_node_head *head)
{
	if (__list_empty(head))
		return NULL;

	struct list_node *node = head->next;

	head->next = node->next;
	node->next->prev = (struct list_node *)head;
	--head->qlen;

	return node;
}
