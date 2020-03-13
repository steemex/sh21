#ifndef FT_BTREE_H
# define FT_BTREE_H
typedef struct			s_btree
{
	struct s_btree		*parent;
	struct s_btree		*right;
	struct s_btree		*left;
	void				*item;
}						t_btree;
t_btree		*btree_create_node(void *item);

#endif
